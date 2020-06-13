#ifndef MINE_H
#define MINE_H

#include <QPointer>

#include "PluginExportBase.h"
#include "mine_global.h"
#include "MineListArea.h"
#include "MineDetailsArea.h"

class MINE_EXPORT Mine : public PluginExportBase
{
	Q_OBJECT
public:
	Mine(TNPluginParamPtr pluginParam, QWidget *parent = 0);
	~Mine();

private:
public:
    QPointer<MenuAreaBase> GetMenu() override;
	QPointer<ListAreaBase> GetList() override;
	QPointer<DetailsAreaBase> GetDetails() override;
	int GetID() override;
	void registerToonCommand() override;

private:
	QPointer<MenuAreaBase> _MineMenuArea;
	QPointer<ListAreaBase> _MineListArea;
    QPointer<DetailsAreaBase> _MineDetailsArea;
	int _ID;
};

extern "C" MINE_EXPORT Mine* getMenu(TNPluginParamPtr pluginParam, QWidget *parent);

#endif // MINE_H
