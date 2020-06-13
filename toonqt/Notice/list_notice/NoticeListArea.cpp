#include <QHBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QCoreApplication>
#include <QDir>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QScrollBar>
#include <QKeyEvent>
#include "tnnoticelisttableview.h"
#include "NoticeListArea.h"
#include "TNDataControlServer.h"
#include "TNPathUtil.h"
#include "TNIMCoreClient.h"
#include "tnnotifycenter.h"
#include "network/tnsendimsg.h"
#include "TNUtil.h"
#include "TNDbUtil.h"
#include "TNQLineEdit.h"
#include "TNDataSearch.h"
#include "Search/TNSearchAreaV2.h"
#include "Search/TNSearchNameItem.h"
#include "TNSimpleBrowser.h"
#include "TNDataStatistics.h"
#include "TNGroupChatCreator.h"
#include "TNHttpObtainGroupChatInfoByGroupChatIdSyn.h"
#include "noticelistdelegate.h"
#include "noticelistmodel.h"
#include "TNDataStatistics.h"
#include "TNInputGroupChatNameDialog.h"
#include "TNUserDataHelper.h"
#include "TNCreateGroupChatDialog.h"
#include "TNDataCache.h"
#include "TNMessageBox.h"
#include "TNNameSpace.h"

NoticeListArea::NoticeListArea(int id, TNPluginParamPtr param, QWidget *parent /* = 0 */)
    : ListAreaBase(id, parent)
    , _listWidgetMessage(NULL)
    , _pNoticelistTable(NULL)
    , _isSelected(false)
    , _pluginParam(param)
    , _searchArea(NULL)
    , _initTime(QDateTime::currentDateTime())
	, _latestUnReadIndex(-1)
	, _latestUnReadIndexTray(-1)
	, _nullPage(nullptr)
    , _nullPageStatus(false)
    , _noticeListDelegate(NULL)
    , _noticeListModel(NULL)
    , _httpObtainFeedList(std::make_shared<TNHttpObtainFeedList>())
    ,_httpObtainGroupInfo(std::make_shared<TNHttpObtainGroupChatInfoByGroupChatId>())
{
    initView();
    connect(_listWidgetMessage, SIGNAL(clicked(const QModelIndex &)), this, SIGNAL(ListAreaClicked(const QModelIndex &)));
    connect(_listWidgetMessage, SIGNAL(doubleClicked(const QModelIndex &)), this, SIGNAL(ListAreaDoubleClicked(const QModelIndex &)));
    //链接通知Menu界面未读消息条数信号
    connect(_noticeListModel, SIGNAL(messageNumberChanged(int)),
            this, SIGNAL(messageNumberChanged(int)));
    //链接通知Menu界面未读消息红点信号
    connect(_noticeListModel, SIGNAL(outlineUpdateUnread(const QString&,int,int)),
            this,SIGNAL(outlineUpdateUnread(const QString&,int,int)));
	//通知Tray未读列表
    connect(_noticeListModel, SIGNAL(outlineUpdateUnreadTray(TNMessageListAdapter, int)),
		this, SIGNAL(outlineUpdateUnreadTray(TNMessageListAdapter, int)));
	//手动设置免打扰、取消免打扰 通知Tray
    connect(_noticeListModel, SIGNAL(manualNoAlarmNotifyTray(const QString &, bool, int)),
		this, SIGNAL(manualNoAlarmNotifyTray(const QString &, bool, int)));
    connect(_listWidgetMessage,SIGNAL(seOnAlarm(QModelIndex)),
            this,SLOT(onManualOnAlarm(QModelIndex)));
    connect(_listWidgetMessage,SIGNAL(seOnNoAlarm(QModelIndex)),
            this,SLOT(onManualNoAlarm(QModelIndex)));
    //置顶
    connect(_listWidgetMessage,SIGNAL(seOnTop(QModelIndex)),
            this,SLOT(onManualOnTop(QModelIndex)));
    //取消置顶
    connect(_listWidgetMessage,SIGNAL(seOnNoTop(QModelIndex)),
            this,SLOT(onManualNoTop(QModelIndex)));
    //更改群聊名称
    connect(_noticeListModel, SIGNAL(manualModifySessionName(QString, QString)),
        this, SIGNAL(manualModifyGroupName(QString, QString)));
    connect(_listWidgetMessage,SIGNAL(seOnModifyGroupName(QModelIndex)),
              this,SLOT(onModifyGroupName(QModelIndex)));
    //手动删除会话
    connect(_noticeListModel, SIGNAL(manualRemoveCurSession(const QString&,bool)),
		this, SIGNAL(manualRemoveCurrentSession(const QString&,bool)));
    connect(_noticeListModel, SIGNAL(manualRemoveCurSession(const QString&,bool)),
        this, SLOT(slotRemoveSession(const QString&, bool)));
    connect(_listWidgetMessage, SIGNAL(seOnRemoveSession(QModelIndex)),
            this,SLOT(onManualDelSession(QModelIndex)));

    TNNotifyCenter::instance()->connectNotifySendForward(this);
    TNNotifyCenter::instance()->connnectNotifyCreateGroupChatFinished(this);
	TNNotifyCenter::instance()->connectNotifyKeyEventDis(this);

    _searchWidget->installEventFilter(this);
    _searchLineEdit->installEventFilter(this);
    _createGroupChatButton->installEventFilter(this);
    _listWidgetMessage->installEventFilter(this);
    //离线消息,如果选中详情区更新消息
    connect(_noticeListModel, SIGNAL(reLoadDetailsModel(TNMessageListAdapter*)),
        this, SIGNAL(reLoadDetailsData(TNMessageListAdapter*)));
    connect(_noticeListModel, SIGNAL(reSelectOutLine(TNMessageListAdapter,bool,bool,bool,bool,bool)),
            this, SLOT(slotAppendSessionTop(TNMessageListAdapter,bool,bool,bool,bool,bool)));
    //默认背景
    connect(_noticeListModel,SIGNAL(showDefaultBack()),
            this,SLOT(onShowDefaultBackGround()));
    _updateTimer = new QTimer(this);
    connect(_updateTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
    _updateTimer->start(1000);
}

NoticeListArea::~NoticeListArea()
{
    if (_noticeListModel!= NULL){
        delete _noticeListModel;
        _noticeListModel = NULL;
    }
    if (_listWidgetMessage != NULL){
        delete _listWidgetMessage;
        _listWidgetMessage = NULL;
    }
    if (_noticeListDelegate!= NULL){
        delete _noticeListDelegate;
        _noticeListDelegate = NULL;
    }
	if (_nullPage != nullptr)
	{
		delete _nullPage;
		_nullPage = NULL;
	}
    TNSendIMsg::releaseInstance();
}

void NoticeListArea::initView()
{
    _searchWidget = new QWidget(this);
    _searchWidget->setObjectName("searchWidget");
	_searchLineEdit = new QSearchLineText(this);
    _searchLineEdit->setObjectName("noticeSearch");
    _searchWidget->setContentsMargins(0,0,0,0);

    _createGroupChatButton = new QPushButton(this);
    _createGroupChatButton->setObjectName("createGroupChatButton");
    _createGroupChatButton->setText("");
    _createGroupChatButton->setFixedSize(26, 26);
	_createGroupChatButton->setCursor(Qt::PointingHandCursor);
    _createGroupChatButton->setFlat(true);
    connect(_createGroupChatButton, SIGNAL(clicked()), this, SLOT(slotCreateGroupChat()));

    QHBoxLayout *pLayout = new QHBoxLayout();
    pLayout->addWidget(_searchLineEdit);
    pLayout->addStretch();
    pLayout->addWidget(_createGroupChatButton);
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(15, 20, 15, 0);
    _searchWidget->setLayout(pLayout);
    connect(_searchLineEdit, SIGNAL(textChanged(QString)), this, SLOT(slotSearch(QString)));

    _listWidgetMessage = new TNNoticeListTableView(this);
    _listWidgetMessage->setShowGrid(false);//不显示格子线
    _listWidgetMessage->setObjectName("Notice_ListArea");
    _listWidgetMessage->setSelectionBehavior(QAbstractItemView::SelectItems);
    _listWidgetMessage->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    _listWidgetMessage->setEditTriggers(QAbstractItemView::AllEditTriggers);

    _noticeListDelegate = new NoticeListDelegate();
    _noticeListModel = new NoticeListModel();
    _listWidgetMessage->setModel(_noticeListModel);
    _listWidgetMessage->setItemDelegate(_noticeListDelegate);
    //im赋值
    TNSendIMsg::getInstance()->setListMsgModel(_noticeListModel);
    ///////

    _listWidgetMessage->verticalHeader()->setDefaultSectionSize(LIST_AREA_HEIGHT);
    _listWidgetMessage->horizontalHeader()->setDefaultSectionSize(LIST_AREA_WIDTH);
    _listWidgetMessage->horizontalHeader()->setVisible(false);// 水平不可见
    _listWidgetMessage->verticalHeader()->setVisible(false);// 垂直不可见
    QVBoxLayout *main_layout = new QVBoxLayout( this );
    main_layout->addWidget(_searchWidget);
    main_layout->addWidget(_listWidgetMessage);
#ifndef Q_OS_WIN
    main_layout->setSpacing(0);
#else
    main_layout->setSpacing(10);
#endif
    main_layout->setContentsMargins(0, 0, 0, 0);

    this->setLayout(main_layout);
    this->_listWidgetMessage->setStyleSheet("border: none");
    //Search Area
    _searchArea = new TNSearchAreaV2(_pluginParam,this);
    _searchArea->hide();
    _searchArea->setObjectName("tnsearcharea");
    connect(_searchArea, SIGNAL(ClickedSearchItem(const QString &, const QString &, const QString &)),
            this, SLOT(searchClickedSlot(const QString &, const QString &, const QString &)));

	_nullPage = new TNDefaultPage(this);
	_nullPage->hide();
	_nullPage->setObjectName("NULLPageNoticeList");
    _nullPage->setTextTitle(("还没有消息，去看看别的吧！"));
    _nullPage->setBackPic("noticelistnullico", QSize(51, 51));
}

void NoticeListArea::init()
{
    _noticeListModel->init_data();
    //更新session,离线消息启动时更新
    TNNotifyCenter::instance()->connectNotifyRefreshSession(this);
}
void NoticeListArea::initLocalSession()
{
	init();
}
void NoticeListArea::on_NotifySendForward(QList<TNMessageListAdapter> msgListAdapter)
{
    for (int i = 0; i < msgListAdapter.size(); i++){
        bool isSendToCurrentGroupChat = false;
        //是否向当前群聊转发消息
        if (msgListAdapter[i].getSessionId() == _currentSessionID){
            isSendToCurrentGroupChat = true;
        }
        slotAppendSessionTop(msgListAdapter[i], isSendToCurrentGroupChat, true);
    }
}

void NoticeListArea::slotAppendSessionTop(TNMessageListAdapter messageAdapter,
    bool isSelected /* = false */,
    bool isSend /* = false */,
    bool isActive,
    bool isOnLine,
    bool isBubble)
{
    if(!messageAdapter.isValid()){
        qInfo() << "[Notice] [NoticeListArea] slotAppendSessionTop adapter is not valid";
        qInfo() << "[Notice] [NoticeListArea] slotAppendSessionTop adapter sessionId:" <<
                   messageAdapter.getSessionId() << " myFeedId:" << messageAdapter.getMyFeedId()
                << " toFeedId:" << messageAdapter.getToFeed() << " type:" << messageAdapter.getType();
        return;
    }
    //设置备注
    if(messageAdapter.getType() == MSG_BIZ_SINGLECHAT){
        Q_ASSERT(!messageAdapter.getMyFeedId().isEmpty());
        Q_ASSERT(!messageAdapter.getToFeed().isEmpty());
        //单聊需要备注
        QString remark = TNDataCache::GetInstance()->getFriendFeedReMark(messageAdapter.getToFeed(),messageAdapter.getMyFeedId());
        messageAdapter.setRemark(remark);
    }
    //////////////////
    messageAdapter.setActive(isActive);
    QString qs_log = "[Notice] [NoticeListArea] slotAppendSessionTop begin...";
    qInfo() << qs_log;
    TNMessageListAdapter* topItemData = NULL;
    int row = -1;
    qs_log = "[Notice] [NoticeListArea] slotAppendSessionTop isTop begin...";
    qInfo() << qs_log;
	if (!isSelected && !isSend && 
		!messageAdapter.getNoAlarm()){
		//收到新消息,重新开始滚动
		_latestUnReadIndex = -1;
		_latestUnReadIndexTray = -1;
	}
    bool bAutoAdd = true;
    if (isSend || !isOnLine){
        bAutoAdd = false;
    }
    if (_noticeListModel->isTop(messageAdapter, &topItemData, row,
        isSelected, bAutoAdd, isSend, isBubble)){
        Q_ASSERT(topItemData);
        QModelIndex index = _noticeListModel->index(row, 0);
        if (isSelected){
            qs_log = "[Notice] [NoticeListArea] slotAppendSessionTop isTop  clicked begin...";
            qInfo() << qs_log;
            _noticeListModel->setSessionUnSelected(_currentSessionID);
            emit _listWidgetMessage->clicked(index);
            qs_log = "[Notice] [NoticeListArea] slotAppendSessionTop isTop  clicked end...";
            qInfo() << qs_log;
        }
        //发送消息提醒信号,如果没有开启消息免打扰
		messageAdapter.setNoAlarm(topItemData->getNoAlarm());
		messageAdapter.setUnreadCount(topItemData->getUnreadCount());
        if ((!messageAdapter.getNoAlarm() || messageAdapter.getIsAtMe()) && !isSend && (!isSelected || (isSelected && !isActive)) && isBubble)
			emit messageNotify(messageAdapter,false);
        qs_log = "[Notice] [NoticeListArea] slotAppendSessionTop is top end.";
        qInfo() << qs_log;
        return;
    }
    qs_log = "[Notice] [NoticeListArea] slotAppendSessionTop is not top.";
    qInfo() << qs_log;
    int insert_index = _noticeListModel->prependData(messageAdapter, &topItemData,
        isSelected, bAutoAdd, isSend, isBubble);//置顶
    qs_log = "[Notice] [NoticeListArea] slotAppendSessionTop prependData end.";
    qInfo() << qs_log;
    //发送消息提醒信号,如果没有开启消息免打扰(@除外)
	messageAdapter.setNoAlarm(topItemData->getNoAlarm());
	messageAdapter.setUnreadCount(topItemData->getUnreadCount());
	if ((!messageAdapter.getNoAlarm() || messageAdapter.getIsAtMe()) && !isSend
        && (!isSelected || (isSelected && !isActive)) && isBubble)
		emit messageNotify(messageAdapter, false);
    ///////////////////////////////////////
    //滚动条滚动到具体消息条数
    if (isSelected){
        QModelIndex qindex = _noticeListModel->index(insert_index, 0);
        _noticeListModel->setSessionUnSelected(_currentSessionID);
        emit _listWidgetMessage->clicked(qindex);
        _listWidgetMessage->scrollTo(qindex);
    }
    qs_log = "[Notice] [NoticeListArea] slotAppendSessionTop end.";
    qInfo() << qs_log;
}

void NoticeListArea::slotRemoveSessionTop(TNMessageListAdapter MessageAdapter,bool isSelected)
{
    QString qs_log = "[Notice] [NoticeListArea] slotRemoveSessionTop begin...";
    qInfo() << qs_log;
    //_noticeListModel->removeRowBySessionId(MessageAdapter.getSessionId());
    _noticeListModel->removeSession(MessageAdapter.getSessionId(),isSelected);
    if(isSelected)
        _currentSessionID = "";
    qs_log = "[Notice] [NoticeListArea] slotRemoveSessionTop end.";
    qInfo() << qs_log;
}

void NoticeListArea::OnMessageSlot(TNMessageListAdapter messageListAdapter, bool showDetailArea)
{
    Q_UNUSED(showDetailArea);
    slotAppendSessionTop(messageListAdapter, true, true);//删除所在行,然后在top添加新的一行

    QWidget *mainWindow = TNUtil::getMainWidget();
    if (!mainWindow->isMaximized())
        mainWindow->showNormal();
    else
        mainWindow->showMaximized();
    mainWindow->raise();
    mainWindow->activateWindow();
}

void NoticeListArea::slotInitiateGroupChat(const QString &belongFeedId, const QString &groupChatId)
{
    qInfo() << "[Notice] [NoticeListArea] slotInitiateGroupChat-belongFeedId="
          << belongFeedId << " groupChatId=" << groupChatId;
    Q_ASSERT (!belongFeedId.isEmpty());
    Q_ASSERT (groupChatId.startsWith("gc_"));

    TNSimpleBrowser::getInstance()->hide();

    emit activeMenu(MENU_NOTICE_ID);

    QString from = belongFeedId;
    QString to   = groupChatId;
    QString groupChatName;
    QString avatarUrl;

    st_GroupInfoPtr  groupInfo = TNDbUtil::getGroupChatInfo(groupChatId);
    if (groupInfo)
    {
        qInfo() << "[Notice] [NoticeListArea] slotInitiateGroupChat-db";
        groupChatName = groupInfo->GetName();
        avatarUrl = groupInfo->GetHeaderImage();
    }
    else
    {
        qInfo() << "[Notice] [NoticeListArea] slotInitiateGroupChat-http";
        TNHttpObtainGroupChatInfoByGroupChatIdSyn obtainGroupChatInfoByGroupChatIdSyn;
        if (obtainGroupChatInfoByGroupChatIdSyn.obtainGroupChatInfo(_pluginParam, groupChatId.mid(3)))
        {
            groupChatName = obtainGroupChatInfoByGroupChatIdSyn.getGroupChatName();
            avatarUrl = obtainGroupChatInfoByGroupChatIdSyn.getGroupChatHeadImage();
        }
    }
    Q_ASSERT (!groupChatName.isEmpty());
    Q_ASSERT (!avatarUrl.isEmpty());
    if (groupChatName.isEmpty() || avatarUrl.isEmpty())
    {
        qCritical() << "[Notice] [NoticeListArea]" << Q_FUNC_INFO <<
                       "error! groupChatName or avatarUrl is empty";
        return;
    }

    QString sessionId = TNIMCoreClient::GetSessionId(from, to, MSG_BIZ_GROUPCHAT);
    TNMessageListAdapter messageListAdapter(sessionId, MSG_BIZ_GROUPCHAT);
    messageListAdapter.setName(groupChatName);
    messageListAdapter.setMyFeedId(from);
    messageListAdapter.setToFeed(to);
    messageListAdapter.setAvatarPhotoUrl(avatarUrl);
    QDateTime curTime = QDateTime::currentDateTime();
    messageListAdapter.setTime(curTime.toTime_t());

    slotAppendSessionTop(messageListAdapter, true, true);
}

void NoticeListArea::slotCreateGroupChatFromMenuArea(TNMessageListAdapter adpter)
{
    emit activeMenu(MENU_NOTICE_ID);
    slotAppendSessionTop(adpter, true, true);
}

void NoticeListArea::onListAreaClicked(const QModelIndex& index)
{
    //获取选中行的model数据
    TNMessageListAdapter *adapter = (TNMessageListAdapter*)index.data().toLongLong();
    if (adapter != NULL){
        setItemUnSelected();//反选
        adapter->setBackStatus(TNMessageListAdapter::em_notice_list_select);
        if(adapter->getActive()){
            //设置已读标记,更新数据库,未读条数设为0
            if(adapter->getUnreadCount() > 0){
                TNIMCoreClient::GetIMClient()->ReadSession(adapter->getSessionId());
                adapter->setUnreadCount(0);
            }
            ////////////////////////////////////////////////////////////////////
        }
        if(_currentSessionID == adapter->getSessionId()){//点击当前选中会话
            return;
        }
        //手动更新头像
        if(adapter->getType() == MSG_BIZ_SINGLECHAT){
            dynamicUpdateFeedInfo(adapter->getToFeed());
        }else if(adapter->getType() == MSG_BIZ_GROUPCHAT){
            dynamicUpdateGroupChatInfo(adapter->getSessionId());
        }
        _currentSessionID = adapter->getSessionId();

        if (!adapter->getNoAlarm())
            emit _noticeListModel->updateTotalUnread();
		emit updateTrayUnRead(adapter->getSessionId());
    }
}

void NoticeListArea::OnUnreadedUpdate(const QString& sessionId)
{
    _noticeListModel->incrementUnreadCount(sessionId);
}

void NoticeListArea::on_notifyRefresh(QStringList sList)
{
    _noticeListModel->incrementalSession(sList);
}

void NoticeListArea::onUpdateSessionName(QString sessionId)
{
    TableBaseVec tableVec;
    TNDataControlServer::GetInstance()->Query(tableVec, "GroupInfo", "groupId", sessionId,DBTYPE_USER);
    if (!tableVec.empty()){
        st_GroupInfoPtr groupInfo = std::dynamic_pointer_cast<st_GroupInfo>(*tableVec.begin());
        if(groupInfo.get() != NULL)
			/*
			通知Tray
			*/
			emit manualModifySessionNameToTray(sessionId, groupInfo->GetName());
            _noticeListModel->updateSessionName(sessionId, groupInfo->GetName());
    }
}

void NoticeListArea::setItemUnSelected()
{
    QModelIndex q_index = getSelectedModelIndex();
    if(!q_index.isValid()) return;
    TNMessageListAdapter* session = (TNMessageListAdapter*)_noticeListModel->data(q_index).toLongLong();
    if(session){
        session->setBackStatus(TNMessageListAdapter::em_notice_list_normal);
        emit _noticeListModel->dataChanged(q_index,q_index);
    }
}

void NoticeListArea::onManualOnTop(QModelIndex q_index)
{
    //卖点
    TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_Notice_SetTop,
        TNUserDataHelper::GetInstance()->_pluginParam);

    _noticeListModel->manulOnTopSession(q_index);
    TNMessageListAdapter* session = (TNMessageListAdapter*)_noticeListModel->data(q_index).toLongLong();
    TNMessageListAdapter* topItemData = NULL;
    bool isSelect = session->getBackStatus() == TNMessageListAdapter::em_notice_list_select;
    int insert_index = _noticeListModel->prependData(*session, &topItemData,
        isSelect,false, true);//置顶
	if (topItemData != NULL && topItemData->getUnreadCount() > 0){
		_latestUnReadIndex = -1;
		_latestUnReadIndexTray = -1;
	}
    //滚动条滚动到顶部
    if (isSelect){
        QModelIndex qindex = _noticeListModel->index(insert_index, 0);
        _listWidgetMessage->scrollTo(qindex);
    }
}

