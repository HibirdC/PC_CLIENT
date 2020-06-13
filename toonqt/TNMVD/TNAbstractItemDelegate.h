#ifndef TNABSTRACTITEMDELEGATE_H
#define TNABSTRACTITEMDELEGATE_H

#include <QStyledItemDelegate>

#include "TNMVD_global.h"

class TNMVD_EXPORT TNAbstractItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TNAbstractItemDelegate(QAbstractItemView *itemView);

public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, 
		const QModelIndex &index) const;

signals:
    void itemClicked(QModelIndex index);
    void itemDoubleClicked(QModelIndex index);

protected:
    // 创建用于填充指定index的widget。
    virtual QWidget *createItemWidget(const QModelIndex &index) const = 0;
	virtual void setRowHeight(const QModelIndex &index) const;

protected slots:
	void onItemClicked(QModelIndex index);
	void onItemDoubleClicked(QModelIndex index);

protected:
    QAbstractItemView *_itemView;
};

#endif // TNABSTRACTITEMDELEGATE_H
