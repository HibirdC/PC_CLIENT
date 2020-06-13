#ifndef TNHttpUploadCloud_H
#define TNHttpUploadCloud_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"

class NETWORKAPI_EXPORT TNHttpUploadCloud : public TNHttpBaseApi
{
	Q_OBJECT

public:
	TNHttpUploadCloud();
	~TNHttpUploadCloud();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a JSON. </summary>
	///
	/// <remarks>	ÀîÌÎ, 2017/4/7. </remarks>
	///
	/// <param name="callback">   	The callback. </param>
	/// <param name="pluginParam">	The plugin parameter. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void GetJson(std::function<void(bool, QJsonObject, QVector<QVariant>, TNHttpUploadCloud*)> callback, const QString& stoken);
	void SetMsgData(const QString& fileName, const QVector<QVariant>& appendData){ this->_fileName = fileName; _appendData = appendData; };
	QString GetMsgId(){ return _appendData[0].toString(); }
	void SetDomain(QString& domain){ this->_domain = domain; };
	void GetDomainUrl(QString& url);
	void CancelRequest();
Q_SIGNALS:
	void UpLoadProgressCloud(qint64, qint64, QString msgId);
	public slots:
	void  On_UploadProgressCloud(qint64, qint64);

protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	void SetParam(QUrl& url, QByteArray& data);

private:
	std::function<void(bool, QJsonObject, QVector<QVariant>, TNHttpUploadCloud*)> checkCallback;
	QVector<QVariant>						_appendData;
	QString								   _domain;
	QString								   _fileName;
	QNetworkReply*						   _reply;
};

typedef std::shared_ptr<TNHttpUploadCloud>  TNHttpUploadCloudPtr;

#endif // TNHttpUploadCloud_H
