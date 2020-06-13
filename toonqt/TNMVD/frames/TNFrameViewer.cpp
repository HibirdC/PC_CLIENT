#include "TNFrameViewer.h"

#include "TNUtil.h"
#include "TNDbUtil.h"
#include "frames/TNFrameId.h"
#include "TNSimpleBrowser.h"
#include "TNDataControlServer.h"
#include "TNBizActionResponder.h"
#include "TNUserDataHelper.h"
#include "TNMessageBox.h"
#include <QApplication>

TNFrameViewer *TNFrameViewer::m_instance = 0;

TNFrameViewer *TNFrameViewer::instance()
{
    static QMutex mutex;

    if (m_instance == 0)
    {
        mutex.lock();
        m_instance = new TNFrameViewer();
        mutex.unlock();
    }

    return m_instance;
}

void TNFrameViewer::freeInstance()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = 0;
    }
}

TNFrameViewer::TNFrameViewer(QObject *parent) : QObject(parent)
{
    m_bizActionResponder = new TNBizActionResponder(this);
    //connect(TNSimpleBrowser::getInstance(), SIGNAL(sendReceivedTextFromH5(const QString&)), m_bizActionResponder, SLOT(slotReceiveMessageFromH5(const QString&)));
}

void TNFrameViewer::showFrame(const QString &feedId, const QString &inBelongFeedId, bool isFriendApply)
{
    /*
    QTime time;
    time.start();
    if (feedId.startsWith("c_") || feedId.startsWith("s_") || feedId.startsWith("o_"))
    {
        if (!TNUserDataHelper::GetInstance()->GetSingleCardStatus(feedId))
        {
            QString content = feedId.startsWith("c_") ? tr(QStringLiteral("删除").toUtf8().data()) : tr(QStringLiteral("回收").toUtf8().data());
            TNMessageBox messageBox(QApplication::activeWindow());
            messageBox.setMsg(tr(QStringLiteral("该名片已被").toUtf8().data()) + content);
            messageBox.exec();
            return;
        }
    }
    qInfo()<<"[TNMVD][TNFrameViewer]showFrame-GetSingleCardStatus-time="<<time.elapsed();
    */

    // 因为TNSimpleBrowser窗口每次关闭都会销毁掉，所以这里每次都需要断开重连
    disconnect(TNSimpleBrowser::getInstance(), SIGNAL(sendReceivedTextFromH5(const QString&)), m_bizActionResponder, SLOT(slotReceiveMessageFromH5(const QString&)));
    connect(TNSimpleBrowser::getInstance(), SIGNAL(sendReceivedTextFromH5(const QString&)), m_bizActionResponder, SLOT(slotReceiveMessageFromH5(const QString&)));

    QString belongFeedId = inBelongFeedId;
    if (belongFeedId.isEmpty())
        belongFeedId = TNDbUtil::getMyBelongToFeedId(feedId);
    QString frame = TNFrameId::getFrameId(feedId, belongFeedId);
    QString frameFlag;
    if (isFriendApply)
    {
        frameFlag = QString("1");
    }
    else
    {
        frameFlag = QString("0");
    }

    const QString curLocalH5Url = QString("%1/%2/%3/%4/%5").arg(NetWorkAPI::s_urlLocalH5Url).arg(feedId).arg(frame).arg(belongFeedId).arg(frameFlag);
    qInfo()<<"[TNMVD][TNFrameViewer]showFrame-Url="<<curLocalH5Url;
    TNSimpleBrowser::getInstance()->setPluginParam(TNUserDataHelper::GetInstance()->_pluginParam);
    TNSimpleBrowser::getInstance()->setUrl(curLocalH5Url);
    TNSimpleBrowser::getInstance()->showOnTop();
}
