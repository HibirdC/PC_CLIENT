#include "TNHttpCloudApi.h"
#include <QJsonObject>
#include <QThread>
#include <QApplication>
#include <QEvent>
#include <QMutex>
#include <QTimer>

TNHttpCloudApi::TNHttpCloudApi() :_stoken(""), _domain(""), _tokenTimer(nullptr), _isTokenTimeout(false)
{
	_httpGetStoken = std::make_shared<TNHttpObtainStoken>();
	_tokenTimer = new QTimer;
	connect(_tokenTimer, SIGNAL(timeout()), this, SLOT(onTokenTimerout()));
	_tokenTimer->setSingleShot(true);
}

TNHttpCloudApi::TNHttpCloudApi(const TNHttpCloudApi & a)
{
	/*
	废弃构造函数
	*/
}

TNHttpCloudApi::~TNHttpCloudApi()
{
	for (int index = 0; index < _httpDownList.size(); index++)
	{
		TNHttpDownCloud* cloud = _httpDownList[index];
		if (cloud)
			delete cloud;
	}
	_httpDownList.clear();
	for (int index = 0; index < _httpUpList.size(); index++)
	{
		TNHttpUploadCloud* cloud = _httpUpList[index];
		if (cloud)
			delete cloud;
	}
	if (_tokenTimer != nullptr)
	{
		delete _tokenTimer;
		_tokenTimer = nullptr;
	}
	_httpUpList.clear();
	DestroyUnuseDownList();
	DestroyUnuseUpList();
}

TNHttpCloudApi* TNHttpCloudApi::GetInstance()
{
	static QMutex			 s_mutex;
	static TNHttpCloudApi	*s_cloudApi = NULL;
	if (s_cloudApi== NULL)
	{
		QMutexLocker locker(&s_mutex);
		if (s_cloudApi == NULL)  
			 s_cloudApi = new TNHttpCloudApi;
	}
	return s_cloudApi;
}

TNHttpCloudApi * TNHttpCloudApi::clone()
{
    TNHttpCloudApi *pRetApi = new TNHttpCloudApi(*this);
    return pRetApi;
}

void TNHttpCloudApi::UploadFileToCloud(std::function<void(bool, QString, QVector<QVariant>)> callback, const TNPluginParamPtr& pluginParam, const QString& fileName, QVector<QVariant> appendData)
{
	qInfo() << "[NetWorkAPI][TNHttpCloudApi] UploadFileToCloud msgid=" << appendData[0].toString();
	DestroyUnuseUpList();
	this->uploadCallback = callback;
	if (GetCloudStoken(pluginParam))
	{
		//上传文件
		TNHttpUploadCloud* httpUploadCloud = new TNHttpUploadCloud;
		connect(httpUploadCloud, SIGNAL(UpLoadProgressCloud(qint64, qint64, QString)),
			this, SIGNAL(UpLoadProgressCloud(qint64, qint64, QString)));
		QVector<QVariant> upAppendData;
		upAppendData.append(appendData);
		httpUploadCloud->SetMsgData(fileName, upAppendData);
		httpUploadCloud->SetDomain(_domain);
		_httpUpList.append(httpUploadCloud);
		httpUploadCloud->GetJson([&](bool success, QJsonObject jsonObject, QVector<QVariant> appendData, TNHttpUploadCloud* upCloud)
		{
			if (upCloud)
				DestroyUpThread(upCloud);
			if (success)
			{
				qInfo() << "[NetWorkAPI][TNHttpCloudApi] UploadFileToCloud suc msgid= " << appendData[0].toString();
				if (jsonObject.find("pubUrl") != jsonObject.end())
				{
					QString url = jsonObject.value("pubUrl").toString();
					QString stoid = jsonObject.value("stoid").toString();
					QString fileCloudUrl;
					if (url.length() == 0)
					{
						upCloud->GetDomainUrl(fileCloudUrl);
						fileCloudUrl += stoid;
					}
					else
					{
						fileCloudUrl = url.left(url.indexOf("/", 7) + 1);
						fileCloudUrl.append(stoid);
					}
					uploadCallback(true, fileCloudUrl, appendData);
					return;
				}
			}
			uploadCallback(false, "", appendData);
		}, _stoken);
	}
	else
	{
		QVector<QVariant> callBackData;
		callBackData.append(appendData);
		uploadCallback(false, "", callBackData);
	}
}

