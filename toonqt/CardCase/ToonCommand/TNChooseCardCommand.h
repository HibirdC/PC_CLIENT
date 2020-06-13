#ifndef TNCHOOSECARDCOMMAND_H
#define TNCHOOSECARDCOMMAND_H

#include "TNAbstractToonCommand.h"

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonDocument>

class TNChooseCardCommand : public TNAbstractToonCommand
{
	Q_OBJECT

public:
	explicit TNChooseCardCommand(QObject *parent = Q_NULLPTR);
	~TNChooseCardCommand();

	virtual QJsonObject executeToonCommand(const QJsonObject &inJsonData);

};


#endif // TNCHOOSECARDCOMMAND_H

