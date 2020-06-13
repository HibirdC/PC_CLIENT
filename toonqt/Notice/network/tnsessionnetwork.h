#ifndef TNSESSIONNETWORK_H
#define TNSESSIONNETWORK_H

#include <QObject>
#include "common_global.h"
#include "TNHttpCloudApi.h"

class NoticeListModel;
class TNSessionNetWork : public QObject
{
	Q_OBJECT

private:
	TNSessionNetWork(QObject *parent = 0);
public:
	static TNSessionNetWork* getInstance(QObject *parent = 0);
	~TNSessionNetWork();
    void setSessionModel(NoticeListModel* msgModel);
	//下载头像
    void downloadAvatar(const QString& url,const QString& toFeedId,
                        const QString& sessionId, int type);
private slots:
    void onAvatarDownLoadFinishEx(bool success,QString file_path,QString toFeedId,QString sessionId);
    void feedCardUpdateFromCatche(const QString &feedId,
                                  const QString &avatarId,
                                  const QString &name,
                                  const QString &subName,
								  const QString &userId,
								  const QString &namePy,
                                  int sourceType);
public slots:
    void GroupChatUpdateFromCatche(const QString &);
private:
    TNHttpCloudApi*				_httpCloudApi;//http下载上传
	TNPluginParamPtr			_pluginParam;//路由表(登陆获得)
    NoticeListModel*			_sessionListModel = NULL;
};

#endif // TNSESSIONNETWORK_H
