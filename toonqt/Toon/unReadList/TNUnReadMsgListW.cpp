#include "TNUnReadMsgListW.h"
#include <QTimer>
#include <QDebug>

TNUnReadMsgListW::TNUnReadMsgListW(QWidget *parent)
	: QWidget(parent)
	,ui(new Ui::TNUnReadMsgListW)
	, _bFocus(false)
{
	ui->setupUi(this);
	ui->unMsgListLabelTitle->setObjectName("unMsgListLabelTitle");
	ui->unMsgListButton->setObjectName("unMsgListButton");
	ui->unMsgListButton->setText(tr(QStringLiteral("忽略所有").toUtf8().data()));
	ui->unReadListView->setSelectionBehavior(QAbstractItemView::SelectItems);
	ui->unReadListView->setMouseTracking(true);
	ui->unReadListView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->unReadListView->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
	ui->unMsgListButton->setCursor(Qt::PointingHandCursor);

    ui->unReadListView->setFixedWidth(230);
	connect(ui->unReadListView, SIGNAL(clicked(const QModelIndex &)), this, SIGNAL(unReadListAreaClicked(const QModelIndex &)));
	connect(ui->unMsgListButton, SIGNAL(clicked(bool)), this, SIGNAL(ignoreAll(bool)));

	_delayTimer.setSingleShot(true);
	_delayTimer.setInterval(200);
	connect(&_delayTimer, SIGNAL(timeout()), this, SLOT(delayHideSlot()));
}

TNUnReadMsgListW::~TNUnReadMsgListW()
{
	delete ui;
}
void TNUnReadMsgListW::setDelegate(TNUnReadListDelegate *delegate)
{
	ui->unReadListView->setItemDelegate(delegate);
}
void TNUnReadMsgListW::setModel(TNUnReadMsgModel *model)
{
	ui->unReadListView->setModel(model);
}
void TNUnReadMsgListW::setTotalCount(int count)
{
	QString text = tr(QStringLiteral("新消息").toUtf8().data());
	if (count >99)
		text = tr(QStringLiteral("新消息(99+)").toUtf8().data());
	else if (count>0)
		text = tr(QStringLiteral("新消息").toUtf8().data()) + QString("(%1)").arg(count);
	ui->unMsgListLabelTitle->setText(text);
}
void TNUnReadMsgListW::setViewHeight(int height)
{
	ui->unReadListView->setFixedHeight(height);
}
bool TNUnReadMsgListW::event(QEvent *event)
{
	if (event->type() == QEvent::Leave)
	{
		delayHide();
	}
	else if (event->type() == QEvent::Enter)
	{
		_bFocus = true;
		qDebug() << "[Toon][TNUnReadMsgListW] event ,status: " << _bFocus;
	}
	return QWidget::event(event);
}

void TNUnReadMsgListW::paintEvent(QPaintEvent * event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void TNUnReadMsgListW::delayHide()
{
	qDebug() << "[Toon][TNUnReadMsgListW] delayHide";
	_bFocus = false;
	if (!_delayTimer.isActive())
	{
		qDebug() << "[Toon][TNUnReadMsgListW] delayHide start";
		_delayTimer.start();
	}
}
void TNUnReadMsgListW::delayHideSlot()
{
	qDebug() << "[Toon][TNUnReadMsgListW] delayHideSlot ,status: "<< _bFocus;
	if (!_bFocus)
	{
		this->hide();
	}
}
void TNUnReadMsgListW::showWindow()
{
	this->show();
	this->raise();
	this->activateWindow();
}
void TNUnReadMsgListW::showWindowStatus(bool status)
{
	qDebug() << "[Toon][TNUnReadMsgListW] showWindowStatus ,status: " << status;
	_bFocus = status;
}