void NoticeListArea::onManualNoTop(QModelIndex q_index)
{
    TNMessageListAdapter* session = (TNMessageListAdapter*)_noticeListModel->data(q_index).toLongLong();
    int insert_index = _noticeListModel->manulCancelTopSession(q_index);
    if(insert_index == -1){
        return;
    }
    if (session->getUnreadCount() > 0){
        _latestUnReadIndex = -1;
        _latestUnReadIndexTray = -1;
    }
    //滚动条滚动到相应的index
    bool isSelect = session->getBackStatus() == TNMessageListAdapter::em_notice_list_select;
    if (isSelect){
        _listWidgetMessage->scrollTo(_noticeListModel->index(insert_index,0));
    }
}

void NoticeListArea::onManualOnAlarm(QModelIndex q_index)
{
    //消息提醒
    TNMessageListAdapter* session = (TNMessageListAdapter*)_noticeListModel->data(q_index).toLongLong();
    Q_ASSERT(session);
    switch (session->getType())
    {
    case MSG_BIZ_SINGLECHAT:
        setSigleChatAlarmStatus(session,false);
        break;
    case MSG_BIZ_GROUPCHAT:
        setGroupChatAlarmStatus(session,false);
        break;
    default:
        break;
    }
}

void NoticeListArea::onManualNoAlarm(QModelIndex q_index)
{
    //消息免打扰
    //埋点
    TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_Notice_Disturb,
        TNUserDataHelper::GetInstance()->_pluginParam);
    TNMessageListAdapter* session = (TNMessageListAdapter*)_noticeListModel->data(q_index).toLongLong();
    Q_ASSERT(session);
    switch (session->getType())
    {
    case MSG_BIZ_SINGLECHAT:
        setSigleChatAlarmStatus(session,true);
        break;
    case MSG_BIZ_GROUPCHAT:
        setGroupChatAlarmStatus(session,true);
        break;
    default:
        break;
    }
}

