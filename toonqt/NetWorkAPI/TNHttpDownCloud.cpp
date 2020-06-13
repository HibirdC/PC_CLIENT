#include "TNHttpDownCloud.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>
#include <QPixmap>
#include <QWidget>
#include <QCoreApplication>						
#include <QDir>

#include "TNPathUtil.h"
#include "TNConfig.h"
#include "TNHttpCloudApi.h"
TNHttpDownCloud::TNHttpDownCloud() : _url(""), _msgId(""), _pathFile("")
, _bAppendData(false), _bIsDownLoadOringalSize(false), _reply(NULL), _appendData(0)
{
	
}

TNHttpDownCloud::~TNHttpDownCloud()
{
}


void TNHttpDownCloud::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
	if (statusCode == 200 && data.size() != 0) 
	{
		QFile file(_saveFile);
		qInfo() << "[NetWorkAPI][TNHttpDownCloud] SaveFilePath:" << _saveFile;
		int dataSize = data.size();
		if (file.open(QIODevice::WriteOnly))
		{
			qDebug() << "File:" << _saveFile << ",size:" << dataSize;
			file.write(data); 
            file.resize(qint64(dataSize));
			file.close();
		}
		else 
		{
			qWarning() << "[NetWorkAPI][TNHttpDownCloud] openFile fail:" << file.errorString();
		}
		if (!_bAppendData) 
			this->checkCallback(true, _saveFile, _msgId, _pathFile, this);
		else
			this->appendCallback(true, _saveFile, _msgId[0], _msgId[1], _pathFile, _appendData, this);
		return;
	}
    if (statusCode == 500 || statusCode == 400)
	{
		TNHttpCloudApi::GetInstance()->ResetCloudStoken();
	}
	if (!_bAppendData)
		this->checkCallback(false, _saveFile, _msgId, _pathFile, this);
	else 
		this->appendCallback(false, _saveFile, _msgId[0], _msgId[1], _pathFile, _appendData, this);
}

//void TNHttpDownCloud::GetJson(std::function<void(bool, QString, QString, QString, TNHttpDownCloud*)> callback, const QString& stoken)
//{
//	_bAppendData = false;
//	this->checkCallback = callback;
//	SendDownLoadRequest(stoken);
//}
void TNHttpDownCloud::GetJsonOnlyForAvator(std::function<void(bool, QString, QStringList, QString, TNHttpDownCloud*)> callback, const QString& stoken)
{
	_bAppendData = false;
	this->checkCallback = callback;
	SendDownLoadRequestOnlyForAvator(stoken);
}

void TNHttpDownCloud::SendDownLoadRequestOnlyForAvator(const QString& stoken)
{
	//判断是否是缩略图url
	QString name = _msgId[0];
	if (_pathFile.isEmpty())
		_saveFile = TNPathUtil::getFeedAvatarPath() + name;
	else
	{
		QString selectName = _pathFile;
		while (QFile::exists(selectName))
		{
			QFile::remove(selectName);
		}
		_saveFile = selectName;
	}
	QUrl baseUrl(_url);
	QUrl latestUrl = covertHttpToHttps(baseUrl);
	Q_ASSERT(latestUrl.isValid());
	qDebug() << latestUrl;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("stoken"), stoken.toStdString().c_str());
	QNetworkReply* reply = get(_httpRequest, latestUrl);
	connect(reply, SIGNAL(downloadProgress(qint64, qint64)),
		this, SLOT(On_DownLoadProgressCloud(qint64, qint64)));
}
void TNHttpDownCloud::SendDownLoadRequest(const QString& stoken)
{
	//判断是否是缩略图url
	QString name = _msgId[0];
    if (_bIsDownLoadOringalSize)
    {
        name += "_org";
    }
	if (_pathFile.isEmpty())
		_saveFile = TNPathUtil::getUserRecFile() + name;
	else
	{
		//另存为文件
		QString selectName = _pathFile;
		int index = 1;
		while (QFile::exists(selectName))
		{
			QString path = selectName.left(selectName.lastIndexOf("/"));
			QString temp = selectName.right(selectName.size() - selectName.lastIndexOf("/") - 1);
			int left = temp.lastIndexOf('(');
			int right = temp.lastIndexOf(')');
			if (left>-1 && right>-1)
				temp = temp.left(left) + temp.right(temp.length() - right-1);
			int end = temp.lastIndexOf('.');
			QString strIndex = QString("(%1)").arg(index);
			if (end > 0)
				temp.insert(end, strIndex);
			else
				temp.append(strIndex);
			selectName = path + "/" + temp;
			index++;
		}
		_saveFile = selectName;
	}
	QUrl baseUrl(_url);
	QUrl latestUrl = covertHttpToHttps(baseUrl);
	Q_ASSERT(latestUrl.isValid());
	qDebug() << latestUrl;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("stoken"), stoken.toStdString().c_str());
	QNetworkReply* reply = get(_httpRequest, latestUrl);
	connect(reply, SIGNAL(downloadProgress(qint64, qint64)),
		this, SLOT(On_DownLoadProgressCloud(qint64, qint64)));
	_reply = reply;
}

