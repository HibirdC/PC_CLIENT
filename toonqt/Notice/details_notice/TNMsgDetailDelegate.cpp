#include <QTableView>
#include <QDebug>
#include <QStaticText>
#include <QTransform>
#include <math.h>
#include "TNMsgDetailDelegate.h"
#include "model_data/TNModelUserMessage.h"
#include "TNMsgDetailItemWidget.h"

#define  TIME_SPEC_SHOW 5 * 60

TNMsgDetailDelegate::TNMsgDetailDelegate(QAbstractItemView *itemView) :
    TNAbstractItemDelegate(itemView), _parentWidget(NULL)
{

}

void TNMsgDetailDelegate::setParentWidget(TNChatDetailBase *parentWidget)
{
	_parentWidget = parentWidget;
}

void TNMsgDetailDelegate::paint(QPainter *painter,
	const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	Q_UNUSED(painter);
	Q_UNUSED(option);

	if (_itemView->indexWidget(index) == NULL){
        QWidget *itemWidget = createItemWidget(index);
        if (itemWidget != NULL){
            _itemView->setIndexWidget(index, itemWidget);
            TNMsgDetailItemWidget* detailItem = static_cast<TNMsgDetailItemWidget*>
                (itemWidget);
            TNModelUserMessage *userMessage = reinterpret_cast<TNModelUserMessage*>(index.data().toLongLong());
            MESSAGE_TYPE type = userMessage->GetMessageType();
            if (type == em_text || type == em_image ||
                type == em_groupchat_notice || type == em_notsupport
                || type == em_group_operate || type == em_single_operate
                || type == em_card_not_exist){
                connect(detailItem, SIGNAL(autoHeight(int, QModelIndex)),
                    this, SLOT(onAutoHeight(int, QModelIndex)));
            }else{
                setRowHeight(index);
            }
			connect(detailItem, SIGNAL(sendRevokeSignal(int, int, qint64,const QString&, const QString&, const QString&)),
				this, SIGNAL(revokeProcessSignal(int, int, qint64,const QString&, const QString&, const QString&)));
			connect(detailItem, SIGNAL(deleteMsgSignal(const QString &)), this, SIGNAL(deleteMsgSignalDelegate(const QString &)));
            connect(detailItem, SIGNAL(jumpToMsg(QString)), this, SIGNAL(jumpMsgSignalDelegate(QString)));
        }
    }else{
        setRowHeight(index);
    }
}

QWidget *TNMsgDetailDelegate::createItemWidget(const QModelIndex &index) const
{
	TNModelUserMessage *userMessage = reinterpret_cast<TNModelUserMessage*>(index.data().toLongLong());
	if (userMessage == NULL)
		return NULL;
	//获取前一条数据
	QModelIndex last_index = index.sibling(index.row() - 1, index.column());
	QDateTime message_time = userMessage->getTime();
	bool time_visible = true;
	QDateTime last_time;
	if (last_index.isValid()){
		last_time = reinterpret_cast<TNModelUserMessage*>(last_index.data().toLongLong())->getTime();
		qint64 spe_sec = abs(message_time.secsTo(last_time));
		if (spe_sec < TIME_SPEC_SHOW){//小于三分钟不显示时间
			time_visible = false;
		}
	}
    QWidget *widgetMsg = NULL;
	widgetMsg = _parentWidget->CreateDetailItemFromUserMsg(userMessage,
		index,
        _itemView->size(),
		static_cast<TNMsgDetailModel*>(_itemView->model()),
		index.row() == 0, time_visible);

    return widgetMsg;
}

void TNMsgDetailDelegate::setRowHeight(const QModelIndex &index) const
{
	QWidget* itemWidget = _itemView->indexWidget(index);
	if (QTableView * tableView = dynamic_cast<QTableView*>(_itemView)){
		int widget_height = itemWidget->height();
		int row_height = tableView->rowHeight(index.row());
		if (widget_height > row_height)
			tableView->setRowHeight(index.row(), itemWidget->height());
	}
}


void TNMsgDetailDelegate::onAutoHeight(int height, QModelIndex index)
{
    QTableView * tableView = dynamic_cast<QTableView*>(_itemView);
    tableView->resizeRowToContents(index.row());
}

QSize TNMsgDetailDelegate::sizeHint(const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    QWidget* itemWidget = _itemView->indexWidget(index);
    if(itemWidget != NULL){
        return itemWidget->size();
    }else{
        return TNAbstractItemDelegate::sizeHint(option, index);
    }
}
