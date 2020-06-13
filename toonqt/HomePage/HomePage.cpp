#include "HomePage.h"

#include "TNDbUtil.h"
#include "TNConfig.h"
#include "TNDataCache.h"
#include "tnnotifycenter.h"
#include "HomePageListArea.h"
#include "HomePageDetailsArea.h"
#include "TNAppJsonObjectParser.h"
#include "TNToonCommandManager.h"
#include "TNUploadPhotoCommand.h"

static QMap<QString/*comId*/, QString/*feedId*/> getComIdToFeedIdMap()
{
    QMap<QString/*comId*/, QString/*feedId*/> comIdToFeedIdMap;
    QList<st_FeedPtr> myAllStuff;
    TNDataCache::GetInstance()->getMyStuff(myAllStuff);
    for (st_FeedPtr aStuff : myAllStuff)
    {
        if (!aStuff->GetComID().isEmpty())
            comIdToFeedIdMap.insert(aStuff->GetComID(), aStuff->GetFeedID());
    }
    qInfo()<<"[HomePage][HomePage]-comIdToFeedIdMap="<<comIdToFeedIdMap;

    return comIdToFeedIdMap;
}

HomePage::HomePage(TNPluginParamPtr pluginParam, QWidget *parent)
    : PluginExportBase(pluginParam, parent)
    , _ID(MENU_HOMEPAGE_ID)
{
    QMap<QString/*comId*/, QString/*feedId*/> comIdToFeedIdMap = getComIdToFeedIdMap();
    m_configParser = new TNHomePageConfigParser(pluginParam, this);
    connect(m_configParser, SIGNAL(parserFinished()), this, SLOT(slotUrlConfigParserFinished()));
    m_configParser->requestHomePageConfigInfos(comIdToFeedIdMap);

    _HomePageMenuArea = new MenuAreaBase(_ID, (""), MEUNU_SHOW_TYPE_HOMEPAGE);
    _HomePageMenuArea->setText((""));
    _HomePageMenuArea->setObjectName("Menu_Homepage");
    _HomePageMenuArea->setCheckable(true);
    _HomePageMenuArea->setToolTip(tr(QStringLiteral("主页").toUtf8().data()));
    if (TNConfig::instance()->hasHomePage())
        _HomePageMenuArea->show();
    else
        _HomePageMenuArea->hide();

    _HomePageListArea = new HomePageListArea(_ID, pluginParam, this);

    HomePageDetailsArea *homePageDetailsArea = new HomePageDetailsArea(_ID, pluginParam, this);
    _HomePageDetailsArea = homePageDetailsArea;

    m_httpApi = std::make_shared<TNHttpApi>();
    m_httpApi->InitDomainUrl(pluginParam->str_new_user_systoon_com);

    connect(_HomePageMenuArea, SIGNAL(clicked()), this, SLOT(slotGetHomePageInfosFromServer()));
    connect(_HomePageListArea, SIGNAL(clickedItem(QString, QString)), homePageDetailsArea, SLOT(slotShowHome(QString, QString)));
}

HomePage::~HomePage()
{

}

void HomePage::slotGetHomePageInfosFromServer()
{
    // TODO: 每次点击从服务器拉取一次最新的主页信息配置数据，然后更新列表
    QMap<QString/*comId*/, QString/*feedId*/> comIdToFeedIdMap = getComIdToFeedIdMap();
    m_configParser->requestHomePageConfigInfos(comIdToFeedIdMap);
}

