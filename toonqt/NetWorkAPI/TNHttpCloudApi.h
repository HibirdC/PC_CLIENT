#ifndef TNHttpCloudApi_H
#define TNHttpCloudApi_H

#include <functional>
#include <QTimer>
#include "TNHttpUploadCloud.h"
#include "TNHttpObtainStoken.h"
#include "TNHttpDownCloud.h"
class NETWORKAPI_EXPORT TNHttpCloudApi : public QObject
{
	Q_OBJECT

public:
	TNHttpCloudApi();
	~TNHttpCloudApi();

	static TNHttpCloudApi* GetInstance();

    //为了解决大图现在慢的问题，暂时添加一个克隆函数
    TNHttpCloudApi * clone();
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	上传文件</summary>
	///
	/// <remarks>	李涛 2017/4/8. </remarks>
	///
	/// <param name="msgId"> 消息id </param>
	/// <param name="fileName">	文件全路径 </param>
	/// callback 回调参数顺序：bool 是否成功  qstring 上传成功url  qstring： msgId qstring： sessionid
	/// appendData 第一个参数必须是msgid
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void UploadFileToCloud(std::function<void(bool, QString, QVector<QVariant>)> callback, const TNPluginParamPtr& pluginParam, const QString& fileName, QVector<QVariant> appendData);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	下载文件</summary>
	///
	/// <remarks>	李涛 2017/4/17. </remarks>
	///
	/// <param name="msgId"> 消息id </param>
	/// <param name="url">	文件服务器路径 </param>
	/// <param name="pathFile">	另存为本地路径 </param>
	/// callback 回调参数顺序：bool 是否成功 qstring 返回本地文件下载路径 qstring： msgid qstring sessionid qstring int type
	////////////////////////////////////////////////////////////////////////////////////////////////////
	bool DownFileFromCloudEx(
		std::function<void(bool, QString, QVector<QVariant>)> callback,
		const TNPluginParamPtr& pluginParam,
		const QString& url,
		const QString& pathFile,
		const QString& msgId,
		QVector<QVariant> appendData,
		bool isOrignalSize = false
        );
    void DestroyDownThread(TNHttpDownCloud* downThread);
	//取消上传或者下载
	void CancelRequest(QString msgId, bool bUpload = true);
	bool GetCloudStoken(const TNPluginParamPtr& pluginParam);
	void ResetCloudStoken();
	bool DownAvatorFromCloud(std::function<void(bool, QString, QStringList, QString, TNHttpDownCloud*)> callback, const QString& url, const QStringList& msgId, const QString& pathFile, TNHttpDownCloud* Cloud, bool tokenReady);
signals:
	void GetStokenFinished();
	void DownLoadProgressCloud(qint64, qint64, QStringList msgId);
	void UpLoadProgressCloud(qint64, qint64, QString msgId);
public slots:
	void  On_DownLoadProgressCloud(qint64, qint64, QString msgId);
	void  On_UpLoadProgressCloud(qint64, qint64, QString msgId);
	void  onTokenTimerout();
private:
	TNHttpCloudApi(const TNHttpCloudApi &);
	void DestroyUnuseDownList();
	void DestroyUpThread(TNHttpUploadCloud* downThread);
	void DestroyUnuseUpList();
	std::function<void(bool, QString, QVector<QVariant>)> uploadCallback;
	std::function<void(bool, QString, QString, QString, TNHttpDownCloud*)> downCallback;
	std::function<void(bool, QString, QVector<QVariant>)> appendDownCallback;

private:
	QString		_stoken;
	QString		_domain;
	QTimer*								 _tokenTimer;
	bool                                 _isTokenTimeout;
	TNHttpObtainStokenPtr				 _httpGetStoken;
	QList<TNHttpUploadCloud*>			 _httpUpList;
	QList<TNHttpUploadCloud*>			 _httpDeleteUpList;
	QList<TNHttpDownCloud*>				 _httpDownList;
	QList<TNHttpDownCloud*>				 _httpDeleteDownList;
};

typedef std::shared_ptr<TNHttpCloudApi>  TNHttpCloudApiPtr;

#endif // TNHttpCloudApi_H
