#ifndef tnsearcharea_H
#define tnsearcharea_H

#include <QWidget>
#include "LocalStorageCommon.h"
#include "../Common/common_global.h"
#include "../LocalStorage/TNDataControlServer.h"
#include "TNSearchAdapter.h"
#include "TNSearchListItemDelegate.h"
#include "tnsearchbottom.h"

namespace Ui {
	class tnsearcharea;
}

class SEARCH_EXPORT tnsearcharea : public QWidget
{
	Q_OBJECT

public:
	explicit tnsearcharea(TNPluginParamPtr param,QWidget *parent = 0);
	~tnsearcharea();
	void setSearchResult(QMap<QString, QList<TNSearchAdapter*>> result);
    void setShowAllResult(const QString &tag, const QMap<QString, QList<TNSearchAdapter*>> &result);
	QMap<TNSearchAdapter*, QString> getSelectedResult()
	{
		return _SelectedResult;
	}
	QMap<QString, QList<TNSearchAdapter*>>  getSearchResult()
	{
		return _SearchResult;
	}
	void setParentparam(int h, int w)
	{
		_parentHeight = h;
		_parentWidth = w;
	}
	void showDialog();
signals:
	void ShowButtonClickedSignal(const QString &tag,const QString &button);
private:
	void InitBottomPage(int tagCount,int itemCount);
private:
	int _parentHeight;
	int _parentWidth;
	Ui::tnsearcharea *ui;
	TNPluginParamPtr  m_pluginParam;
	tnsearchbottom *_SearchAreaBottom;

	QTableView * _SearchlistWidgt;
	TNCardCaseSearchListModel * _listSearchModel;
	TNSearchListItemDelegate *_SearchDelegate;
	QMap<QString,QList<TNSearchAdapter*>> _SearchResult;
	QMap<TNSearchAdapter*, QString> _SelectedResult;
	void DownLoadAvatarForSearch(QString feedId, QString url);
public slots:
	void OnListAreaClickedSlot(const QModelIndex & index);
	void buttonShowAll(const QModelIndex &index, const QString &tagString,const QString &buttonName,bool showType);
	void onItemCreateFinished(const QModelIndex& index, int type);
	void onAvatarDownLoadFinish(bool success, QString url, QString feedId);
};

#endif // tnsearcharea_H
