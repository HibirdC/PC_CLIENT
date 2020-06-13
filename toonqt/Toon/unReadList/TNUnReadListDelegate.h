#ifndef TNUNREADLISTDELEGATE_H
#define TNUNREADLISTDELEGATE_H

#include <QStyledItemDelegate>
#include <QAbstractItemView>
#include "common_global.h"

class TNUnReadListDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	TNUnReadListDelegate();

public:
	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	virtual QSize sizeHint(const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	virtual bool helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index);
	//bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index);

private:
	QFont   normalFont;
	QColor  countColor;
	QColor  normalColor;
	QColor  countBrushC;
	QFont   countFont;

	QMap<QString, QPixmap> latestAvatarMap;
};

#endif // TNUNREADLISTDELEGATE_H
