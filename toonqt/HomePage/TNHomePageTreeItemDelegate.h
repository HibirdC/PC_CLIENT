#ifndef TNHomePageTreeItemDelegate_H
#define TNHomePageTreeItemDelegate_H

#include <QPushButton>
#include <QStyledItemDelegate>

#include "TNHomePageTreeItem.h"

class TNHomePageTreeItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    TNHomePageTreeItemDelegate();
    ~TNHomePageTreeItemDelegate();

    void setSelectItemId(const QPair<int, int> &selectedItemIds);
    void setButtonStatus(const QModelIndex &index, bool expanded);

public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

protected:
    virtual bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index);

Q_SIGNALS:
    void clickedArrowButton(const QModelIndex &index, bool expanded);
    void clickedItemOtherArea(const QModelIndex &index);

private:
    QScopedPointer<QPushButton> m_pButton;
    QFont   tagFont;

    mutable QMap<QModelIndex, bool> m_buttonStausMap;

    QPair<int, int> m_selectedItemIds;
    bool isSelected(TNHomePageTreeItem *item) const;
};

#endif // TNHomePageTreeItemDelegate_H
