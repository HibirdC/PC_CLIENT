#ifndef TNSEARCHLISTITEMDELEGATEV2_H
#define TNSEARCHLISTITEMDELEGATEV2_H

#include <QStyledItemDelegate>
#include <QPushButton>

#include "TNSearchTreeItemV2.h"
#include "TNSearchNameItem.h"

class TNSearchListItemDelegateV2 : public QStyledItemDelegate
{
	Q_OBJECT

public:
	TNSearchListItemDelegateV2();
	~TNSearchListItemDelegateV2();

public:
	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	virtual QSize sizeHint(const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	//virtual bool helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index);
	bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index);
	
private:
	void paintTag(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index, TNSearchTreeItemV2 *item) const;
	void paintFriendItem(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index, TNSearchNameItem *item) const;
	void paintTargetAvator(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index, TNSearchNameItem *item) const;
	void paintMyAvator(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index, TNSearchNameItem *item) const;
	void paintColleagueItem(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index, TNSearchNameItem *item) const;
	void paintGroupItem(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index, TNSearchNameItem *item) const;
	void paintGroupChatItem(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index, TNSearchNameItem *item) const;
	void paintNotifyItem(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index, TNSearchNameItem *item) const;
	//void paintFriendToolTip(QHelpEvent *event, QAbstractItemView *view, 
	//	const QStyleOptionViewItem &option, const QModelIndex &index, TNSearchNameItem *item);
	//void paintColleagueToolTip(QHelpEvent *event, QAbstractItemView *view,
	//	const QStyleOptionViewItem &option, const QModelIndex &index, TNSearchNameItem *item);
private:
	QFont   tagFont;
	QColor  tagColor;
	QFont   nameFont;
	QColor  nameColor;
	QFont   nickFont;
	QColor  nickColor;
	QColor  keyColor;
	QScopedPointer<QPushButton> m_pButton;
	QMap<int, bool> m_ButtonStaus;
	QMap<QModelIndex, int> m_ButtonMap;
	int    m_currentType;
Q_SIGNALS:
	void showButtonClickedIntag(QModelIndex, int, bool) const;
	void downLoadAvatar(const QString feedId, const QString &url, int type) const;

public slots:
	void resetShowAllStatus();
};

#endif // TNSEARCHLISTITEMDELEGATEV2_H
