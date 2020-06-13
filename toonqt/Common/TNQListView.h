#ifndef TNQLISTVIEW_H
#define TNQLISTVIEW_H

#include <QListView>
#include "common_global.h"

class COMMON_EXPORT TNQListView : public QListView
{
	Q_OBJECT

public:
	TNQListView(QWidget *parent);
	~TNQListView();

protected:
	void mousePressEvent(QMouseEvent *event);
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void updateGeometries();
};

#endif // TNQLISTVIEW_H
