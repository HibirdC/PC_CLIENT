#include "cardCaseNewFriendItem.h"
#include "TNSettingData.h"
#include <QMenu>
#include <QMouseEvent>
#include <QDebug> 
#include <QSize>
#include <QPainter>

cardCaseNewFriendItem::cardCaseNewFriendItem(QModelIndex index, QWidget *parent)
: QWidget(parent), ui(new Ui::cardCaseNewFriendItem)
, _index(index)
, m_number(0)
, _selected(false)
{
	ui->setupUi(this);
	this->setObjectName("CardCaseNewFriendListItem");

	ui->btnItemPhotoIcon->setMaximumSize(QSize(40, 40));
	ui->btnItemPhotoIcon->setMinimumSize(QSize(40, 40));
	ui->btnItemPhotoIcon->setFlat(true);

	ui->newFriendItemTitle->setElideMode(Qt::ElideMiddle);

	_numberLabel = new QLabel("5",this);
	_numberLabel->setObjectName("lbimte_readed_num");
	_numberLabel->setAlignment(Qt::AlignCenter);
	_numberLabel->setFixedSize(16, 16);
    _numberLabel->move(34,10);

	connect(ui->btnItemPhotoIcon, SIGNAL(clicked()), SLOT(onPhotoButtonClicked()));
}

cardCaseNewFriendItem::~cardCaseNewFriendItem()
{
	delete ui;
}
void cardCaseNewFriendItem::setDialogID(const QString &dialogID)
{
	_dialogID = dialogID;
}
void cardCaseNewFriendItem::setPhoto(const QString &resid, const QString &defaultImg, Cust_Type type, QSize photoSize)
{
	QString strTemp = resid;
	ui->btnItemPhotoIcon->setMaximumSize(photoSize);
	ui->btnItemPhotoIcon->setMinimumSize(photoSize);
	if (photoSize.width() != 40)
	{
		ui->btnItemPhotoIcon->setSmallMask(TN::Small);
	}
	if (strTemp.isEmpty() || strTemp.isNull())
	{
		QPixmap pixmap(defaultImg);
		ui->btnItemPhotoIcon->setAvatorImagePath(defaultImg);
		ui->btnItemPhotoIcon->setCustType(type);
	}
	else
	{
		ui->btnItemPhotoIcon->setAvatorImagePath(resid);
		ui->btnItemPhotoIcon->setCustType(type);
	}
}

void cardCaseNewFriendItem::setTitle(const QString &title)
{
	QString sTmp = title;
	sTmp.replace("\n", " ");
	ui->newFriendItemTitle->setToolTip(sTmp);
	ui->newFriendItemTitle->setText(sTmp);
}
void cardCaseNewFriendItem::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void cardCaseNewFriendItem::onPhotoButtonClicked()
{
	emit photoClicked(_index);
}

int cardCaseNewFriendItem::getNewRequestNumber() const
{
    return m_number;
}
void cardCaseNewFriendItem::setNewRequestNumber(int number)
{
    m_number = number;

    if (m_number > 0)
    {
        _numberLabel->setVisible(true);
        if (m_number < 10)
        {
            _numberLabel->setText(QString("%1").arg(m_number));
            _numberLabel->setFixedWidth(16);
            _numberLabel->move(34, 10);
        }
        else if (m_number < 100)
        {
            _numberLabel->setText(QString("%1").arg(m_number));
            _numberLabel->setFixedWidth(22);
            _numberLabel->move(28, 10);
        }
        else
        {
            _numberLabel->setText("99+");
            _numberLabel->setFixedWidth(28);
            _numberLabel->move(22, 10);
        }
        _numberLabel->raise();
    }
    else
    {
        _numberLabel->setVisible(false);
    }
}
void cardCaseNewFriendItem::setSelected(bool isSelect)
{
	_selected = isSelect;
	QPalette pal = palette();
	if (isSelect){
#if defined(BJTOON) || defined(QLTOON) || defined(MCTOON)
		setStyleSheet("QWidget#CardCaseNewFriendListItem {background-color: #f1f1f1;}");
#else
		QString selectStyle = QString("QWidget#CardCaseNewFriendListItem {background-color: %1;}").arg(TNSettingData::instance()->GetCurrentSelectSkin());
		setStyleSheet(selectStyle);
#endif
	}
	else{
		setStyleSheet("QWidget#CardCaseNewFriendListItem {background-color: transparent;}");
	}
}


void cardCaseNewFriendItem::enterEvent(QEvent * event)
{
	if (!_selected){
#if defined(BJTOON) || defined(QLTOON) || defined(MCTOON)
		setStyleSheet("QWidget#CardCaseNewFriendListItem {background-color: #f6f6f6;}");
#else
		QString hoverStyle = QString("QWidget#CardCaseNewFriendListItem {background-color: %1;}").arg(TNSettingData::instance()->GetCurrentHoverSkin());
		setStyleSheet(hoverStyle);
#endif
	}
}

void cardCaseNewFriendItem::leaveEvent(QEvent *event)
{
	if (!_selected){
		setStyleSheet("QWidget#CardCaseNewFriendListItem {background-color: #transparent;}");
	}
}
