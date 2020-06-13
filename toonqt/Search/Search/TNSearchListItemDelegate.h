#ifndef TNSearchListItemDelegate_H
#define TNSearchListItemDelegate_H

#include "TNAbstractItemDelegate.h"

#include "common_global.h"
#include "search_global.h"
class QTableView;
class CGDMainDialog;

class SEARCH_EXPORT TNSearchListItemDelegate : public TNAbstractItemDelegate
{
    Q_OBJECT
public:
    TNSearchListItemDelegate(QAbstractItemView *itemView);

    void setParentWidget(QWidget *parentWidget) { _parentWidget = parentWidget; }

protected:
    QWidget *createItemWidget(const QModelIndex &index) const;
private:
	QWidget *_parentWidget;
signals:
	void showButtonClickedIntag(const QModelIndex &index,const QString &tagString,const QString &buttonName, bool showType);
Q_SIGNALS:
	void createWidgetFinished(const QModelIndex& index, int type) const;
	void photoButtonClicked(const QModelIndex& index);
};

#endif // TNSearchListItemDelegate_H
