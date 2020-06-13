#pragma once

#include "common_global.h"

#include <QWidget>
#include <QString>
#include <QDateTime>

class COMMON_EXPORT TNUtil
{
public:
	TNUtil();
	~TNUtil();

    static QString appendParameterForUrl(const QString &url, const QString &feedId);

	static QString handleTimeForDetailArea(quint64 time);
	static QString handleTimeForDetailArea(const QDateTime &dateTime);

    static QRect getScreenWindowRect();  //取得屏幕窗口区域
    static qreal getDevicePixelRatioF();
    static QRect adjustRectByRatio(const QRect &orgRect);
    static QRect adjustWin32RectByRatio(const QRect &orgRect);

    static void setMainWidget(QWidget *w);
    static QWidget* getMainWidget();
    static void moveCenterInMainWidget(QWidget *w);

    static void setPasswordLogin(bool yes);
    static bool getPasswordLogin();

    static void setIsFirstLoginHomePage(bool yes);
    static bool isFirstLoginHomePage();

	static QString getUUID();

private:
    static QWidget *m_mainWidget;
    static bool m_isPasswordLogin;
    static bool m_isFirstLoginHomePage;
};

