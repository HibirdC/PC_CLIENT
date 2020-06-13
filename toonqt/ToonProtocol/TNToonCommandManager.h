#ifndef TNTOONPCOMMANDMANAGER_H
#define TNTOONPCOMMANDMANAGER_H

#include <QMap>
#include <QObject>
#include <QSharedPointer>

#include "ToonProtocol_global.h"
#include "httpserver/httpserver.h"
#include "TNAbstractToonCommand.h"

class HttpServer;
class TOONPROTOCOL_EXPORT TNToonCommandManager : public QObject
{
	Q_OBJECT

public:
	static TNToonCommandManager *instance();

	explicit TNToonCommandManager(QObject *parent = Q_NULLPTR);
	~TNToonCommandManager();

	void registerToonCommand(const QString &modulePath, const TNAbstractToonCommandPtr &toonCommand);
	void executeToonCommand(const QString &modulePath, const QJsonObject &jsonData);

	HttpServer *server() { return m_server; }

private:
	HttpServer *m_server;
	TNAbstractToonCommandPtr m_defaultToonCommand;
	QMap<QString, TNAbstractToonCommandPtr> m_toonCommandMap;
};

#endif // TNTOONPCOMMANDMANAGER_H

