#ifndef MINELISTAREA_H
#define MINELISTAREA_H

#include "ListAreaBase.h"
#include "LocalStorageCommon.h"
#include "TNQListView.h"
#include "TNMineModel.h"
#include "TNMineDelegate.h"
#include "TNHttpObtainFeedList.h"

class MineListArea : public ListAreaBase
{
	Q_OBJECT

public:
    MineListArea(int id, TNPluginParamPtr pluginParam, QWidget *parent = 0);
	~MineListArea();

public slots:
	void feedCardUpdateFromCatche(const QString &feedId, 
								  const QString &avatarId, 
								  const QString &name,
								  const QString &subName, 
								  const QString &userId, 
								  const QString &namePy, 
								  int sourceType);
	void OnListAreaClickedSlot(const QModelIndex & index);
	void onAvatarDownLoadFinish(bool success, QString url, QString feedId);
	void needToDownLoadAvatar(const QString &feedId, const QString &url, int type);
	void on_notifyKeyEventDis(int keyEvent);
	void currentSelectedPage(int page);

private slots:
    void on_notifyRefresh(int, QList<UINotifyData>);
private:
    void loadData();
	void dynamicUpdateFeedInfo(QString feedId, QVector<QString>baseInfo,int type);
	void downLoadAvatar(QString feedId, QString url, bool isOriginal);
	void dynamicUpdateFeedUI(st_FeedPtr feed, int type);
	void downSelected();
	void upSelected();
	void enterSelected();
	void selectedDefaultPage();
Q_SIGNALS:
	void ListMineToDetailEvent(const QModelIndex &index);
	void CloseDetailPage(const QString &feed, const QString &belongFeed);

private:
	TNQListView  *   _MineListWidgt;
	TNMineModel *    _MineModel;
	TNMineDelegate * _MineDelegate;

	TNHttpObtainFeedListPtr _httpObtainFeedList;
	TNPluginParamPtr        _pluginParam;
	QString m_selected;
	int                     _currentSelectedPage;
protected:
	virtual bool eventFilter(QObject *watched, QEvent *event);
};

#endif // MINELISTAREA_H
