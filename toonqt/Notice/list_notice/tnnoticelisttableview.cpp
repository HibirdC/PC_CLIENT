#include "tnnoticelisttableview.h"
#include <QScrollBar>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QDebug>
#include <QMenu>
#include "TNConfig.h"
#include "TNMessageListAdapter.h"
#include "imcore_global.h"
#include "noticelistmodel.h"
#include "noticelistdelegate.h"

TNNoticeListTableView::TNNoticeListTableView(QWidget *parent)
    : QTableView(parent)
    , _pop_menu(NULL)
{
    initContextMenu();
}

TNNoticeListTableView::~TNNoticeListTableView()
{
    if(_pop_menu){
        delete _pop_menu;
        _pop_menu = NULL;
    }
}

void TNNoticeListTableView::updateGeometries()
{
    QTableView::updateGeometries();
    this->verticalScrollBar()->setSingleStep(10);
}

void TNNoticeListTableView::mousePressEvent(QMouseEvent *event)
{
    return QTableView::mousePressEvent(event);
}

void TNNoticeListTableView::paintEvent(QPaintEvent *e)
{
    return QTableView::paintEvent(e);
}

void TNNoticeListTableView::cancelMenuHover()
{
    QModelIndex q_index = this->indexAt(mapFromGlobal(QCursor::pos()));
    if(q_index.isValid()){
        TNMessageListAdapter* session = (TNMessageListAdapter*)this->model()->data(q_index).toLongLong();
        if(!session)
            return;
        if(!_curHotSessionId.isEmpty() && session->getSessionId() != _curHotSessionId){
            ((NoticeListModel*)this->model())->setBackStatus(_curHotSessionId,TNMessageListAdapter::em_notice_list_normal);
            _curHotSessionId = "";
        }
    }else{
        if(!_curHotSessionId.isEmpty()){
            ((NoticeListModel*)this->model())->setBackStatus(_curHotSessionId,TNMessageListAdapter::em_notice_list_normal);
            _curHotSessionId = "";
        }
    }
}

void TNNoticeListTableView::leaveEvent(QEvent *event)
{
    return QTableView::leaveEvent(event);
}

void TNNoticeListTableView::enterEvent(QEvent *event)
{
    NoticeListDelegate* delegate = (NoticeListDelegate*)this->itemDelegate();
    delegate->setFocuseIn(true);
    return QTableView::enterEvent(event);
}

void TNNoticeListTableView::initContextMenu()
{
    //初始化右键菜单
    _pop_menu = new QMenu();
    LANGUE_TYPE languageIndex = TNConfig::instance()->GetCurrentLangueSet();
    if (languageIndex == TYPE_LANGUE_EN){
        _pop_menu->setObjectName("noticeQmenu");
    }
    _on_top = new QAction(this);
    _no_top = new QAction(this);
    _remove_session = new QAction(this);
    _modify_group_name = new QAction(this);
    _alarm = new QAction(this);
    _noAlarm = new QAction(this);
    _on_top->setText(("置顶"));
    _no_top->setText(("取消置顶"));
    _remove_session->setText(("删除聊天"));
    _modify_group_name->setText(("修改群名称"));
    _alarm->setText(("开启消息提醒"));
    _noAlarm->setText(("消息免打扰"));
    //清除原有菜单
    _pop_menu->addAction(_on_top);
    _pop_menu->addAction(_no_top);
    _pop_menu->addAction(_remove_session);
    _pop_menu->addAction(_modify_group_name);
    _pop_menu->addAction(_noAlarm);
    _pop_menu->addAction(_alarm);

    connect(_on_top, SIGNAL(triggered()), this, SLOT(onTop()));
    connect(_no_top, SIGNAL(triggered()), this, SLOT(onNoTop()));
    connect(_remove_session, SIGNAL(triggered()), this, SLOT(onRemoveSession()));
    connect(_modify_group_name, SIGNAL(triggered()), this, SLOT(onModifyGroupName()));
    connect(_alarm, SIGNAL(triggered()), this, SLOT(onAlarm()));
    connect(_noAlarm, SIGNAL(triggered()), this, SLOT(onNoAlarm()));
}

void TNNoticeListTableView::onTop()
{
    emit seOnTop(_menuOperateIndex);
}

void TNNoticeListTableView::onNoTop()
{
    emit seOnNoTop(_menuOperateIndex);
}

void TNNoticeListTableView::onRemoveSession()
{
    emit seOnRemoveSession(_menuOperateIndex);
}

void TNNoticeListTableView::onModifyGroupName()
{
    emit seOnModifyGroupName(_menuOperateIndex);
}

void TNNoticeListTableView::onAlarm()
{
    emit seOnAlarm(_menuOperateIndex);
}

void TNNoticeListTableView::onNoAlarm()
{
    emit seOnNoAlarm(_menuOperateIndex);
}

void TNNoticeListTableView::contextMenuEvent(QContextMenuEvent *event)
{
    QModelIndex q_index = this->indexAt(event->pos());
    if(q_index.isValid()){
        TNMessageListAdapter* adapter = (TNMessageListAdapter*)this->model()
                                ->data(q_index).toLongLong();
        if(!adapter) return;
        _menuOperateIndex = q_index;
        if(adapter->getBackStatus() != TNMessageListAdapter::em_notice_list_select){
            adapter->setBackStatus(TNMessageListAdapter::em_notice_list_hover);
            _curHotSessionId = adapter->getSessionId();
        }
        switch(adapter->getType()){
        case MSG_BIZ_GROUPCHAT:
            if(adapter->getNoAlarm()){
                _noAlarm->setVisible(false);
                _alarm->setVisible(true);
            }else{
                _noAlarm->setVisible(true);
                _alarm->setVisible(false);
            }
            _modify_group_name->setVisible(true);
            break;
        case MSG_BIZ_SINGLECHAT:
            if(adapter->getNoAlarm()){
                _noAlarm->setVisible(false);
                _alarm->setVisible(true);
            }else{
                _noAlarm->setVisible(true);
                _alarm->setVisible(false);
            }
            _modify_group_name->setVisible(false);
            break;
        default:
            _noAlarm->setVisible(false);
            _alarm->setVisible(false);
            _modify_group_name->setVisible(false);
            break;
        }
        if(adapter->getTopStatus()){
            _on_top->setVisible(false);
            _no_top->setVisible(true);
        }else{
            _on_top->setVisible(true);
            _no_top->setVisible(false);
        }
        _pop_menu->exec(event->globalPos());
        cancelMenuHover();
        NoticeListDelegate* delegate = (NoticeListDelegate*)this->itemDelegate();
        delegate->setFocuseIn(false);
    }
}
