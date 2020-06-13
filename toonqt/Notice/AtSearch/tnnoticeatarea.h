#ifndef TNNOTICEATAREA_H
#define TNNOTICEATAREA_H

#include <qwidget.h>
#include "ui_tnnoticeatarea.h"
#include "LocalStorageCommon.h"
#include "common_global.h"
#include "TNATSearchAdapter.h"
#include "TNATSearchListItemDelegate.h"

class tnnoticeatarea : public QWidget
{
	Q_OBJECT

public:
	tnnoticeatarea(TNPluginParamPtr param, QWidget *parent = 0);
	~tnnoticeatarea();
	void setSearchResult(QList<TNATSearchAdapter*> result);
	TNATSearchAdapter* getSelectedResult()
	{
		return _SelectedResult;
	}
	QList<TNATSearchAdapter*>  getSearchResult()
	{
		return _SearchResult;
	}
	void setParentparam(int h, int w)
	{
		_parentHeight = h;
		_parentWidth = w;
	}
	void setSize(int x, int y){ _WidgeWidth = x; _WidgeHeight = y; }
	void getSize(int &x, int &y){ x = _WidgeWidth; y = _WidgeHeight; }

	void downSelection();
	void upSelection();
	void enterKey();
private:
	Ui::tnnoticeatarea ui;
	int _parentHeight;
	int _parentWidth;
	int _needSelectedItem;
	int _WidgeWidth;
	int _WidgeHeight;

	TNPluginParamPtr  m_pluginParam;

	QTableView * _SearchlistWidgt;
	TNATSearchListModel * _listSearchModel;
	TNATSearchListItemDelegate *_SearchDelegate;
	QList<TNATSearchAdapter*>  _SearchResult;
	TNATSearchAdapter*         _SelectedResult;
	void DownLoadAvatarForNoticeAt(QString feedId, QString url);

	QModelIndex getSelectedModelIndex();
	void setSelected(bool select,int i);
public slots:
	void OnListAreaClickedSlot(const QModelIndex & index);
	void onItemCreateFinished(const QModelIndex& index);
	void onAvatarDownLoadFinish(bool success, QString url, QString feedId);
	void ShowDialog();
signals:
    void ItemClicked(QString text,QString feedId,QString nickName);
};

#endif // TNNOTICEATAREA_H
