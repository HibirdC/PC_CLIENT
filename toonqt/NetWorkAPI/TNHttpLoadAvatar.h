#ifndef TNHTTPLOADAVATAR_H
#define TNHTTPLOADAVATAR_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpLoadAvatar : public TNHttpBaseApi
{
public:
	TNHttpLoadAvatar();
	~TNHttpLoadAvatar();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a JSON. </summary>
	///
	/// <remarks>	Ìïºã, 2017/3/13. </remarks>
	///
	/// <param name="callback">   	The callback. </param>
	/// <param name="pluginParam">	The plugin parameter. </param>
	/// <param name="URL">		  	URL of the document. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void GetJson(std::function<void(bool, QByteArray)> callback, const TNPluginParamPtr &pluginParam, const QString & URL, const QString &SavePath);
protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	


private:
	std::function<void(bool, QByteArray)> checkCallback;
	QString _SavePath;
};

typedef std::shared_ptr<TNHttpLoadAvatar>  TNHttpLoadAvatarPtr;

#endif // TNHTTPLOADAVATAR_H
