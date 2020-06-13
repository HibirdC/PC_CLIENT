#include "TNHttpDam.h"

#include "qdebug.h"
#include "TNVersionInfo.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>
#include <QUuid>							
#include <QApplication>
#include <QDesktopWidget>
#include "TNConfig.h"

QString TNHttpDam::s_funTables[FUNC_TYPE_MAX] = {
	"PCDL0001", "PCDL0002", "PCDL0003", "PCDL0004", "PCDL0005", "PCDL0006", "PCWJMM0001", "PCHDDL0002",
	"PCTZ0001", "PCTZ0002", "PCTZ0003", "PCTZ0004", "PCTZ0005", "PCTZ0006", "PCTZ0007", "PCTZ0008", "PCTZ0009", "PCTZ0010", "PCTZ0011", "PCTZ0012", "PCTZ0013", "PCTZ0015", "PCTZ0016", "PCTZ0017", "PCTZ0018",
	"PCTXL0001", "PCTXL0002", "PCTXL0009", "PCTXL0003", "PCTXL0004", "PCTXL0005", "PCTXL0006", "PCTXL0007", "PCTXL0008", "PCTXL0010"
	"PCWD0001", "PCWD0002", 
	"PCSZ0001", "PCSZ0002", 
	"PCTP0001", "PCTP0002"
};

QString TNHttpDam::s_typeTables[SEARCH_TYPE_MAX] = { "haoyou", "tongshi", "xiaozu", "qunliao" };
TNHttpDam::TNHttpDam()
{
	
}

TNHttpDam::~TNHttpDam()
{

}


void TNHttpDam::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
	if (statusCode == 200) 
	{
		QJsonParseError jsonError;
		QString content = data;
		QJsonObject jsonObject = QJsonDocument::fromJson(data, &jsonError).object();
		if (jsonError.error == QJsonParseError::NoError) 
		{
			QString code = jsonObject.value("code").toString();
			QString msg = jsonObject.value("msg").toString();
			qDebug() << "RecordDam:code" << code << msg;
			return;
		}
	}
	else
		qDebug() << "RecordDam:fail";
}

QString TNHttpDam::GetUUID()
{
	QUuid id = QUuid::createUuid();
	QString strId = id.toString();
	strId.remove('{');
	strId.remove('}');

	return strId;
}

void TNHttpDam::RecordDeviceData(const TNPluginParamPtr &pluginParam, OPERATE_TYPE type)
{
	QJsonObject deviceJson;
	QString strOPType = QString::number(type);
	//操作类型
	deviceJson.insert("ot", strOPType);
	//启动标识
	deviceJson.insert("sf", GetUUID());
	//设备号windows PC或Mac OS
	deviceJson.insert("dn", pluginParam->strMacAddress);
	//用户id
	deviceJson.insert("ui", pluginParam->strTnUserID);
	//设备型号
	deviceJson.insert("dc", QSysInfo::productType());
	//操作系统
	deviceJson.insert("os", QSysInfo::prettyProductName());
	//操作系统版本
	deviceJson.insert("ov", QSysInfo::productVersion());
	//toon版本
    deviceJson.insert("tv", TNVersionInfo::appVersion());
	//TOON-Bulid版本
    deviceJson.insert("bv", TNVersionInfo::buildNo());
	//分辨率
	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect screenRect = desktopWidget->screenGeometry();
	int width = screenRect.width();
	int height = screenRect.height();
	QString size = QString("%1*%2").arg(width).arg(height);
	deviceJson.insert("rs", size);
	//网络情况
	deviceJson.insert("nw", "5");
	//运营商
	deviceJson.insert("op", "4");
	//渠道
	deviceJson.insert("ch", "");
	//激活
	if (TNConfig::instance()->isFirstStartUp())
		deviceJson.insert("at", "1");
	else
		deviceJson.insert("at", "0");
	//mac地址
	deviceJson.insert("mac", pluginParam->strMacAddress);
	//toontype
	deviceJson.insert("tt", APPTYPE);
	//数据版本
	deviceJson.insert("dv", "6");
	QJsonObject jsonObject;
	jsonObject.insert("t", "1504603116");
	jsonObject.insert("data", deviceJson);
	jsonObject.insert("sign", "144ed18803e86866da4ca6692531ee65");
	jsonObject.insert("appKey", "1c9fc9ac4d8dacce014d8dad55a30103");
	QJsonDocument document;
	document.setObject(jsonObject);	
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);

	// 基本 URL
	QString baseUrl = URL_DAM;
	QUrl url(baseUrl);
	qDebug() << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	post(_httpRequest, url, dataArray);
}

void TNHttpDam::RecordFunctionData(const TNPluginParamPtr &pluginParam, FUNCTION_TYPE type)
{
	QJsonObject extData;
	RecordFunctionInnerData(pluginParam, type, extData);
}

void TNHttpDam::RecordSearchData(const TNPluginParamPtr &pluginParam, FUNCTION_TYPE type, TNDamSearchData searchData)
{
	QJsonObject jsonObject;
	jsonObject.insert("moduleId", "24");
	jsonObject.insert("keyword", searchData.keyWord);
	jsonObject.insert("number", searchData.number);
	jsonObject.insert("dataId", searchData.dataId);
	RecordFunctionInnerData(pluginParam, type, jsonObject);
}


void TNHttpDam::RecordFunctionInnerData(const TNPluginParamPtr &pluginParam, FUNCTION_TYPE type, const QJsonObject& searchData)
{
	QJsonObject functionJson;
	//启动标识，一次启动有效
	static QString startFlag = GetUUID();
	functionJson.insert("sf", startFlag);
	//设备号
	functionJson.insert("dn", pluginParam->strMacAddress);
	//用户id
	functionJson.insert("ui", pluginParam->strTnUserID);
	//名片id
	functionJson.insert("ci", "");
	//功能类型
	functionJson.insert("ft", "1");
	//功能id
	functionJson.insert("fi", s_funTables[type]);
	//业务入口分类
	functionJson.insert("bc", "24");
	//业务数据
	functionJson.insert("bd", searchData);
	//toon类型
	functionJson.insert("tt", APPTYPE);
	//dv 版本号
	functionJson.insert("dv", "4");

	QJsonObject jsonObject;
	jsonObject.insert("t", "1504603116");
	jsonObject.insert("data", functionJson);
	jsonObject.insert("sign", "144ed18803e86866da4ca6692531ee65");
	jsonObject.insert("appKey", "1c9fc9ac4d8dacce014d8dad55a30103");
	QJsonDocument document;
	document.setObject(jsonObject);
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);

	// 基本 URL
	QString baseUrl = URL_DAM_FUNC;
	QUrl url(baseUrl);
	qDebug() << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	post(_httpRequest, url, dataArray);
}
