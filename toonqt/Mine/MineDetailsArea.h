#ifndef MINEDETAILS_H
#define MINEDETAILS_H

#include "TNWebViewDetailsArea.h"
#include "LocalStorageCommon.h"

class MenuAreaBase;
class MineDetailsArea : public TNWebViewDetailsArea
{
	Q_OBJECT

public:
	MineDetailsArea(int id, TNPluginParamPtr pluginParam, QWidget *parent = 0);
	~MineDetailsArea();

public Q_SLOTS:
	void OnListAreaClickedSlot(const QModelIndex & index);
};

#endif // MINEDETAILS_H
