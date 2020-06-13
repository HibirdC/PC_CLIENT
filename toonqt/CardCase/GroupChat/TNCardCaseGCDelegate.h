#ifndef TNCARDCASEGCDELEGATE_H
#define TNCARDCASEGCDELEGATE_H

#include <QStyledItemDelegate>
#include "common_global.h"

class TNCardCaseGCDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	TNCardCaseGCDelegate(QObject *parent);
	~TNCardCaseGCDelegate();

public:
	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	virtual QSize sizeHint(const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	virtual bool helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index);
private:
	QFont   titleFont;
	QFont   memberFont;
	QColor  memberColor;
Q_SIGNALS:
	void downLoadAvatar(const QString feedId, const QString &url, int type) const;
};

#endif // TNCARDCASEGCDELEGATE_H