void HomePage::slotUrlConfigParserFinished()
{
    m_homePageInfos = m_configParser->getHomePageInfos();
    qDebug()<<"m_homePageInfos.size="<<m_homePageInfos.size();
    if (m_homePageInfos.isEmpty())
    {
        qobject_cast<HomePageListArea*>(_HomePageListArea)->showNullPage(true);
        qobject_cast<HomePageListArea*>(_HomePageListArea)->initListWidget(m_homePageInfos);
        qobject_cast<HomePageDetailsArea*>(_HomePageDetailsArea)->setCurrentPage(1);
    }
    else
    {
        _HomePageMenuArea->show();

        // TODO： 同步获取APP，可能会存在效率问题，待观察
        for (int i=0; i<m_homePageInfos.size(); i++)
        {
            if (m_homePageInfos[i].showOrgApp)
            {
                // 获取组织名片的APP
                QString orgFeedId = TNDbUtil::getCompanyFeedId(m_homePageInfos[i].comId);
                m_homePageInfos[i].appInfos.append(getOrgAppInfos(m_homePageInfos[i].comId, orgFeedId));
            }
            if (m_homePageInfos[i].showStaffApp)
            {
                // 获取员工名片的APP
                m_homePageInfos[i].appInfos.append(getStaffAppInfos(m_homePageInfos[i].comId, m_homePageInfos[i].staffFeedId));
            }
        }

        qobject_cast<HomePageListArea*>(_HomePageListArea)->showNullPage(false);
        qobject_cast<HomePageListArea*>(_HomePageListArea)->initListWidget(m_homePageInfos);
    }
}

QPointer<MenuAreaBase> HomePage::GetMenu()
{
    return _HomePageMenuArea;
}

QPointer<ListAreaBase> HomePage::GetList()
{
    return _HomePageListArea;
}

QPointer<DetailsAreaBase> HomePage::GetDetails()
{
    return _HomePageDetailsArea;
}

int HomePage::GetID()
{
    return _ID;
}

void HomePage::registerToonCommand()
{
    TNToonCommandManager::instance()->registerToonCommand(QString("mwap/window"), TNAbstractToonCommandPtr(new CloseH5WindowCommand()));
    TNToonCommandManager::instance()->registerToonCommand(QString("mwap/network"), TNAbstractToonCommandPtr(new CheckNetwokCommand()));
    TNToonCommandManager::instance()->registerToonCommand(QString("mwap/photo"), TNAbstractToonCommandPtr(new TNUploadPhotoCommand()));
}


static AppInfo makeAppObject(const TNAppJsonObjectParser &parser,
                             const QString &visitorUserId, const QString &visitorFeedId,
                             const QString &ownerCompanyId)
{
    AppInfo aAppObject;
    /*
    aAppObject.insert("pubStatus", parser.getPubStatus());
    aAppObject.insert("registerType", parser.getRegisterType());

    aAppObject.insert("frame", parser.getFrame());
    aAppObject.insert("visitorUserId", visitorUserId);
    aAppObject.insert("visitorFeedId", visitorFeedId);
    aAppObject.insert("ownerCompanyId", ownerCompanyId);
    aAppObject.insert("ownerFeedId", parser.getFeedId());

    aAppObject.insert("appId", parser.getAppId());
    aAppObject.insert("appName", parser.getAppName());
    aAppObject.insert("appIconUrl", parser.getAppIconUrl());
    aAppObject.insert("appLinkUrl", parser.getAppLinkUrl());

    aAppObject.insert("linkType", parser.getLinkType());
    aAppObject.insert("sublinkType", parser.getSubLinkType());
    */

    aAppObject.appRegisterId = parser.getAppRegisterId().toInt();

    aAppObject.iconUrl = parser.getAppIconUrl();
    aAppObject.title = parser.getAppName();
    aAppObject.url   = parser.getAppLinkUrl();

    aAppObject.frame = parser.getFrame();
    aAppObject.companyId_owner = ownerCompanyId;
    aAppObject.feedId_owner = parser.getFeedId();
    aAppObject.userId_visitor = visitorUserId;
    aAppObject.feedId_visitor = visitorFeedId;

    aAppObject.registerType = parser.getRegisterType();
    aAppObject.appId        = parser.getAppId().toInt();
    qInfo()<<"aAppObject-registerType="<<aAppObject.registerType<<" appId="<<aAppObject.appId<<" appRegisterId="<<aAppObject.appRegisterId;

    return aAppObject;
}

