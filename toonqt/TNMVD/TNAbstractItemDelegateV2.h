#ifndef TNABSTRACTITEMDELEGATEV2_H
#define TNABSTRACTITEMDELEGATEV2_H

#include <QStyledItemDelegate>

#include "TNMVD_global.h"

class TNMVD_EXPORT TNAbstractItemDelegateV2 : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TNAbstractItemDelegateV2();

public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, 
		const QModelIndex &index) const = 0;
	virtual QSize sizeHint(const QStyleOptionViewItem &option,
		const QModelIndex &index) const = 0;
//signals:
//    void itemClicked(QModelIndex index);
//    void itemDoubleClicked(QModelIndex index);
//
//protected slots:
//	void onItemClicked(QModelIndex index);
//	void onItemDoubleClicked(QModelIndex index);
};

#endif // TNABSTRACTITEMDELEGATEV2_H
