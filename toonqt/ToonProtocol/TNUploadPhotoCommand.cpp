#include "TNUploadPhotoCommand.h"

#include "TNUtil.h"
#include <QDebug>
#include <QFileDialog>
#include <QApplication>

TNUploadPhotoCommand::TNUploadPhotoCommand(QObject *parent) : TNAbstractToonCommand(parent)
{

}

TNUploadPhotoCommand::~TNUploadPhotoCommand()
{

}

QJsonObject TNUploadPhotoCommand::executeToonCommand(const QJsonObject &inJsonData)
{
	QJsonObject outJsonResult;

    qDebug() << "[ToonProtocol][TNUploadPhotoCommand]executeToonCommand-activeWindow=" << QApplication::activeWindow();
	QString suffixFilter(QStringLiteral("Images (*.png *.jpg *.jpeg *.gif)"));
    QString fileName = QFileDialog::getOpenFileName(TNUtil::getMainWidget(), QStringLiteral("Find File"), QString(), suffixFilter);
    qInfo() << "[ToonProtocol][TNUploadPhotoCommand]executeToonCommand-fileName=" << fileName;
	if (!fileName.isEmpty())
	{
		QFile file(fileName);
		if (file.open(QFile::ReadOnly))
		{
			QJsonObject json;
			qint64 fileSize = file.size();
			json.insert("size", fileSize);
			json.insert("imageType", "jpeg");
			json.insert("base64", QString(file.readAll().toBase64()));
			json.insert("width", "200");
			json.insert("height", "200");

			outJsonResult.insert("data", json);

			file.close();
		}
	}

	return outJsonResult;
}
