#ifndef SEARCHTABLEVIEW_H
#define SEARCHTABLEVIEW_H

#include <QTableView>

class searchTableView : public QTableView
{
	Q_OBJECT

public:
	searchTableView(QWidget *parent = 0);
	~searchTableView();
protected:
	virtual void updateGeometries();
};

#endif // SEARCHTABLEVIEW_H
