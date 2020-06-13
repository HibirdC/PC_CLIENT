#ifndef TNAvatarChoiceListItemDelegate_H
#define TNAvatarChoiceListItemDelegate_H

#include "TNAbstractItemDelegate.h"
#include "common_global.h"

class QTableView;
class CGDMainDialog;

class TNAvatarChoiceListItemDelegate : public TNAbstractItemDelegate
{
    Q_OBJECT
public:
    TNAvatarChoiceListItemDelegate(QAbstractItemView *itemView);

    void setParentWidget(QWidget *parentWidget) { _parentWidget = parentWidget; }

protected:
    QWidget *createItemWidget(const QModelIndex &index) const;
	virtual void setRowHeight(const QModelIndex &index) const;

private:
	QWidget *_parentWidget;
Q_SIGNALS:
	void createWidgetFinished(const QModelIndex& index) const;
	void photoButtonClicked(const QModelIndex& index);
};

#endif // TNAvatarChoiceListItemDelegate_H
