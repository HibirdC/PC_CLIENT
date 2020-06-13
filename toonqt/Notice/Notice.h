#ifndef NOTICE_H
#define NOTICE_H

#include <QPointer>
#include <PluginExportBase.h>
#include "notice_global.h"
#include "NoticeListArea.h"
#include "details_notice/NoticeDetailsArea.h"


class NOTICE_EXPORT Notice : public PluginExportBase
{
	Q_OBJECT
public:
	Notice(TNPluginParamPtr pluginParam, QWidget *parent = 0);
	~Notice();

public:
	QPointer<MenuAreaBase> GetMenu() override;
	QPointer<ListAreaBase> GetList() override;
	QPointer<DetailsAreaBase> GetDetails() override;
	int GetID() override;
	void registerToonCommand() override;

private:
	QPointer<MenuAreaBase> _NoticeMenuArea;
	QPointer<ListAreaBase> _NoticeListArea;
	QPointer <DetailsAreaBase> _NoticeDetailsArea;
	int _ID;
};

extern "C" NOTICE_EXPORT Notice* getMenu(TNPluginParamPtr pluginParam, QWidget *parent);

#endif // NOTICE_H
