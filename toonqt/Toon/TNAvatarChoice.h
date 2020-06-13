#ifndef TNAVATARCHOICE_H
#define TNAVATARCHOICE_H

#include <QWidget>
#include "ui_TNAvatarChoice.h"
#include "LocalStorageCommon.h"
#include "common_global.h"
#include "Avatar/TNAvatarChoiceAdapter.h"
#include "Avatar/TNAvatarChoiceItem.h"
#include "Avatar/TNChoiceListItemDelegate.h"

class TNAvatarChoice : public QWidget
{
	Q_OBJECT

public:
	TNAvatarChoice(TNPluginParamPtr param, QWidget *parent = 0);
	~TNAvatarChoice();
	void showWidget(bool isShow);
    void setChoiceResult(QList<TNAvatarChoiceAdapter*> result);

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
	Ui::TNAvatarChoice ui;
	TNPluginParamPtr  m_pluginParam;
	QWidget * _tableWidget;
	QTableView * _listWidgt;
	TNAvatarChoiceListModel * _listModel;
	TNAvatarChoiceListItemDelegate *_listDelegate;
	void DownLoadAvatar(QString feedId, QString url);
public slots:
	void OnListClickedSlot(const QModelIndex& index);
	void onItemCreateFinished(const QModelIndex& index);
	void onAvatarDownLoadFinish(bool success, QString url, QString feedId);
signals:
	void ItemClicked(const QString &type, const QString &feed, const QString &resID, const QString &avatarLink);
};

#endif // TNAVATARCHOICE_H
