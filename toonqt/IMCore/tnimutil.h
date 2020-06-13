#ifndef TNIMUTIL_H
#define TNIMUTIL_H
#include <QString>
#include <QVariantMap>

class TNIMUtil
{
public:
    TNIMUtil();

    static QString getUUID();
    static QVariantMap jsonToMap(const QString& json);
    static QString mapToJson(QVariantMap& jsonMap);
	static qlonglong getCurrentTime();
	static QString GetFileFormat(QString& suffix);
};

#endif // TNIMUTIL_H
