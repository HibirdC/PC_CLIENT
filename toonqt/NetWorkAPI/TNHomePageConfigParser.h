#ifndef TNHomePageConfigParser_H
#define TNHomePageConfigParser_H

#include <QMap>
#include <QString>
#include <QNetworkReply>

#include "common_global.h"
#include "NetWorkAPI_global.h"

struct AppInfo
{
    int appRegisterId;
    QString iconUrl;
    QString title;
    QString url;

    QString frame;
    QString companyId_owner;
    QString feedId_owner;
    QString userId_visitor;
    QString feedId_visitor;

    int registerType;
    int appId;
};

struct HomePageInfo
{
    int id;
    QString iconUrl;
    QString title;
    QString url;
    QString comId;
    bool showOrgApp;
    bool showStaffApp;
    QString staffFeedId;
    QList<AppInfo> appInfos;
};

class QNetworkAccessManager;
class NETWORKAPI_EXPORT TNHomePageConfigParser : public QObject
{
    Q_OBJECT

public:
    explicit TNHomePageConfigParser(const TNPluginParamPtr &pluginParam, QObject *parent=Q_NULLPTR);
    ~TNHomePageConfigParser();

    void requestHomePageConfigInfos(const QMap<QString/*comId*/, QString/*feedId*/> &comIdToFeedIdMap);
    QList<HomePageInfo> getHomePageInfos() const;

signals:
    void parserFinished();

public slots:
    void slotServiceRequestFinished(QNetworkReply *reply);
    void slotOnError(QNetworkReply::NetworkError code);

private:
    TNPluginParamPtr m_pluginParam;
    QMap<QString/*comId*/, QString/*feedId*/> m_comIdToFeedIdMap;
    QNetworkAccessManager* m_networkAccessManager;
    QNetworkReply* m_reply;

    mutable QMap<int/*顺序号*/, HomePageInfo> m_homePageInfos;
};

#endif // TNHomePageConfigParser_H
