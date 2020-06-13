#include "TNShowGroupFrameCommand.h"

#include "frames/TNFrameViewer.h"

#include <QDebug>

TNShowGroupFrameCommand::TNShowGroupFrameCommand(QObject *parent) : TNAbstractToonCommand(parent)
{

}

TNShowGroupFrameCommand::~TNShowGroupFrameCommand()
{

}

QJsonObject TNShowGroupFrameCommand::executeToonCommand(const QJsonObject &inJsonData)
{
    QJsonObject outJsonResult;

    if (inJsonData.contains("feedId"))
    {
        QString groupId = inJsonData["feedId"].toString();
        QString myFeedId = inJsonData["myFeedId"].toString();
        TNFrameViewer::instance()->showFrame(groupId, myFeedId);
    }
    else
    {
        DefaultToonCommand::defaultToonProtocolTipBox();
    }

    return outJsonResult;
}
