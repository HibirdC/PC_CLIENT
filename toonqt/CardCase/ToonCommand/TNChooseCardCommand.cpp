#include "TNChooseCardCommand.h"

#include "TNDbUtil.h"
#include "TNNameSpace.h"
#include "TNSimpleBrowser.h"
#include "TNChooseCardDialog.h"

#include <QDebug>
#include <QFileDialog>
#include <QApplication>

TNChooseCardCommand::TNChooseCardCommand(QObject *parent) : TNAbstractToonCommand(parent)
{

}

TNChooseCardCommand::~TNChooseCardCommand()
{

}

QJsonObject TNChooseCardCommand::executeToonCommand(const QJsonObject &inJsonData)
{
	QJsonObject outJsonResult;

    TNChooseCardDialog chooseCardDialog(false, QApplication::activeWindow());
	chooseCardDialog.setObjectName("chooseCardDialog");
	if (chooseCardDialog.exec() == QDialog::Accepted)
	{
		QString cardFeedId = chooseCardDialog.getCardFeedId();
		QJsonObject json;
		json.insert("feedId", cardFeedId);
		//json.insert("avatarId", "");
		//json.insert("title", "");
		//json.insert("subtitle", "");

		outJsonResult.insert("data", json);
	}

	return outJsonResult;
}
