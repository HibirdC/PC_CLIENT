#include "TNHttpObtainGroupChatInfoByGroupChatIdSyn.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>
#include <QTimer>
#include "TNHttpApi.h"
TNHttpObtainGroupChatInfoByGroupChatIdSyn::TNHttpObtainGroupChatInfoByGroupChatIdSyn(QObject *parent) :
    QObject(parent),
    m_networkManager(new QNetworkAccessManager(this)), m_currNum(0), m_maxNum(0)
{

}

TNHttpObtainGroupChatInfoByGroupChatIdSyn::~TNHttpObtainGroupChatInfoByGroupChatIdSyn()
{

}

bool TNHttpObtainGroupChatInfoByGroupChatIdSyn::obtainGroupChatInfo(const TNPluginParamPtr &pluginParam, const QString &groupChatId)
{
    QNetworkRequest request;

    request.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
    request.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
    request.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
    request.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));

    QString baseUrl = pluginParam->str_api_new_groupchat_systoon_com + URL_OBTAIN_GROUP_CHATINFO_BYGROUPCHATID;
    QUrl url(baseUrl);
    QUrlQuery query;
    query.addQueryItem("groupChatId", groupChatId);
    url.setQuery(query);

    request.setUrl(url);

    qInfo() <<"[NetWorkAPI][TNHttpObtainGroupChatInfoByGroupChatIdSyn]-url=" << url;
    m_networkManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
    TNHttpApi::sslVerify(request);
    QNetworkReply *networkReply = m_networkManager->get(request);

    QEventLoop eventLoop;
    QObject::connect(networkReply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    QTimer::singleShot(1000*5, &eventLoop, SLOT(quit()));
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);

    QVariant statusCode = networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    qInfo() << "[NetWorkAPI][TNHttpObtainGroupChatInfoByGroupChatIdSyn]-statusCode=" << statusCode;
    QString contents(networkReply->readAll());
    qInfo() << "[NetWorkAPI][TNHttpObtainGroupChatInfoByGroupChatIdSyn]-readAll=" << contents;

    QJsonParseError jsonError;
    QJsonDocument jsonDoucment = QJsonDocument::fromJson(contents.toUtf8(), &jsonError);
    if (jsonError.error == QJsonParseError::NoError)
    {
        if (jsonDoucment.isArray())
        {
            qInfo() << "[NetWorkAPI][TNHttpObtainGroupChatInfoByGroupChatIdSyn]error! json format error! jason should object.";
        }
        if (jsonDoucment.isObject())
        {
            const QJsonObject jsonObject(jsonDoucment.object());

            QJsonObject dataObject = jsonObject["data"].toObject();
            QString debugText = QJsonDocument(dataObject).toJson();
            qInfo()<<"[NetWorkAPI][TNHttpObtainGroupChatInfoByGroupChatIdSyn]-debugText="<<debugText;

            m_createFeedId = dataObject["creatorFeedId"].toString();
            m_groupChatName = dataObject["groupChatName"].toString();
            m_myFeedId = dataObject["myFeedId"].toString();
            m_groupChatHeadImage = dataObject["groupChatHeadImage"].toString();
            m_currNum = dataObject["currNum"].toInt();
            m_maxNum = dataObject["maxNum"].toInt();
            m_topic = dataObject["topic"].toString();
        }

        return true;
    }

    return false;
}

QString TNHttpObtainGroupChatInfoByGroupChatIdSyn::getCreateFeedId() const
{
    return m_createFeedId;
}

QString TNHttpObtainGroupChatInfoByGroupChatIdSyn::getGroupChatName() const
{
    return m_groupChatName;
}

QString TNHttpObtainGroupChatInfoByGroupChatIdSyn::getMyFeedId() const
{
    return m_myFeedId;
}

QString TNHttpObtainGroupChatInfoByGroupChatIdSyn::getGroupChatHeadImage() const
{
    return m_groupChatHeadImage;
}

int TNHttpObtainGroupChatInfoByGroupChatIdSyn::getCurrNum() const
{
    return m_currNum;
}

int TNHttpObtainGroupChatInfoByGroupChatIdSyn::getMaxNum() const
{
    return m_maxNum;
}

QString TNHttpObtainGroupChatInfoByGroupChatIdSyn::getTopic() const
{
    return m_topic;
}
