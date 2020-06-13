#ifndef TNSHOWGROUPFRAMECOMMAND_H
#define TNSHOWGROUPFRAMECOMMAND_H

#include "TNAbstractToonCommand.h"

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonDocument>

class TNShowGroupFrameCommand : public TNAbstractToonCommand
{
    Q_OBJECT

public:
    explicit TNShowGroupFrameCommand(QObject *parent = Q_NULLPTR);
    ~TNShowGroupFrameCommand();

    virtual QJsonObject executeToonCommand(const QJsonObject &inJsonData);
};


#endif // TNSHOWGROUPFRAMECOMMAND_H

