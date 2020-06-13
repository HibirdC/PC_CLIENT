#ifndef MENUBASE_H
#define MENUBASE_H

#include <QWidget>
#include <QPoint>
#include "MenuAreaBase.h"
#include "ListAreaBase.h"
#include "DetailsAreaBase.h"

class COMMON_EXPORT PluginExportBase : public QWidget
{
	Q_OBJECT

public:
	PluginExportBase(TNPluginParamPtr pluginParam, QWidget *parent);
	~PluginExportBase();

	virtual QPointer<MenuAreaBase> GetMenu() = 0;
	virtual QPointer<ListAreaBase> GetList() = 0;
	virtual QPointer<DetailsAreaBase> GetDetails() = 0;
	virtual int GetID() = 0;
	virtual void registerToonCommand() = 0;

protected:
	TNPluginParamPtr _pluginParam;
};

#endif // MENUBASE_H
