#include <QUrlQuery>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QProcessEnvironment>
#include <QWebEngineProfile>
#include <QVBoxLayout>
#include <QLabel>

#include "MineDetailsArea.h"
#include "MenuAreaBase.h"
#include "TNMineAdapter.h"

MineDetailsArea::MineDetailsArea(int id, TNPluginParamPtr pluginParam, QWidget *parent)
: TNWebViewDetailsArea(id, pluginParam, parent)
{
    setCurrentPage(2);

}

MineDetailsArea::~MineDetailsArea()
{

}

void MineDetailsArea::OnListAreaClickedSlot(const QModelIndex & index)
{
	TNMineAdapter *adapter = (TNMineAdapter*)index.data().toLongLong();
	if ((adapter == NULL))
		return;

	setCurrentPage(1);
	setTitleNameLabel(adapter->getTitle());

	QString feedId = adapter->getFeedId();
	QString belongId = adapter->getFeedId();
	showFrameH5(feedId, belongId);
}