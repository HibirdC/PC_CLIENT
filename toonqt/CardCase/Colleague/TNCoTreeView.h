#ifndef TNCOTREEVIEW_H
#define TNCOTREEVIEW_H

#include <QTreeView>

class TNCoTreeView : public QTreeView
{
	Q_OBJECT

public:
	explicit TNCoTreeView(QWidget *parent = Q_NULLPTR);
	~TNCoTreeView();

protected:
	virtual void updateGeometries();
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void keyPressEvent(QKeyEvent *event);
};

#endif // TNCOTREEVIEW_H
