#ifndef TNFRAMEVIEWER_H
#define TNFRAMEVIEWER_H

#include <QMap>
#include <QObject>
#include <QJsonObject>

#include "TNMVD_global.h"

class TNBizActionResponder;
class TNMVD_EXPORT TNFrameViewer : public QObject
{
    Q_OBJECT

public:
    static TNFrameViewer *instance();
    static void freeInstance();
    explicit TNFrameViewer(QObject *parent = 0);

    // 当为好友申请页时，则isFriendApply==true
    void showFrame(const QString &feedId, const QString &inBelongFeedId = QString::null, bool isFriendApply = false);

private:
    TNBizActionResponder *m_bizActionResponder;

    static TNFrameViewer *m_instance;
};

#endif // TNFRAMEVIEWER_H
