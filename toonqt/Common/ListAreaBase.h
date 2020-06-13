#ifndef LISTAREABASE_H
#define LISTAREABASE_H

#include <QWidget>

#include "TNMessageListAdapter.h"
#include "common_global.h"

class COMMON_EXPORT ListAreaBase : public QWidget
{
	Q_OBJECT

public:
	ListAreaBase(int id, QWidget *parent);
	~ListAreaBase();
	virtual void LoadDefaultPage(){}; 
	virtual void LoadScropUnRead(bool isDoubleC){};

	int GetID();
public Q_SLOTS:
	virtual void OnMessageSlot(TNMessageListAdapter messageListAdapter, bool showDetailArea){};
	virtual void OnUnreadedUpdate(const QString& toFeedId){};
private:
	int _ID;
};

#endif // LISTAREABASE_H
