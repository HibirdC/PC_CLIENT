#ifndef TNATSearchListItemDelegate_H
#define TNATSearchListItemDelegate_H

#include "TNAbstractItemDelegate.h"
#include "common_global.h"

class QTableView;
class CGDMainDialog;

class TNATSearchListItemDelegate : public TNAbstractItemDelegate
{
    Q_OBJECT
public:
    TNATSearchListItemDelegate(QAbstractItemView *itemView);

    void setParentWidget(QWidget *parentWidget) { _parentWidget = parentWidget; }

protected:
    QWidget *createItemWidget(const QModelIndex &index) const;
	virtual void setRowHeight(const QModelIndex &index) const;

private:
	QWidget *_parentWidget;
Q_SIGNALS:
	void createWidgetFinished(const QModelIndex& index) const;
};

#endif // TNATSearchListItemDelegate_H
