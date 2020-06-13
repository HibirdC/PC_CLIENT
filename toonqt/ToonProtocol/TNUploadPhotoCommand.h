#ifndef TNUPLOADPHOTOCOMMAND_H
#define TNUPLOADPHOTOCOMMAND_H

#include "TNAbstractToonCommand.h"

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

class TOONPROTOCOL_EXPORT TNUploadPhotoCommand : public TNAbstractToonCommand
{
	Q_OBJECT

public:
	explicit TNUploadPhotoCommand(QObject *parent = Q_NULLPTR);
	~TNUploadPhotoCommand();

	virtual QJsonObject executeToonCommand(const QJsonObject &inJsonData);
};


#endif // TNUPLOADPHOTOCOMMAND_H

