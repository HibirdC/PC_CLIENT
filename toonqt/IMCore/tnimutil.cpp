#include "tnimutil.h"
#include <QJsonDocument>
#include <QUuid>
#include <QDateTime>
#include "imcore_global.h"
TNIMUtil::TNIMUtil()
{

}

QString TNIMUtil::getUUID()
{
    QUuid id = QUuid::createUuid();
    QString strId = id.toString();
    strId.remove('{');
    strId.remove('}');

    return strId;
}

QVariantMap TNIMUtil::jsonToMap(const QString& json)
{
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    QVariant vParse = doc.toVariant();
   QVariantMap mapResp = vParse.toMap();
   return mapResp;
}

QString TNIMUtil::mapToJson(QVariantMap& jsonMap)
{
    QJsonDocument doc = QJsonDocument::fromVariant(jsonMap);
    QByteArray baJson = doc.toJson();

    return QString(baJson);
}

qlonglong TNIMUtil::getCurrentTime()
{
	QDateTime curTime = QDateTime::currentDateTime();
	return (qlonglong)curTime.toMSecsSinceEpoch() / 1000;
}

QString TNIMUtil::GetFileFormat(QString& suffix)
{
	static QMap<QString, QString>* formatMap = NULL;
	if (formatMap == NULL)
	{
		formatMap = new QMap<QString, QString>;
		formatMap->insert(".txt", TXTMIME);
		formatMap->insert(".mov", MOVMIME);
		formatMap->insert(".mp4", MP4MIME);
		formatMap->insert(".3gp", GP3MIME);
		formatMap->insert(".pdf", PDFMIME);
		formatMap->insert(".doc", DOCMIME);
		formatMap->insert(".docx", DOCXMIME);
		formatMap->insert(".pdf", PDFMIME);
		formatMap->insert(".xls", XLSMIME);
		formatMap->insert(".xlsx", XLSXMIME);
		formatMap->insert(".ppt", PPTMIME);
		formatMap->insert(".pptx", PPTXMIME);
	}
	
	QString strSuffix = suffix.toLower();
	QMap<QString, QString>::iterator itFind = formatMap->find(strSuffix);
	if (itFind != formatMap->end())
		return itFind.value();
	return  "";
}
