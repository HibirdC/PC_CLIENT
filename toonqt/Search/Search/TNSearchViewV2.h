#ifndef TNSEARCHVIEWV2_H
#define TNSEARCHVIEWV2_H

#include <QObject>
#include <QTreeView>
#include "search_global.h"

class SEARCH_EXPORT TNSearchViewV2 : public QTreeView
{
	Q_OBJECT

public:
	explicit TNSearchViewV2(QWidget *parent = Q_NULLPTR);
	~TNSearchViewV2();

private slots :
	void setItemExpanded(const QModelIndex &index, bool expanded);
protected:
	virtual void updateGeometries();
	virtual void mouseDoubleClickEvent(QMouseEvent *event);
	virtual void keyPressEvent(QKeyEvent *event);
};

#endif // TNSEARCHVIEWV2_H