void NoticeListArea::onManualDelSession(QModelIndex q_index)
{
    _noticeListModel->removeSession(q_index);
}

void NoticeListArea::onModifyGroupName(QModelIndex q_index)
{
    //埋点
    TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_Notice_ChangeGroup,
        TNUserDataHelper::GetInstance()->_pluginParam);

    TNMessageListAdapter* session = (TNMessageListAdapter*)_noticeListModel->data(q_index).toLongLong();
    Q_ASSERT(session);

    TNInputGroupChatNameDialog inputGroupChatNameDialog;
    inputGroupChatNameDialog.setObjectName("inputGroupChatNameDialog");
    TNUtil::moveCenterInMainWidget(&inputGroupChatNameDialog);
    if (inputGroupChatNameDialog.exec() == QDialog::Accepted){
        QString changeGroupName = inputGroupChatNameDialog.getGroupChatName();
        inputGroupChatNameDialog.close();
        //修改群聊名称接口

        st_FeedPtr stFeedInfo;
        TNUserDataHelper::GetInstance()->GetFeedInfo(session->getMyFeedId(), stFeedInfo);
        if(stFeedInfo.get() == NULL){
            return;
        }
        //扩展参数传入回调
        std::vector<QVariant> extern_params;
        extern_params.push_back(session->getSessionId());
        extern_params.push_back(changeGroupName);
		extern_params.push_back(session->getBackStatus() == TNMessageListAdapter::em_notice_list_select);
		extern_params.push_back(session->getUnreadCount());

        _tnHttpUpdateGroup.SetUpdateInfo(session->getMyFeedId(), session->getSessionId(), changeGroupName, stFeedInfo->GetTitle());
        _tnHttpUpdateGroup.GetJson([&](bool success, QJsonObject jsObject,std::vector<QVariant> params){
            if (success){
                if (!jsObject.contains("meta")){
                    return;
                }
                if (!jsObject["meta"].isObject()){
                    return;
                }
                if (jsObject["meta"].toObject()["code"] != 0){
                    return;
                }
                Q_ASSERT(_noticeListModel);
                //手动更新数据库，数据库更新有消息触发更新，此处更新数据库有几率导致ui卡顿。
                //如果选中,则更新右侧详情区标题
                _noticeListModel->manulModifySessionName(params[0].toString(), params[1].toString());
                QString qs_log = "[Notice] [TNMessageListItemWidget] onModifyGroupNameCall：" + params[1].toString();
                qInfo() << qs_log;
            }else{
                QString qs_log = "[Notice] [TNMessageListItemWidget] onModifyGroupNameCall：" + params[1].toString() + "sessionId: " +
                        params[0].toString() + " failed";
                qInfo() << qs_log;
            }
        }, TNUserDataHelper::GetInstance()->_pluginParam,extern_params);
    }
}