//bool TNHttpCloudApi::DownFileFromCloud(std::function<void(bool, QString, QString, QString, TNHttpDownCloud*)> callback, const TNPluginParamPtr& pluginParam, const QString& url, const QString& msgId, const QString& pathFile)
//{
//	DestroyUnuseDownList();
//	this->downCallback = callback;
//	QString filePath;
//	if (TNHttpDownCloud::GetPathFromLocal(url, filePath))
//	{
//		downCallback(true, filePath, msgId, pathFile, NULL);
//		return true;
//	}
//	if (GetCloudStoken(pluginParam))
//	{
//		//下载文件
//		TNHttpDownCloud*	downCloud = new TNHttpDownCloud;
//		downCloud->SetDownCloudUnique(msgId, pathFile, url);
//		_httpDownList.append(downCloud);
//		downCloud->GetJson([&](bool success, QString filePath, QString msgId, QString pathFile, TNHttpDownCloud* downThread)
//		{
//			if (downThread)
//				DestroyDownThread(downThread);
//			if (success)
//				downCallback(true, filePath, msgId, pathFile, downThread);
//			else
//				downCallback(false, "", msgId, pathFile, NULL);
//		}, _stoken);
//	}
//	return false;
//}
bool TNHttpCloudApi::DownAvatorFromCloud(std::function<void(bool, QString, QStringList, QString, TNHttpDownCloud*)> callback, const QString& url, const QStringList& msgId, const QString& pathFile, TNHttpDownCloud* Cloud, bool tokenReady)
{
	if (Cloud == NULL)
		return false;
	if (tokenReady)
	{
		Cloud->SetDownLoadFinishedCallback(callback);
		Cloud->SetDownCloudUnique(msgId, pathFile, url);
		Cloud->GetJsonOnlyForAvator([&](bool success, QString filePath, QStringList msgId, QString pathFile, TNHttpDownCloud* downThread)
		{
			if (success)
				downThread->downFinishedcallback(true, filePath, msgId, pathFile, downThread);
			else
				downThread->downFinishedcallback(false, "", msgId, pathFile, downThread);
		}, _stoken);
	}
	return false;
}
bool TNHttpCloudApi::DownFileFromCloudEx(
	std::function<void(bool, QString, QVector<QVariant>)> callback,
	const TNPluginParamPtr& pluginParam,
	const QString& url,
	const QString& pathFile,
	const QString& msgId,
	QVector<QVariant> appendData,
    bool isOringalSize
    )
{
	DestroyUnuseDownList();
	this->appendDownCallback = callback;
	QString filePath;
	if (TNHttpDownCloud::GetPathFromLocal(url, filePath))
	{
		QVector<QVariant> callBackData;
		callBackData.append(appendData);
		appendDownCallback(true, filePath, callBackData);
		return true;
	}
	if (GetCloudStoken(pluginParam))
	{
		//下载文件
		TNHttpDownCloud*	downCloud = new TNHttpDownCloud;
		connect(downCloud, SIGNAL(DownLoadProgressCloud(qint64, qint64, QStringList)),
			this, SIGNAL(DownLoadProgressCloud(qint64, qint64, QStringList)));
        downCloud->moveToThread(this->thread());
        if (isOringalSize)
        {
            downCloud->setDownLoadOrinalSize(true);
        }
		QStringList msgIds;
		msgIds.append(appendData[0].toString());
		msgIds.append(appendData[1].toString());
		downCloud->SetDownCloudUnique(msgIds, pathFile, url, appendData[2].toInt());
		_httpDownList.append(downCloud);
		downCloud->GetJsonEx([&](bool success, QString filePath, QString msgId, QString sessionId, QString pathFile, int appendData, TNHttpDownCloud* downThread)
		{
			QVector<QVariant> callbackData;
			if (success)
			{
				callbackData.append(msgId);
				callbackData.append(sessionId);
				callbackData.append(appendData);
				appendDownCallback(true, filePath, callbackData);
			}
			else
			{
				callbackData.append(msgId);
				callbackData.append(sessionId);
				callbackData.append(appendData);
				appendDownCallback(false, "", callbackData);
			}
			
			if (downThread)
				DestroyDownThread(downThread);
		}, _stoken);
	}
	else
	{
		QVector<QVariant> callbackData;
		callbackData.append(appendData);
		appendDownCallback(false, "", callbackData);
	}
	return false;
}

