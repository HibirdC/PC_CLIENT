#ifndef TNGCTREEVIEW_H
#define TNGCTREEVIEW_H

#include <QTreeView>

class TNGCTreeView : public QTreeView
{
	Q_OBJECT

public:
	explicit TNGCTreeView(QWidget *parent = Q_NULLPTR);
	~TNGCTreeView();

protected:
	virtual void updateGeometries();
	void mousePressEvent(QMouseEvent *event);
};

#endif // TNGCTREEVIEW_H