QModelIndex NoticeListArea::getSelectedModelIndex()
{
    int count = _noticeListModel->rowCount();
    for(int i=0;i<count;i++){
        QModelIndex index = _noticeListModel->index(i,0);
        TNMessageListAdapter* itemData = (TNMessageListAdapter*)_noticeListModel->data(index).toLongLong();
        if(itemData){
            if(itemData->getBackStatus() == TNMessageListAdapter::em_notice_list_select)
                return index;
        }
    }
    return _noticeListModel->index(0,0);
}

void NoticeListArea::upSelection()
{
    int count = _noticeListModel->rowCount();
    if(count == 0){
        return;
    }
    QModelIndex index = getSelectedModelIndex();
    if(index.row() > 0){
        TNMessageListAdapter* session = (TNMessageListAdapter*)
                _noticeListModel->data(index).toLongLong();
        Q_ASSERT(session);
        session->setBackStatus(TNMessageListAdapter::em_notice_list_normal);
        QModelIndex sibIndex = index.sibling(index.row() - 1,
                                             index.column());
        session =  (TNMessageListAdapter*)_noticeListModel->data(sibIndex).toLongLong();
        Q_ASSERT(session);
        session->setBackStatus(TNMessageListAdapter::em_notice_list_select);
        _noticeListModel->setSessionUnSelected(_currentSessionID);
        emit _listWidgetMessage->clicked(sibIndex);//选中
        _listWidgetMessage->scrollTo(sibIndex);
    }
}

