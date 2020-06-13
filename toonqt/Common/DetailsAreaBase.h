#ifndef DETAILSAREABASE_H
#define DETAILSAREABASE_H

#include <QWidget>

#include "TNMessageListAdapter.h"
#include "common_global.h"

class COMMON_EXPORT DetailsAreaBase : public QWidget
{
	Q_OBJECT

public:
	DetailsAreaBase(int id=0, QWidget *parent=0);
	~DetailsAreaBase();
	
	int GetID();
Q_SIGNALS:
	void MessageSignal(TNMessageListAdapter messageListAdapter, bool showDetailArea);
	void MessageSignal(int id);
	void SendQuitSignal();

private:
	int _ID;
};

#endif // DETAILSAREABASE_H
