#ifndef TNCARDCASEGROUPCHATDELEGATE_H
#define TNCARDCASEGROUPCHATDELEGATE_H

#include <QStyledItemDelegate>

class TNCardCaseGroupChatDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	explicit TNCardCaseGroupChatDelegate();
	~TNCardCaseGroupChatDelegate();

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

	QMap<QString, QPixmap>latestAvatarMap;
Q_SIGNALS:
	void downLoadAvatar(const QString feedId, const QString &url, int type) const;
};

#endif // TNCARDCASEGROUPCHATDELEGATE_H