void NoticeListArea::downSelection()
{
    int count = _noticeListModel->rowCount();
    if(count == 0){
        return;
    }
    QModelIndex index = getSelectedModelIndex();
    if(index.row() < count - 1){
        TNMessageListAdapter* session = (TNMessageListAdapter*)_noticeListModel->data(index).toLongLong();
        Q_ASSERT(session);
        session->setBackStatus(TNMessageListAdapter::em_notice_list_normal);
        QModelIndex sibIndex = index.sibling(index.row() + 1,
                                             index.column());
        session =  (TNMessageListAdapter*)_noticeListModel->data(sibIndex).toLongLong();
        Q_ASSERT(session);
        _noticeListModel->setSessionUnSelected(_currentSessionID);
        emit _listWidgetMessage->clicked(sibIndex);//选中
        _listWidgetMessage->scrollTo(sibIndex);
    }
}

bool NoticeListArea::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == _listWidgetMessage){
        if(event->type() == QEvent::KeyPress){
            QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(event);
            if(keyEvent == NULL) return ListAreaBase::eventFilter(watched,event);
            if(keyEvent->key() == Qt::Key_Up){
                upSelection();
            }else if(keyEvent->key() == Qt::Key_Down){
                downSelection();
            }
        }
    }else if((watched == _searchWidget) || (watched == _searchLineEdit) || (watched == _createGroupChatButton)){
        if(event->type() == QEvent::FocusIn){
            emit TNNotifyCenter::instance()->signalHideGroupChatMemberWidget();
        }
    }
    return ListAreaBase::eventFilter(watched,event);
}

void NoticeListArea::paintEvent(QPaintEvent *event)
{
    return ListAreaBase::paintEvent(event);
}

void NoticeListArea::slotReduceUnreadNum(const QString& sessionId, int number)
{
    int count  = _noticeListModel->getUnreadCount(sessionId);
    count += number;
    if(count < 0) {count = 0;}
    int index = _noticeListModel->setUnreadCount(sessionId,count);
    if(index != -1){
        emit _noticeListModel->updateTotalUnread();
    }
	emit reduceUnReadTray(sessionId, count);
}

void NoticeListArea::slotSearch(QString content)
{
	if (_nullPageStatus && _nullPage != nullptr)
	{
		_nullPage->hide();
	}
    initSearchPage();
    QString key = content;
    searchContent(key.replace(" ", ""));
}

void NoticeListArea::initSearchPage()
{
    _searchArea->hide();
#ifndef Q_OS_WIN
    _searchArea->move(0, _searchWidget->height());
#else
    _searchArea->move(0, _searchWidget->height() + 10);
#endif
    _searchArea->setFixedWidth(this->width());
    _searchArea->setFixedHeight(_listWidgetMessage->height());
}

void NoticeListArea::searchContent(QString text)
{
    if (text.isEmpty()){
		if (_nullPageStatus && _nullPage != nullptr)
		{
			_nullPage->show();
		}
        return;
    }
    _searchArea->ExcuteSearch(text, TNSearchAreaV2::Session);
}

