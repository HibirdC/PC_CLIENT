#include "searchtableview.h"
#include <QScrollBar>

searchTableView::searchTableView(QWidget *parent)
	: QTableView(parent)
{
}

searchTableView::~searchTableView()
{

}
void searchTableView::updateGeometries()
{
	QTableView::updateGeometries();
#ifdef Q_OS_WIN
	this->verticalScrollBar()->setSingleStep(8);
#else
	this->verticalScrollBar()->setSingleStep(8);
#endif
}