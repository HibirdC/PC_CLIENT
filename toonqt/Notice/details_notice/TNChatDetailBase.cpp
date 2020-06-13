#include "TNChatDetailBase.h"
#include "TNMsgDetailItemWidget.h"
#include "TNUtil.h"

TNChatDetailBase::TNChatDetailBase(int id, QWidget *parent)
: DetailsAreaBase(id, parent)
{

}

TNChatDetailBase::~TNChatDetailBase()
{
	qDebug() << "~TNChatDetailBase";
}

QWidget* TNChatDetailBase::CreateDetailItemFromUserMsg(TNModelUserMessage * userMessage,
	const QModelIndex& index,
    const QSize& parentSize,
	TNMsgDetailModel* detailModel,
	bool is_firstMessage,
	bool time_visible)
{
	TNMsgDetailItemWidget * msgDetailItem = NULL;
    msgDetailItem = new TNMsgDetailItemWidget(userMessage, index , parentSize,this, detailModel,
		is_firstMessage,time_visible);
	msgDetailItem->setObjectName("MsgDetailItem");
	QString qs_time = TNUtil::handleTimeForDetailArea(userMessage->getTime());
	msgDetailItem->setTime(qs_time);
	return msgDetailItem;
}
