#include "TNBizActionResponder.h"

#include "TNUtil.h"
#include "TNPathUtil.h"
#include "TNNameSpace.h"
#include "TNFrameViewer.h"
#include "TNSimpleBrowser.h"
#include "tnnotifycenter.h"
#include "TNMessageBox.h"
#include "TNUserDataHelper.h"
#include "TNDataControlServer.h"
#include "TNChooseCardDialog.h"
#include "TNPictureViewerDialog.h"
#include "TNNetAvatarDown.h"
#include "TNWebEnginePage.h"
#include "TNDataStatistics.h"
#include "TNDataCache.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QApplication>

TNBizActionResponder::TNBizActionResponder(QObject *parent) : QObject(parent)
{
    m_pluginParam = TNUserDataHelper::GetInstance()->_pluginParam;

    m_httpApi = std::make_shared<TNHttpApi>();
    m_httpApi->InitDomainUrl(m_pluginParam->str_new_user_systoon_com);
}

void TNBizActionResponder::slotReceiveMessageFromH5(const QString &text)
{
    qInfo()<<"[TNMVD][TNBizActionResponder]slotReceiveMessageFromH5 begin...";
    QJsonParseError jsonError;
    QJsonDocument jsonDoucment = QJsonDocument::fromJson(text.toUtf8(), &jsonError);
    if (jsonError.error == QJsonParseError::NoError)
    {
        if (jsonDoucment.isArray())
        {
            qInfo() << "[TNMVD][TNBizActionResponder]error! json format error! jason should object.";
        }
        if (jsonDoucment.isObject())
        {
            handleBiz(jsonDoucment.object());
        }
    }
    qInfo()<<"[TNMVD][TNBizActionResponder]slotReceiveMessageFromH5 end.";
}

void TNBizActionResponder::handleBiz(const QJsonObject &jsonObject)
{
    qInfo()<<"[TNMVD][TNBizActionResponder]handleBiz begin...";
    QString debugText = QJsonDocument(jsonObject).toJson();
    qInfo()<<"[TNMVD][TNBizActionResponder]handleBiz-debugText="<<debugText;
    TN::H5BizType bizType = TN::H5BizType(jsonObject["bizType"].toInt());

    if (bizType == TN::Friend)
    {
        TNNotifyCenter::instance()->postNotifyCreateToChat(jsonObject);
    }
    if (bizType == TN::Colleague)
    {
        TNNotifyCenter::instance()->postNotifyCreateToChat(jsonObject);
    }
    if (bizType == TN::GroupChat)
    {
        TNNotifyCenter::instance()->postNotifyCreateToChat(jsonObject);
    }
    if (bizType == TN::OrgFrame)
    {
        showOrgFrame(jsonObject);
    }
    if (bizType == TN::ClickAvatarViewBigPict)
    {
        clickAvatarViewBigPicture(jsonObject);
    }   
    if (bizType == TN::ClickAvatarInApp)
    {
        clickAvatarInAppToFrame(jsonObject);
    }
    if (bizType == TN::OpenGroupChatSession)
    {
        openGroupChatSession(jsonObject);
    }
	if (bizType == TN::UpdateReMark)
	{
		QString feedId = jsonObject["feedId"].toString();
		QString belongFeedId = jsonObject["belongFeedId"].toString();
		QString remark = jsonObject["remark"].toString();
		if (TNDataCache::GetInstance()->getFriendFeedReMark(feedId, belongFeedId) != remark)
		{
			TNNotifyCenter::instance()->postNotifyReMarkUpdate(feedId, belongFeedId, remark,true);
		}
	}
	if (bizType == TN::UpdateOrgComm)
	{
		QString feedId = jsonObject["feedId"].toString();
		QString orgCommStatus = QString::number(jsonObject["orgCommunicationStatus"].toInt());
		if (TNDataCache::GetInstance()->innerGetOrgCommunicationStatus(feedId) != orgCommStatus)
		{
			QMap<QString, QString>statusMap;
			statusMap.insert(feedId, orgCommStatus);

			//更新数据库
			TNDataControlServer::GetInstance()->updateSetValueByValueMap("Feed", "ext1", "feedId", statusMap, DBTYPE_USER);
			//更新缓存
			TNDataCache::GetInstance()->updateOrgCommunicationStatus(feedId, orgCommStatus);
			//发送通知
			TNNotifyCenter::instance()->postNotifyOrgCommunicationStatus(feedId, orgCommStatus);
		}
	}
    if (bizType == TN::AppOpen)
    {
        const QString ownerFeedId = jsonObject["ownerFeedId"].toString();
        bool isMySelf = TNDataControlServer::GetInstance()->isMySelf(ownerFeedId);
        if (isMySelf)
            TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_MINE_APP, m_pluginParam);
        else
            TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_Address_App, m_pluginParam);

        QString url = jsonObject["url"].toString();
        openApp(url);
    }
    qInfo()<<"[TNMVD][TNBizActionResponder]handleBiz end.";
}

