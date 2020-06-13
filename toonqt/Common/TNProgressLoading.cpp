#include "TNProgressLoading.h"

#include <QLabel>
#include <QMovie>
#include <QHBoxLayout>

const QSize LoadingSize = QSize(60, 60);

TNProgressLoading::TNProgressLoading(QWidget *parent)
: QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setAttribute(Qt::WA_NoSystemBackground, false);

	QLabel *picLabel = new QLabel(this);
	//picLabel->setAttribute(Qt::WA_NoSystemBackground);
	picLabel->setStyleSheet("background:rgba(0,0,0,0.5);border-radius:10px;border:0;");
	QHBoxLayout *hLayout = new QHBoxLayout();
	hLayout->setContentsMargins(0, 0, 0, 0);
	hLayout->addWidget(picLabel);
	this->setLayout(hLayout);
	this->setFixedSize(LoadingSize);
    this->setStyleSheet("border:0;");

	m_loadMovie = new QMovie(":/Resources/loading.gif");
	m_loadMovie->setScaledSize(LoadingSize);
	picLabel->setMovie(m_loadMovie);

	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(slotTimerOut()));
}

TNProgressLoading::~TNProgressLoading()
{

}

void TNProgressLoading::slotTimerOut()
{
	stop();
}

void TNProgressLoading::start(int maxMillSec)
{
	m_loadMovie->start();
	m_timer->start(maxMillSec);
	if (this->exec() == QDialog::Accepted)
	{
	}
}

void TNProgressLoading::stop()
{
	this->hide();
	m_loadMovie->stop();
    m_timer->stop();
}
