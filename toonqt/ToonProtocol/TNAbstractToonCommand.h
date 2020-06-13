#ifndef TNABSTRACTTOONPCOMMAND_H
#define TNABSTRACTTOONPCOMMAND_H

#include <QPair>
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QApplication>
#include <QMessageBox>

#include "ToonProtocol_global.h"
#include "TNMessageBox.h"
#include "TNSimpleBrowser.h"

class TOONPROTOCOL_EXPORT TNAbstractToonCommand : public QObject
{
	Q_OBJECT

public:
	explicit TNAbstractToonCommand(QObject *parent = Q_NULLPTR);
	~TNAbstractToonCommand();

	virtual QJsonObject executeToonCommand(const QJsonObject &inJsonData) = 0;

private:

};

typedef QSharedPointer<TNAbstractToonCommand> TNAbstractToonCommandPtr;

class DefaultToonCommand : public TNAbstractToonCommand
{
	Q_OBJECT

public:
	explicit DefaultToonCommand(QObject *parent = Q_NULLPTR) : TNAbstractToonCommand(parent) {}

	virtual QJsonObject executeToonCommand(const QJsonObject &inJsonData)
	{
		QJsonObject outJsonResult;

        defaultToonProtocolTipBox();

		return outJsonResult;
	}

    static void defaultToonProtocolTipBox()
    {
        QString content(QStringLiteral("暂不支持该功能!"));
        TNMessageBox messageBox(QApplication::activeWindow(), 5 * 1000);
        messageBox.setMsg(content);
        messageBox.exec();
    }
};

class TOONPROTOCOL_EXPORT CheckNetwokCommand : public TNAbstractToonCommand
{
	Q_OBJECT

public:
	explicit CheckNetwokCommand(QObject *parent = Q_NULLPTR) : TNAbstractToonCommand(parent) {}

	virtual QJsonObject executeToonCommand(const QJsonObject &inJsonData)
	{
		QJsonObject outJsonResult;

		QJsonObject json;
		json.insert("typeName", QStringLiteral("WIFI"));
		json.insert("type", "1");
		json.insert("isConnected", "true");

		outJsonResult.insert("data", json);

		return outJsonResult;
	}
};

class TOONPROTOCOL_EXPORT CloseH5WindowCommand : public TNAbstractToonCommand
{
    Q_OBJECT

public:
    explicit CloseH5WindowCommand(QObject *parent = Q_NULLPTR) : TNAbstractToonCommand(parent) {}

    virtual QJsonObject executeToonCommand(const QJsonObject &inJsonData)
    {
        QJsonObject outJsonResult;

        TNSimpleBrowser::getInstance()->slotClose();

        return outJsonResult;
    }
};

#endif // TNABSTRACTTOONPCOMMAND_H