void NoticeListArea::searchClick(TNSearchNameItem* adapter)
{
    Q_ASSERT(adapter);
    if(adapter == NULL){
        return;
    }
    TNMessageListAdapter message;
    switch (adapter->getType()) {
    case TNSearchAdapter::FriendItem:
    case TNSearchAdapter::ColleagueItem:{
        message.setType(MSG_BIZ_SINGLECHAT);
        message.setUserId(adapter->getUserId());
        message.setMyFeedId(adapter->getBelongFeedId());
        message.setToFeed(adapter->getFeedID());
        message.setAvatarPhotoUrl(adapter->getAvatarURL());
        message.setName(adapter->getTitle());
        message.setPhotoResID(adapter->getPhotoResourceID());
        QString sessionId = TNIMCoreClient::GetSessionId(message.getMyFeedId(), message.getToFeed(), MSG_BIZ_SINGLECHAT);
        message.setSessionId(sessionId);
        message.setTime(QDateTime::currentDateTime().toTime_t());
        break;
    }
    case TNSearchAdapter::GroupChatItem:{
        message.setType(MSG_BIZ_GROUPCHAT);
        message.setUserId(adapter->getUserId());
        message.setMyFeedId(adapter->getBelongFeedId());
        message.setToFeed(adapter->getFeedID());
        message.setAvatarPhotoUrl(adapter->getAvatarURL());
        message.setName(adapter->getTitle());
        message.setPhotoResID(adapter->getPhotoResourceID());
        QString sessionId = TNIMCoreClient::GetSessionId(message.getMyFeedId(), message.getToFeed(), MSG_BIZ_GROUPCHAT);
        message.setSessionId(sessionId);
        message.setTime(QDateTime::currentDateTime().toTime_t());
        break;
    }
	case TNSearchAdapter::NotifyItem:{
        message.setType(MSG_BIZ_NOTIFY);
        message.setUserId(adapter->getUserId());
        message.setMyFeedId(adapter->getBelongFeedId());
        message.setToFeed(adapter->getFeedID());
        message.setAvatarPhotoUrl(adapter->getAvatarURL());
        message.setName(adapter->getTitle());
        message.setPhotoResID(adapter->getPhotoResourceID());
        QString sessionId = TNIMCoreClient::GetSessionId(message.getMyFeedId(), message.getToFeed(), MSG_BIZ_GROUPCHAT);
        message.setSessionId(sessionId);
        message.setTime(QDateTime::currentDateTime().toTime_t());
        break;
	}
    default:
        _searchArea->hide();
        return;
    }
    _searchArea->hide();
    slotAppendSessionTop(message,true,true);
}

bool NoticeListArea::updateSessionActive(const QString &sessionId, bool isActive)
{
    return _noticeListModel->updateActive(sessionId,isActive);
}

bool NoticeListArea::slotUpdateSessionUnreadNum(const QString &sessionId, int num)
{
    int index = _noticeListModel->setUnreadCount(sessionId,num);
    if(num == 0){
        _noticeListModel->setSomeoneAtYou(sessionId,false);
    }
    if(index != -1){
        emit _noticeListModel->updateTotalUnread();
    }
    return index != -1;
}

void NoticeListArea::searchClickedSlot(const QString &type, const QString &feedId, const QString &belongFeedId)
{
    _searchLineEdit->clear();
    TNSearchNameItem searchItem(type);
    _searchArea->GetSearchResultForSession(type,feedId,belongFeedId,searchItem);
    searchClick(&searchItem);
}

void NoticeListArea::hideSearchArea()
{
    _searchLineEdit->clear();
}

bool NoticeListArea::slotRemoveSession(const QString &sessionId)
{
    TNMessageListAdapter* itemData = NULL;
    int index = _noticeListModel->findItemDataBySessionId(sessionId,&itemData);
    if(index != -1 && itemData != NULL){
        if(_currentSessionID == sessionId)
            _currentSessionID = "";
        return _noticeListModel->removeSession(sessionId,itemData->getBackStatus() == TNMessageListAdapter::em_notice_list_select);
    }
    return false;
}

void NoticeListArea::slotRemoveSession(const QString&sessionId, bool isSelected)
{
	Q_UNUSED(sessionId);
	Q_UNUSED(isSelected);
    _currentSessionID = "";
}

void NoticeListArea::slotUpOrDownSession(bool upOrDown)
{
    if(upOrDown){
        upSelection();
    }else{
        downSelection();
    }
}

void NoticeListArea::updateTime()
{
    QDateTime currTime = QDateTime::currentDateTime();
    if(currTime.date() > _initTime.date()){
        //更新会话界面时间
        int rowCount = _noticeListModel->rowCount();
        for(int i=0;i<rowCount;++i){
            QModelIndex q_index = _noticeListModel->index(i,0);
            emit _noticeListModel->dataChanged(q_index,q_index);
        }
        _initTime = currTime;
        //notice 日志
        QString qs_log = "[Notice] [NoticeListArea] updateTime end time:" + currTime.toString();
        qInfo() << qs_log;
    }
}

void NoticeListArea::slotUpdateSession(const QString &sessionId,bool isAll)
{
    if(isAll){
        //忽略所有会话未读消息
        _noticeListModel->setAllSessionReaded();
        emit _noticeListModel->updateTotalUnread();
        return;
    }
    TNMessageListAdapter* itemData = NULL;
    int index = _noticeListModel->findItemDataBySessionId(sessionId,&itemData);
    if(index != -1){
        QModelIndex q_index = _noticeListModel->index(index,0);
        if(itemData->getSessionId() != _currentSessionID){
            _noticeListModel->setSessionUnSelected(_currentSessionID);
            emit _listWidgetMessage->clicked(q_index);
            //滚动条滚动到具体消息条数
            _listWidgetMessage->scrollTo(q_index);
        }
    }
}
/*
1. 单击列表，手机端已读，撤回（可能） 3种情况未读可能变已读
2. 以上三中情况需要注意 免打扰消息
撤回： slotReduceUnreadNum
手机端已读：slotUpdateSessionUnreadNum(const QString &sessionId, int num)
单击会话：onListAreaClicked
3. 收到新会话、手动置顶、取消置顶会话： _unReadList 清空重新循环
4. 删除会话： 删除未读记录
*/
//详细规则：
//单击通知图标定位规则：
//1. 通知有消息数红点时，单击通知图标，定位到列表中第一条未读。再次单击依次定位下面未读
//2. 单击到最后一条时， 若未读存在，回到第一条未读。
//3. 若无未读消息回到顶部。
//4. 来新消息时，优先跳转新消息，然后重新轮训
//5. 免打扰消息不定位
//6. 手动置顶、取消置顶 ，重新轮训
//
//双击托盘定位规则：
//1. 通知有消息数红点时，双击托盘图标，定位到列表中第一条未读，并打开 。再次双击，定位到下一条未读，并打开。
//2. 如果无未读， 双击打开窗口
void NoticeListArea::LoadScropUnRead(bool isDoubleC)
{
	qInfo() << "[Notice][NoticeListArea] LoadScropUnRead ,isDouble:" << isDoubleC;
	Q_ASSERT(_listWidgetMessage);
    Q_ASSERT(_noticeListModel);

	if (isDoubleC)
	{
        QModelIndex q_index = _noticeListModel->index(0, 0);
		_listWidgetMessage->scrollTo(q_index, QAbstractItemView::PositionAtTop);
		return;
	}
    int index = _noticeListModel->getScropUnReadItem(_latestUnReadIndex);
	if (index == -1)
	{
		_latestUnReadIndex = -1;
        index = _noticeListModel->getScropUnReadItem(_latestUnReadIndex); //游标指到头部
	}
	if (index != -1)
	{
		qInfo() << "[Notice][NoticeListArea] LoadScropUnRead ,scroll:" << index;
        QModelIndex q_index = _noticeListModel->index(index, 0);
		_listWidgetMessage->scrollTo(q_index, QAbstractItemView::PositionAtTop);
	}
	else
	{
		//回到第一个
		qInfo() << "[Notice][NoticeListArea] LoadScropUnRead ,return top";
        QModelIndex q_index = _noticeListModel->index(0, 0);
		_listWidgetMessage->scrollTo(q_index, QAbstractItemView::PositionAtTop);
	}
	_latestUnReadIndex = index;
}

