#ifndef TNSEARCHAREAV2_H
#define TNSEARCHAREAV2_H

#include <QWidget>
#include "LocalStorageCommon.h"
#include "../Common/common_global.h"
#include "../LocalStorage/TNDataControlServer.h"
#include "TNSearchAdapter.h"
#include "TNSearchListItemDelegateV2.h"
#include "TNSearchViewV2.h"
#include "TNSearchListModelV2.h"
#include "TNSearchNameItem.h"
#include "TNDefaultPage.h"

namespace Ui {
	class TNSearchAreaV2;
}

class SEARCH_EXPORT TNSearchAreaV2 : public QWidget
{
	Q_OBJECT

public:
	explicit TNSearchAreaV2(TNPluginParamPtr param, QWidget *parent = 0);
	~TNSearchAreaV2();
	enum SearchMode{CardCase,Session};
	void ExcuteSearch(QString text,int searchMode);
	void showDialog();
	void GetSearchResultForSession(const QString &type, const QString &feed, const QString &belongFeed, TNSearchNameItem &resultItem);
	void keyboadEventMgr(int keyEvent);
private:
	Ui::TNSearchAreaV2 *ui;

signals:
	void ClickedSearchItem(const QString &,const QString &, const QString &);
	void resetShowAll();

public slots:
	void needToDownLoadAvatar(const QString &feedId, const QString &url, int type);

private:
	void showNullPage(bool status);
	QMap<QString, QList<TNSearchNameItem *>> _searchResult;
	void DownLoadAvatarForSearch(QString feedId, QString url,bool isOriginal);
	void downSelected();
	void upSelected();
	void enterSelected();

public slots:
	void OnListAreaClickedSlot(const QModelIndex & index);
	void buttonShowAll(const QModelIndex &index, int tag,bool showType);
	void onAvatarDownLoadFinish(bool success, QString url, QString feedId);
	void selectedDefaultPage();

private:
	TNPluginParamPtr  m_pluginParam;
	TNSearchViewV2  * _SearchlistWidgt;
	TNSearchListModelV2 * _listSearchModel;
	TNSearchListItemDelegateV2 *_SearchDelegate;
	TNDefaultPage          *_nullPage;
	int _SearchMode;
	QString _keyText;

protected:
	virtual bool eventFilter(QObject *watched, QEvent *event);
};

#endif // TNSEARCHAREAV2_H