bool TNHttpCloudApi::GetCloudStoken(const TNPluginParamPtr& pluginParam)
{
	if (!_stoken.isEmpty())
	{	
		if (_isTokenTimeout)
			_stoken = "";
		else
			return true;
	}
	//获取stoken
	_httpGetStoken->GetJson([&](bool success, QJsonObject jsonObject)
	{
		if (success)
		{
			_stoken = jsonObject.value("data").toObject().value("stoken").toString();
			_domain = jsonObject.value("data").toObject().value("domain").toString();
			qInfo() << "[NetWorkAPI][TNHttpCloudApi] get cloud stoken:" << _stoken;
		}
		emit GetStokenFinished();	
	}, pluginParam);
    QEventLoop eventLoop;
	connect(this, &TNHttpCloudApi::GetStokenFinished, &eventLoop, &QEventLoop::quit);
	QTimer::singleShot(1000*5, &eventLoop, SLOT(quit()));
	eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
	qInfo() << "[NetWorkAPI][TNHttpCloudApi] Get Stoken end";
	if (!_stoken.isEmpty())
	{
		_isTokenTimeout = false;
		_tokenTimer->setInterval(25*60*1000);
		_tokenTimer->start();
	}
	return !_stoken.isEmpty();
}

void TNHttpCloudApi::ResetCloudStoken()
{
	qInfo() << "[NetWorkAPI][TNHttpCloudApi] resetCloudStoken";
	if (!_stoken.isEmpty())
	{
		if (_tokenTimer->isActive())
			_tokenTimer->stop();
		_stoken = "";
	}
}

void TNHttpCloudApi::CancelRequest(QString msgId, bool bUpload)
{
	if (bUpload)
	{
		//取消上传
		for (TNHttpUploadCloud* cloud : _httpUpList)
		{
			if (cloud->GetMsgId() == msgId)
			{
				cloud->CancelRequest();
			}	
		}
	}
	else
	{
		//取消下载
		for (TNHttpDownCloud* cloud : _httpDownList)
		{
			if (cloud->GetMsgId() == msgId)
			{
				cloud->CancelRequest();
			}
		}
	}

}

void TNHttpCloudApi::DestroyDownThread(TNHttpDownCloud* downThread)
{
	if (_httpDownList.size() > 0)
	{
		_httpDownList.removeOne(downThread);
	}
	_httpDeleteDownList.append(downThread);
}

void TNHttpCloudApi::DestroyUnuseDownList()
{
	for (int index = 0; index < _httpDeleteDownList.size(); index++)
	{
		TNHttpDownCloud* cloud = _httpDeleteDownList[index];
		if (cloud)
			cloud->deleteLater();
	}
	_httpDeleteDownList.clear();

}

void TNHttpCloudApi::DestroyUpThread(TNHttpUploadCloud* upThread)
{
	if (_httpUpList.size() > 0)
	{
		_httpUpList.removeOne(upThread);
	}
	_httpDeleteUpList.append(upThread);
}

void TNHttpCloudApi::DestroyUnuseUpList()
{
	for (int index = 0; index < _httpDeleteUpList.size(); index++)
	{
		TNHttpUploadCloud* cloud = _httpDeleteUpList[index];
		if (cloud)
			cloud->deleteLater();
	}
	_httpDeleteUpList.clear();
}

void  TNHttpCloudApi::On_DownLoadProgressCloud(qint64 recv, qint64 total, QString msgId)
{
	//test
	//QString str = msgId;
}

void  TNHttpCloudApi::On_UpLoadProgressCloud(qint64, qint64, QString msgId)
{
	//test
	//QString str = msgId;
}
void  TNHttpCloudApi::onTokenTimerout()
{
	//token 超时
	_isTokenTimeout = true;
	qInfo() << "[NetWorkAPI][TNHttpCloudApi] token time out";
}