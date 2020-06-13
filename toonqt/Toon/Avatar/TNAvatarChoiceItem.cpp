#include "TNAvatarChoiceItem.h"
#include <QPainter>

TNAvatarChoiceItem::TNAvatarChoiceItem(QModelIndex index, QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::TNAvatarChoiceItem)
	, _selected(false)
	, _index(index)
    , _unReadCount(nullptr)
{
	ui->setupUi(this);
    this->setObjectName("avatarChoiceItem");
	ui->avatarChoiceBtnItem->setFlat(true);
    ui->avatarChoiceBtnItem->setMinimumSize(QSize(30, 30));
    ui->avatarChoiceBtnItem->setMaximumSize(QSize(30, 30));
    ui->avatarChoiceBtnItem->setIconSize(QSize(30,30));
	//ui->avatorlbitem_name->setElideMode(Qt::ElideMiddle);

	_unReadCount = new QLabel(QString::null, this);
	_unReadCount->setObjectName("avatarChoiceLabelStatus");
	_unReadCount->setFixedSize(10, 10);
    _unReadCount->move(32, 3);
	_unReadCount->setText("");

	connect(ui->avatarChoiceBtnItem, SIGNAL(clicked()), SLOT(onPhotoButtonClicked()));
}

TNAvatarChoiceItem::~TNAvatarChoiceItem()
{
	if (_unReadCount != nullptr)
		delete _unReadCount;
	delete ui;
}
void TNAvatarChoiceItem::setDialogID(const QString &dialogID)
{
	_dialogID = dialogID;
}
void TNAvatarChoiceItem::setPhoto(const QString &resid, const QString &defaultImg, Cust_Type type)
{
	QString strTemp = resid;
	if (strTemp.isEmpty() || strTemp.isNull())
	{
        ui->avatarChoiceBtnItem->setIcon(TNCommonDealAvator::getTypeQIcon(defaultImg, QSize(30, 30), type, TN::MiddleSmall));
	}
	else
	{
        ui->avatarChoiceBtnItem->setIcon(TNCommonDealAvator::getTypeQIcon(resid, QSize(30, 30), type, TN::MiddleSmall));
	}
}

void TNAvatarChoiceItem::setTitle(const QString &title)
{
	QString sTmp = title;
	sTmp.replace("\n", " ");
	ui->avatorlbitem_name->setToolTip(sTmp);
	ui->avatorlbitem_name->setText(sTmp);
}
void TNAvatarChoiceItem::setSelected(bool isSelect)
{
	_selected = isSelect;
}

void TNAvatarChoiceItem::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(event);
}
void TNAvatarChoiceItem::setCurrentStatus(bool status)
{
	ui->avatorlbitem_status->setVisible(status);
}
void TNAvatarChoiceItem::setCurrentUnRead(bool status)
{
	_unReadCount->setVisible(status);
}
void TNAvatarChoiceItem::onPhotoButtonClicked()
{
	emit photoClicked(_index);
}
