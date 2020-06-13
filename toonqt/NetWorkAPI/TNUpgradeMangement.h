#ifndef TNUPGRADEMANGEMENT
#define TNUPGRADEMANGEMENT
#include <QObject>
#include "common_global.h"
#include "NetWorkAPI_global.h"
//升级管理类
class NETWORKAPI_EXPORT TNUpgradeMangement : public QObject
{
	Q_OBJECT
public:
    static TNUpgradeMangement * instance();
    
    //检查类型:启动检查、定时检查、用户点击按钮检查
    enum CheckType
    {
        ctBoot,
        ctTimed,
        ctUser
    };
private:
    TNUpgradeMangement();
private:
    QString m_currentVersion;
    QString m_newestVersion;
    QString m_downLoadURL;
    QString m_verDesc;
    bool m_isNeedUpgrade;
    bool m_isForceUpgrade;
public:
    void checkNewVersion(TNPluginParamPtr _pluginParam, int nCheckType);

signals:
    void checkVersionFinished(
        bool isNeedupgrade,
        bool isForceUpgrade,
        QString strDownLoadURL,
        int nCheckType,
        QString strVerDes
        );
};

#endif
