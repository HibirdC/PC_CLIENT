#ifndef SETUP_H
#define SETUP_H

#include <QPointer>
#include "setup_global.h"
#include "PluginExportBase.h"
#include "SetUpListArea.h"
#include "SetUpDetailsArea.h"

class SETUP_EXPORT SetUp : public PluginExportBase
{
	Q_OBJECT
public:
	SetUp(TNPluginParamPtr pluginParam, QWidget *parent = 0);
	~SetUp();

public:
	QPointer<MenuAreaBase> GetMenu() override;
	QPointer<ListAreaBase> GetList() override;
	QPointer<DetailsAreaBase> GetDetails() override;
	int GetID() override;
	void registerToonCommand() override;
    void saveScreenShotHotKeySettingToDB(const QString &key);

public slots:
    void on_notifyCheckVersionFinished(
            bool isNeedUpgrade,
            bool isForceUpgrade,
            QString downLoadURL,
            int nCheckType,
            QString versionDesc
            );

private:
	QPointer<MenuAreaBase> _SetUpMenuArea;
	QPointer<ListAreaBase> _SetUpListArea;
	QPointer <DetailsAreaBase> _SetUpDetailsArea;
	int _ID;

};
extern "C" SETUP_EXPORT SetUp* getMenu(TNPluginParamPtr pluginParam, QWidget *parent);

#endif // SETUP_H
