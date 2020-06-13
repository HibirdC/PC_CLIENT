#ifndef TNCARDCASEGROUPDELEGATE_H
#define TNCARDCASEGROUPDELEGATE_H

#include <QStyledItemDelegate>
#include "common_global.h"

class TNCardCaseGroupDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	explicit TNCardCaseGroupDelegate();
	~TNCardCaseGroupDelegate();

public:
	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	virtual QSize sizeHint(const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	virtual bool helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index);
private:
	QFont   titleFont;
	QFont   tagFont;

	QMap<QString, QPixmap>latestAvatarMap;
Q_SIGNALS:
	void downLoadAvatar(const QString feedId, const QString &url, int type) const;
};

#endif // TNCARDCASEGROUPDELEGATE_H
