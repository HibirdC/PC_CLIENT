#ifndef TNSEARCHTREEITEMV2_H
#define TNSEARCHTREEITEMV2_H

#include <QList>
#include <QVariant>
#include "search_global.h"
class SEARCH_EXPORT TNSearchTreeItemV2
{
public:
	enum SearchTreeItemEnum { Invalid = 0, Type, Name};

public:
	explicit TNSearchTreeItemV2(const QList<QVariant> &data, int itemCount, TNSearchTreeItemV2 *parentItem = 0);
	virtual ~TNSearchTreeItemV2();

	virtual SearchTreeItemEnum getItemGrade() const;

	void appendChild(TNSearchTreeItemV2 *item);
	void removeChild(int row);
	void updateChild(int row, TNSearchTreeItemV2 *item);

	TNSearchTreeItemV2 *child(int row);
	int childCount() const;
	int columnCount() const;
	QVariant data(int column) const;
	int row() const;
	TNSearchTreeItemV2 *parentItem() const;
	void setTitle(const QList<QVariant> &itemData){ _itemData = itemData; }
	void setParent(TNSearchTreeItemV2 *parentItem){ _parentItem = parentItem; }
	int getItemCount(){ return _itemCount; }

private:
	QList<TNSearchTreeItemV2*> _childItems;
	QList<QVariant> _itemData;
	int             _itemCount;
protected:
	TNSearchTreeItemV2 *_parentItem;
};

#endif // TNSEARCHTREEITEMV2_H
