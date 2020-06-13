#include "TNToonCommandManager.h"

#include "httpserver/httpserver.h"
#include <QDebug>
#include <QJsonDocument>

//Q_GLOBAL_STATIC(TNToonCommandManager, toonCommandManager)

TNToonCommandManager *TNToonCommandManager::instance()
{
	static TNToonCommandManager* s_commandManager = NULL;
	if (s_commandManager == NULL)
		s_commandManager = new TNToonCommandManager(QCoreApplication::instance());
	return s_commandManager;
}

TNToonCommandManager::TNToonCommandManager(QObject *parent) : QObject(parent), m_defaultToonCommand(new DefaultToonCommand())
{
	m_server = new 	HttpServer(this);
	if (!m_server->listen(6780))
	{
        qInfo() << "[ToonProtocol][TNToonCommandManager]server-failed";
	}
    qInfo() << "[ToonProtocol][TNToonCommandManager]server-ok";
}

TNToonCommandManager::~TNToonCommandManager()
{

}

void TNToonCommandManager::registerToonCommand(const QString &modulePath, const TNAbstractToonCommandPtr &toonCommand)
{
	m_toonCommandMap[modulePath] = toonCommand;
}

void TNToonCommandManager::executeToonCommand(const QString &modulePath, const QJsonObject &inJsonData)
{
    if (m_toonCommandMap.contains(modulePath))
    {
        QString flagId;
        QJsonObject json = m_toonCommandMap[modulePath]->executeToonCommand(inJsonData);
        if (inJsonData.contains("flagId") && !json.isEmpty()) // 需要传回返回值的一定有flagId
        {
            flagId = QString::number(inJsonData.value("flagId").toDouble(), 'f', 4);
            m_server->setJsonData(flagId, json);
        }
    }
    else
    {
        m_defaultToonCommand->executeToonCommand(inJsonData);
    }
}