void NoticeListArea::showNullPage(bool status)
{
	if (_nullPage != nullptr){
		int w = _nullPage->width();
		_nullPage->move((LIST_AREA_WIDTH - w) / 2, 240);
		_nullPageStatus = status;
		status ? _nullPage->show() : _nullPage->hide();
	}
}

void NoticeListArea::onShowDefaultBackGround()
{
    showNullPage(_noticeListModel->rowCount() == 0);
}

void NoticeListArea::trayDoubleClickMsg()
{
	qInfo() << "[Notice][NoticeListArea] trayDoubleClickMsg ";
	Q_ASSERT(_listWidgetMessage);
    Q_ASSERT(_noticeListModel);
    int index = _noticeListModel->getScropUnReadItem(_latestUnReadIndexTray);
	if (index != -1)
	{
        QModelIndex q_index = _noticeListModel->index(index, 0);
		emit ListAreaClicked(q_index);
		_listWidgetMessage->scrollTo(q_index, QAbstractItemView::PositionAtTop);
	}
	_latestUnReadIndexTray = index;
}

void NoticeListArea::slotCreateGroupChat()
{
    QString currentBelongFeedId = TNDataCache::GetInstance()->GetCurrentMyFeed();
    if (currentBelongFeedId.startsWith("o_") && !TNDataCache::GetInstance()->getOrgCommunicationStatus(currentBelongFeedId))
    {
        TNMessageBox messageBox(this);
        messageBox.setMsg(("当前名片不支持创建群聊"));
        messageBox.exec();
        return;
    }
    TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_Notice_CreateChat, _pluginParam);
    TNCreateGroupChatDialog createGroupChatDialog;
    TNUtil::moveCenterInMainWidget(&createGroupChatDialog);
    if (createGroupChatDialog.exec() == QDialog::Accepted)
    {
        TNGroupChatCreator groupChatCreator;
        groupChatCreator.createGroupChat(createGroupChatDialog.getBelongFeedId(), createGroupChatDialog.getSelectedContact());
    }
}

void NoticeListArea::setSigleChatAlarmStatus(const TNMessageListAdapter* session,bool alarm)
{
    st_FeedPtr feedInfo;
    TNUserDataHelper::GetInstance()->GetFeedInfo(session->getToFeed(),feedInfo);
    if(feedInfo.get() == NULL){
        return;
    }
    //调用接口
    _tnHttpSwitchSet.SetSwitchInfo(session->getMyFeedId(), session->getToFeed(), feedInfo->GetUserID());
    //传递任意参数
    std::vector<QVariant> extern_params;
    extern_params.push_back(session->getSessionId());
    extern_params.push_back(session->getMyFeedId());
    extern_params.push_back(session->getToFeed());
    extern_params.push_back(session->getUserId());
    extern_params.push_back(alarm);

    _tnHttpSwitchSet.GetJson([&](bool success, QJsonObject jsObject,std::vector<QVariant> params){
        QString sessionId = params[0].toString();
        QString myFeedId = params[1].toString();
        QString toFeedId = params[2].toString();
        QString userId = params[3].toString();
        Q_UNUSED(userId);
        bool b_alarm = params[4].toBool();
        if(success){
            if(!jsObject.contains("meta")){
                return;
            }
            if(!jsObject["meta"].isObject()){
                return;
            }
            if(jsObject["meta"].toObject()["code"] != 0){
                return;
            }
            //更新数据库
            QString feedId_passiveFeedId = myFeedId + toFeedId;
            QString value = QString("%1").arg(b_alarm);
            TableBaseVec tempTableBaseVec;
            bool bFlag = false;
            TNDataControlServer::GetInstance()->Query(tempTableBaseVec,
                                                   "BlackList",
                                                   "feedId_passiveFeedId",
                                                   feedId_passiveFeedId, DBTYPE_USER);
            if(tempTableBaseVec.size() > 0){
                bFlag = TNDataControlServer::GetInstance()->UpdateSetValueByField("BlackList", "status",
                                value, "feedId_passiveFeedId", feedId_passiveFeedId, DBTYPE_USER);
            }else{
                st_BlackListPtr stBlackInfo = std::make_shared<st_BlackList>();
                stBlackInfo->SetFeedId(myFeedId);
                stBlackInfo->SetPassiveFeedId(toFeedId);
                stBlackInfo->SetStatus(b_alarm);
                bFlag = TNDataControlServer::GetInstance()->InsertDatas(stBlackInfo, DBTYPE_USER);
            }
            //更新界面
            if(bFlag){
                Q_ASSERT(_noticeListModel);
                _noticeListModel->manulSetSessionAlarm(sessionId, b_alarm);
            }else{
                //Notice日志
                QString qs_log = "[Notice] [TNMessageListItemWidget] setSigleChatAlarmStatus fialed sessionId:" + sessionId;
                qInfo() << qs_log;
             }
        }else{
            //Notice日志
            QString qs_log = "[Notice] [TNMessageListItemWidget] setSigleChatAlarmStatus httpget fialed sessionId:" + sessionId;
            qInfo() << qs_log;
        }
    }, TNUserDataHelper::GetInstance()->_pluginParam, alarm,extern_params);
}

