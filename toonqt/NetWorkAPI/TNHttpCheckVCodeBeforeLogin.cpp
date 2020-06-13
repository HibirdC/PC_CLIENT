#include "TNHttpCheckVCodeBeforeLogin.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QDebug>

#include "TNUtil.h"
#include "TNVersionInfo.h"
#include "TNUpgradePlatform.h"

TNHttpCheckVCodeBeforeLogin::TNHttpCheckVCodeBeforeLogin()
{

}

TNHttpCheckVCodeBeforeLogin::~TNHttpCheckVCodeBeforeLogin()
{

}

void TNHttpCheckVCodeBeforeLogin::setParams(const QString &teleCode, const QString &mobile, const QString &mobileVerfiyCode)
{
    m_teleCode = teleCode;
    m_mobile   = mobile;
    m_mobileVerfiyCode = mobileVerfiyCode;
}

void TNHttpCheckVCodeBeforeLogin::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
    if (statusCode == 200)
    {
        QJsonParseError jsonError;
        QJsonObject jsonObject = QJsonDocument::fromJson(data, &jsonError).object();
        if (jsonError.error == QJsonParseError::NoError)
        {
            this->checkCallback(true, jsonObject);
            return;
        }
    }
    QJsonObject jsonObject;
    this->checkCallback(false, jsonObject);
}

void TNHttpCheckVCodeBeforeLogin::GetJson(std::function<void(bool, QJsonObject)> callback,
                                          const TNPluginParamPtr& pluginParam)
{
    this->checkCallback = callback;

    const QString channel = TNUpgradePlatform::getPlatformChannelNo().mid(0, 10);
    const QString deviceName = QSysInfo::productType();

    QJsonObject jsonObject;
    jsonObject.insert("channel", channel);
    //jsonObject.insert("code", code); // 手机端没有传，PC端也不传，估计目前没有用到该字段
    jsonObject.insert("deviceName", deviceName);
    jsonObject.insert("deviceToken", pluginParam->strMacAddress);
    jsonObject.insert("fromWhere", APPTYPE);
    jsonObject.insert("idfa", "");  // 针对ios的idfa获取
    jsonObject.insert("imei", "");  // 只针对android:imei号
    jsonObject.insert("macAddress", pluginParam->strMacAddress);
    jsonObject.insert("mobile", m_mobile);
    jsonObject.insert("mobileVerfiyCode", m_mobileVerfiyCode);
    jsonObject.insert("teleCode", m_teleCode);
    jsonObject.insert("type", 1); // 短信验证码:1;邮箱验证码:2
    jsonObject.insert("uuid", pluginParam->strMacAddress);

    QJsonDocument document;
    document.setObject(jsonObject);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

    QString baseUrl = pluginParam->str_new_user_systoon_com + URL_CHECK_VCODE;
    QUrl url(baseUrl);
    qInfo() << "[NetWorkAPI][TNHttpCheckVCodeBeforeLogin]-url=" << url;
    QNetworkRequest _httpRequest;
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), "1");
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), "1");
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
    QNetworkReply* reply = post(_httpRequest, url, dataArray);
    Q_UNUSED(reply);
}
