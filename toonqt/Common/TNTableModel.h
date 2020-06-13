#ifndef TNTABLEMODEL_H
#define TNTABLEMODEL_H

#include <QAbstractTableModel>
#include <QRect>

#include "common_global.h"

class COMMON_EXPORT TNModelItemBase
{
public:
    TNModelItemBase(){}
    virtual ~TNModelItemBase(){}
};

class COMMON_EXPORT TNTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TNTableModel(QObject *parent = 0);
    ~TNTableModel();

    qint32 rowCount(const QModelIndex &parent = QModelIndex()) const;
    qint32 columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, qint32 role = Qt::DisplayRole) const;
    QVariant headerData(qint32 section, Qt::Orientation orientation, qint32 role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
	bool insertData(int row, QList<TNModelItemBase*> &listData);
    bool insertData(int row, TNModelItemBase *data);
    virtual void clearData();
protected:
	QList<TNModelItemBase*> _listItemData;
};

#endif // TNTABLEMODEL_H
