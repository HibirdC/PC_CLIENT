#include "HomePageListArea.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QEvent>

#include "TNUtil.h"
#include "TNMessageBox.h"

HomePageListArea::HomePageListArea(int id, TNPluginParamPtr pluginParam, QWidget *parent)
    : ListAreaBase(id, parent)
    , m_pluginParam(pluginParam)
    , m_homePageView(nullptr)
    , m_homePageModel(nullptr)
    , m_homePageDelegate(nullptr)
    , m_nullPage(nullptr)
{
    QVBoxLayout *pMainLayout = new QVBoxLayout();
    pMainLayout->setSpacing(0);
    pMainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(pMainLayout);

    m_homePageView = new TNHomePageTreeView(this);
    m_homePageView->setObjectName("ListArea");
    m_homePageView->setStyleSheet("border: 0;");
    m_homePageView->setAttribute(Qt::WA_MacShowFocusRect, 0);
    m_homePageView->setContentsMargins(0, 0, 0, 0);

    m_homePageDelegate = new TNHomePageTreeItemDelegate();
    m_homePageView->setItemDelegate(m_homePageDelegate);
    m_homePageView->setMouseTracking(true);
    m_homePageView->setHeaderHidden(true);
    m_homePageView->setIndentation(0);
    m_homePageView->setFocus();
    m_homePageView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_homePageView->setSelectionMode(QAbstractItemView::SingleSelection);

    pMainLayout->addWidget(m_homePageView);

    m_nullPage = new TNDefaultPage(this);
    m_nullPage->setObjectName("NULLPageCardCase");
    m_nullPage->setTextTitle(tr((QStringLiteral("暂无主页")).toUtf8().data()));
    m_nullPage->setBackPic("homepagenullico", QSize(52, 50));
    m_nullPage->setVisible(false);

    m_httpObtainAppCode = std::make_shared<TNHttpObtainAppCode>();

    connect(m_homePageDelegate, SIGNAL(clickedArrowButton(QModelIndex, bool)), this, SLOT(slotClickedArrowButton(QModelIndex, bool)));
    connect(m_homePageDelegate, SIGNAL(clickedItemOtherArea(const QModelIndex &)), this, SLOT(slotOnClickedTreeView(const QModelIndex &)));
}

HomePageListArea::~HomePageListArea()
{

}

void HomePageListArea::initListWidget(const QList<HomePageInfo> &homePageInfos)
{
    TNHomePageTreeItem *root = new TNHomePageTreeItem(TNHomePageTreeItem::Invalid, QList<QVariant>()<<QStringLiteral("homepages"));
    foreach (const HomePageInfo &homePageInfo, homePageInfos)
    {
        TNHomePageTreeItem *homePageItem = new TNHomePageTreeItem(TNHomePageTreeItem::HomePageWeb, TNHomePageTreeItem::makeItemDatas(homePageInfo), root);
        root->appendChild(homePageItem);
        foreach (const AppInfo &appInfo, homePageInfo.appInfos)
        {
            TNHomePageTreeItem *appItem = new TNHomePageTreeItem(TNHomePageTreeItem::AppWeb, TNHomePageTreeItem::makeItemDatas(appInfo), homePageItem);
            homePageItem->appendChild(appItem);
        }
    }

    if (m_homePageModel)
    {
        m_homePageModel->resetModel(root);
        if (homePageInfos.size()>0)
        {
            if (TNUtil::isFirstLoginHomePage())
            {
                TNUtil::setIsFirstLoginHomePage(false);
                defaultExpandFirstItem(root);
                defaultShowFirstItem(root);
            }
            else
            {
                restoreTreeViewExpand();
            }
        }
    }
    else
    {
        m_homePageModel = new TNHomePageTreeModel(root, this);
        m_homePageView->setModel(m_homePageModel);
    }
}

void HomePageListArea::slotOnClickedTreeView(const QModelIndex &index)
{
    TNHomePageTreeItem *item = static_cast<TNHomePageTreeItem*>(index.internalPointer());
    if (item)
    {
        if (item->getItemGrade() == TNHomePageTreeItem::HomePageWeb)
        {
            m_selectedItemIds = qMakePair(item->getId(), -1);
            const QString title = item->getTitle();
            const QString url   = item->getUrl();
            emit clickedItem(title, url);
        }
        else
        {
            m_selectedItemIds = qMakePair(item->parentItem()->getId(), item->getId());
            openAppWeb(item);
        }
        m_homePageDelegate->setSelectItemId(m_selectedItemIds);
    }
}

void HomePageListArea::slotClickedArrowButton(const QModelIndex &index, bool expanded)
{
    TNHomePageTreeItem *item = static_cast<TNHomePageTreeItem*>(index.internalPointer());
    if (item)
    {
        // 先把其它的Item都收起
        if (expanded)
        {
            m_expandIdSet.clear();
            TNHomePageTreeItem *parentItem = item->parentItem();
            for (int i=0; i<parentItem->childCount(); ++i)
            {
                TNHomePageTreeItem *curItem = parentItem->child(i);
                if (curItem != item)
                {
                    int row = curItem->row();
                    QModelIndex curIndex(m_homePageModel->index(row, 0));
                    m_homePageView->setExpanded(curIndex, false);
                    m_homePageDelegate->setButtonStatus(curIndex, false);
                }
            }
        }

        // 再把当前的Item展开
        m_homePageView->setExpanded(index, expanded);
        int id = item->getId();
        if (expanded)
            m_expandIdSet.insert(id);
        else
            m_expandIdSet.remove(id);
    }
}

