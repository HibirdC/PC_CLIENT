#include "TNMessageBox.h"
#include "ui_TNMessageBox.h"

#include <QPainter>
#include <QDesktopWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QTimer>


TNMessageBox::TNMessageBox(QWidget *parent, int expireTime_ms)
: QDialog(parent)
{
	ui = new Ui::TNMessageBox();
	ui->setupUi(this);

	ui->pushButton_MessageBox->installEventFilter(this);
	ui->lineEdit_MessageBox->installEventFilter(this);
    ui->pushButton_MessageBox->setVisible(false);

	m_parentPoint = parent->mapToGlobal(parent->pos());

	m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(OnTimerSlot()));
	m_pTimer->start(expireTime_ms);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setFixedSize(QSize(200, 40));
	this->setObjectName("TNMessageBox");
}

TNMessageBox::~TNMessageBox()
{
	delete ui;
}

void TNMessageBox::OnTimerSlot()
{
	QDialog::accept();
}

void TNMessageBox::setPositionToParent(int dx, int dy)
{
    this->move(m_parentPoint.rx() + dx, m_parentPoint.ry() + dy);
}

void TNMessageBox::setIconVisible(bool visible)
{
    ui->pushButton_MessageBox->setVisible(visible);
}

void TNMessageBox::setMsg(const QString &msg)
{
    ui->lineEdit_MessageBox->setWordWrap(false);
    ui->lineEdit_MessageBox->setText(msg);
    ui->lineEdit_MessageBox->adjustSize();
    int width = ui->lineEdit_MessageBox->width();
    if(width > 200)
    {
        ui->lineEdit_MessageBox->setFixedWidth(200);
        ui->lineEdit_MessageBox->setWordWrap(true);
        ui->lineEdit_MessageBox->setText(msg);
        ui->lineEdit_MessageBox->adjustSize();
        int height = ui->lineEdit_MessageBox->height();
        this->setFixedHeight(height + 20);
    }
    else
    {
        ui->lineEdit_MessageBox->setFixedWidth(width);
        ui->lineEdit_MessageBox->setWordWrap(true);
        ui->lineEdit_MessageBox->setText(msg);
        ui->lineEdit_MessageBox->adjustSize();
    }
}

void TNMessageBox::paintEvent(QPaintEvent * event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

bool TNMessageBox::eventFilter(QObject *target, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
		if (mouseEvent->buttons() & Qt::LeftButton)
		{
			QDialog::accept();
			return true;
		}
	}

	return QDialog::eventFilter(target, event);
}
