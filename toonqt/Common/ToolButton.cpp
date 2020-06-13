#include "ToolButton.h"

#include <QLabel>

ToolButton::ToolButton(const QString &pic_name, int type, QWidget *parent)
	: QToolButton(parent)
{
    m_number = 0;
	numberLabel = new QLabel(QString::null, this);
	switch (type)
	{
	case MENU_SHOW_TYPE_AVATAR:
		numberLabel->setObjectName("upgradePromptLabel");
		break;
	case MEUNU_SHOW_TYPE_MESSAGE:
		numberLabel->setObjectName("messageNumberLabel");
		break;
	case MENU_SHOW_TYPE_CARDCASE:
		numberLabel->setObjectName("messageNumberLabel");
		break;
	case MENU_SHOW_TYPE_SETUP:
		numberLabel->setObjectName("upgradePromptLabel");
		break;
	default:
		break;
	}

	numberLabel->setVisible(false);
	numberLabel->setAlignment(Qt::AlignCenter);
	numberLabel->raise();
	//
	////设置文本颜色
	//QPalette text_palette = palette();
	//text_palette.setColor(QPalette::ButtonText, QColor(230, 230, 230));
	//setPalette(text_palette);

	////设置文本粗体
	//QFont &text_font = const_cast<QFont &>(font());
	//text_font.setWeight(QFont::Bold);

	//setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

	//设置图标
	//QPixmap pixmap(pic_name);
	//setIcon(pixmap);
	//setIconSize(pixmap.size());

	////设置大小
	//setFixedSize(pixmap.width()-10, pixmap.height()-10);
	//setAutoRaise(true);
	//setObjectName("transparentToolButton");

	mouse_over = false;
	mouse_press = false;
}

ToolButton::~ToolButton()
{

}

void ToolButton::enterEvent(QEvent *)
{
	mouse_over = false;
	this->setCursor(Qt::PointingHandCursor);
}

void ToolButton::leaveEvent(QEvent *)
{
	mouse_over = false;
	this->setCursor(Qt::ArrowCursor);
}

void ToolButton::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		emit clicked();
	}
}

void ToolButton::setMousePress(bool mouse_press)
{
	this->mouse_press = mouse_press;
	update();
}

void ToolButton::setMessageNumber(int count)
{
    m_number = count;
	numberLabel->move(34, 10);
	if (count > 0)
	{
		numberLabel->setVisible(true);
		if (count < 10)
		{
			numberLabel->setText(QString("%1").arg(count));
			numberLabel->setFixedWidth(16);
            numberLabel->move(36, 16);
		}
		else if (count < 100)
		{
			numberLabel->setText(QString("%1").arg(count));
			numberLabel->setFixedWidth(22);
            numberLabel->move(36, 16);
		}
		else
		{
			numberLabel->setText("99+");
			numberLabel->setFixedWidth(28);
            numberLabel->move(30, 16);
		}
		numberLabel->raise();
	}
	else
	{
		numberLabel->setVisible(false);
	}
}

int ToolButton::getMessageNumber() const
{
    return m_number;
}

void ToolButton::painterInfo(int top_color, int middle_color, int bottom_color)
{
	QPainter painter(this);
	QPen pen(Qt::NoBrush, 1);
	painter.setPen(pen);
	QLinearGradient linear(rect().topLeft(), rect().bottomLeft());
	linear.setColorAt(0, QColor(230, 230, 230, top_color));
	linear.setColorAt(0.5, QColor(230, 230, 230, middle_color));
	linear.setColorAt(1, QColor(230, 230, 230, bottom_color));
	painter.setBrush(linear);
	painter.drawRect(rect());
}

void ToolButton::showRedPoint(bool status,int callType)
{
	numberLabel->setVisible(status);
    numberLabel->setText(QString::null);
	switch (callType)
	{
	case MENU_SHOW_TYPE_SETUP:
        numberLabel->move(40, 17);
		break;
	case MENU_SHOW_TYPE_AVATAR:
        numberLabel->move(40, 0);
		break;
	default:
		break;
	}
}
void ToolButton::setFeedType(const QString &feed)
{
	return;
}
void ToolButton::setAvatarPath(const QString &path)
{
	return;
}
void ToolButton::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		emit doubleClicked();
	}
}