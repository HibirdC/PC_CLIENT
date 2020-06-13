#include "TNHttpUploadCloud.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>
#include <QFile>		
#include <QDataStream>
#include <quuid.h>
#include <qmap.h>  
#include "TNHttpCloudApi.h"
#include "TNUtil.h"
#define URL_HTTP				"http://" 
#define PARAM_CLIENTIP			"127.0.0.1"
#define PARAM_LOCATION			"111.132,123.123"
#ifdef DAOTOON
	#define PUB_TYPE				"0"  //公开为1 私有为0，私有下载需要传stoken
#else
	#define PUB_TYPE				"1"  //公开为1 私有为0，私有下载需要传stoken
#endif
TNHttpUploadCloud::TNHttpUploadCloud() :_domain(""), _reply(NULL)
{
	
}

TNHttpUploadCloud::~TNHttpUploadCloud()
{

}


void TNHttpUploadCloud::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
	if (statusCode == 200) 
	{
		QJsonParseError jsonError;
		QJsonObject jsonObject = QJsonDocument::fromJson(data, &jsonError).object();
		QString res(data);
		qDebug() << res;
		if (jsonError.error == QJsonParseError::NoError) 
		{
			this->checkCallback(true, jsonObject, _appendData, this);	
			return;
		}
	}
    if (statusCode == 500 || statusCode == 400)
	{
		TNHttpCloudApi::GetInstance()->ResetCloudStoken();
	}
	QJsonObject jsonObject;
	this->checkCallback(false, jsonObject, _appendData, this);
}

void TNHttpUploadCloud::GetJson(std::function<void(bool, QJsonObject, QVector<QVariant>, TNHttpUploadCloud*)> callback, const QString& stoken)
{
	this->checkCallback = callback;
	qInfo() << "[NetWorkAPI][TNHttpUploadCloud] uploadCloud filepath = " << _fileName;
	QFile* file = new QFile(_fileName);

	if (!file->open(QIODevice::ReadOnly))
	{
		qInfo() << "[NetWorkAPI][TNHttpUploadCloud]can not open this file errcode=" << file->error() << "errInfo= " << file->errorString();
		delete file;
		return ;
	}
	QByteArray picArray;
	picArray = file->readAll();
	//拼装表单数据
	//边界
	QString boundary = "----weasdashDsdesd";
	//起始边界
	QString startBoundary = "--" + boundary;
	//结束边界
	QString endBoundary = "\r\n--" + boundary + "--\r\n";
	//设置传输类型
	QString qContentType = "multipart/form-data; boundary=" + boundary;
	//要发送的内容
	QByteArray content;
	QMap<QString, QString> parameList;
	parameList.insert("clientIp", PARAM_CLIENTIP);
	parameList.insert("location", PARAM_LOCATION);
	parameList.insert("pub", PUB_TYPE);
	QString ext = _fileName.right(_fileName.size() - _fileName.lastIndexOf("."));
	parameList.insert("suffix", ext);
	QString uuid = TNUtil::getUUID();
	qInfo() << "[NetWorkAPI][TNHttpUploadCloud]:uuid=" << uuid;
	QMap<QString, QString>::iterator it;  
	for (it = parameList.begin(); it != parameList.end(); ++it) {	
		QString formData = startBoundary;
		formData += "\r\nContent-Disposition: form-data;name=\"" + it.key() + "\"\r\n\r\n";
		content += formData;
		content += it.value();
		content += "\r\n";
	}
	parameList.clear();
	QString fileData = startBoundary;
	QString name = _fileName.right(_fileName.size() - _fileName.lastIndexOf("\\") - 1);
	fileData += "\r\nContent-Disposition: form-data; name=\"file\"; filename=\"" + name + "\"\r\n";
	fileData += "Content-Type: application/octet-stream\r\n\r\n";
	content += fileData;
	content += picArray;
	content += endBoundary;
	QString baseUrl = URL_HTTP + _domain + URL_UPLOAD_CLOUD;
	QUrl url(baseUrl);
	qDebug() << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setHeader(QNetworkRequest::ContentTypeHeader, qContentType.toStdString().c_str());
	QString length = QString::number(content.length());
	_httpRequest.setRawHeader(QByteArray("Content-Length"), length.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("stoken"), stoken.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("trace_reserve_mark"), uuid.toStdString().c_str());
	QNetworkReply* reply = post(_httpRequest, url, content);
	connect(reply, SIGNAL(uploadProgress(qint64, qint64)),
		this, SLOT(On_UploadProgressCloud(qint64, qint64)));
	_reply = reply;
	file->close();
	delete file;
}

void TNHttpUploadCloud::SetParam(QUrl& url, QByteArray& data)
{
	QUrlQuery query;
	QDateTime time = QDateTime::currentDateTime();
	int timeT = time.toTime_t();
	QString strTime = QString::number(timeT);
	query.addQueryItem("trace_reserve_mark", strTime);
	//sha256生成，去除最后一个字符
	QByteArray sha256 = QCryptographicHash::hash(data, QCryptographicHash::Sha256);
	QByteArray sha256To64 = sha256.toBase64();
	sha256To64.replace("/", "-");
	sha256To64.remove(43, 1);
	query.addQueryItem("sha256", sha256To64);
	query.addQueryItem("base64", "0");
	url.setQuery(query);
}

void TNHttpUploadCloud::GetDomainUrl(QString& url)
{
	url = URL_HTTP + _domain + "/";
}

void  TNHttpUploadCloud::On_UploadProgressCloud(qint64 upData, qint64 totalData)
{
	QString msgId = _appendData[0].toString();
	emit UpLoadProgressCloud(upData, totalData, msgId);
}

void TNHttpUploadCloud::CancelRequest()
{
	if (_reply && _reply->isRunning() && !_reply->isFinished())
	{
		_reply->abort();
		_reply->deleteLater();
		_reply = NULL;
	}
}
