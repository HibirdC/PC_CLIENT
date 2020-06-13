#ifndef TNHomePageTreeModel_H
#define TNHomePageTreeModel_H

#include <QObject>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include "TNHomePageTreeItem.h"
#include "TNHomePageTreeView.h"

class TNHomePageTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit TNHomePageTreeModel(TNHomePageTreeItem *rootItem, QObject *parent = 0);
    virtual ~TNHomePageTreeModel();

    TNHomePageTreeItem *rootItem() const;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    void removeItem(const QModelIndex index,int totalItemCount, int type);
    void insertItem(const QModelIndex index, QList<TNHomePageTreeItem *> itemList, int type);
    void resetModel(TNHomePageTreeItem *rootItem);
    QModelIndex getNextIndex(QModelIndex oldIndex);
    QModelIndex getPreIndex(QModelIndex oldIndex);

private:
    TNHomePageTreeItem   * _rootItem;
    QModelIndex           _latestSelectedParent;
};

#endif // TNHomePageTreeModel_H
