#ifndef TNNOTICELISTTABLEVIEW_H
#define TNNOTICELISTTABLEVIEW_H
#include <QTableView>


class TNNoticeListTableView : public QTableView
{
    Q_OBJECT
public:
    TNNoticeListTableView(QWidget *parent=0);
    ~TNNoticeListTableView();
protected:
    virtual void updateGeometries();
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void paintEvent(QPaintEvent *e);
    virtual void leaveEvent(QEvent *event);
    virtual void enterEvent(QEvent *event);
    virtual void contextMenuEvent(QContextMenuEvent *);
Q_SIGNALS:
    void seOnTop(QModelIndex);
    void seOnNoTop(QModelIndex);
    void seOnRemoveSession(QModelIndex);
    void seOnModifyGroupName(QModelIndex);
    void seOnAlarm(QModelIndex);
    void seOnNoAlarm(QModelIndex);
private Q_SLOTS:
    void onTop();
    void onNoTop();
    void onRemoveSession();
    void onModifyGroupName();
    void onAlarm();
    void onNoAlarm();
private:
    void initContextMenu();
    void cancelMenuHover();
private:
    QMenu*			_pop_menu;
    QAction			*_on_top;
    QAction			*_no_top;
    QAction			*_remove_session;
    QAction			*_modify_group_name;
    QAction		    *_alarm;
    QAction			*_noAlarm;
    QString 		_curHotSessionId;
    QModelIndex		_menuOperateIndex;
};

#endif // TNNOTICELISTTABLEVIEW_H