QList<AppInfo> HomePage::getOrgAppInfos(const QString &companyId, const QString &orgFeedId) const
{
    QList<AppInfo> results;
    QJsonObject jsonObject;
    int nRet = m_httpApi->GetCompanyApps(_pluginParam, companyId, orgFeedId, jsonObject);
    if (nRet == 0)
    {
        QString debugText = QJsonDocument(jsonObject).toJson();
        qDebug()<<"TNHomePageConfigParser::getOrgAppInfos-debugText="<<debugText;

        QJsonArray jsonArray = jsonObject.value("data").toArray();
        for (int i = 0; i < jsonArray.size(); i++)
        {
            TNAppJsonObjectParser jsonObjectParser(orgFeedId, jsonArray.at(i).toObject());
            const QString belongFeedId = orgFeedId; // 自己访问自己的应用
            const QString url = jsonObjectParser.getAppLinkUrl();
            Q_UNUSED(url);
            if (!jsonObjectParser.showInHomePage())
                continue;
            int pubStatus = jsonObjectParser.getPubStatus();
            if (pubStatus == 0)
            {
                if (jsonObjectParser.isMyself())
                {
                    AppInfo aAppObject = makeAppObject(jsonObjectParser, _pluginParam->strTnUserID, belongFeedId, companyId);
                    results.append(aAppObject);
                }
            }
            else if (pubStatus == 1)
            {
                AppInfo aAppObject = makeAppObject(jsonObjectParser, _pluginParam->strTnUserID, belongFeedId, companyId);
                results.append(aAppObject);
            }
            else if (pubStatus == 2)
            {
                if (jsonObjectParser.isMyself() || jsonObjectParser.isFriend())
                {
                    AppInfo aAppObject = makeAppObject(jsonObjectParser, _pluginParam->strTnUserID, belongFeedId, companyId);
                    results.append(aAppObject);
                }
            }
            else
            {
                qDebug() << "pubStatus is wrong. pubStatus=" << pubStatus;
                Q_ASSERT(!"never come to here. pubStatus error!");
            }
        }
    }

    return results;
}

QList<AppInfo> HomePage::getStaffAppInfos(const QString &companyId, const QString &staffFeedId) const
{
    QList<AppInfo> results;
    QJsonObject jsonObject;
    int nRet = m_httpApi->GetStaffApps(_pluginParam, companyId, staffFeedId, jsonObject);
    if (nRet == 0)
    {
        QString debugText = QJsonDocument(jsonObject).toJson();
        qDebug()<<"TNHomePageConfigParser::getStaffAppInfos-debugText="<<debugText;

        QJsonArray jsonArray = jsonObject.value("data").toArray();
        for (int i = 0; i < jsonArray.size(); i++)
        {
            TNAppJsonObjectParser jsonObjectParser(staffFeedId, jsonArray.at(i).toObject());
            const QString belongFeedId = staffFeedId; // 自己访问自己的应用
            const QString url = jsonObjectParser.getAppLinkUrl();
            Q_UNUSED(url);
            if (!jsonObjectParser.showInHomePage())
                continue;
            int pubStatus = jsonObjectParser.getPubStatus();
            if (pubStatus == 0)
            {
                if (jsonObjectParser.isMyself())
                {
                    AppInfo aAppObject = makeAppObject(jsonObjectParser, _pluginParam->strTnUserID, belongFeedId, companyId);
                    results.append(aAppObject);
                }
            }
            else if (pubStatus == 1)
            {
                AppInfo aAppObject = makeAppObject(jsonObjectParser, _pluginParam->strTnUserID, belongFeedId, companyId);
                results.append(aAppObject);
            }
            else if (pubStatus == 2)
            {
                if (jsonObjectParser.isMyself() || jsonObjectParser.isFriend())
                {
                    AppInfo aAppObject = makeAppObject(jsonObjectParser, _pluginParam->strTnUserID, belongFeedId, companyId);
                    results.append(aAppObject);
                }
            }
            else
            {
                qDebug() << "pubStatus is wrong. pubStatus=" << pubStatus;
                Q_ASSERT(!"never come to here. pubStatus error!");
            }
        }
    }

    return results;
}

HomePage* getMenu(TNPluginParamPtr pluginParam, QWidget *parent)
{
    return new HomePage(pluginParam, parent);
}
