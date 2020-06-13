#include "tnemojiwidget.h"
#include "details_notice/NoticeDetailsArea.h"
#include <QPainter>
#include <QPaintEvent>

TNEmojiWidget::TNEmojiWidget(QWidget *parent)
: QWidget(parent, Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint)
{
	ui.setupUi(this);

#ifndef Q_OS_WIN
    this->setStyleSheet("#TNEmojiWidget QPushButton{margin:5px 2px;}");
#endif

	NoticeDetailsArea *msg = (NoticeDetailsArea*)parent;
	connect(ui.pushButton_emoji_1, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_2, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_3, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_4, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_5, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_6, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_7, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_8, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_9, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_10, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_11, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_12, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_13, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_14, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_15, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_16, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_17, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_18, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_19, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_20, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_21, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_22, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_23, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_24, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_25, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_26, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_27, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_28, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_29, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_30, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_31, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_32, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_33, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_34, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_35, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_36, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_37, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_38, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_39, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_40, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_41, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_42, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_43, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_44, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_45, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_46, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_47, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_48, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_49, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_50, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_51, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_52, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_53, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_54, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_55, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_56, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_57, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_58, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_59, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_60, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_61, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_62, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_63, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_64, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_65, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_66, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_67, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_68, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_69, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_70, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_71, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_72, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_73, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_74, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_75, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_76, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_77, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_78, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_79, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
	connect(ui.pushButton_emoji_80, SIGNAL(clicked()), msg, SLOT(btn_clicked()));
}

TNEmojiWidget::~TNEmojiWidget()
{

}

void TNEmojiWidget::focusOutEvent(QFocusEvent *event)
{
	QWidget::focusOutEvent(event);
}

void TNEmojiWidget::paintEvent(QPaintEvent * event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
