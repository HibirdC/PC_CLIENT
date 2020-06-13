#include "TNStartloadingpage.h"

#include <QLabel>
#include <QMovie>
#include <QHBoxLayout>
#ifdef  Q_OS_WIN32
#include <Windows.h>
#endif 
const QSize LoadingSize = QSize(320, 432);

TNStartloadingpage::TNStartloadingpage(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::Tool);
	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::Popup);
	setAttribute(Qt::WA_TranslucentBackground);
	setAttribute(Qt::WA_NoSystemBackground, false);

	QLabel *picLabel = new QLabel(this);
	picLabel->setObjectName("tnLoadingLabel");
	picLabel->setContentsMargins(10, 0, 10, 20);
	picLabel->setAlignment(Qt::AlignCenter);
	QHBoxLayout *hLayout = new QHBoxLayout();
	hLayout->setSpacing(0);
	hLayout->setContentsMargins(0, 0, 0, 0);
	hLayout->addWidget(picLabel);
	this->setLayout(hLayout);
	this->setFixedSize(LoadingSize);
	this->setContentsMargins(0, 0, 0, 0);
	this->setObjectName("tnLoadingBox");

	m_loadMovie = new QMovie(":/skin/Resources/img/skin/default/loading_data.gif");
	m_loadMovie->setScaledSize(QSize(200,200));
	picLabel->setMovie(m_loadMovie);
}

TNStartloadingpage::~TNStartloadingpage()
{
	stop();
	if (m_loadMovie != NULL)
		delete m_loadMovie;
}
void TNStartloadingpage::slotTimerOut()
{
	stop();
	emit TimeOutSignal();
}

void TNStartloadingpage::start()
{
	m_loadMovie->start();
#ifdef Q_OS_WIN32
    ::SetWindowPos(HWND(winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    ::SetWindowPos(HWND(winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
#endif
	this->exec();
}

void TNStartloadingpage::stop()
{
	m_loadMovie->stop();
}
