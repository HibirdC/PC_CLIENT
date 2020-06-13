#pragma once

#include <QString>

class TNFrameId
{
public:
    static QString getFrameId(const QString &feedId, const QString &belongFeedId);
};
