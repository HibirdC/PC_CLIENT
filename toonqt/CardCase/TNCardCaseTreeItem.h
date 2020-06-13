#ifndef TNCARDCASETREEITEM_H
#define TNCARDCASETREEITEM_H

#include <QList>
#include <QVariant>

class TNCardCaseTreeItem
{
public:
    enum ColleagueTreeItem {Invalid=0, Company, Department, Staff, Expand, Group, GroupChat};

public:
    explicit TNCardCaseTreeItem(const QList<QVariant> &data, TNCardCaseTreeItem *parentItem = 0);
    virtual ~TNCardCaseTreeItem();

    virtual ColleagueTreeItem getItemGrade() const;

	void appendChild(TNCardCaseTreeItem *item);
	void removeChild(int row);
	void updateChild(int row, TNCardCaseTreeItem *item);

    TNCardCaseTreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
	TNCardCaseTreeItem *parentItem() const;
	void setStatus(bool status){ _secondNodeStatus = status; }
	bool getStatus(){ return _secondNodeStatus; }
	void setTitle(const QList<QVariant> &itemData){ _itemData = itemData; }
private:
    QList<TNCardCaseTreeItem*> _childItems;
    QList<QVariant> _itemData;
	bool            _secondNodeStatus;
protected:
    TNCardCaseTreeItem *_parentItem;
};

#endif // TNCARDCASETREEITEM_H
