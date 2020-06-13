#ifndef TNLISTMODEL_H
#define TNLISTMODEL_H

#include <QAbstractListModel>

#include "common_global.h"

class COMMON_EXPORT TNModelItemBaseV2
{
public:
    TNModelItemBaseV2(){}
    virtual ~TNModelItemBaseV2(){}
};

class COMMON_EXPORT TNListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TNListModel(QObject *parent = 0);
    ~TNListModel();

    qint32 rowCount(const QModelIndex &parent = QModelIndex()) const;
    qint32 columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, qint32 role = Qt::DisplayRole) const;
    QVariant headerData(qint32 section, Qt::Orientation orientation, qint32 role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
	bool insertData(int row, QList<TNModelItemBaseV2*> &listData);
    bool insertData(int row, TNModelItemBaseV2 *data);
    virtual void clearData();

protected:
	QList<TNModelItemBaseV2*> _listItemData;
};

#endif // TNLISTMODEL_H
