/*******************************************************************
*  Copyright(c) 2000-2018 syswin
*  All rights reserved.
*
*  文件名称: TNGlobalShotCutManagement.h
*  说明:    全局快捷键管理类
******************************************************************/
#ifndef TNGLOBALSHOTCUTMANAGEMENT_H
#define TNGLOBALSHOTCUTMANAGEMENT_H

#include "common_global.h"
#include <QObject>
class QxtGlobalShortcut;
class COMMON_EXPORT TNGlobalShotCutManagement : public QObject
{
    Q_OBJECT

public:
    static TNGlobalShotCutManagement *instance();
    ~TNGlobalShotCutManagement();
    void setScreenShotKey(const QString &key);
    void disableScreenShotKey();
    void enableScreenShotKey();

private:
    TNGlobalShotCutManagement(QObject *parent);

signals:
    void screenShotKeyActived(QxtGlobalShortcut*);

private:
    QxtGlobalShortcut *m_pScreeShotCut;//截屏快捷键
};

#endif // TNGLOBALSHOTCUTMANAGEMENT_H