void NoticeListArea::setGroupChatAlarmStatus(const TNMessageListAdapter* session,bool alarm)
{
    Q_ASSERT(session);
    //传递任意参数
    std::vector<QVariant> extern_params;
    extern_params.push_back(session->getSessionId());
    extern_params.push_back(session->getMyFeedId());
    extern_params.push_back(alarm);
    _tnHttpSetGroupChatDisb.SetDisturb(alarm, session->getMyFeedId(), session->getSessionId());
    _tnHttpSetGroupChatDisb.GetJson([&](bool success, QJsonObject jsObject,std::vector<QVariant> params){
        //解析参数
        QString session_id = params[0].toString();
        QString myFeed_id = params[1].toString();
        Q_UNUSED(myFeed_id);
        bool b_alarm = params[2].toBool();
        if (success){
            if (!jsObject.contains("meta")){
                return;
            }
            if (!jsObject["meta"].isObject()){
                return;
            }
            if (jsObject["meta"].toObject()["code"] != 0){
                return;
            }
            //更新数据库
            QString value = QString("%1").arg(b_alarm);
            TableBaseVec tempTableBaseVec;
            bool bFlag = false;
            TNDataControlServer::GetInstance()->Query(tempTableBaseVec,
                                                   "GroupInfo",
                                                   "groupId",
                                                   session_id,
                                                   DBTYPE_USER);
            if(tempTableBaseVec.size() > 0){
                bFlag = TNDataControlServer::GetInstance()->UpdateSetValueByField("GroupInfo", "disturbStatus",
                    value, "groupId", session_id,DBTYPE_USER);
            }
            //更新界面
            if(bFlag){
                Q_ASSERT(_noticeListModel);
                _noticeListModel->manulSetSessionAlarm(session_id, b_alarm);
             }else{
                //Notice日志
                QString qs_log = "[Notice] [TNMessageListItemWidget] setGroupChatAlarmStatus database fialed sessionId:" + session_id;
                qInfo() << qs_log;
            }
        }else{
            //Notice日志
            QString qs_log = "[Notice] [TNMessageListItemWidget] setGroupChatAlarmStatus httpget fialed sessionId:" + session_id;
            qInfo() << qs_log;
        }
    }, TNUserDataHelper::GetInstance()->_pluginParam,extern_params);
}
void NoticeListArea::on_notifyKeyEventDis(int keyEvent)
{
	if (_searchArea != nullptr &&
		!_searchArea->isHidden())
	{
		_searchArea->keyboadEventMgr(keyEvent);
	}
}

void NoticeListArea::onUpdateSessionLastMsg(QString sessionId)
{
    _noticeListModel->updateLastMsg(sessionId);
}

void NoticeListArea::dynamicUpdateFeedInfo(const QString &feedId)
{
    Q_ASSERT(!feedId.isEmpty());
    QSet<QString> feedList;
    feedList.insert(feedId);

    QList<UINotifyData> extData;
	std::vector<QVariant> extern_params;
	extern_params.push_back(-1);

    _httpObtainFeedList->GetJson([&](bool success, QJsonObject jsonObject, QList<UINotifyData> extData, TNHttpObtainFeedList* httpFeed, std::vector<QVariant>){
        if (success){
            QJsonArray feeds = jsonObject.value("data").toArray();
            QString avatarUrl = feeds.at(0).toObject().value("avatarId").toString();
            QString feedId = feeds.at(0).toObject().value("feedId").toString();
            QString userId = feeds.at(0).toObject().value("userId").toString();
            QString title = feeds.at(0).toObject().value("title").toString();
            QString titlePinYin = feeds.at(0).toObject().value("titlePinYin").toString();
            QString subTitle = feeds.at(0).toObject().value("subtitle").toString();
            if(feedId.startsWith("s_")){
                _noticeListModel->updateSessionUserIdByFeedId(feedId,userId);
            }
            _noticeListModel->updateSessionByFeedId(feedId,avatarUrl,title);
            //更新数据库
            TNDataControlServer::GetInstance()->UpdateSetValueByField("Feed","title",title,"feedId",feedId,DBTYPE_USER);
            TNDataControlServer::GetInstance()->UpdateSetValueByField("Feed","avatarId",avatarUrl,"feedId",feedId,DBTYPE_USER);
            //更新缓存
            st_FeedPtr st_feed = std::make_shared<st_Feed>();
            st_feed->SetFeedID(feedId);
            st_feed->SetTitle(title);
            st_feed->SetAvatarID(avatarUrl);
            st_feed->SetTitlePinYin(titlePinYin);
            st_feed->SetSubTile(subTitle);
			st_feed->SetUserID(userId);
            TNDataCache::GetInstance()->SynUpdateFeedCache(st_feed,0,TN::SessionList);
        }
	}, _pluginParam, feedList.toList(), extData, extern_params);
}

void NoticeListArea::dynamicUpdateGroupChatInfo(const QString &groupId)
{
    Q_ASSERT(!groupId.isEmpty());
    _httpObtainGroupInfo->GetJson([&](bool success, QJsonObject jsonObject){
        if (success){
            QJsonObject dataObject = jsonObject["data"].toObject();
            QString avatarUrl = dataObject["groupChatHeadImage"].toString();
            QString groupId = dataObject["topic"].toString();
            _noticeListModel->updateSessionAvatarBySessionId(groupId,avatarUrl);
        }
    }, _pluginParam, groupId.mid(3));
}

void NoticeListArea::onUpdateSessionListAvatar(QList<UINotifyData> dataList, bool isReady)
{
    if(isReady){
        for(QList<UINotifyData>::const_iterator itera = dataList.begin(); itera != dataList.end(); ++itera){
            std::map<int,TNMessageListAdapter*> map_itemData;
            if(!_noticeListModel->findItemDataByFeedId(itera->feedId,map_itemData)){
                continue;
            }
            for(std::map<int,TNMessageListAdapter*>::const_iterator itera = map_itemData.begin();
                itera != map_itemData.end();++itera){
                int index = itera->first;
                emit _noticeListModel->dataChanged(_noticeListModel->index(index,0),_noticeListModel->index(index,0));
            }
        }
    }else{
        for(QList<UINotifyData>::const_iterator itera = dataList.begin(); itera != dataList.end(); ++itera){
            if(itera->operateType == UI_OPERATE_DEL) continue;
            std::map<int,TNMessageListAdapter*> map_itemData;
            if(!_noticeListModel->findItemDataByFeedId(itera->feedId,map_itemData)){
                continue;
            }
            for(std::map<int,TNMessageListAdapter*>::const_iterator itera = map_itemData.begin();
                itera != map_itemData.end();++itera){
                //手动更新头像
                if(itera->second->getType() == MSG_BIZ_SINGLECHAT){
                    dynamicUpdateFeedInfo(itera->second->getToFeed());
                }else if(itera->second->getType() == MSG_BIZ_GROUPCHAT){
                    dynamicUpdateGroupChatInfo(itera->second->getSessionId());
                }
            }
        }
    }
}
