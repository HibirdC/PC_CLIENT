#include "someoneatyou.h"
#include <qdebug.h>
#include <QPainter>
#include <QDesktopWidget>
#include <QPaintEvent>
#include <QMouseEvent>

someoneatyou::someoneatyou(QWidget *parent)
: QWidget(parent)
	,_index(-1)
{
	ui = new Ui::someoneatyou();
	ui->setupUi(this);
	setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SubWindow);
	setAttribute(Qt::WA_TranslucentBackground, true);

	ui->lineEdit_AtYou_MessageBox->installEventFilter(this);
	ui->AtClosePushButton->setCursor(Qt::PointingHandCursor);
	ui->lineEdit_AtYou_MessageBox->setCursor(Qt::PointingHandCursor);
	ui->lineEdit_AtYou_MessageBox->setAlignment(Qt::AlignLeft);
	ui->lineEdit_AtYou_MessageBox->setElideMode(Qt::ElideMiddle);
	connect(ui->AtClosePushButton, SIGNAL(clicked()), this, SLOT(OnCloseBox()));
}

someoneatyou::~someoneatyou()
{
	delete ui;
}

void someoneatyou::setText(const QString &text)
{
    int oldLineWidth = ui->lineEdit_AtYou_MessageBox->width();
    ui->lineEdit_AtYou_MessageBox->setWordWrap(false);
    ui->lineEdit_AtYou_MessageBox->setText(text);
    ui->lineEdit_AtYou_MessageBox->adjustSize();
    int newLineWidth = ui->lineEdit_AtYou_MessageBox->width();

    this->setFixedWidth(this->width() + (newLineWidth - oldLineWidth));
}

QString someoneatyou::getText()
{
	return ui->lineEdit_AtYou_MessageBox->text();
}

void someoneatyou::paintEvent(QPaintEvent * event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

bool someoneatyou::eventFilter(QObject *target, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
		if (mouseEvent->buttons() & Qt::LeftButton)
		{
            emit ClickedMsgBox(_msgId,_index);
            return true;
		}
	}
	return QWidget::eventFilter(target, event);
}

void someoneatyou::OnCloseBox()
{
    emit ClickedMsgBox(_msgId,_index,false);
    this->hide();
}
