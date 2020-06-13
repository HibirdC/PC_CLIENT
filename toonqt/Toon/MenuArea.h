////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	title_widget.h
//
// summary:	Declares the title widget class
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MENUAREA_H
#define MENUAREA_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QVBoxLayout>

#include "PluginExportBase.h"
#include "MenuAreaBase.h"
#include "common_global.h"
#include "TNAvatarChoice.h"

class MenuArea : public QWidget
{
    Q_OBJECT
public:
	explicit MenuArea(TNPluginParamPtr pluginParam, QWidget *parent = 0);
	void translateLanguage();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Loads menu library. </summary>
	///
	/// <remarks>	田恒, 2016/12/12. </remarks>
	///
	/// <param name="button_layout">	[in,out] If non-null, the button layout. </param>
	/// <param name="signal_mapper">	[in,out] If non-null, the signal mapper. </param>
	/// <param name="Dimension">		The dimension. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void LoadMenuLibrary(PluginExportBase *tempMenu, int Dimension);
signals:
	void closeWidget();
	void turnPage(int current_page);
	void doubleClickPage(int current_page);
	void maxMinSet(bool status);

protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void mouseDoubleClickEvent(QMouseEvent*);

public slots:
	void slotTurnPage(int pageIndex);
	void turnPage(QString current_page);
	void doubleClickPage(QString current_page);
	void ChoiceClickedSlot(const QString & type, const QString &feedId, const QString& res, const QString& Avatar);
	void unReadCountSlot(const QString &feedID, int unCount,int type);
	void feedCardUpdateFromCatche(const QString &feedId, 
								  const QString &avatarId, 
								  const QString &name,
								  const QString &subName, 
								  const QString &userId, 
								  const QString &namePy, 
								  int sourceType);
private slots:
	void on_notifyRefresh(int type, QList<UINotifyData> data);
    void slotShowHomePageButton();

private:
	QList<MenuAreaBase *> button_list;
	TNPluginParamPtr _pluginParam;
	QSignalMapper *signal_clickMapper;
	QSignalMapper *signal_doubleClickMapper;
	QVBoxLayout* topLayout;
	QVBoxLayout* centerLayout;
	QVBoxLayout* bottomLayout;
	TNAvatarChoice * _choiceWidget;
	MenuAreaBase * _avatarButton;
	QString _lastestSelectedFeed;
	bool    _isUnReadNotify;  //标识通知未读
	QMap<QString,bool>    _isShowunReadMap;  //标识是否显示未读红点
private:
	void Init();
	void ShowAvatarChoiceWidget(bool isShow);
	bool loadData();
	void InitAvatarChoicePage(int itemCount);
	bool isShowUnReadStatus(const QString &feedId);
};

typedef PluginExportBase* (*GetMyMenu)(TNPluginParamPtr, QWidget *parent);//定义函数指针   

#endif // MENUAREA_H
