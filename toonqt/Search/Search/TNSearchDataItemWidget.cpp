#include "TNSearchDataItemWidget.h"
#include "TNSettingData.h"
#include <QDateTime>
#include <QMenu>
#include <QMouseEvent>
#include <QDebug> 
#include <QSize>
#include <QPainter>
#include "TNVersionInfo.h"
TNSearchDataItemWidget* TNSearchDataItemWidget::s_lastSeleted = NULL;

TNSearchDataItemWidget::TNSearchDataItemWidget(QModelIndex index, QWidget *parent) :
QWidget(parent), ui(new Ui::TNSearchDataItemWidget)
, _selected(false)
, _index(index)
{
	ui->setupUi(this);

	this->setObjectName("CardCaseSearchListItem");
	ui->btnItemPhotoIcon->setMaximumSize(QSize(30, 30));
	ui->btnItemPhotoIcon->setMinimumSize(QSize(30, 30));
	ui->btnItemPhotoIcon->setFlat(true);
	ui->btnItemMyPhotoIcon->setFlat(true);

	//ui->labelItemTitle->setElideMode(Qt::ElideMiddle);
	setArrowVisible(false);
	setMyPhotoVisible(false);
	connect(ui->btnItemPhotoIcon, SIGNAL(clicked()), SLOT(onPhotoButtonClicked()));
}

TNSearchDataItemWidget::~TNSearchDataItemWidget()
{
	if (s_lastSeleted == this)
		s_lastSeleted = NULL;

	delete ui;
}
void TNSearchDataItemWidget::setFeedID(const QString &dialogID)
{
	_dialogID = dialogID;
}
void TNSearchDataItemWidget::setMyFeedID(const QString &belongFeedID)
{
	_belongFeedID = belongFeedID;
}
void TNSearchDataItemWidget::setPhoto(const QString &resid, const QString &defaultImg,QSize photoSize)
{
	QString strTemp = resid;
	ui->btnItemPhotoIcon->setMaximumSize(photoSize);
	ui->btnItemPhotoIcon->setMinimumSize(photoSize);
	ui->btnItemPhotoIcon->setSmallMask(TN::Small);
	ui->btnItemPhotoIcon->setCustType(GetPhotoType(_dialogID));

	if (strTemp.isEmpty() || strTemp.isNull())
	{
		QPixmap pixmap(defaultImg);
		ui->btnItemPhotoIcon->setAvatorImagePath(defaultImg);
	}
	else
	{
		ui->btnItemPhotoIcon->setAvatorImagePath(resid);
	}
}
void TNSearchDataItemWidget::setMyPhoto(const QString &resid, const QString &defaultImg, QSize photoSize)
{
	QString strTemp = resid;
	ui->btnItemMyPhotoIcon->setMaximumSize(photoSize);
	ui->btnItemMyPhotoIcon->setMinimumSize(photoSize);
	ui->btnItemMyPhotoIcon->setSmallMask(TN::Small);
	ui->btnItemMyPhotoIcon->setCustType(GetPhotoType(_belongFeedID));

	if (strTemp.isEmpty() || strTemp.isNull())
	{
		QPixmap pixmap(defaultImg);
		ui->btnItemMyPhotoIcon->setAvatorImagePath(defaultImg);
	}
	else
	{
		ui->btnItemMyPhotoIcon->setAvatorImagePath(resid);
	}
}
void TNSearchDataItemWidget::setTitle(const QString &title)
{
	QString sTmp = title;
	sTmp.replace("\n", " ");
	ui->labelItemTitle->setToolTip(sTmp);
	ui->labelItemTitle->setText(sTmp);
}
void TNSearchDataItemWidget::setSex(const QString &sex)
{
	if (sex.isEmpty())
	{
		ui->sexLabel->setText(QString::null);
	}
	else
	{
        bool isMale = sex.compare(("男"), Qt::CaseInsensitive) == 0;
		QString pictureFileName = isMale ? (":/Resources/male.png") : (":/Resources/female.png");
		QPixmap sexFlag(12, 12);
		if (sexFlag.load(pictureFileName)){
			ui->sexLabel->setPixmap(sexFlag);
		}
	}
}

void TNSearchDataItemWidget::setAge(int age)
{
	if ((age <= 0) || (age > 150))
	{
		ui->ageLabel->setText(QString::null);
	}
	else
	{
		ui->ageLabel->setText(QString::number(age));
	}
}
void TNSearchDataItemWidget::setSexLabelVisible(bool visible)
{
	ui->sexLabel->setVisible(visible);
}

void TNSearchDataItemWidget::setAgeLabelVisible(bool visible)
{
	ui->ageLabel->setVisible(visible);
}

void TNSearchDataItemWidget::setArrowVisible(bool visible)
{
	ui->exchangeArrow->setVisible(visible);
}

void TNSearchDataItemWidget::setMyPhotoVisible(bool visible)
{
	ui->btnItemMyPhotoIcon->setVisible(visible);
}
void TNSearchDataItemWidget::setSelected(bool isSelect)
{
	_selected = isSelect;
	QPalette pal = palette();
	if (isSelect){
		if(!TNVersionInfo::IsBaseToonVersion())
			setStyleSheet("QWidget#CardCaseSearchListItem {background-color: #f1f1f1;}");
		else
		{
			QString selectStyle = QString("QWidget#CardCaseSearchListItem {background-color: %1;}").arg(TNSettingData::instance()->GetCurrentSelectSkin());
			setStyleSheet(selectStyle);
		}
	}
	else{
		setStyleSheet("QWidget#CardCaseSearchListItem {background-color: transparent;}");
	}
}


void TNSearchDataItemWidget::enterEvent(QEvent * event)
{
	if (!_selected)
	{
		if(!TNVersionInfo::IsBaseToonVersion())
			setStyleSheet("QWidget#CardCaseSearchListItem {background-color: #f6f6f6;}");
		else
		{
			QString hoverStyle = QString("QWidget#CardCaseSearchListItem {background-color: %1;}").arg(TNSettingData::instance()->GetCurrentHoverSkin());
			setStyleSheet(hoverStyle);
		}
		
	}
}

void TNSearchDataItemWidget::leaveEvent(QEvent *event)
{
	if (!_selected){
		setStyleSheet("QWidget#CardCaseSearchListItem {background-color:transparent;}");
	}
}

void TNSearchDataItemWidget::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TNSearchDataItemWidget::onPhotoButtonClicked()
{
	emit photoClicked(_index);
}
Cust_Type TNSearchDataItemWidget::GetPhotoType(const QString &feedId)
{
	if (feedId.startsWith("c_"))
	{
		return Cust_Type::cust_ellipse;
	}
	else if (feedId.startsWith("g_"))
	{
		return Cust_Type::cust_hexagon;
	}
	else if (feedId.startsWith("gc_"))
	{
		return Cust_Type::cust_radius;
	}
	else if (feedId.startsWith("s_"))
	{
		return Cust_Type::cust_radius;
	}
	return Cust_Type::cust_radius;
}
