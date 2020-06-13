#include "TNGlobalShotCutManagement.h"
#include "qxtglobalshortcut.h"
#include <QDebug>

TNGlobalShotCutManagement * TNGlobalShotCutManagement::instance()
{
    static TNGlobalShotCutManagement instance(nullptr);
    return &instance;
}
TNGlobalShotCutManagement::TNGlobalShotCutManagement(QObject *parent)
    : QObject(parent)
    , m_pScreeShotCut(nullptr)
{
}

TNGlobalShotCutManagement::~TNGlobalShotCutManagement()
{
    if(m_pScreeShotCut){
        delete m_pScreeShotCut;
        m_pScreeShotCut = NULL;
    }
}

void TNGlobalShotCutManagement::setScreenShotKey(const QString &key)
{
    const QKeySequence shortcut(key);
    if (m_pScreeShotCut == nullptr){
        m_pScreeShotCut = new QxtGlobalShortcut(shortcut, this);
        if(!m_pScreeShotCut->isValid()){
            qInfo() << QString("Error: Failed to set shortcut %1").arg(shortcut.toString());
        }
        connect(m_pScreeShotCut, SIGNAL(activated(QxtGlobalShortcut*)), this, SIGNAL(screenShotKeyActived(QxtGlobalShortcut*)));
    }else{
        if(!m_pScreeShotCut->setShortcut(shortcut)){
            qInfo() << QString("Error: Failed to set shortcut %1").arg(shortcut.toString());
        }
    }
}

void TNGlobalShotCutManagement::enableScreenShotKey()
{
    if(m_pScreeShotCut)
        m_pScreeShotCut->setEnabled();
}

void TNGlobalShotCutManagement::disableScreenShotKey()
{
    if(m_pScreeShotCut)
        m_pScreeShotCut->setDisabled();
}
