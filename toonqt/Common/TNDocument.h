#ifndef TNDOCUMENT_H
#define TNDOCUMENT_H

#include "common_global.h"

#include <QObject>
#include <QString>
#include <QJsonObject>


Q_DECLARE_METATYPE(QJsonObject)

class COMMON_EXPORT TNDocument : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QJsonObject text MEMBER s_text NOTIFY sendText)

public:
    explicit TNDocument(QObject *parent = nullptr) : QObject(parent) {qRegisterMetaType<QJsonObject>("QJsonObject");}

	void setSendTextText(const QJsonObject &text);

public slots:
    void receiveText(const QString &r_text);

signals:
    void sendText(const QJsonObject &text);
	void sendReceiveText(const QString  &text);

private:
    QJsonObject s_text;
    QString recieve_text;
};

#endif // TNDOCUMENT_H
