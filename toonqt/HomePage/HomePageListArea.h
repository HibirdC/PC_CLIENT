#ifndef HomePageListArea_H
#define HomePageListArea_H

#include "TNDefaultPage.h"
#include "ListAreaBase.h"
#include "LocalStorageCommon.h"
#include "TNHomePageTreeView.h"
#include "TNHomePageTreeModel.h"
#include "TNHttpObtainAppCode.h"
#include "TNHomePageConfigParser.h"
#include "TNHomePageTreeItemDelegate.h"

class HomePageListArea : public ListAreaBase
{
    Q_OBJECT

public:
    HomePageListArea(int id, TNPluginParamPtr pluginParam, QWidget *parent = 0);
    ~HomePageListArea();

    void showNullPage(bool visible);
    void initListWidget(const QList<HomePageInfo> &homePageInfos);

signals:
    void clickedItem(const QString &title, const QString &url);

public slots:
    void slotOnClickedTreeView(const QModelIndex &index);
    void slotClickedArrowButton(const QModelIndex &index, bool expanded);

private:
    TNPluginParamPtr     m_pluginParam;
    TNHomePageTreeView  *m_homePageView;
    TNHomePageTreeModel *m_homePageModel;
    TNHomePageTreeItemDelegate *m_homePageDelegate;

    TNDefaultPage       *m_nullPage;

    void defaultShowFirstItem(TNHomePageTreeItem *root);
    void defaultExpandFirstItem(TNHomePageTreeItem *root);

    void restoreTreeViewExpand();
    QSet<int> m_expandIdSet;
    QPair<int, int> m_selectedItemIds;

    void openAppWeb(TNHomePageTreeItem *item);
    QMap<QString, QPair<QString, QString> > m_feedIdToTitleUrlMap;
    TNHttpObtainAppCodePtr  m_httpObtainAppCode;
};

#endif // HomePageListArea_H
