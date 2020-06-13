#include "ui_tnatlistitemwidget.h"
#include "tnatlistitemwidget.h"
#include "TNNameSpace.h"
#include "tncommondealavator.h"

#include <QDateTime>
#include <QMenu>
#include <QMouseEvent>
#include <QDebug> 
#include <QSize>
#include <QPainter>
#include "TNVersionInfo.h"
TNATListItemWidget::TNATListItemWidget(QModelIndex index, QWidget *parent) :QWidget(parent)
	, ui(new Ui::TNATListItemWidget)
	, _selected(false)
	, _index(index)
{
	ui->setupUi(this);
	ui->atbtnitem_icon->setFlat(true);
	//ui->atlbitem_name->setElideMode(Qt::ElideMiddle);
}

TNATListItemWidget::~TNATListItemWidget()
{
	delete ui;
}
void TNATListItemWidget::setDialogID(const QString &dialogID)
{
	_dialogID = dialogID;
}
void TNATListItemWidget::setPhoto(const QString &resid, const QString &defaultImg, Cust_Type type)
{
	QString strTemp = resid;
	if (strTemp.isEmpty() || strTemp.isNull())
	{
		ui->atbtnitem_icon->setIcon(TNCommonDealAvator::getTypeQIcon(defaultImg, QSize(20, 20), type,TN::MoreSmall));
	}
	else
	{
		ui->atbtnitem_icon->setIcon(TNCommonDealAvator::getTypeQIcon(resid, QSize(20, 20), type, TN::MoreSmall));
	}
}

void TNATListItemWidget::setTitle(const QString &title)
{
	QString sTmp = title;
	sTmp.replace("\n", " ");
	ui->atlbitem_name->setToolTip(sTmp);
	ui->atlbitem_name->setText(sTmp);
}
void TNATListItemWidget::setSelected(bool isSelect)
{
	_selected = isSelect;
	QPalette pal = palette();
	if (isSelect)
	{
		if (!TNVersionInfo::IsBaseToonVersion())
			setStyleSheet("QWidget#TNATListItemWidget {background-color: #f1f1f1;}");
		else
			setStyleSheet("QWidget#TNATListItemWidget {background-color: #e4f0ff;}");
	}
	else{
		setStyleSheet("QWidget#TNATListItemWidget {background-color: transparent;}");
	}
}


void TNATListItemWidget::enterEvent(QEvent * event)
{
	if (!_selected)
	{
		if(!TNVersionInfo::IsBaseToonVersion())
			setStyleSheet("QWidget#TNATListItemWidget {background-color:  #f6f6f6;}");
		else
			setStyleSheet("QWidget#TNATListItemWidget {background-color:  #eaf4ff}");
	}
}

void TNATListItemWidget::leaveEvent(QEvent *event)
{
	if (!_selected){
		setStyleSheet("QWidget#TNATListItemWidget {background-color: transparent;}");
	}
}
void TNATListItemWidget::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(event);
}