void TNHttpDownCloud::GetJsonEx(std::function<void(bool, QString, QString, QString, QString, int, TNHttpDownCloud*)> callback, const QString& stoken)
{
	_bAppendData = true;
	this->appendCallback = callback;
	SendDownLoadRequest(stoken);
}


void TNHttpDownCloud::On_DownLoadProgressCloud(qint64 receive, qint64 total)
{
	QStringList CloudData;
	CloudData.append(_msgId[0]);
	CloudData.append(_pathFile);
	emit DownLoadProgressCloud(receive, total, CloudData);
}

bool TNHttpDownCloud::GetPathFromLocal(const QString& url, QString& filePath)
{
	if (url.size() > 0)
	{
		QString name = url.right(url.size() - url.lastIndexOf("/") - 1);
		filePath = TNPathUtil::getUserRecFile() + name;
		if (QFile::exists(filePath))
		{
			return true;
		}
	}
	return false;

}

void TNHttpDownCloud::SetDownLoadFinishedCallback(std::function<void(bool, QString, QStringList, QString, TNHttpDownCloud*)> callback)
{
	this->downFinishedcallback = callback;
}

void TNHttpDownCloud::setDownLoadOrinalSize(bool bOrgSize)
{
    _bIsDownLoadOringalSize = bOrgSize;
}

void TNHttpDownCloud::SetDownCloudUnique(QStringList msgId, QString pathFile, QString url, int appendData)
{
	this->_msgId = msgId;
	this->_pathFile = pathFile;
	qDebug() << "pathFile:" << _pathFile;
	this->_url = url;
	if (appendData)
	{
		_bAppendData = true;
		this->_appendData = appendData;
	}
}

QString TNHttpDownCloud::GetThumbUrl(int width, int height,
                                     const QString& url,
                                     const QString& format,
                                     int quality)
{
    QString suffix;
    if(format.isEmpty()){
        suffix = "png";
    }else{
        suffix = format;
    }
	if (url.indexOf("/f/") > 0)
	{
		QString fileName = url.right(url.length() - url.lastIndexOf("/f/")-3);
		qDebug() << "avator name: "<< fileName;
		QString thumbUrl = url;
		//静态图片
        QString thumbUrlMid = QString("_%1_%2_%3_0").arg(width).arg(height).arg(quality);
		if (fileName.lastIndexOf(".") > 0)
			thumbUrl = thumbUrl.insert(url.lastIndexOf("."), thumbUrlMid);
		else
			thumbUrl = thumbUrl.append(thumbUrlMid + ".jpg");
		return thumbUrl;
	}
    QString thumbUrl = QString("%1?imageView2/3/w/%2/h/%3/ignore-error/1/format/%4")
        .arg(url).arg(width).arg(height).arg(suffix);
	return thumbUrl; 
}
void TNHttpDownCloud::setEmitAvatarFinishedSignal(bool success, QString file, QString feedId)
{
	emit downAvatarFinshed(success, file, feedId);
}

void TNHttpDownCloud::setEmitAvatarFinishedSignalEx(bool success, QString file,QString feedId,QString appendData)
{
	emit downAvatarFinshedEx(success, file, feedId, appendData);
}


void TNHttpDownCloud::CancelRequest()
{
	if (_reply && _reply->isRunning() && !_reply->isFinished())
	{
		_reply->abort();
		_reply->deleteLater();
		_reply = NULL;
	}

}
