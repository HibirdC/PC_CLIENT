#include "tnsessionnetwork.h"
#include "noticelistmodel.h"
#include "TNNetAvatarDown.h"
#include "TNDataCache.h"
#include "TNPathUtil.h"
#include "TNUserDataHelper.h"
#include "TNNameSpace.h"

TNSessionNetWork::TNSessionNetWork(QObject *parent /* = 0 */) : QObject(parent)
{
    _httpCloudApi = TNHttpCloudApi::GetInstance();
    TNDataCache::GetInstance()->InstallCatcheFeedUpdateNotify(this);
    TNDataCache::GetInstance()->InstallCatcheGroupChatUpdateNotify(this);
    _pluginParam = TNUserDataHelper::GetInstance()->_pluginParam;
}

TNSessionNetWork::~TNSessionNetWork()
{
}


void TNSessionNetWork::setSessionModel(NoticeListModel* msgModel)
{
	_sessionListModel = msgModel;
}

TNSessionNetWork* TNSessionNetWork::getInstance(QObject *parent /* = 0 */)
{
	static TNSessionNetWork* p_instance = NULL;
	if (p_instance == NULL){
		p_instance = new TNSessionNetWork(parent);
	}
	return p_instance;
}

void TNSessionNetWork::downloadAvatar(const QString& url,const QString& toFeedId,
                                      const QString& sessionId,int type)
{
    bool isOrignal = false;
    if(sessionId.startsWith("gc_")){
        isOrignal = true;
    }
    qInfo() << "[TNSessionNetWork] downloadAvatar, url: " << url << " feedId:" << sessionId;
    if(type != MSG_BIZ_NOTIFY){
        TNNetAvatarDown::GetInstance()->DownLoadFeedAvatar(toFeedId, url,
            TNHttpCloudApi::GetInstance()->GetCloudStoken(_pluginParam),
            this,isOrignal,sessionId);
    }else{
        TNNetAvatarDown::GetInstance()->DownLoadFeedAvatar(sessionId, url,
            TNHttpCloudApi::GetInstance()->GetCloudStoken(_pluginParam),
            this,isOrignal,sessionId);
    }
}

void TNSessionNetWork::onAvatarDownLoadFinishEx(bool success,QString file_path,
                                              QString toFeedId,QString sessionId)
{
	if (success){
		//notice 日志
        QString qs_log = "[Notice] [TNSessionNetWork] session list onAvatarDownLoadFinish success sessionId:" + sessionId + " file_path:" + file_path;
        qInfo() << qs_log;
		_sessionListModel->updateAvatarPhoto(sessionId, file_path);
	}else{
		//notice 日志
        QString qs_log = "[Notice] [TNSessionNetWork] session list onAvatarDownLoadFinish failed sessionId:" + sessionId;
        qInfo() << qs_log;
	}
    Q_UNUSED(toFeedId);
}

void TNSessionNetWork::feedCardUpdateFromCatche(const QString &feedId,
                                                const QString &avatarId,
                                                const QString &name,
                                                const QString &subName,
												const QString &userId,
												const QString &namePy,
                                                int sourceType)
{
    Q_UNUSED(subName);
	Q_UNUSED(userId);
	Q_UNUSED(namePy);

	qInfo() << "[Notice][TNSessionNetWork]feedCardUpdateFromCatche :" << feedId 
		<< " sourceType:" << sourceType;
    if(sourceType != TN::SessionList)
        _sessionListModel->updateSessionByFeedId(feedId,avatarId,name);
}

void TNSessionNetWork::GroupChatUpdateFromCatche(const QString & feedId)
{
    //更新群聊头像
    if(feedId.startsWith("gc_")){
        QString file_path = TNPathUtil::getFeedAvatarPath(feedId);
        file_path += "_org";
        if(QFile::exists(file_path))
            _sessionListModel->updateAvatarPhoto(feedId,file_path);
    }
}
