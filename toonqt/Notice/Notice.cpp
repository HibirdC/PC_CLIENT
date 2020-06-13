#include "Notice.h"
#include "frames/TNFrameViewer.h"
#include "TNSimpleBrowser.h"
#include "emotion/TNEmojiSingleton.h"

#include "TNToonCommandManager.h"
#include "ToonCommand/TNShowGroupFrameCommand.h"
#include "ToonCommand/TNInitiateGroupChatCommand.h"
#include "TNPictureViewerDialog.h"
#include "TNIMCoreClient.h"
Notice::Notice(TNPluginParamPtr pluginParam, QWidget *parent)
:PluginExportBase(pluginParam, parent)
, _ID(MENU_NOTICE_ID)
{
	_NoticeMenuArea = new MenuAreaBase(_ID, (""), MEUNU_SHOW_TYPE_MESSAGE);
	_NoticeMenuArea->setText((""));
	//初始化固定的ui image
	TNEmojiSingleton::GetInstance();
	//默认选中
	_NoticeMenuArea->setCheckable(true);
	_NoticeMenuArea->click();

	_NoticeMenuArea->setObjectName("Menu_Notice");
    _NoticeMenuArea->setToolTip(("通知"));
	_NoticeListArea    = new NoticeListArea(_ID, pluginParam, this);
	_NoticeDetailsArea = new NoticeDetailsArea(_ID, pluginParam, this);

	connect(_NoticeListArea, SIGNAL(ListAreaClicked(const QModelIndex &)), _NoticeDetailsArea,
		SLOT(OnListAreaClickedSlot(const QModelIndex &)));

    connect(_NoticeListArea, SIGNAL(reLoadDetailsData(TNMessageListAdapter*)),
            _NoticeDetailsArea, SLOT(reloadChatDetails(TNMessageListAdapter*)));

    connect(_NoticeListArea, SIGNAL(outlineUpdateUnread(const QString&,int,int)),
            _NoticeDetailsArea, SIGNAL(unReadCountSignal(const QString&,int,int)));

    connect(_NoticeDetailsArea, SIGNAL(reduceUnreadNum(QString,int)),
            _NoticeListArea, SLOT(slotReduceUnreadNum(QString,int)));

    connect(_NoticeDetailsArea, SIGNAL(readSessionUnreadNum(const QString&,int)),
            _NoticeListArea, SLOT(slotUpdateSessionUnreadNum(const QString&,int)));
	
    connect(_NoticeDetailsArea, SIGNAL(activeSessionTop(TNMessageListAdapter, bool, bool, bool, bool, bool)),
        _NoticeListArea, SLOT(slotAppendSessionTop(TNMessageListAdapter, bool, bool, bool, bool, bool)));

	connect(_NoticeDetailsArea, SIGNAL(updateSessionName(QString)),
		_NoticeListArea, SLOT(onUpdateSessionName(QString)));

    connect(_NoticeDetailsArea, SIGNAL(removeSession(TNMessageListAdapter,bool)),
        _NoticeListArea, SLOT(slotRemoveSessionTop(TNMessageListAdapter,bool)));

	connect(_NoticeListArea, SIGNAL(messageNumberChanged(int)),
		_NoticeMenuArea, SLOT(setMessageNumber(int)));
	//手动修改群名称
	connect(_NoticeListArea, SIGNAL(manualModifyGroupName(QString, QString)),
		_NoticeDetailsArea, SLOT(on_manualModifyGroupName(QString, QString)));
	//手动删除会话
	connect(_NoticeListArea, SIGNAL(manualRemoveCurrentSession(const QString&,bool)),
		_NoticeDetailsArea, SLOT(on_manualRemoveCurrentSession(const QString&,bool)));

	//消息声音和闪烁提醒
	connect(_NoticeListArea, SIGNAL(messageNotify(TNMessageListAdapter, bool)),
		_NoticeDetailsArea, SIGNAL(messageNotify(TNMessageListAdapter, bool)));
    //更新会话点击
    connect(_NoticeDetailsArea, SIGNAL(updateSessionClicked(const QModelIndex&)),
            _NoticeListArea, SLOT(onListAreaClicked(const QModelIndex&)));
    //up or down session
    connect(_NoticeDetailsArea, SIGNAL(upOrDownSession(bool)),
            _NoticeListArea,SLOT(slotUpOrDownSession(bool)));

    connect(_NoticeDetailsArea, SIGNAL(updateSessionLastMsg(QString)),
            _NoticeListArea, SLOT(onUpdateSessionLastMsg(QString)));
}

Notice::~Notice()
{
    TNFrameViewer::freeInstance();
    TNSimpleBrowser::freeInstance();
    TNPictureViewerDialog::freeInstance();
}

QPointer<MenuAreaBase> Notice::GetMenu()
{
	return _NoticeMenuArea;
}

QPointer<ListAreaBase> Notice::GetList()
{
	return _NoticeListArea;
}

QPointer<DetailsAreaBase> Notice::GetDetails()
{
	return _NoticeDetailsArea;
}

int Notice::GetID()
{
	return _ID;
}

void Notice::registerToonCommand()
{
    TNToonCommandManager::instance()->registerToonCommand(QString("frame"), TNAbstractToonCommandPtr(new TNShowGroupFrameCommand()));

    TNInitiateGroupChatCommand  *groupChatCommand = new TNInitiateGroupChatCommand();
    connect(groupChatCommand, SIGNAL(sigInitiateGroupChat(QString, QString)), _NoticeListArea, SLOT(slotInitiateGroupChat(QString, QString)));
    TNToonCommandManager::instance()->registerToonCommand(QString("groupChat"), TNAbstractToonCommandPtr(groupChatCommand));

    TNInitiateGroupChatCommand  *groupChatDefaultCommand = new TNInitiateGroupChatCommand();
    connect(groupChatDefaultCommand, SIGNAL(sigInitiateGroupChat(QString, QString)), _NoticeListArea, SLOT(slotInitiateGroupChat(QString, QString)));
    TNToonCommandManager::instance()->registerToonCommand(QString("groupChat/default"), TNAbstractToonCommandPtr(groupChatDefaultCommand));
}

Notice* getMenu(TNPluginParamPtr pluginParam, QWidget *parent)
{
	return new Notice(pluginParam, parent);
}
