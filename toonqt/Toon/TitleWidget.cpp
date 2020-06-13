#include <QStyleOption>
#include <QPainter>
#include "TitleWidget.h"

TitleWidget::TitleWidget(QWidget *parent)
: QWidget(parent)
{
	min_button = new QPushButton();
	max_button = new QPushButton();
	close_button = new QPushButton();
#ifdef Q_OS_WIN
    this->setObjectName("toonTitle");
    this->setContentsMargins(0,0,6,0);
    this->setFocusPolicy(Qt::ClickFocus);
    min_button->setObjectName("toonMin");
    max_button->setObjectName("toonMax");
    close_button->setObjectName("toonClose");
#else
    this->setObjectName("titleWidget_unix");
    this->setContentsMargins(0,0,0,0);
    min_button->setObjectName("macMin");
    max_button->setObjectName("macMax");
    close_button->setObjectName("macClose");
#endif
	max_button->setCheckable(true);
	max_button->setChecked(false);

	close_button->setCursor(Qt::PointingHandCursor);
	max_button->setCursor(Qt::PointingHandCursor);
    min_button->setCursor(Qt::PointingHandCursor);

    connect(min_button, SIGNAL(clicked()), this, SIGNAL(showMin()));
	connect(max_button, SIGNAL(clicked(bool)), this, SLOT(showMaxSlot(bool)));
	connect(close_button, SIGNAL(clicked()), this, SIGNAL(closeWidget()));


	QHBoxLayout *title_layout = new QHBoxLayout();
#ifdef Q_OS_WIN
    title_layout->addStretch();
    title_layout->addWidget(min_button, 0, Qt::AlignVCenter);
    title_layout->addWidget(max_button, 0, Qt::AlignVCenter);
    title_layout->addWidget(close_button, 0, Qt::AlignVCenter);
    title_layout->setSpacing(2);
    title_layout->setContentsMargins(0, 0, 0, 0);
#else
    title_layout->setSpacing(9);
    title_layout->setContentsMargins(8, 0, 8, 0);
    title_layout->addWidget(close_button, 0, Qt::AlignVCenter);
    title_layout->addWidget(min_button, 0, Qt::AlignVCenter);
    title_layout->addWidget(max_button, 0, Qt::AlignVCenter);
#endif

	this->translateLanguage();
	setLayout(title_layout);
}

void TitleWidget::translateLanguage()
{
	min_button->setToolTip(tr(QStringLiteral("最小化").toUtf8().data()));
	close_button->setToolTip(tr(QStringLiteral("关闭").toUtf8().data()));
	max_button->setToolTip(tr(QStringLiteral("最大化").toUtf8().data()));
}

void TitleWidget::paintEvent(QPaintEvent * event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void TitleWidget::showMaxSlot(bool status)
{
	updateMaxStatus(status);
	emit showMax(status);
}
void TitleWidget::updateMaxStatus(bool status)
{
	if (status)
		max_button->setToolTip(tr(QStringLiteral("还原").toUtf8().data()));
	else
		max_button->setToolTip(tr(QStringLiteral("最大化").toUtf8().data()));
	max_button->setChecked(status);
}

void TitleWidget::setEnabledMinBtn(bool isEnabled)
{
    min_button->setEnabled(isEnabled);
}
