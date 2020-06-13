#include <QProcessEnvironment>
#include "Mine.h"

Mine::Mine(TNPluginParamPtr pluginParam, QWidget *parent)
:PluginExportBase(pluginParam,parent)
,_ID(MENU_MINE_ID)
, _MineDetailsArea(NULL)
{
	_MineMenuArea = new MenuAreaBase(_ID, (""), MEUNU_SHOW_TYPE_MINE);
    _MineMenuArea->setObjectName("Menu_Mine");
    _MineMenuArea->setCheckable(true);
    _MineMenuArea->setToolTip(tr(QStringLiteral("我的名片").toUtf8().data()));
	_MineDetailsArea = new MineDetailsArea(_ID, pluginParam, this);
    _MineListArea = new MineListArea(_ID, pluginParam, this);

	connect(_MineListArea, SIGNAL(ListMineToDetailEvent(const QModelIndex &)), _MineDetailsArea,
		SLOT(OnListAreaClickedSlot(const QModelIndex &)));
}

Mine::~Mine()
{

}

QPointer<MenuAreaBase> Mine::GetMenu()
{
	return _MineMenuArea;
}

QPointer<ListAreaBase> Mine::GetList()
{
    return _MineListArea;
}

QPointer<DetailsAreaBase> Mine::GetDetails()
{
    return _MineDetailsArea;
}

int Mine::GetID()
{
	return _ID;
}

void Mine::registerToonCommand()
{

}

Mine* getMenu(TNPluginParamPtr pluginParam, QWidget *parent)
{
	return new Mine(pluginParam, parent);
}
