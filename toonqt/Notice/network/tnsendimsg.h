#ifndef TNSENDIMSG_H
#define TNSENDIMSG_H

#include <QObject>
#include <list>
#include <QMutex>
#include <map>

#include "notice_global.h"
#include "TNHttpCloudApi.h"
#include "TNIMCoreClient.h"
#include "model_data/TNModelUserMessage.h"
using namespace std;




/*
负责消息发送接收单例类
*/

struct down_mark{
public:
    explicit down_mark() : _is_org(0){
    }

    explicit down_mark(QString msg_id,int is_org = 0)
        : _msg_id(msg_id),_is_org(is_org){
    }

    inline bool operator ==(const down_mark& obj) const{
        return equalTo(obj) && obj.equalTo(*this);
    }
    inline bool operator !=(const down_mark& obj) const{
        return !equalTo(obj) || !obj.equalTo(*this);
    }

    inline bool operator ==(const down_mark& obj){
        return equalTo(obj) && obj.equalTo(*this);
    }
    inline bool operator !=(const down_mark& obj){
        return !equalTo(obj) || !obj.equalTo(*this);
    }
    inline bool operator <(const down_mark& obj){
        if(_msg_id < obj._msg_id){
            return true;
        }else if(_msg_id == obj._msg_id){
            return _is_org < obj._is_org;
        }else{
            return false;
        }
    }
    inline bool operator <(const down_mark& obj) const{
        if(_msg_id < obj._msg_id){
            return true;
        }else if(_msg_id == obj._msg_id){
            return _is_org < obj._is_org;
        }else{
            return false;
        }
    }

    QString _msg_id;
    int _is_org;
protected:
    virtual bool equalTo( const down_mark &obj) const{
        return _msg_id == obj._msg_id && _is_org == obj._is_org;
    }
};

class TNMsgDetailModel;
class NoticeListModel;
class TNSessionNetWork;


class NOTICE_EXPORT TNSendIMsg : public QObject
{
	Q_OBJECT
private:
	TNSendIMsg(QObject *parent = 0);
public:
    static TNSendIMsg* getInstance();
    static void releaseInstance();
	~TNSendIMsg();
	
	void setDetailModel(TNMsgDetailModel* msgModel);
    void setListMsgModel(NoticeListModel* listModel);
    NoticeListModel* getListMsgModel();
	void setTNPluginParamPtr(const TNPluginParamPtr& param);

	//im 发送消息处理
    void ProcessIMMSG(TNModelUserMessage message);
	//下载文件
    void DownloadFile(const QString& url, const QString& msgId, const QString& sessionId, const QString& file_path);
    //下载图片,下载缩略图和原图
    void DownloadImage(TNModelUserMessage message);
    //下载原图
    void downLoadOrgImage(TNModelUserMessage message);
	//下载音频,音频下载完成后再创建界面
    void DownloadAudio(TNModelUserMessage data);
	//下载头像
    void DownloadAvatar(const QString& url,const QString& feedId,
                        const QString& msgId, const QString& file_path="");
    //会话下载头像
    void downLoadAvator(TNMessageListAdapter itemData);
    //加入上传下载进度
    void appendProgress(const down_mark& mark);
    //更新上传下载进度
    bool updateProgress(const down_mark& mark, int progress);
    //删除上传下载进度
    bool removeProgress(const down_mark& mark);
    //获取上传下载进度
    bool getProgress(const down_mark& mark, int* progress);
    //取消下载/上传
    void cancelUpLoad(const QString& msgId);
    void cancelDownLoad(const QString& msgId,const QString& sessionId);
private:
	void SendMsgToIMServer(TNModelUserMessage* message);
    void SendMsgToIMServer(const QString& sessionId, const QString& msgId);
	void UploadCloud(TNModelUserMessage* message);
    TNMsgData convertMsgData(TNModelUserMessage* message);
	bool isFileDownloaded(const QString& msgId, QString& localPath);
	bool isAudioDownloaded(const QString& msgId, QString& localPath);

    bool pushBackDownload(const down_mark& mark);
    void popUpDownload(const down_mark& mark);
    bool isDownloading(const down_mark& mark);

    bool pushBackUpload(const QString& msgId);
    void popUpUpload(const QString& msgId);
    bool isUploading(const QString& msgId);
signals:
    void upLoadFinishSign(bool, QString, QString, QString);
    void downloadFinishSign(bool, QString, QString, QString, int type, bool is_org=false);
	void notifyRefresh(QString type, int statCode, const QString statDesc, TNMsgData msgData);
	void notifyRefresh(QString type, TNNoticeInfo &noticeInfo);
    void org_image_progress(QString msgId,int progress);
    void orig_image_finished(bool,QString msgId, QString file_path);
public slots:
	//在线消息
	void on_notifyRefresh(QString type, int statCode, const QString statDesc, TNMsgData msgData);
	void on_notifyRefresh(QString type, TNNoticeInfo &noticeInfo);
	void on_notifyRefreshAck(QString msgId, int bSuc);
	void on_notifyRefresh(int , QList<UINotifyData>);
private slots:
	//上传完成
    void onUpLoadFinish(bool success, QString url, QString msgId, QString sessionId);
    void onDownLoadFinish(bool success, QString url,QString msgId,
                          QString sessionId, int type, bool is_org);
    void onUpLoadProgress(qint64 per,qint64 total,QString msgId);
    void onDownLoadProgress(qint64 per,qint64 total,QStringList info);
    void onAvatarDownLoadFinishEx(bool success,QString file_path,
            QString feedId,QString msgId);
private:
    void onFileDownLoadFinish(bool success, QString url, QString msgId,QString sessionId,bool is_org_image=false);
    void onAudioDownLoadFinish(bool success, QString url, QString msgId,QString sessionId);
    void onAvatarDownLoadFinishSign(bool success, QString url,
            QString feedId, QString msgId);

    static void download_file_callback(bool success, QString file_path, QVector<QVariant> params);
private:
	enum downloadType{
		download_image = 1,
		download_file,
		download_audio,
		download_avator
	};

    TNHttpCloudApi*	   	   _httpCloudApi;//http下载上传
	TNPluginParamPtr	   _pluginParam;//路由表(登陆获得)
	TNMsgDetailModel*      _msgModel;
    NoticeListModel*       _listMsgModel;
    //图片附件语音
    list<down_mark>		   _listDown;//下载时,不出现重复下载
    QMutex				   _mutexDown;
    list<QString>		   _listUp;//上传时,不出现重复上传
    QMutex 				   _mutexUp;
    //头像
    list<QString>		   _listAvator;//头像下载时,不出现重复下载
    QMutex				   _mutexAvator;
    static TNSendIMsg* 	   _instance;//sigle
    QMutex 				   _mutex_progress;
    std::map<down_mark,int>  _up_down_progress;

    TNSessionNetWork*		_sessionNetWork;//负责下载资源(如头像)
};

#endif // TNSENDIMSG_H
