#ifndef TNBIZACTIONRESPONDER_H
#define TNBIZACTIONRESPONDER_H

#include <QObject>
#include <QMap>

#include "TNMVD_global.h"
#include "TNHttpApi.h"
#include "TNHttpObtainAppCode.h"
#include "TNHttpFriendRequest.h"


class TNMVD_EXPORT TNBizActionResponder : public QObject
{
    Q_OBJECT

public:
    explicit TNBizActionResponder(QObject *parent = 0);

private slots:
    void slotReceiveMessageFromH5(const QString &text);

private:
    void handleBiz(const QJsonObject &jsonObject);
    void openApp(const QString &url);
    void openGroupChatSession(const QJsonObject &jsonObject);
    void clickAvatarViewBigPicture(const QJsonObject &jsonObject);
    void clickAvatarInAppToFrame(const QJsonObject &jsonObject);
    void showOrgFrame(const QJsonObject &jsonObject);

    void showAvatarBigPicture(QString file_path);
    // 异步更新下载头像
    void asynDownloadAvatar(const QString& url, const QString& sessionId, const QString& file_path);
private slots:
    void onAvatarDownLoadFinish(bool success, QString file_path, QString sessionId);

private:
    TNPluginParamPtr m_pluginParam;

    TNHttpApiPtr			m_httpApi;

    QSet<QString> m_bigPictureFeedIdSet;
};

#endif // TNBIZACTIONRESPONDER_H
