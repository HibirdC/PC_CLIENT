#include "TNUtil.h"

#include "TNVersionInfo.h"

#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QUuid>

QWidget* TNUtil::m_mainWidget = nullptr;
bool TNUtil::m_isPasswordLogin = true;
bool TNUtil::m_isFirstLoginHomePage = true;

TNUtil::TNUtil()
{
}

TNUtil::~TNUtil()
{
}

QString TNUtil::appendParameterForUrl(const QString &url, const QString &feedId)
{
	return url + QString("?buildNo=") + TNVersionInfo::buildNo() + QString("&feedId=") + feedId;
}

QString TNUtil::handleTimeForDetailArea(quint64 time)
{
    if (QString::number(qlonglong(time)).length()<11) // 服务器返回的时间单位为秒
        time = time*1000;
    QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(time);
    return handleTimeForDetailArea(dateTime);
}

QString TNUtil::handleTimeForDetailArea(const QDateTime &dateTime)
{
	QDate currDate = QDateTime::currentDateTime().date();
	if (dateTime.date() == currDate) // 今天
	{
		return dateTime.toString("hh:mm");
	}
	else if (currDate.daysTo(dateTime.date()) == -1) // 昨天
	{
		return QObject::tr(QStringLiteral("昨天 ").toUtf8().data()) + dateTime.toString("hh:mm");
	}
	else if (currDate.year() - dateTime.date().year() < 1) // 本年度
	{
		return dateTime.toString("MM-dd hh:mm");
	}
	else
	{
		return dateTime.toString("yyyy-MM-dd hh:mm");
	}

	Q_ASSERT(!"never come to here");
    return QString::null;
}

QRect TNUtil::getScreenWindowRect()
{
    QRect fullScreenRect = QApplication::desktop()->screenGeometry();
    //qDebug()<<"fullScreenRect="<<fullScreenRect;
    return fullScreenRect;
}

qreal TNUtil::getDevicePixelRatioF()
{
    qreal ratioF = QApplication::desktop()->screen()->devicePixelRatioF();
    return ratioF;
}

QRect TNUtil::adjustRectByRatio(const QRect &orgRect)
{
    qreal ratioF = QApplication::desktop()->screen()->devicePixelRatioF();
    QRect newRect;
    newRect.setX(orgRect.x() * ratioF);
    newRect.setY(orgRect.y() * ratioF);
    newRect.setWidth(orgRect.width() * ratioF);
    newRect.setHeight(orgRect.height() * ratioF);
    return newRect;
}

QRect TNUtil::adjustWin32RectByRatio(const QRect &orgRect)
{
    qreal ratioF = QApplication::desktop()->screen()->devicePixelRatioF();
    QRect newRect;
    newRect.setX(orgRect.x() / ratioF);
    newRect.setY(orgRect.y() / ratioF);
    newRect.setWidth(orgRect.width() / ratioF);
    newRect.setHeight(orgRect.height() / ratioF);
    return newRect;
}

void TNUtil::setMainWidget(QWidget *w)
{
    m_mainWidget = w;
}

QWidget *TNUtil::getMainWidget()
{
    return m_mainWidget;
}

void TNUtil::moveCenterInMainWidget(QWidget *w)
{
    // 将this移动到主窗口的中间
    QWidget *mainWidget = TNUtil::getMainWidget();
    if (mainWidget)
    {
        int dw = (mainWidget->width() - w->width())/2;
        int dh = (mainWidget->height() - w->height())/2;
        QPoint p = mainWidget->pos();
        QPoint np(p.x() + dw, p.y() + dh);
        w->move(np);
    }
}

void TNUtil::setPasswordLogin(bool yes)
{
    m_isPasswordLogin = yes;
}

bool TNUtil::getPasswordLogin()
{
    return m_isPasswordLogin;
}

void TNUtil::setIsFirstLoginHomePage(bool yes)
{
    m_isFirstLoginHomePage = yes;
}

bool TNUtil::isFirstLoginHomePage()
{
    return m_isFirstLoginHomePage;
}

QString TNUtil::getUUID()
{
	QUuid id = QUuid::createUuid();
	QString strId = id.toString();
	strId.remove('{');
	strId.remove('}');

	return strId;
}
