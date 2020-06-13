#include "TNHomePageTreeItem.h"

#include <QSize>
#include <QPoint>
#include <QFile>
#include <QColor>
#include <QStringList>

#include "TNHttpCloudApi.h"
#include "TNUserDataHelper.h"
#include "TNPathUtil.h"
#include "TNNetAvatarDown.h"

TNHomePageTreeItem::TNHomePageTreeItem(HomePageTreeItemEnum itemType, const QList<QVariant> &data, TNHomePageTreeItem *parent) :
    _itemType(itemType), _itemData(data), _parentItem(parent)
{

}

TNHomePageTreeItem::~TNHomePageTreeItem()
{
    qDeleteAll(_childItems);
}

TNHomePageTreeItem::HomePageTreeItemEnum TNHomePageTreeItem::getItemGrade() const
{
    return _itemType;
}

void TNHomePageTreeItem::appendChild(TNHomePageTreeItem *item)
{
    _childItems.append(item);
}

void TNHomePageTreeItem::removeChild(int row)
{
    _childItems.removeAt(row);
}

void TNHomePageTreeItem::updateChild(int row, TNHomePageTreeItem *item)
{
    _childItems[row] = item;
}

TNHomePageTreeItem *TNHomePageTreeItem::child(int row)
{
    return _childItems.value(row);
}

int TNHomePageTreeItem::childCount() const
{
    return _childItems.count();
}

int TNHomePageTreeItem::columnCount() const
{
    return _itemData.count();
}

QVariant TNHomePageTreeItem::data(int column) const
{
    return _itemData.value(column);
}

int TNHomePageTreeItem::row() const
{
    if (_parentItem)
        return _parentItem->_childItems.indexOf(const_cast<TNHomePageTreeItem*>(this));

    return 0;
}

TNHomePageTreeItem *TNHomePageTreeItem::parentItem() const
{
    return _parentItem;
}

int TNHomePageTreeItem::getId() const
{
    Q_ASSERT(_itemData.size()>0);
    return data(0).toInt();
}

QString TNHomePageTreeItem::getIconFile() const
{
    Q_ASSERT(_itemData.size()>1);
    QString iconUrl = data(1).toString();
    //qDebug()<<"iconUrl="<<iconUrl;
    QString feedId = QString("ToonHomePage_") + QUrl(iconUrl).fileName();
    QString avatarFileName;
    if (TNPathUtil::isDownloadedAvatarPhoto(feedId, avatarFileName))
    {
        return avatarFileName;
    }
    else
    {
        asynDownloadAvatar(iconUrl, feedId);
        return getDefaultIconFile();
    }
}

QString TNHomePageTreeItem::getTitle() const
{
    Q_ASSERT(_itemData.size()>2);
    return data(2).toString();
}

QString TNHomePageTreeItem::getUrl() const
{
    Q_ASSERT(_itemData.size()>3);
    return data(3).toString();
}

QList<QVariant> TNHomePageTreeItem::getItemDatas() const
{
    return _itemData;
}

QSize TNHomePageTreeItem::getItemSizeHint() const
{
    QSize size(250, 70);
    if (_itemType == AppWeb)
        size = QSize(250, 46);

    return size;
}

QSize TNHomePageTreeItem::getIconSize() const
{
    QSize size(34, 34);
    if (_itemType == AppWeb)
        size = QSize(22, 22);

    return size;
}

QPoint TNHomePageTreeItem::getIconPosition() const
{
    QPoint pos(24, 15);
    if (_itemType == AppWeb)
        pos = QPoint(34, 12);

    return pos;
}

QString TNHomePageTreeItem::getDefaultIconFile() const
{
    return QStringLiteral(":/sysIcon/Resources/img/sysIcon/windowsicon.png");
}

QColor TNHomePageTreeItem::getFontColor() const
{
    QColor color("#333333");
    if (_itemType == AppWeb)
        color = QColor("#7281A6");

    return color;
}

QPoint TNHomePageTreeItem::getTitlePosition() const
{
    QPoint pos(16, 25);
    if (_itemType == AppWeb)
        pos = QPoint(16, 12);

    return pos;
}

bool TNHomePageTreeItem::isLastChildItemOfParent() const
{
    return (row() == _parentItem->childCount() - 1);
}

void TNHomePageTreeItem::asynDownloadAvatar(const QString& url, const QString& feedID) const
{
    bool isOrigal = false;
    if(feedID.startsWith("gc_"))
    {
        isOrigal = true;
    }
    qInfo() << "[HomePage][TNHomePageTreeItem] asynDownloadAvatar, url: " << url << " feedId:" << feedID;
    TNNetAvatarDown::GetInstance()->DownLoadFeedAvatar(feedID, url,
                                                       TNHttpCloudApi::GetInstance()->GetCloudStoken(TNUserDataHelper::GetInstance()->_pluginParam),
                                                       0, isOrigal);
}

void TNHomePageTreeItem::onAvatarDownLoadFinish(bool success, QString file_path, QString feedID)
{
    if (success)
    {
        //updateAvatarPhoto(m_feedIdToRowMap[feedID], file_path);
    }
}
