#ifndef TNHomePageTreeItem_H
#define TNHomePageTreeItem_H

#include <QList>
#include <QPoint>
#include <QVariant>

#include "TNHomePageConfigParser.h"

class TNHomePageTreeItem
{
public:
    enum HomePageTreeItemEnum { Invalid = 0, HomePageWeb, AppWeb};

public:
    explicit TNHomePageTreeItem(HomePageTreeItemEnum itemType, const QList<QVariant> &data, TNHomePageTreeItem *parentItem = 0);
    virtual ~TNHomePageTreeItem();

    HomePageTreeItemEnum getItemGrade() const;

    void appendChild(TNHomePageTreeItem *item);
    void removeChild(int row);
    void updateChild(int row, TNHomePageTreeItem *item);

    TNHomePageTreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TNHomePageTreeItem *parentItem() const;

    int getId() const;
    QString getIconFile() const;
    QString getTitle() const;
    QString getUrl() const;

    QList<QVariant> getItemDatas() const;

    QSize getItemSizeHint() const;

    QSize getIconSize() const;
    QPoint getIconPosition() const;
    QString getDefaultIconFile() const;

    QColor getFontColor() const;
    QPoint getTitlePosition() const;

    bool isLastChildItemOfParent() const;

private:
    HomePageTreeItemEnum _itemType;
    QList<TNHomePageTreeItem*> _childItems;
    QList<QVariant> _itemData; // 0: id | 1: iconUrl | 2: title | 3: url

public:
    static QList<QVariant> makeItemDatas(const HomePageInfo &homePageInfo)
    {
        QList<QVariant> itemDatas;
        itemDatas.append(homePageInfo.id);
        itemDatas.append(homePageInfo.iconUrl);
        itemDatas.append(homePageInfo.title);
        itemDatas.append(homePageInfo.url);

        return itemDatas;
    }
    static QList<QVariant> makeItemDatas(const AppInfo &appInfo)
    {
        QList<QVariant> itemDatas;

        itemDatas.append(appInfo.appRegisterId);
        itemDatas.append(appInfo.iconUrl);
        itemDatas.append(appInfo.title);
        itemDatas.append(appInfo.url);

        itemDatas.append(appInfo.frame);
        itemDatas.append(appInfo.companyId_owner);
        itemDatas.append(appInfo.feedId_owner);
        itemDatas.append(appInfo.userId_visitor);
        itemDatas.append(appInfo.feedId_visitor);

        itemDatas.append(appInfo.registerType);
        itemDatas.append(appInfo.appId);

        return itemDatas;
    }

protected:
    TNHomePageTreeItem *_parentItem;

private slots:
    void onAvatarDownLoadFinish(bool success, QString file_path, QString feedID);
private:
    void asynDownloadAvatar(const QString& url, const QString& feedID) const;
};

#endif // TNSEARCHTREEITEMV2_H
