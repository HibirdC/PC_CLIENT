#ifndef CARDCASE_H
#define CARDCASE_H

#include <QPointer>
#include "cardcase_global.h"
#include "PluginExportBase.h"
#include "CardCaseListArea.h"
#include "CardCaseDetailsArea.h"



class CARDCASE_EXPORT CardCase : public PluginExportBase
{
	Q_OBJECT
public:
	CardCase(TNPluginParamPtr pluginParam, QWidget *parent = 0);
	~CardCase();

public:
	QPointer<MenuAreaBase> GetMenu() override;
	QPointer<ListAreaBase> GetList() override;
	QPointer<DetailsAreaBase> GetDetails() override;
	int GetID() override;
	void registerToonCommand() override;

public slots :
    void on_notifyRefresh(int type, QList<UINotifyData> dataListo);

private slots:
    void slotUpdateNewFriendPage();

private:
	QPointer<MenuAreaBase> _CardCaseMenuArea;
	QPointer<ListAreaBase> _CardCaseListArea;
	QPointer <DetailsAreaBase> _CardCaseDetailsArea;
	int _ID;
};

extern "C" CARDCASE_EXPORT CardCase* getMenu(TNPluginParamPtr pluginParam, QWidget *parent);

#endif // CARDCASE_H
