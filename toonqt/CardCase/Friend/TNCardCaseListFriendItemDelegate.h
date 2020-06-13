#ifndef TNCardCaseListFriendItemDelegate_H
#define TNCardCaseListFriendItemDelegate_H

#include <QStyledItemDelegate>
#include "common_global.h"

class TNCardCaseListFriendItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
	explicit TNCardCaseListFriendItemDelegate();

public:
	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	virtual QSize sizeHint(const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	virtual bool helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index);
private:
	QFont   titleFont;
	QFont   subTitleFont;
	QFont   tagFont;
	QFont   newFriendFont;
	QColor  subTitleColor;

	QMap<QString, QPixmap> latestAvatarMap;
Q_SIGNALS:
	void downLoadAvatar(const QString feedId, const QString &url, int type) const;
};

#endif // TNCardCaseListFriendItemDelegate_H
