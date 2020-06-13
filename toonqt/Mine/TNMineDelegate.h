#ifndef TNMINEDELEGATE_H
#define TNMINEDELEGATE_H

#include <QStyledItemDelegate>

class TNMineDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	TNMineDelegate();
	~TNMineDelegate();

public:
	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	virtual QSize sizeHint(const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	virtual bool helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index);
private:
	QFont   titleFont;
	QFont   subTitleFont;
	QColor  subTitleColor;

	QMap<QString, QPixmap>latestAvatarMap;
Q_SIGNALS:
	void downLoadAvatar(const QString feedId, const QString &url, int type) const;
};

#endif // TNMINEDELEGATE_H
