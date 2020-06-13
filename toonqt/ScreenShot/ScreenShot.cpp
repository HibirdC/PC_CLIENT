#include "ScreenShot.h"
#include "TNScreenShotWindow.h"
#include "TNScreenshotEditOptionData.h"

#include <QDebug>
#include <QApplication>

bool TNScreenShot::m_screenShoting = false;

TN::ScreenShotExitFlag TNScreenShot::screenShot()
{
    if (m_screenShoting)
    {
        qInfo()<<"[ScreenShot][TNScreenShot]I am screenShoting....";
        return TN::ClosedExit;
    }
    m_screenShoting = true;
    static TNScreenShotWindow *pScreenWindow = nullptr;
    if (nullptr == pScreenWindow)
    {
        QWidget *pCurrent = qApp->activeModalWidget();
        if (pCurrent == nullptr)
            qInfo()<<"[ScreenShot][TNScreenShot]TNScreenShot::screenShot-pCurrent is null";
        pScreenWindow = new TNScreenShotWindow(pCurrent);
    }
    pScreenWindow->showFullScreen();
    pScreenWindow->raise();
    pScreenWindow->exec();
    TN::ScreenShotExitFlag exitFlag = pScreenWindow->exitFlag();
    delete pScreenWindow;
    pScreenWindow = nullptr;
    m_screenShoting = false;
    TNScreenshotEditOptionData::freeInstance();
    return exitFlag;
}

bool TNScreenShot::getCurrentScreenShot()
{
    return m_screenShoting;
}