void HomePageListArea::defaultShowFirstItem(TNHomePageTreeItem *root)
{
    // 默认显示第一个Item的Url
    if (root && root->childCount()>0)
    {
        TNHomePageTreeItem *firstItem = root->child(0);
        if (firstItem)
        {
            const QString title = firstItem->getTitle();
            const QString url   = firstItem->getUrl();
            emit clickedItem(title, url);
        }
    }
}

void HomePageListArea::defaultExpandFirstItem(TNHomePageTreeItem *root)
{
    // 默认展开第一个Item
    if (root && root->childCount()>0)
    {
        TNHomePageTreeItem *firstItem = root->child(0);
        if (firstItem && (firstItem->childCount()>0))
        {
            int row = firstItem->row();
            QModelIndex index(m_homePageModel->index(row, 0));
            m_homePageView->setExpanded(index, true);
            m_homePageDelegate->setButtonStatus(index, true);
            m_expandIdSet.insert(firstItem->getId());
        }
    }
}

void HomePageListArea::restoreTreeViewExpand()
{
    TNHomePageTreeItem *rootItem = m_homePageModel->rootItem();
    Q_ASSERT(rootItem);
    if (rootItem == nullptr)
        return;

    // 设置展开
    for (int i=0; i<rootItem->childCount(); ++i)
    {
        TNHomePageTreeItem *hpItem = rootItem->child(i);
        if (hpItem && m_expandIdSet.contains(hpItem->getId()))
        {
            int row = hpItem->row();
            QModelIndex index(m_homePageModel->index(row, 0));
            m_homePageView->setExpanded(index, true);
            m_homePageDelegate->setButtonStatus(index, true);
        }
    }

    // 设置选中
    m_homePageDelegate->setSelectItemId(m_selectedItemIds);
    m_selectedItemIds = qMakePair(-1, -1);
}

void HomePageListArea::openAppWeb(TNHomePageTreeItem *item)
{
    QList<QVariant> itemDatas = item->getItemDatas();
    Q_ASSERT(itemDatas.size() == 11);
    if (itemDatas.size() < 11)
        return;

    const QString title = itemDatas.at(2).toString();
    const QString url   = itemDatas.at(3).toString();
    int registerType = itemDatas.at(9).toInt();
    if (registerType == 1)
    {
        const QString appId = QString::number(itemDatas.at(10).toInt());
        const QString frame = itemDatas.at(4).toString();
        const QString companyId_owner = itemDatas.at(5).toString();
        const QString feedId_owner   = itemDatas.at(6).toString();
        const QString userId_visitor = itemDatas.at(7).toString();
        const QString feedId_visitor = itemDatas.at(8).toString();
        m_feedIdToTitleUrlMap[feedId_owner] = QPair<QString, QString>(title, url);

        auto httpObtainAppCodeFinished = [&](bool success, QString retFeedId, QJsonObject json)
        {
            if (success)
            {
                QString debugText = QJsonDocument(json).toJson();
                qDebug()<<"HomePageListArea::appendCodeForUrl-httpObtainAppCodeFinished-debugText="<<debugText;
                int retCode = json["meta"].toObject().value("code").toInt();
                if (retCode == 0)
                {
                    QString code = json.value("data").toString();
                    if (m_feedIdToTitleUrlMap[retFeedId].second.contains(QChar('?')))
                        m_feedIdToTitleUrlMap[retFeedId].second += ("&code=" + code);
                    else
                        m_feedIdToTitleUrlMap[retFeedId].second += ("?code=" + code);

                    QPair<QString, QString> titleUrlPair = m_feedIdToTitleUrlMap.take(retFeedId);
                    emit clickedItem(titleUrlPair.first, titleUrlPair.second);
                }
                else
                {
                    QString message = json.value("meta").toObject().value("message").toString();
                    TNMessageBox messageBox(QApplication::activeWindow());
                    messageBox.setMsg(message);
                    messageBox.exec();
                }
            }
        };

        qInfo()<<"ObtainAppCode-appId="<<appId<<" frame="<<frame<<" companyId_owner="<<companyId_owner<<" feedId_owner="<<feedId_owner
               <<" userId_visitor="<<userId_visitor<<" feedId_visitor="<<feedId_visitor;
        m_httpObtainAppCode->GetJson(httpObtainAppCodeFinished, m_pluginParam, appId, frame, companyId_owner, feedId_owner, userId_visitor, feedId_visitor);

        //openApp(url);
    }
    else if (registerType == 2)
    {
        emit clickedItem(title, url);
    }
}

void HomePageListArea::showNullPage(bool visible)
{
    Q_ASSERT (m_nullPage);
    int w = m_homePageView->width();
    if (w < 250)
        w = 250;
    int h = m_homePageView->height();
    if (h < 650)
        h = 650;
    int x = (w - m_nullPage->width())/2;
    int y = (h - m_nullPage->height())/2;
    m_nullPage->move(x, y);
    if (visible)
        m_nullPage->show();
    else
        m_nullPage->hide();
}
