#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QPointer>
#include "TNHttpApi.h"
#include "homepage_global.h"
#include "PluginExportBase.h"
#include "TNHomePageConfigParser.h"

class HOMEPAGE_EXPORT HomePage : public PluginExportBase
{
    Q_OBJECT
public:
    HomePage(TNPluginParamPtr pluginParam, QWidget *parent = 0);
    ~HomePage();

public:
    virtual QPointer<MenuAreaBase> GetMenu() override;
    virtual QPointer<ListAreaBase> GetList() override;
    virtual QPointer<DetailsAreaBase> GetDetails() override;
    virtual int GetID() override;
    virtual void registerToonCommand() override;

private slots:
    void slotGetHomePageInfosFromServer();
    void slotUrlConfigParserFinished();

private:
    QPointer<MenuAreaBase> _HomePageMenuArea;
    QPointer<ListAreaBase> _HomePageListArea;
    QPointer <DetailsAreaBase> _HomePageDetailsArea;
    int _ID;

    TNHomePageConfigParser *m_configParser;
    QList<HomePageInfo> m_homePageInfos;

    TNHttpApiPtr m_httpApi;
    QList<AppInfo> getOrgAppInfos(const QString &companyId, const QString &orgFeedId) const;
    QList<AppInfo> getStaffAppInfos(const QString &companyId, const QString &staffFeedId) const;
};

extern "C" HOMEPAGE_EXPORT HomePage* getMenu(TNPluginParamPtr pluginParam, QWidget *parent);

#endif // HOMEPAGE_H
