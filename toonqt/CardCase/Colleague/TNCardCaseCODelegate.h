#ifndef TNCARDCASECODELEGATE_H
#define TNCARDCASECODELEGATE_H

#include <QStyledItemDelegate>

class TNCardCaseCODelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	explicit TNCardCaseCODelegate(QObject *parent);
	~TNCardCaseCODelegate();

public:
	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	virtual QSize sizeHint(const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	virtual bool helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index);
private:
	QFont   companyFont;
	QFont   departFont;
	QFont   staffFont;
	QFont   subTitleFont;
	QColor  companyColor;
	QColor  departNumberColor;
	QColor  subTitleColor;

	QMap<QString, QPixmap>latestAvatarMap;
Q_SIGNALS:
	void downLoadAvatar(const QString feedId, const QString &url, int type) const;
};

#endif // TNCARDCASECODELEGATE_H
