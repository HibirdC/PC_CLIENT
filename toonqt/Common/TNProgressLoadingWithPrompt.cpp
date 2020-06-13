#include "TNProgressLoadingWithPrompt.h"

#include <QLabel>
#include <QMovie>
#include <QVBoxLayout>

const QSize LoadingSize = QSize(60, 60);

TNProgressLoadingWithPrompt::TNProgressLoadingWithPrompt(QWidget *parent)
: QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setAttribute(Qt::WA_NoSystemBackground, false);
	setObjectName("TNToastWidget");

	QVBoxLayout *hLayout = new QVBoxLayout();
	hLayout->setContentsMargins(0, 0, 0, 0);
	setLayout(hLayout);
	setFixedSize(80, 80);
	

	QLabel *picLabel = new QLabel(this);
	picLabel->setContentsMargins(0, 0, 0, 0);
	hLayout->addWidget(picLabel, 0, Qt::AlignCenter);

	m_textLabel = new QLabel(this);
	m_textLabel->setObjectName("TNToastLabel");
	m_textLabel->setFixedSize(80, 20);
	m_textLabel->setAlignment(Qt::AlignCenter);
	hLayout->addWidget(m_textLabel, 0, Qt::AlignCenter);

	m_loadMovie = new QMovie(":/Resources/loading.gif");
	m_loadMovie->setScaledSize(LoadingSize);
	picLabel->setAlignment(Qt::AlignCenter);
	picLabel->setMovie(m_loadMovie);

	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(stop()));
}

TNProgressLoadingWithPrompt::~TNProgressLoadingWithPrompt()
{

}

void TNProgressLoadingWithPrompt::setText(const QString &strPrompt)
{
    m_textLabel->setText(strPrompt);
}

void TNProgressLoadingWithPrompt::showLoding(int maxMillSec)
{
    if (maxMillSec > 0)
    {
        m_timer->start(maxMillSec);
    }
    else
    {
        m_timer->stop();
    }
	m_loadMovie->start();
    exec();
}

void TNProgressLoadingWithPrompt::showComplete(int maxMillSec)
{
    if (maxMillSec > 0)
    {
        m_timer->start(maxMillSec);
    }
    else
    {
        m_timer->stop();
    }
    //需要切换成对号图片
	m_loadMovie->stop();
    exec();
}

void TNProgressLoadingWithPrompt::stop()
{
    accept();
}