void TNBizActionResponder::openApp(const QString &url)
{
    qInfo() << "[TNMVD][TNBizActionResponder]openApp-url=" << url;
    TNSimpleBrowser::getInstance()->setUrl(url);
    TNSimpleBrowser::getInstance()->showOnTop();
}

void TNBizActionResponder::clickAvatarViewBigPicture(const QJsonObject &jsonObject)
{
    Q_ASSERT(jsonObject.contains("avatar"));
    Q_ASSERT(jsonObject.contains("feedId"));
    const QString avatarUrl = jsonObject.value("avatar").toString();
    const QString feedID = jsonObject.value("feedId").toString();

    Q_ASSERT(!avatarUrl.isEmpty());
    Q_ASSERT(!feedID.isEmpty());
    QString avatarFileName;
	if (TNPathUtil::isDownloadedOriginalAvatarPhoto(feedID, avatarFileName))
    {
        showAvatarBigPicture(avatarFileName);
    }
    else
    {
        m_bigPictureFeedIdSet.insert(feedID);
        asynDownloadAvatar(avatarUrl, feedID, avatarFileName);
    }
}
void TNBizActionResponder::asynDownloadAvatar(const QString& url, const QString& feedID, const QString& file_path)
{
	/*
	此处下载原图 2018.2.6WZY
	*/
	qDebug() << "[TNMVD][TNBizActionResponder] asynDownloadAvatar, url: " << url << " feedId:" << feedID;
	TNNetAvatarDown::GetInstance()->DownLoadFeedAvatar(feedID, url, TNHttpCloudApi::GetInstance()->GetCloudStoken(m_pluginParam), this, true);
}

void TNBizActionResponder::onAvatarDownLoadFinish(bool success, QString file_path, QString feedID)
{
    if (success)
    {
        if (m_bigPictureFeedIdSet.contains(feedID))
        {
            showAvatarBigPicture(file_path);
            m_bigPictureFeedIdSet.remove(feedID);
        }
    }
}

void TNBizActionResponder::showAvatarBigPicture(QString file_path)
{
    TNPictureViewerDialog *picViewer = TNPictureViewerDialog::getInstance();
    if (picViewer->isMinimized())
    {
        picViewer->showNormal();
    }
    else
    {
        picViewer->show();
    }
    picViewer->activateWindow();
    picViewer->raise();
    picViewer->showSpecifiedPicture(file_path);
}

void TNBizActionResponder::clickAvatarInAppToFrame(const QJsonObject &jsonObject)
{
    const QString belongFeedId = jsonObject.value("belongId").toString();
    const QString feedId = jsonObject.value("feedId").toString();
    TNFrameViewer::instance()->showFrame(feedId, belongFeedId);
}

void TNBizActionResponder::openGroupChatSession(const QJsonObject &jsonObject)
{
    const QString groupId = jsonObject["groupId"].toString();
    const QString groupChatId = jsonObject["url"].toString();
    // groupChatId
    // toon://groupChat?params=%7B%22groupChatId%22%3A%221489941312091440%22%2C%22myFeedId%22%3A%22c_5149085608456475%22%7D
    //??? begin: 进行URL解码（decode）
    QString url = QByteArray::fromPercentEncoding(groupChatId.toLatin1());
    // end

    QMap<QString, QString> extraArgs;
    extraArgs["groupId"] = groupId;

    qInfo() << "[TNMVD][TNBizActionResponder]openGroupChatSession-url=" << url;
    TNWebEnginePage::handleToonProtocol(url.toUtf8(), extraArgs);
}

void TNBizActionResponder::showOrgFrame(const QJsonObject &jsonObject)
{
    Q_ASSERT(jsonObject.contains("companyId"));
    Q_ASSERT(jsonObject.contains("belongId"));
    const QString companyId = QString::number(jsonObject["companyId"].toInt());
    const QString belongFeedId = jsonObject.value("belongId").toString();
    Q_ASSERT(!companyId.isEmpty());
    Q_ASSERT(!belongFeedId.isEmpty());
    if (companyId.isEmpty())
    {
        qInfo()<<"[TNMVD][TNBizActionResponder]error! TNBizActionResponder::showOrgFrame companyId is null";
        return;
    }
    if (belongFeedId.isEmpty())
    {
        qInfo()<<"[TNMVD][TNBizActionResponder]error! TNBizActionResponder::showOrgFrame belongFeedId is null";
        return;
    }

    QJsonObject companyInfoJson;
    int nRet = m_httpApi->GetCompanyFeedIdByComId(m_pluginParam, companyId, companyInfoJson);
    if (nRet == 0)
    {
        QString debugText = QString(QJsonDocument(companyInfoJson).toJson());
        qInfo() << "[TNMVD][TNBizActionResponder]showOrgFrame-debugText=" << debugText;
        const QString companyFeedId = companyInfoJson.value("data").toArray().at(0).toObject().value("feedId").toString();
        Q_ASSERT(companyFeedId.startsWith("o_"));
        TNFrameViewer::instance()->showFrame(companyFeedId, belongFeedId);
    }
}
