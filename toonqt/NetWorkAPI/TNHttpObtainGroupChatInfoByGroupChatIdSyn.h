#ifndef TNHTTPOBTAINGROUPCHATINFOBYGROUPCHATIDSYN_H
#define TNHTTPOBTAINGROUPCHATINFOBYGROUPCHATIDSYN_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QString>

#include "common_global.h"
#include "NetWorkAPI_global.h"

class NETWORKAPI_EXPORT TNHttpObtainGroupChatInfoByGroupChatIdSyn : public QObject
{
public:
	explicit TNHttpObtainGroupChatInfoByGroupChatIdSyn(QObject *parent = 0);
	~TNHttpObtainGroupChatInfoByGroupChatIdSyn();

	bool obtainGroupChatInfo(const TNPluginParamPtr &pluginParam, const QString &groupChatId);
	
    QString getCreateFeedId() const;
    QString getGroupChatName() const;
    QString getMyFeedId() const;
    QString getGroupChatHeadImage() const;
    int getCurrNum() const;
    int getMaxNum() const;
    QString getTopic() const;

private:
	QNetworkAccessManager *m_networkManager;

    QString m_createFeedId;
    QString m_groupChatName;
    QString m_myFeedId;
    QString m_groupChatHeadImage;
    int m_currNum;
    int m_maxNum;
    QString m_topic;
};

#endif // TNHTTPOBTAINGROUPCHATINFOBYGROUPCHATIDSYN_H
