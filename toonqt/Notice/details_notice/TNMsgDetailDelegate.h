#ifndef CWQMSGDETAILDELEGATE_H
#define CWQMSGDETAILDELEGATE_H

#include <QDateTime>

#include "TNAbstractItemDelegate.h"
#include "TNChatDetailBase.h"

class TNChatDetailBase;

class TNMsgDetailDelegate : public TNAbstractItemDelegate
{
    Q_OBJECT
public:
    explicit TNMsgDetailDelegate(QAbstractItemView *itemView);

    void setParentWidget(TNChatDetailBase *parentWidget);

	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
protected:
    QWidget *createItemWidget(const QModelIndex &index) const;
	virtual void setRowHeight(const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const;
private slots:
	void onAutoHeight(int height, QModelIndex index);
private:
    TNChatDetailBase *_parentWidget;
    QSize			  _size;

Q_SIGNALS:
	void revokeProcessSignal(int resultType, int msgType, qint64 msgTime,const QString & sessionId, const QString &msgId, const QString &pushInfo) const;
	void deleteMsgSignalDelegate(const QString & msgId);
    void jumpMsgSignalDelegate(const QString &msgId);
};

#endif // CWQMSGDETAILDELEGATE_H
