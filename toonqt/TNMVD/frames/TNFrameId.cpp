#include "TNFrameId.h"

#include "TNDbUtil.h"
#include "TNDataControlServer.h"

QString TNFrameId::getFrameId(const QString &feedId, const QString &belongFeedId)
{
    QString frame;
    if (feedId.startsWith("gc_"))
    {
        frame = QString("sf");
    }
    else if (TNDataControlServer::GetInstance()->isMySelf(feedId))
    {
        frame = QString("sf");
    }
    else if (TNDbUtil::isFriendRelation(belongFeedId, feedId))
    {
        frame = QString("ff");
    }
    else if (TNDbUtil::isInGroup(belongFeedId, feedId))
    {
        frame = QString("ff");
    }
    else if (TNDbUtil::isColleageRelation(belongFeedId, feedId))
    {
        frame = QString("cf");
    }
    else
    {
        frame = QString("af");
    }

    return frame;
}
