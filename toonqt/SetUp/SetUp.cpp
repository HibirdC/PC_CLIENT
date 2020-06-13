#include "SetUp.h"
#include "TNPromptSignLabel.h"
#include "TNSettingData.h"
#include "tnnotifycenter.h"
#include "TNGlobalShotCutManagement.h"
#include "TNDataControlServer.h"

SetUp::SetUp(TNPluginParamPtr pluginParam, QWidget *parent)
:PluginExportBase(pluginParam, parent)
,_SetUpDetailsArea(NULL)
, _ID(MENU_SETUP_ID)
{
	_SetUpMenuArea = new MenuAreaBase(_ID, (""), MENU_SHOW_TYPE_SETUP);
	_SetUpMenuArea->setObjectName("Menu_SetUp");
	_SetUpMenuArea->setCheckable(true);
    _SetUpMenuArea->setToolTip(("设置"));
	_SetUpListArea = new SetUpListArea(_ID, pluginParam, this);
	_SetUpDetailsArea = new SetUpDetailsArea(_ID, pluginParam, this);
    TNNotifyCenter::instance()->connectNotifyCheckVersionFinished(this);
    if (!TNSettingData::instance()->isNewestVersion())
    {
        _SetUpMenuArea->showRedPoint(true,MENU_SHOW_TYPE_SETUP);
    }

    //截屏热键
    QString screenShotHotKey = TNSettingData::instance()->ScreenShotKey();
    if (screenShotHotKey.isEmpty())
    {
#ifdef  Q_OS_MAC
        screenShotHotKey = "Meta+A";
#else
        screenShotHotKey = "Alt+A";
#endif
        TNSettingData::instance()->SetScreenShotKey(screenShotHotKey);
        saveScreenShotHotKeySettingToDB(screenShotHotKey);
        TNGlobalShotCutManagement::instance()->setScreenShotKey(screenShotHotKey);
    }
	connect(_SetUpListArea, SIGNAL(clickedButton(int)), _SetUpDetailsArea, SLOT(setCurrentWidgetIndex(int)));
}

SetUp::~SetUp()
{

}

QPointer<MenuAreaBase> SetUp::GetMenu()
{
	return _SetUpMenuArea;
}

QPointer<ListAreaBase> SetUp::GetList()
{
	return _SetUpListArea;
}

QPointer<DetailsAreaBase> SetUp::GetDetails()
{
	return _SetUpDetailsArea;
}

int SetUp::GetID()
{
	return _ID;
}

void SetUp::registerToonCommand()
{
	
}

void SetUp::saveScreenShotHotKeySettingToDB(const QString &key)
{
    st_SetUpPtr localPathSetting = std::make_shared<st_SetUp>();
    localPathSetting->SetKey("ScreenShotHotKey");
    localPathSetting->SetValue(key);
	TNDataControlServer::GetInstance()->InsertDatas(std::dynamic_pointer_cast<TableBase>(localPathSetting), DBTYPE_USER);
}

SetUp* getMenu(TNPluginParamPtr pluginParam, QWidget *parent)
{
	return new SetUp(pluginParam, parent);
}

void SetUp::on_notifyCheckVersionFinished(bool isNeedUpgrade,
                                          bool isForceUpgrade,
                                          QString downLoadURL,
                                          int nCheckType,
                                          QString versionDecs
                                          )
{
	_SetUpMenuArea->showRedPoint(true,MENU_SHOW_TYPE_SETUP);
}
