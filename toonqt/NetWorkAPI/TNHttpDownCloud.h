#ifndef TNHTTPDOWNCLOUND_H
#define TNHTTPDOWNCLOUND_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpDownCloud : public TNHttpBaseApi
{
	Q_OBJECT

public:
	TNHttpDownCloud();
	~TNHttpDownCloud();
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	云存储下载 </summary>
	///
	/// <remarks>	李涛 2017/4/12. </remarks>
	///
	/// <param name="callback">   	The callback. </param>
	/// <param name="pluginParam">	The plugin parameter. </param>
	/// <param name="URL">		  	URL of the document. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//void GetJson(std::function<void(bool, QString, QString, QString, TNHttpDownCloud*)> callback, const QString& stoken);
	void GetJsonOnlyForAvator(std::function<void(bool, QString, QStringList, QString, TNHttpDownCloud*)> callback, const QString& stoken);
	void GetJsonEx(std::function<void(bool, QString, QString, QString, QString, int, TNHttpDownCloud*)> callback, const QString& stoken);
	void SetDownCloudUnique(QStringList msgId, QString pathFile, QString url, int appendData = 0);
	void SetDownLoadFinishedCallback(std::function<void(bool, QString, QStringList, QString, TNHttpDownCloud*)> callback);
	void SendDownLoadRequest(const QString& stoken);
	void SendDownLoadRequestOnlyForAvator(const QString& stoken);
    void setDownLoadOrinalSize(bool bOrgSize);
	static bool GetPathFromLocal(const QString& url, QString& filePath);
    static QString GetThumbUrl(int width, int height,
                               const QString& url,
                               const QString& format = "png",
                               int quality = 100);
	void setEmitAvatarFinishedSignal(bool success, QString feedId, QString file);
    void setEmitAvatarFinishedSignalEx(bool success, QString file, QString feedId, QString appendData);
	QString GetMsgId(){ return _msgId[0]; }
	void CancelRequest();
Q_SIGNALS:
	void DownLoadProgressCloud(qint64, qint64, QStringList msgId);
	void downAvatarFinshed(bool, QString, QString);
	void downAvatarFinshedEx(bool, QString, QString, QString);

public slots:
	void  On_DownLoadProgressCloud(qint64, qint64);
protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	
	static void InitDownFileDir();
	
public:
	std::function<void(bool, QString, QStringList, QString, TNHttpDownCloud*)> downFinishedcallback;

private:
	std::function<void(bool, QString, QStringList, QString, TNHttpDownCloud*)> checkCallback;
	std::function<void(bool, QString, QString, QString, QString, int, TNHttpDownCloud*)> appendCallback;
	QString					_saveFile;
	QString					_url;
	QString					_pathFile;
	QStringList				_msgId;
	bool					_bAppendData;
	int						_appendData;
    bool					_bIsDownLoadOringalSize;//为true时，只能下载原始大小文件,不能下载缩略图等文件
	QNetworkReply*			_reply;
};

typedef std::shared_ptr<TNHttpDownCloud>  TNHttpDownCloudPtr;

#endif // TNHTTPDOWNCLOUND_H
