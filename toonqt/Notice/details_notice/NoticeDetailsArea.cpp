#include <QKeyEvent>
#include <QVBoxLayout>
#include <QScrollBar>
#include <memory>
#include <QTextBlock>
#include <QDebug>
#include <QFileDialog>
#include <QImageReader>
#include <QPixmap>
#include <QRegExp>

#include "TNMsgDetailDelegate.h"
#include "model_data/TNModelUserMessage.h"
#include "NoticeDetailsArea.h"
#include "ui_NoticeDetailsArea.h"
#include "LocalStorageCommon.h"
#include "TNDataControlServer.h"
#include "emotion/TNEmojiSingleton.h"
#include "Notice.h"
#include "TNIMCoreClient.h"
#include "TNGroupChatMembersWidget.h"
#include "TNDbUtil.h"
#include "tnloadinghository.h"
#include "model_data/tngeneratenoticemodeldata.h"
#include "network/tnsendimsg.h"
#include "TNNewFriendCard.h"
#include "emoji/tnemojiwidget.h"
#include "TNUserDataHelper.h"
#include "tnwarndlag.h"
#include "TNHttpObtainGroupChatInfoByGroupChatIdSyn.h"
#include "TNDataCache.h"
#include "TNMessageBox.h"
#include "TNDataSearch.h"
#include "TNPathUtil.h"
#include "TNNameSpace.h"
#include "someoneatyou.h"
#include "TNMsgDetailItemWidget.h"
#include "emotion/tnconvertrichedit.h"
#include "ScreenShot.h"
#include "TNSendConfirmDialog.h"
#include "tndetailsunreadwdiget.h"
#include "TNSettingData.h"
#include "TNGlobalShotCutManagement.h"
#include "TNUtil.h"
#ifdef __APPLE__
#include "audio/macosx/playsound.h"
#else
#include "audio/tnplayaudio.h"
#endif
#include "tnimagectr.h"
#include "TNDataStatistics.h"
#include "TNShortCutKeyTextMap.h"
#include "TNBatchSendImageConfirmDialog.h"
#include "TNBatchSendFileConfirmDialog.h"
#include "CTNDBAPI.h"
#include "CTNDBHeader.h"
#include "recoredfilebrowser.h"

#ifdef Q_OS_WIN
#include <Windows.h>
#endif

NoticeDetailsArea::NoticeDetailsArea(int id, TNPluginParamPtr param, QWidget *parent)
:TNChatDetailBase(id, parent)
, _currentAdpter(NULL)
, _ATSearchArea(NULL)
, _pluginParam(param)
, _lodingHositoryGif(NULL)
, _isLoading(false)
, _isLastMsg(false)
, _emojiWidget(NULL)
, _modelSize(0)
, _isSendNeedPressCtrl(false)
, _bisAting(false)
, _screenShotMenu(nullptr)
, _actionHideAtScreenShot(nullptr)
, _tnDetailsUnreadWdiget(NULL)
, _downLastMsgIndex(-1)
, _membersWidget(nullptr)
, _someOneAtYouWidget(NULL)
{
    _generateModelData = new TNGenerateNoticeModelData(this);
    ui = new Ui::NoticeDetailsArea();
	ui->setupUi(this);
	
	ui->tableWidget->setNoticeDetailsArea(this);

	ui->stackedWidget->setCurrentIndex(2);

    ui->stackedWidget->widget(0)->setLayout(ui->verticalLayout);
	ui->stackedWidget->widget(1)->setLayout(ui->verticalLayout_5);
	ui->stackedWidget->widget(2)->setLayout(ui->gridLayout_backpic);
	
	ui->pushButton_Expression->setCursor(Qt::PointingHandCursor);
	ui->pushButton_file->setCursor(Qt::PointingHandCursor);
	ui->pushButton_Send->setCursor(Qt::PointingHandCursor);
	ui->pushButton_top_name->setCursor(Qt::PointingHandCursor);
    ui->pushButton_top_arrow->setCursor(Qt::PointingHandCursor);
    ui->pushButton_screenShot->setCursor(Qt::PointingHandCursor);
    ui->pushButton_top_name->setFlat(true);
    ui->pushButton_top_arrow->setFlat(true);

#ifndef Q_OS_WIN
    ui->pushButton_screenShot->setObjectName("pushButton_screenShot_mac");
    ui->widget_top_add->setContentsMargins(0, 0, 10, 0);
#endif

	TNNotifyCenter::instance()->connectNotifyRefreshAddressList(this);
	TNNotifyCenter::instance()->connectNotifyRemoveSession(this);
	TNNotifyCenter::instance()->connectNotifyReadSession(this);
	TNNotifyCenter::instance()->connectNotifyRefreshRevert(this);
	TNNotifyCenter::instance()->connectNotifySendHotKeyChanged(this);
    TNNotifyCenter::instance()->connectScreenShotByShortCut(this);
    TNNotifyCenter::instance()->connectNotifyReMarkUpdate(this);

    _membersWidget = new TNGroupChatMembersWidget(this);
    //_membersWidget->setObjectName("groupChatMembersWidget");
    connect(_membersWidget, SIGNAL(createGroupChatFinished(TNMessageListAdapter)),
		this, SLOT(slotCreateGroupChatFinished(TNMessageListAdapter)));
    connect(_membersWidget, SIGNAL(exitGroupChatFinished(TNMessageListAdapter)),
		this, SLOT(slotExitGroupChatFinished(TNMessageListAdapter)));
    connect(_membersWidget, SIGNAL(widgetHided()), this, SLOT(slotUpdateArrowStatus()));
    connect(TNNotifyCenter::instance(), SIGNAL(signalHideGroupChatMemberWidget()), this, SLOT(slotUpdateArrowStatus()));
    _membersWidget->hide();

	InitReceiveWidget();

	connect(ui->pushButton_Send, SIGNAL(clicked()), this,
		SLOT(OnSendMessageSlot()));
	connect(ui->pushButton_Expression, SIGNAL(clicked()), this,
		SLOT(OnExpressionSlot()));
	connect(ui->pushButton_file, SIGNAL(clicked()), this,
		SLOT(onAddFile()));
	connect(ui->pushButton_screenShot, SIGNAL(clicked()), this,
		SLOT(onScreenShot()));
#ifdef Q_OS_WIN
    connect(ui->pushButton_screenShot, SIGNAL(arrowClick()), this, SLOT(onScreenShotPopupMenu()));
#endif
    
    connect(ui->tableWidget, SIGNAL(readSessionUnreadNum(QString,int)),this,
            SIGNAL(readSessionUnreadNum(QString,int)));
	connect(ui->tableWidget, SIGNAL(updateTrayUnRead(const QString &)), this,
		SIGNAL(updateTrayUnRead(const QString &)));

    ui->stackedWidget->installEventFilter(this);
    ui->widget_top_add->installEventFilter(this);
    ui->textEdit_Send->installEventFilter(this);
	ui->textEdit_Send->viewport()->installEventFilter(this);
    _tableView->installEventFilter(this);
    ui->widget_emoji_file_pic->installEventFilter(this);
    ui->pushButton_screenShot->installEventFilter(this);
    this->installEventFilter(this);

	connect(ui->pushButton_top_name, SIGNAL(clicked(bool)), this, SLOT(onPsuhButtonName(bool)));
    connect(ui->pushButton_top_arrow, SIGNAL(clicked(bool)), this, SLOT(onPsuhButtonName(bool)));
	
    _loadHistoryData = new LoadHistoryData(_msgModel, this);
    connect(_loadHistoryData, SIGNAL(AppandPageFinished(bool,int,bool)),
        this, SLOT(loadHistoryFinshed(bool,int,bool)),Qt::QueuedConnection);

    connect(_generateModelData, SIGNAL(maxFileSize(QString)), this, SLOT(warnMaxFileSize(QString)));

	_ATSearchArea = new tnnoticeatarea(_pluginParam,this);
	_ATSearchArea->raise();
	_ATSearchArea->hide();
	_ATSearchArea->setFocusPolicy(Qt::NoFocus);
	_ATSearchArea->setObjectName("NoticeATSearchArea");
    connect(_ATSearchArea, SIGNAL(ItemClicked(QString, QString, QString)),
        this, SLOT(SearchClickedSlot(QString, QString, QString)));
    TNNotifyCenter::instance()->connnectNotifyCurrentFeedChanged(this);
    TNDataCache::GetInstance()->InstallCatcheFeedUpdateNotify(this);
}

void NoticeDetailsArea::showChatDetails()
{
	ui->stackedWidget->setCurrentIndex(0);
}

void NoticeDetailsArea::showNoticeDetails(const QString &sessionId,
                                          TNMessageListAdapter* adapter)
{
	ui->stackedWidget->setCurrentIndex(1);
    ui->tableWidget->setSessionId(sessionId,adapter);
}

NoticeDetailsArea::~NoticeDetailsArea()
{
	delete ui;
}

void NoticeDetailsArea::onScreenShot()
{
    QWidget *pCurrent = TNUtil::getMainWidget();
#ifdef Q_OS_WIN
    if (TNSettingData::instance()->IsHideAtScreenShot() && nullptr != pCurrent)
    {
        pCurrent->showMinimized();
    }
#endif
    TN::ScreenShotExitFlag exitFlag = TNScreenShot::screenShot();
    if (nullptr != pCurrent)
    {
        pCurrent->showNormal();
        pCurrent->activateWindow();
    }
    if (exitFlag == TN::FinishedExit)
    {
        ui->textEdit_Send->customPaste();
    }
}

void NoticeDetailsArea::slotFinishedScreenShotByShortCut()
{
    qDebug()<<"NoticeDetailsArea::slotFinishedScreenShotByShortCut begin...";
    int index = ui->stackedWidget->currentIndex();
    bool select = _pluginParam->_currentSelectPage == MENU_NOTICE_ID;
    QWidget *toastBlackWidget = qApp->activeModalWidget();
    if (toastBlackWidget && (toastBlackWidget->objectName() == QString("TNMessageBox")))
        toastBlackWidget->close();
    if(ui->textEdit_Send->isActiveWindow() && select && index == 0){
        qDebug()<<"NoticeDetailsArea::slotFinishedScreenShotByShortCut customPaste";
        ui->textEdit_Send->customPaste();
    }
    qDebug()<<"NoticeDetailsArea::slotFinishedScreenShotByShortCut end.";
}

void NoticeDetailsArea::onActionHideAtScreenShot(bool isChecked)
{
    TNSettingData::instance()->SetHideAtScreenShot(!isChecked);
	st_SetUpPtr isHideAtScreenShot = std::make_shared<st_SetUp>();
	isHideAtScreenShot->SetKey("IsHideAtScreenShot");
    isHideAtScreenShot->SetValue(!isChecked ? ("1") : ("0"));
	TNDataControlServer::GetInstance()->InsertDatas(std::dynamic_pointer_cast<TableBase>(isHideAtScreenShot), DBTYPE_USER);
}

void NoticeDetailsArea::onScreenShotPopupMenu()
{
    if (_screenShotMenu == nullptr)
    {
        _screenShotMenu = new QMenu(this);
		_screenShotMenu->setObjectName("shotMenu");
        _actionHideAtScreenShot = new QAction(this);
        _actionHideAtScreenShot->setText(("截图时显示聊天框"));
        _actionHideAtScreenShot->setCheckable(true);
        _actionHideAtScreenShot->setChecked(!TNSettingData::instance()->IsHideAtScreenShot());
        connect(_actionHideAtScreenShot, SIGNAL(triggered(bool)), this, SLOT(onActionHideAtScreenShot(bool)));
        _screenShotMenu->addAction(_actionHideAtScreenShot);
    }
    QPoint refPoint = ui->pushButton_screenShot->mapToGlobal(ui->pushButton_screenShot->rect().bottomLeft());
    QPoint pos(refPoint.x() + 10, refPoint.y() + 2);
    _screenShotMenu->exec(pos);
}

void NoticeDetailsArea::onAddFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, ("选择文件"),
        _oldSelectDir, ("all(*)\n"));
    if (fileName.isEmpty()){
        return;
    }
    QFileInfo fileInfo(fileName);
    _oldSelectDir = fileInfo.dir().absolutePath();
    if(TNImageCtr::isImageFile(fileName)){
        dragImageSend(fileName);
    }else{
        dragFileSend(fileName);
    }
}

void NoticeDetailsArea::InitReceiveWidget()
{
    _tableView = ui->tableView_details;
    _tableView->setObjectName("widget_Receive");
    ui->splitter->setChildrenCollapsible(false);
    ui->splitter->setHandleWidth(0);
    ui->splitter->setStretchFactor(0,10);
    ui->splitter->setStretchFactor(1,1);
	ui->splitter->setStyleSheet("QSplitter::handle{background-color:#ffffff}");

	_msgModel = new TNMsgDetailModel(this);
    TNMsgDetailDelegate *msgDelegate = new TNMsgDetailDelegate(_tableView);
	msgDelegate->setParentWidget(this);
	_msgModel->setChatDetailBase(this);
    _msgModel->setTableView(_tableView);
	_msgModel->setPluginParam(_pluginParam);
    connect(_msgModel,SIGNAL(reSendData(TNModelUserMessage)),
            this,SLOT(on_reSendData(TNModelUserMessage)));
	//初始化下载上传
    _imClient = TNSendIMsg::getInstance();
	_imClient->setDetailModel(_msgModel);
	_imClient->setTNPluginParamPtr(_pluginParam);
	connect(_imClient, SIGNAL(notifyRefresh(QString, int, const QString, TNMsgData)),
		this, SLOT(on_notifyRefresh(QString, int, const QString, TNMsgData)));
	connect(_imClient, SIGNAL(notifyRefresh(QString, TNNoticeInfo&)),
		this, SLOT(on_notifyRefresh(QString, TNNoticeInfo&)));

	connect(msgDelegate, SIGNAL(revokeProcessSignal(int, int, qint64,const QString &, const QString&, const QString&)), this, SLOT(revokeProcess(int, int,qint64, const QString &, const QString&, const QString&)));
	connect(msgDelegate, SIGNAL(deleteMsgSignalDelegate(const QString &)), this, SLOT(deleteMsgSlots(const QString &)));
    connect(msgDelegate, SIGNAL(jumpMsgSignalDelegate(QString)),this,SLOT(jumpToMsgSlots(QString)));
    _tableView->setModel(_msgModel);
    _tableView->setItemDelegate(msgDelegate);
    _tableView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	
    _tableView->setGridStyle(Qt::NoPen);
    _tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    _tableView->horizontalHeader()->setDefaultSectionSize(DETAIL_AREA_WIDTH);
    _tableView->horizontalHeader()->setVisible(false);
    _tableView->verticalHeader()->setVisible(false);
    _tableView->setObjectName("tableConvMsg");

	ui->textEdit_Send->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //connect(ui->textEdit_Send, SIGNAL(textChanged()), this, SLOT(slotEditCtr()));
    connect(ui->textEdit_Send->document(), SIGNAL(contentsChange(int,int,int)), this, SLOT(slotEditCtr(int,int,int)));
    //创建未读消息悬浮窗
    if(_tnDetailsUnreadWdiget == NULL){
        _tnDetailsUnreadWdiget = new TNDetailsUnreadWdiget(this);
        _tnDetailsUnreadWdiget->hide();
        connect(_tnDetailsUnreadWdiget,SIGNAL(downClicked()),
                this,SLOT(onUnreadWidgetDownClicked()));
        connect(_tnDetailsUnreadWdiget,SIGNAL(upClicked()),
                this,SLOT(onUnreadWidgetUpClicked()));
    }
    connect(_tableView->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(scrollBarValueChanged(int)));
    qRegisterMetaType<QList<QUrl>>("");
    connect(_tableView,SIGNAL(dropInUrls(QList<QUrl>)),this,SLOT(onDropUrlsSlot(QList<QUrl>)),Qt::QueuedConnection);
    connect(ui->textEdit_Send,SIGNAL(inputUrls(QList<QUrl>)),this,SLOT(onDropUrlsSlot(QList<QUrl>)),Qt::QueuedConnection);
    //初始化someoneAt悬浮窗
    if(!_someOneAtYouWidget){
        _someOneAtYouWidget = new someoneatyou(this);
        connect(_someOneAtYouWidget, SIGNAL(ClickedMsgBox(QString, int, bool)), this, SLOT(atMsgBoxCliecked(QString, int, bool)));
        _someOneAtYouWidget->hide();
    }
}

void NoticeDetailsArea::AppendSendWidget(MESSAGE_TYPE type,
    const QString& content,
    bool bSend, bool isAt,
    QList<QString> list_feedId)
{
	_currentAdpter->setTime(QDateTime::currentDateTime().toTime_t());
    _tableView->setScrollToBottom(true);//发送数据时，滚动条需要滚动到底部

    int atType = isAt ? 2 : 0;
    TNModelUserMessage *Message = _generateModelData->generateSendMsg(type, content,
        bSend, _currentAdpter, atType, list_feedId);
	//先插入界面
	if (Message != NULL){
		int currentRow = _msgModel->rowCount();
        if(!_msgModel->insertData(currentRow, Message)){
            delete Message;
            return;
        }
        setSessionLastMsg(type, content, _currentAdpter,false,false);
        emit activeSessionTop(*_currentAdpter, true, true, true);
	}
}

void NoticeDetailsArea::setSessionLastMsg(MESSAGE_TYPE type, const QString& last_msg, 
    TNMessageListAdapter* adapter, bool isAt, bool isSenderName,const QString& from)
{
    QString sender_name;
    if(isSenderName){
        //获取备注
        QString remark;
        if(adapter->getType() == MSG_BIZ_GROUPCHAT){
            remark = TNDataCache::GetInstance()->getFriendFeedReMark(from,adapter->getMyFeedId());
            sender_name = adapter->getSenderName();
            if(!remark.isEmpty()){
                sender_name = remark;
            }
        }
    }
    //////////////////////
    QString preMsg;
    if (!sender_name.isEmpty()){
        preMsg = sender_name + ":";
    }
	if (isAt){
        adapter->setIsAtMe(true);
	}
	if (preMsg == (":")){
		preMsg.clear();
		Q_ASSERT("Never here!");
	}
	switch (type){
	case em_image:
        adapter->setLastMessage(preMsg + tr(DEFAULT_IMAGE_LAST_MESSAGE));
		break;
	case em_file:
        adapter->setLastMessage(preMsg + tr(DEFAULT_FILE_LAST_MESSAGE));
		break;
	case em_audio:
        adapter->setLastMessage(preMsg + tr(DEFAULT_AUDIO_LAST_MESSAGE));
		break;
    case em_video:
        adapter->setLastMessage(preMsg + tr(DEFAULT_VIDEO_LAST_MESSAGE));
        break;
	case em_text:
        adapter->setLastMessage(preMsg + last_msg);
		break;
    case em_groupchat_notice:
        adapter->setLastMessage(last_msg);
        break;
	case em_notsupport:
        adapter->setLastMessage(tr(NOTSUPPORT_TEXT));
		break;
	case em_group_operate:
	case em_single_operate:
        adapter->setLastMessage(last_msg);
		break;
    case em_red_card:
        adapter->setLastMessage(tr(RED_ENVELOPES));
        break;
	default:
        adapter->setLastMessage(last_msg);
		break;
	}
}

void NoticeDetailsArea::AppendRevokeWidget(const QString& content, MESSAGE_TYPE type, int revokeResult,int index)
{
    _currentAdpter->setTime(QDateTime::currentDateTime().toTime_t());
    setSessionLastMsg(type, content, _currentAdpter,false,false);
	TNModelUserMessage *Message = _generateModelData->generateRevokeMsg(type, content, _currentAdpter);
	//先插入界面
	if (Message != NULL){
        if(!_msgModel->insertData(index, Message)){
            delete Message;
            return;
        }
        _tableView->scrollTo(_msgModel->index(index, 0), QAbstractItemView::PositionAtBottom);
        emit activeSessionTop(*_currentAdpter, true, true, true);
	}
}

void NoticeDetailsArea::AppendRecvWidget(MESSAGE_TYPE type,
	TNMsgData msgData,
	const QString& myFeedId,
	bool bDownloaded /* = true */)
{
	qDebug() << "[noticedetail]AppendRecvWidget";
	TNModelUserMessage *Message = _generateModelData->generateRecvMsg(msgData,
		(MESSAGE_TYPE)msgData.type,
		myFeedId, bDownloaded);
	qDebug() << "[noticedetail]generateRecvMsg end";
	int currentRow = _msgModel->rowCount();
    if(!_msgModel->insertData(currentRow, Message)){
        delete Message;
        return;
    }
	if (msgData.bizType == MSG_BIZ_GROUPCHAT && msgData.bIsAtMe){
        someoneAtme(msgData.senderName, msgData.msgId, currentRow);
	}
}

void NoticeDetailsArea::OnExpressionSlot()
{
	if (_emojiWidget == NULL){
		_emojiWidget = new TNEmojiWidget(this);
		QPoint pos = mapToGlobal(ui->widget_emoji_file_pic->pos());
        _emojiWidget->move(pos.x() + 1, pos.y() - _emojiWidget->height() + 48);
		_emojiWidget->show();
	}else{
		QPoint pos = mapToGlobal(ui->widget_emoji_file_pic->pos());
        _emojiWidget->move(pos.x() + 1, pos.y() - _emojiWidget->height() + 48);
		_emojiWidget->setVisible(true);
		_emojiWidget->show();
	}
}

void NoticeDetailsArea::btn_clicked()
{
	_emojiWidget->setVisible(false);
	_emojiWidget->hide();

	QString idx = sender()->objectName().split("_")[2];
	int index = idx.toInt();
	char s_index[12] = { 0 };
#ifdef WIN32
	sprintf_s(s_index, "%03d", index);
#else
    sprintf(s_index, "%03d", index);
#endif
	QString file = ":/Resources/images/" + QString(s_index) + ".png";
	ui->textEdit_Send->insertHtml(QString("<img src=\"%1\" width=\"%2\" height=\"%3\" />")
		.arg(file).arg(EMOJI_WIDTH).arg(EMOJI_HEIGHT));
    ui->textEdit_Send->setFocus(Qt::MouseFocusReason);
}

void NoticeDetailsArea::OnListAreaClickedSlot(const QModelIndex & index)
{
	TNMessageListAdapter *adapter = (TNMessageListAdapter*)index.data().toLongLong();
    if (adapter == NULL){
        return;
    }
	//如果在latestmessage 中，有at 标志，则需要去掉
	if (adapter->getType() == MSG_BIZ_GROUPCHAT){
        if(adapter->getIsAtMe()){
            _atActiveList.removeOne(adapter->getSessionId()); //用来显示lastMessage
            adapter->setIsAtMe(false);
        }
	}
    //第一次点击会话
    if(_currentAdpter == NULL){
        if(adapter->getType() != MSG_BIZ_NOTIFY){
            //设置第一条未读消息的msgId
            QString firstUnreadMsgId = _loadHistoryData->getFirstUnreadMsg(adapter->getSessionId(),
                                                                          adapter->getUnreadCount());
            _tnDetailsUnreadWdiget->setFirstUnreadMsgId(firstUnreadMsgId);
            //首先加载离线提示wdiget,因为这时候未读消息还没有置0
            showUnreadWidget(adapter->getUnreadCount(),true,false,false);
            //请求名片的可沟通状态
            TNUserDataHelper::GetInstance()->updateCardStatus(adapter->getMyFeedId(),adapter->getToFeed());
        }
        //然后更新该条会话未读消息为0等
        emit updateSessionClicked(index);
    }else{
        if(adapter->getSessionId() == _currentAdpter->getSessionId()){
            emit updateSessionClicked(index);
            return;//点击同一个会话不重复加载数据
        }
        if(adapter->getType() != MSG_BIZ_NOTIFY){
            //请求名片的可沟通状态
            TNUserDataHelper::GetInstance()->updateCardStatus(adapter->getMyFeedId(),adapter->getToFeed());
        }
        //切换会话时,清空全局变量中存储的附件的msgid
        RecoredFileBrowser::getInstance()->clear_recored_filebrowser();
        //如果上次会话收到了非active消息,切换会话的时候,将上次会话置为0(如果不切换会话则依赖active事件3秒后置0)
        if(_currentAdpter->getUnreadCount() > 0){
            _currentAdpter->setActive(true);
            emit readSessionUnreadNum(_currentAdpter->getSessionId(),0);
            TNIMCoreClient::GetIMClient()->ReadSession(_currentAdpter->getSessionId());
        }
        //设置第一条未读消息的msgId
        QString firstUnreadMsgId = _loadHistoryData->getFirstUnreadMsg(adapter->getSessionId(),
                                                                      adapter->getUnreadCount());
        _tnDetailsUnreadWdiget->setFirstUnreadMsgId(firstUnreadMsgId);
        //首先加载离线提示wdiget,因为这时候未读消息还没有置0
        showUnreadWidget(adapter->getUnreadCount(),true,false,true);
        showUnreadWidget(adapter->getUnreadCount(),true,false,false);
		//然后更新该条会话未读消息为0等
        emit updateSessionClicked(index);
        //单聊和群聊会话保存草稿
        if(_currentAdpter->getType() == MSG_BIZ_GROUPCHAT ||
                        _currentAdpter->getType() == MSG_BIZ_SINGLECHAT){
            saveDraft(_currentAdpter);
        }
        //如果有正在播放的语音停止播放
#ifdef __APPLE__
        PlaySound::getInstance()->StopPlay();
#else
        TNPlayAudio::getInstance()->stopPalyAudio();
#endif
    }
    reloadChatDetails(adapter);
    reloadDraft(adapter);
    ui->textEdit_Send->setFocus(Qt::MouseFocusReason);
}

void NoticeDetailsArea::saveDraft(TNMessageListAdapter *adapter)
{
    QString draft = generateDraft();
    if(draft != adapter->getDraft()){
        adapter->setDraft(draft);
        QDateTime curTime = QDateTime::currentDateTime();
        adapter->setTime(curTime.toTime_t());
        //保存数据库
        TNIMCoreClient::GetIMClient()->SaveDraft(adapter->getSessionId(),
                                                 adapter->getDraft());
        //置顶显示最后一条消息改变
        emit activeSessionTop(*adapter,false,true);
    }
}

void NoticeDetailsArea::reloadDraft(TNMessageListAdapter* adapter)
{
    QString draft = adapter->getDraft();
    if(draft.isEmpty()){
        return;
    }
    QJsonParseError jsonError;
    QByteArray array;
    array.append(draft);
    QJsonObject jsonObject = QJsonDocument::fromJson(array, &jsonError).object();
    if (jsonError.error != QJsonParseError::NoError)
        return;
    QJsonArray draftArray;
    if(jsonObject.find("draft") != jsonObject.end()){
        draftArray = jsonObject["draft"].toArray();
        for(QJsonArray::const_iterator itera = draftArray.begin(); itera != draftArray.end(); ++itera){
            if(!itera->isObject())
                continue;
            QJsonObject temp = itera->toObject();
            if(temp.find("at") != temp.end()){
                QJsonObject atObject = temp["at"].toObject();
                int pos = atObject["pos"].toInt();
                QString atFeedId = atObject["atFeedId"].toString();
                QString atFeedName = atObject["atFeedName"].toString();
                QString showText = atObject["showText"].toString();
                reverseAtObject(pos,atFeedId,atFeedName,showText);
            }else if(temp.find("text") != temp.end()){
                QJsonObject textObject = temp["text"].toObject();
                QString text = textObject["text"].toString();
                TNConvertRichEdit::reverseRichEdit(this->ui->textEdit_Send,text,false);
            }
        }
    }
}

void NoticeDetailsArea::reloadChatDetails(TNMessageListAdapter* adapter)
{
    if (adapter == NULL)
        return;
    if (adapter->getType() == MSG_BIZ_NOTIFY){
        _currentAdpter = adapter;
        const QString sessionId = adapter->getSessionId();
        ui->noticeTitleLabel->setText(adapter->getName());
        showNoticeDetails(sessionId,_currentAdpter);
    }else{
        //显示内容区
        showChatDetails();
        //当前消息详情区scrolltobottom
        _tableView->setScrollToBottom(true);
        //加载历史记录重置
        _isLoading = false;
        _isLastMsg = false;
        //隐藏加载历史记录gif
        if (_lodingHositoryGif != NULL){
            _lodingHositoryGif->hide();
        }
        //////////////////////////////////
        _currentAdpter = adapter;
        ui->pushButton_top_name->setText(wrapTitleLabelName(adapter->getName()));
        _msgModel->clearData();
        _loadHistoryData->readCurrentSession(_currentAdpter);
        ui->textEdit_Send->clear();//清空输入框
        ///////////////////////////////////////////////////////
        _membersWidget->resetSession(_currentAdpter);
    }
	/*
    切换详情区， at 提示框隐藏
	*/
    if(_someOneAtYouWidget){
        _someOneAtYouWidget->hide();
        _someOneAtYouData.clear();
    }
}

void NoticeDetailsArea::OnSendMessageSlot()
{
    int count = ui->textEdit_Send->document()->characterCount();
    if(count > MAXTEXTSIZE){
        TNMessageBox messagebox(this);
        messagebox.setMsg(("字数超过最大限制"));
        messagebox.exec();
        return;
    }
    bool isHaveImage = false,isHaveObjectAt = false;
    //从富文本中生成数据
    std::list<edit_content> list_edit_content = TNConvertRichEdit::getText(ui->textEdit_Send->document(),0,-1);//生成自定义数据
    //清空数据
    ui->textEdit_Send->clear();
    //如果草稿不为空,清空草稿
    if(!_currentAdpter->getDraft().isEmpty()){
        saveDraft(_currentAdpter);
    }
    /////////////////////////////////////
    QString content;
    QList<QString> at_list_feedId;
    if(list_edit_content.size() > 1){
        for(std::list<edit_content>::const_iterator itera = list_edit_content.begin();
            itera != list_edit_content.end(); ++itera){
            isHaveImage = itera->type == edit_content::content_type_image;
            if(isHaveImage){
                if(!content.isEmpty() && !isAllSpace(content)){
                    if(isHaveObjectAt){
                        AppendSendWidget(em_text,content,false,true,at_list_feedId);
                        isHaveObjectAt = false;
                        content.clear();
                        at_list_feedId.clear();
                    }else{
                        AppendSendWidget(em_text,content,false);
                        content.clear();
                    }
                }
                content = itera->content;
                AppendSendWidget(em_image,content,false);
                content.clear();
            }else{
                if(itera->type == edit_content::content_type_objectAt){
                    isHaveObjectAt = true;
                    QString feedId;
                    content += TNConvertRichEdit::formatAtList(*itera,feedId);
                    at_list_feedId.push_back(feedId);
                }else{
                    content += itera->content;
                }
            }
        }
        //文字和@
        if(!content.isEmpty() && !isAllSpace(content)){
            if(isHaveObjectAt){
                AppendSendWidget(em_text,content,false,true,at_list_feedId);
                isHaveObjectAt = false;
                content.clear();
                at_list_feedId.clear();
            }else{
                AppendSendWidget(em_text,content,false);
                content.clear();
            }
        }
    }else{
        for(std::list<edit_content>::const_iterator itera = list_edit_content.begin();
            itera != list_edit_content.end(); ++itera){
            isHaveImage = itera->type == edit_content::content_type_image;
            isHaveObjectAt = itera->type == edit_content::content_type_objectAt;
            content = itera->content;
        }
        if(isAllSpace(content) && !isHaveImage && !isHaveObjectAt){//全是空白字符
            TNMessageBox messagebox(this);
            messagebox.setMsg(("不能发送空白字符"));
            messagebox.exec();
            return;
        }
        if(isHaveImage){
            AppendSendWidget(em_image,content,false);
        }else{
            if(isHaveObjectAt){
                QList<QString> list_feedId;
                content = TNConvertRichEdit::formatAtList(list_edit_content,list_feedId);
                AppendSendWidget(em_text,content,false,true,list_feedId);
            }else{
                if(!content.isEmpty() && !isAllSpace(content))
                    AppendSendWidget(em_text,content,false);
            }
        }
    }
	ui->textEdit_Send->setFocus(Qt::MouseFocusReason);
}

bool NoticeDetailsArea::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->textEdit_Send){
		if (event->type() == QEvent::KeyPress){
            QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(event);
            if(keyEvent == NULL) return TNChatDetailBase::eventFilter(watched, event);
            if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter){
                if (_bisAting){
                    if (_ATSearchArea != NULL && !_ATSearchArea->isHidden()){
						_ATSearchArea->enterKey();
					}
					return true;
				}
                if (_isSendNeedPressCtrl){
                    if (keyEvent->modifiers() & Qt::ControlModifier){
                        OnSendMessageSlot();
                        return true;
                    }
                }else{
                    if (keyEvent->modifiers() & Qt::ControlModifier){
                        keyEvent->setModifiers(keyEvent->modifiers() ^ Qt::ControlModifier);
                    }else if(keyEvent->modifiers() == Qt::NoModifier){
                        OnSendMessageSlot();
                        return true;
                    }
                }
            }else if (keyEvent->key() == Qt::Key_Up){
				if (_bisAting){
					if (_ATSearchArea != NULL && !_ATSearchArea->isHidden()){
						_ATSearchArea->upSelection();
					}
					return true;
				}
                if(ui->textEdit_Send->document()->isEmpty()){
                    emit upOrDownSession(true);
                    return true;
                }
			}else if (keyEvent->key() == Qt::Key_Down){
				if (_bisAting){
					if (_ATSearchArea != NULL && !_ATSearchArea->isHidden()){
						_ATSearchArea->downSelection();
					}
					return true;
				}
                if(ui->textEdit_Send->document()->isEmpty()){
                    emit upOrDownSession(false);
                    return true;
                }
            }
            //按键按下
            noticeFocuseIn();
        }else if (event->type() == QEvent::FocusIn){
            slotUpdateArrowStatus();
        }else if (event->type() == QEvent::FocusOut){
			if (_bisAting){
				_bisAting = false;
				if (_ATSearchArea != NULL && !_ATSearchArea->isHidden()){
					_ATSearchArea->hide();
				}
			}
			/*
			 重置状态
			*/
			ui->textEdit_Send->_isActiveByKey = false;
        }
    }else if (watched == ui->textEdit_Send->viewport()){
		if (event->type() == QEvent::MouseButtonPress){
			if (_bisAting){
				_bisAting = false;
				if (_ATSearchArea != NULL && !_ATSearchArea->isHidden()){
					_ATSearchArea->hide();
				}
			}
		}
    }else if(watched == _tableView){
        if(event->type() == QEvent::WindowActivate){
            noticeFocuseIn();
        }else if(event->type() == QEvent::Enter){
            noticeFocuseIn();
        }else if(event->type() == QEvent::Resize){
            moveUnreadWidget(_tnDetailsUnreadWdiget->getUpOrDown());
            moveSomeOneAtWidget();
        }else if (event->type() == QEvent::FocusIn){
            slotUpdateArrowStatus();
        }
    }else if(watched == ui->pushButton_screenShot){
        if(event->type() == QEvent::Enter){
            QString uiTextByText = TNShortCutKeyTextMap::getUiTextByText(TNSettingData::instance()->ScreenShotKey());
            ui->pushButton_screenShot->setToolTip(("屏幕截图 ") + uiTextByText);
        }
    }else if(watched == this){
        if(event->type() == QEvent::Wheel){
            if(ui->stackedWidget->currentIndex() == 0){//消息详情区
                if (_isLastMsg || _isLoading){
                    return true;
                }
                if (_tableView->verticalScrollBar()->value() == 0){
                    loadHistoryMsg(PAGE_NUM);
                }
            }
        }
    }else if((watched == ui->widget_emoji_file_pic) || (watched == ui->widget_top_add) || (watched == ui->stackedWidget)){
        if(event->type() == QEvent::FocusIn){
            slotUpdateArrowStatus();
        }
    }
    return TNChatDetailBase::eventFilter(watched, event);
}

void NoticeDetailsArea::generateSendFileData(const QString& file_name)
{
    AppendSendWidget(em_file, file_name,false);
}

void NoticeDetailsArea::on_notifyRefresh(QString type, int statCode,
	const QString statDesc, TNMsgData msgData)
{
    Q_UNUSED(type);
    Q_UNUSED(statDesc);
    Q_UNUSED(statCode);
    bool isSameSession = false;
	bool isAt = false;
	bool isSendName = false;
	//接收消息
	if (_currentAdpter != NULL){
        QString sessionId = _currentAdpter->getSessionId();
        isSameSession = (sessionId == msgData.sessionId);
	}
	if (isSameSession){
        Q_ASSERT(_currentAdpter);
        if (msgData.type == MSG_TYPE_NOTICE){ // 有群聊成员退出群聊通知
            _membersWidget->resetSession(_currentAdpter);
		}else if (msgData.bizType == MSG_BIZ_GROUPCHAT && !msgData.senderName.isEmpty() && !msgData.bIsMyself){
			isSendName = true;
			_currentAdpter->setSenderName(msgData.senderName);
		}
        setSessionLastMsg((MESSAGE_TYPE)msgData.type, msgData.data, _currentAdpter, isAt, isSendName, msgData.from);
		_currentAdpter->setTime(msgData.timestmp);
		_currentAdpter->setIsAtMe(msgData.bIsAtMe);

        //当前会话激活
        bool isActive = isNoticeActive();
        _currentAdpter->setActive(isActive);
        if(isActive){
            TNIMCoreClient::GetIMClient()->ReadSession(_currentAdpter->getSessionId());
        }else{
            qInfo() << "[Toon][NoticeDetailsArea] on_notifyRefresh current session is not active";
        }
        emit activeSessionTop(*_currentAdpter, true, msgData.bIsMyself,isActive,true,msgData.bIsBubble);
        AppendRecvWidget((MESSAGE_TYPE)msgData.type, msgData, _currentAdpter->getMyFeedId(), false);
        //创建未读消息悬浮窗
        bool isBootom = _tableView->getIsScrollToBottom();
        if(!isBootom){
            if(_tnDetailsUnreadWdiget->getUpOrDown()){//up
                showUnreadWidget(0,false,false,true);//先清0
            }
            //down
            showUnreadWidget(0,false,true,false);
        }else if(!isActive && isBootom){
            if(_tnDetailsUnreadWdiget->getUpUnreadNum() == 1){
                _tnDetailsUnreadWdiget->setFirstUnreadMsgId(msgData.msgId);
            }
            showUnreadWidget(0,true,true);
        }
    }else{
		//不是当前选中会话发来的消息,更新未读消息
		TNMessageListAdapter messageListAdapter(msgData.sessionId, msgData.bizType);
		messageListAdapter.setTime(msgData.timestmp);
		QString photoId;
		QString photoUrl;
		if (msgData.bizType == MSG_BIZ_SINGLECHAT){
			st_FeedPtr feedInfo;
			//多端多活判断是否自己发来的消息
            QString getFeedInfoId;
			if (!msgData.bIsMyself){
                getFeedInfoId = msgData.from;
				TNUserDataHelper::GetInstance()->GetFeedInfo(msgData.from, feedInfo);
				messageListAdapter.setMyFeedId(msgData.to);
			}else{
                getFeedInfoId = msgData.to;
                TNUserDataHelper::GetInstance()->GetFeedInfo(msgData.to, feedInfo);
				messageListAdapter.setMyFeedId(msgData.from);
			}
            if(feedInfo.get() != NULL){
                messageListAdapter.setName(feedInfo->GetTitle());
                messageListAdapter.setToFeed(feedInfo->GetFeedID());
				photoId = TNPathUtil::getFeedAvatarPath(feedInfo->GetFeedID());
                photoUrl = feedInfo->GetAvatarID();
            }else{
                //notice 日志
                QString qs_log = "[Notice] [NoticeDetailsArea] on_notifyRefresh + GetFeedInfo failed feedId:" + getFeedInfoId;
                qInfo() << qs_log;
            }
		}else if (msgData.bizType == MSG_BIZ_GROUPCHAT){
			TableBaseVec groupTableBaseVec;
			QString groupId = msgData.sessionId;
			TNDataControlServer::GetInstance()->Query(groupTableBaseVec, "GroupInfo", "groupId", groupId, DBTYPE_USER);
            if (groupTableBaseVec.size() > 0){
				st_GroupInfoPtr groupInfo = std::dynamic_pointer_cast<st_GroupInfo>(*groupTableBaseVec.begin());
                if(groupInfo.get() == NULL){
                    return;
                }
				messageListAdapter.setName(groupInfo->GetName());
				messageListAdapter.setMyFeedId(groupInfo->GetMyFeedId());
				messageListAdapter.setToFeed(groupId);
				photoId = TNPathUtil::getFeedAvatarPath(groupInfo->GetGroupId()) + "_org";
				photoUrl = groupInfo->GetHeaderImage();
			}else{
				TNHttpObtainGroupChatInfoByGroupChatIdSyn obtainGroupChatInfoByGroupChatIdSyn;
				if (obtainGroupChatInfoByGroupChatIdSyn.obtainGroupChatInfo(_pluginParam, groupId.mid(3))){
					QString groupChatName = obtainGroupChatInfoByGroupChatIdSyn.getGroupChatName();
					QString myFeedId = obtainGroupChatInfoByGroupChatIdSyn.getMyFeedId();
					QString groupChatHeadImage = obtainGroupChatInfoByGroupChatIdSyn.getGroupChatHeadImage();

					messageListAdapter.setName(groupChatName);
					messageListAdapter.setMyFeedId(myFeedId);
					messageListAdapter.setToFeed(groupId);
					photoId = TNPathUtil::getFeedAvatarPath(groupId) + "_org";
					photoUrl = groupChatHeadImage;
				}
			}
			if (msgData.bIsAtMe && !_atActiveList.contains(groupId)){ //插入一个有标记即可
				_atActiveList.append(groupId);
			}
			if (msgData.type != MSG_TYPE_NOTICE && !msgData.bIsMyself){
				isSendName = true;
				messageListAdapter.setSenderName(msgData.senderName);
			}
			if (_atActiveList.indexOf(groupId) != -1){
				isAt = true;
			}
		}
        setSessionLastMsg((MESSAGE_TYPE)msgData.type, msgData.data, &messageListAdapter, isAt, isSendName, msgData.from);
		messageListAdapter.setAvatarPhotoUrl(photoUrl);
		messageListAdapter.setPhotoResID(photoId);

        QString currentSelectFeed = TNDataCache::GetInstance()->GetCurrentMyFeed();
        if(currentSelectFeed == AVATAR_ALL_FEED ||
                currentSelectFeed == messageListAdapter.getMyFeedId()){
            qInfo() << "[Notice] [NoticeDetailsArea] currentSelectFeed:" << currentSelectFeed << "adapter feedId:" << messageListAdapter.getMyFeedId();
            emit activeSessionTop(messageListAdapter, false, msgData.bIsMyself,true,true,msgData.bIsBubble);
        }
        emit unReadCountSignal(messageListAdapter.getMyFeedId(),1,messageListAdapter.getType());
    }
}

void NoticeDetailsArea::on_notifyRefresh(QString type, TNNoticeInfo &noticeInfo)
{
    Q_UNUSED(type);
	//第一期屏蔽小秘书的可以聊天问题,小秘书聊天sessionid为feedid
	QList<st_FeedPtr> myStuff;
	QString feedId = noticeInfo.sessonId;
	TNDataCache::GetInstance()->getMyStuff(myStuff, feedId);
	if (myStuff.size() > 0)
		return;
	if (noticeInfo.sessonId == _pluginParam->strTnUserID){
		return;
	}

	bool isSameSession = false;
    bool isActive = isNoticeActive();
    if (_currentAdpter)
		isSameSession = QString::compare(_currentAdpter->getSessionId(), noticeInfo.sessonId) == 0;
	if (isSameSession){
		ui->tableWidget->appendNoticeCard(noticeInfo);
        //当前会话激活
        if(isActive){
            TNIMCoreClient::GetIMClient()->ReadSession(_currentAdpter->getSessionId());
        }
	}
	QString avatarUrl;
	QString title;
	if (noticeInfo.sessonId.indexOf("g_") >= 0){
		//群组公告
		st_FeedPtr feed;
		TNUserDataHelper::GetInstance()->GetFeedInfo(noticeInfo.sessonId, feed);
		if (feed.get() != NULL){
			avatarUrl = feed->GetAvatarID();
			title = feed->GetTitle();
		}
	}else{
		st_MessageAppInfoPtr appInfo;
		TNUserDataHelper::GetInstance()->GetAppInfo(noticeInfo.sessonId, appInfo);
		if (appInfo.get() != NULL){
			avatarUrl = appInfo->GetAppLittleIcon();
			title = appInfo->GetAppTitle();
		}
	}
	TNMessageListAdapter aMessageListAdapter(noticeInfo.sessonId, MSG_BIZ_NOTIFY);
	aMessageListAdapter.setAvatarPhotoUrl(avatarUrl);
	aMessageListAdapter.setName(title); // 通知会话标题
	aMessageListAdapter.setLastMessage(noticeInfo.summary);
	aMessageListAdapter.setSessionId(noticeInfo.sessonId);
	aMessageListAdapter.setPhotoResID(TNPathUtil::getFeedAvatarPath(noticeInfo.sessonId));
	aMessageListAdapter.setMyFeedId(noticeInfo.rightFeed); // 我的ID
	QDateTime curTime = QDateTime::currentDateTime();
	aMessageListAdapter.setTime(curTime.toTime_t());
    QString currentSelectFeed = TNDataCache::GetInstance()->GetCurrentMyFeed();
    //通知不分名片
    if(currentSelectFeed == AVATAR_ALL_FEED){
        emit activeSessionTop(aMessageListAdapter, isSameSession, false, isSameSession ? isActive : true);
    }
    if(!isSameSession){
        emit unReadCountSignal(aMessageListAdapter.getMyFeedId(),1,aMessageListAdapter.getType());
    }
}

void NoticeDetailsArea::on_notifyRefresh(int type, QList<UINotifyData> dataList)
{
    if (_currentAdpter){
        if ((_currentAdpter->getType() == MSG_BIZ_GROUPCHAT)
            && (type == RefreshTypeUI_GroupChat || type == RefreshTypeUI_GroupMember)){
            for(QList<UINotifyData>::const_iterator itera = dataList.begin();
                itera != dataList.end();++itera){
                if(itera->feedId == _currentAdpter->getSessionId()){
                    _membersWidget->resetSession(_currentAdpter);
                }
            }
        }
    }
    //群聊名称更改
    if (type != RefreshTypeUI_GroupChat)
        return;
    for(QList<UINotifyData>::const_iterator itera = dataList.begin();
        itera != dataList.end();++itera){
        if(itera->operateType == UI_OPERATE_ADD){
            emit updateSessionName(itera->feedId);
            if (_currentAdpter){
                if (_currentAdpter->getSessionId() == itera->feedId)
                    ui->pushButton_top_name->setText(wrapTitleLabelName(_currentAdpter->getName()));
            }
        }
        if(itera->operateType == UI_OPERATE_ADD){
            // 通知创建群聊的Loading停止
            _membersWidget->stopLoading(itera->feedId);
        }
    }
}

void NoticeDetailsArea::onPsuhButtonName(bool checked)
{
    QPushButton *sendButton = qobject_cast<QPushButton *>(sender());
    if (sendButton == ui->pushButton_top_name){
        ui->pushButton_top_arrow->setChecked(checked);
        if (checked)
            TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_NoticeDetail_Member, _pluginParam);
    }
    if (sendButton == ui->pushButton_top_arrow){
        ui->pushButton_top_name->setChecked(checked);
        if (checked)
            TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_NoticeDetail_ChatDropDown, _pluginParam);
    }

	if (checked){
        // 设置群聊下拉框的位置
        // int x = ui->widget_top_add->geometry().right() - _membersWidget->width() + 1;
        int x = ui->tableView_details->geometry().right() - _membersWidget->width() + 1;
        int y = ui->widget_top_add->geometry().bottom() + 1;
        int w = _membersWidget->width();
        int h = this->height() - ui->widget_top_add->geometry().height();
        _membersWidget->setGeometry(x, y, w, h);
        _membersWidget->updateTableWidget();
        _membersWidget->show();
        _membersWidget->raise();
    }else{
        _membersWidget->hide();
	}
}

void NoticeDetailsArea::wheelEvent(QWheelEvent *event)
{
    return TNChatDetailBase::wheelEvent(event);
}

void NoticeDetailsArea::showHistoryGif()
{
    //出现历史消息gif,同时加载历史数据
    if (_lodingHositoryGif == NULL){
        _lodingHositoryGif = new tnLoadingHository(this);
        _lodingHositoryGif->setStyleSheet("background-color: #FFFFFF;border: none;");
        QPoint pos = ui->widget_top_add->pos();
        _lodingHositoryGif->move(pos.x(), pos.y() + ui->widget_top_add->height());
        _lodingHositoryGif->show();
    }else{
        QPoint pos = ui->widget_top_add->pos();
        _lodingHositoryGif->move(pos.x(), pos.y() + ui->widget_top_add->height());
        _lodingHositoryGif->show();
    }
}

void NoticeDetailsArea::loadHistoryMsg(int num, bool isJump)
{
    showHistoryGif();
    //加载历史数据
    if (!_isLoading){
        _isLoading = true;
        _loadHistoryData->readCurrentSessionMore(num,isJump);
    }
}

void NoticeDetailsArea::loadUpJumpMsg(const QString& firstUnreadMsgId)
{
    showHistoryGif();
    //加载历史数据
    if (!_isLoading){
        _isLoading = true;
        _loadHistoryData->readDataJump(firstUnreadMsgId);
    }
}

void NoticeDetailsArea::loadHistoryFinshed(bool isLastPage, int num, bool isJump)
{
	_isLastMsg = isLastPage;
	if (_lodingHositoryGif != NULL){
        if(_msgModel->getModelSize() == 0 || num == 0){
            _lodingHositoryGif->hide();
            _isLoading = false;//当前加载结束
            return;
        }
        if(!isJump){
            if (!_isLastMsg){
                QModelIndex qindex;
                int modelSize = _msgModel->getModelSize();
                _modelSize = modelSize;
                if (modelSize % num == 0){
                    qindex = _msgModel->index(num, 0);
                }else{
                    qindex = _msgModel->index(modelSize % num, 0);
                }
                _tableView->scrollTo(qindex, QAbstractItemView::PositionAtTop);
            }else{
                if (_modelSize != _msgModel->getModelSize()){
                    QModelIndex qindex;
                    int modelSize = _msgModel->getModelSize();
                    int last_fresh_size = modelSize - _modelSize;
                    if (last_fresh_size % num == 0){
                        qindex = _msgModel->index(num, 0);
                    }else{
                        qindex = _msgModel->index(last_fresh_size % num, 0);
                    }
                    _tableView->scrollTo(qindex, QAbstractItemView::PositionAtTop);
                }
            }
        }else{
            //跳到加载数据的第一条的item
            _tableView->scrollTo(_msgModel->index(0,0));
        }
        _isLoading = false;//当前加载结束
        _lodingHositoryGif->hide();
    }
}

void NoticeDetailsArea::slotCreateGroupChatFinished(TNMessageListAdapter session)
{
    emit activeSessionTop(session, true, true, isNoticeActive(),true,false);
}

void NoticeDetailsArea::slotExitGroupChatFinished(TNMessageListAdapter adpter)
{
	_atActiveList.removeOne(adpter.getSessionId());
	_currentAdpter = NULL;
    emit removeSession(adpter,true);
	ui->stackedWidget->setCurrentIndex(2);
    if(_tnDetailsUnreadWdiget){
        showUnreadWidget(0,false,false,true);
    }
    if(_someOneAtYouWidget){
        _someOneAtYouWidget->hide();
        _someOneAtYouData.clear();
    }
}

void NoticeDetailsArea::slotUpdateArrowStatus()
{
    if (_membersWidget)
        _membersWidget->hide();
	ui->pushButton_top_name->setChecked(false);
    ui->pushButton_top_arrow->setChecked(false);
}

void NoticeDetailsArea::dragFileSend(QString filePath)
{
    if(qApp->activeModalWidget()){
        return;
    }
    QFileInfo fileInfo(filePath);
    if (fileInfo.size() > MAX_FILE_SIZE || fileInfo.size() <= 0){
        QString content = ("发送的文件大小不能大于60MB且不能为0");
        TNMessageBox messageBox(this);
        messageBox.setMsg(content);
        messageBox.exec();
        return;
    }

	QFileInfo info(filePath);
	if (info.isFile())
    {
        TNSendConfirmDialog dialog;
        dialog.setLabelTitle(("发送附件"));
        dialog.setFilePath(filePath);
        //设置窗口置顶
#ifdef Q_OS_WIN
        ::SetWindowPos(HWND(dialog.winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
        ::SetWindowPos(HWND(dialog.winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
#endif
        TNUtil::moveCenterInMainWidget(&dialog);
        if (dialog.exec() != QDialog::Accepted)
        {
            return;
        }
        AppendSendWidget(em_file, filePath, false);
    }
}

void NoticeDetailsArea::dragFileBatchSend(const QStringList &filePaths)
{
    if(qApp->activeModalWidget()){
        return;
    }
    QStringList validFileNames;
    foreach (const QString &filePath, filePaths)
    {
        QFileInfo fileInfo(filePath);
        if (fileInfo.size() > MAX_FILE_SIZE || fileInfo.size() <= 0)
        {
            continue;
        }
        validFileNames.append(filePath);
    }
    if (validFileNames.isEmpty())
    {
        TNMessageBox messageBox(this);
        messageBox.setMsg(("发送的文件大小不能超过60M且不能为0"));
        messageBox.exec();
        return;
    }

    TNBatchSendFileConfirmDialog dialog(filePaths);
    //设置窗口置顶
#ifdef Q_OS_WIN
    ::SetWindowPos(HWND(dialog.winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    ::SetWindowPos(HWND(dialog.winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
#endif
    TNUtil::moveCenterInMainWidget(&dialog);
    if (dialog.exec() == QDialog::Accepted)
    {
        QStringList fileNames = dialog.getFileNames();
        foreach (const QString &fileName, fileNames)
        {
            QFileInfo info(fileName);
            if (info.isFile())
            {
                AppendSendWidget(em_file, fileName, false);
            }
        }
    }
}

void NoticeDetailsArea::dragImageSend(QString filePath)
{
    if(qApp->activeModalWidget()){
        return;
    }
    TNSendConfirmDialog dialog;
    dialog.setLabelTitle(("发送图片"));
    QString suffix = TNImageCtr::getImageTypeRetString(filePath);
    dialog.setImagePath(filePath,suffix);
    //设置窗口置顶
#ifdef Q_OS_WIN
    ::SetWindowPos(HWND(dialog.winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    ::SetWindowPos(HWND(dialog.winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
#endif
    TNUtil::moveCenterInMainWidget(&dialog);
    if (dialog.exec() != QDialog::Accepted)
    {
        return;
    }

    AppendSendWidget(em_image, filePath, false);
}

void NoticeDetailsArea::dragImageBatchSend(const QStringList &filePaths)
{
    if(qApp->activeModalWidget()){
        return;
    }
    TNBatchSendImageConfirmDialog dialog(filePaths);
    dialog.setLabelTitle(("发送图片"));
    //设置窗口置顶
#ifdef Q_OS_WIN
    ::SetWindowPos(HWND(dialog.winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    ::SetWindowPos(HWND(dialog.winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
#endif
    TNUtil::moveCenterInMainWidget(&dialog);
    if (dialog.exec() == QDialog::Accepted)
    {
        QStringList fileNames = dialog.getFileNames();
        foreach (const QString &fileName, fileNames)
        {
            AppendSendWidget(em_image, fileName, false);
        }
    }
}

void NoticeDetailsArea::warnMaxFileSize(QString content)
{
    TNMessageBox messageBox(this);
    messageBox.setMsg(content);
    messageBox.exec();
}

void NoticeDetailsArea::on_notifyRemoveSession(QString sessionId)
{
    bool isSelected = false;
	TNMessageListAdapter tempMessageListAdapter(sessionId, MSG_BIZ_GROUPCHAT);
	if (_currentAdpter != NULL){
		if (_currentAdpter->getSessionId() == sessionId){
            isSelected = true;
			_currentAdpter = NULL;
			ui->stackedWidget->setCurrentIndex(2);
            if(_tnDetailsUnreadWdiget){
                showUnreadWidget(0,false,false,true);
            }
            if(_someOneAtYouWidget){
                _someOneAtYouWidget->hide();
                _someOneAtYouData.clear();
            }
		}
	}
	_atActiveList.removeOne(sessionId);
    emit removeSession(tempMessageListAdapter, isSelected);
}
//手机端已读
void NoticeDetailsArea::on_notifyReadSession(QString sessionId)
{
    _atActiveList.removeOne(sessionId);
	emit readSessionUnreadNum(sessionId, 0);
}
void NoticeDetailsArea::revokeProcess(int resultType, int msgType, qint64 msgTime, const QString &sessionId, const QString &msgId, const QString &pushInfo)
{
    qDebug() << resultType;
    switch (resultType){
    case 0:{
        TNMessageBox messageBox(this);
        messageBox.setMsg(tr(REVOKE_FAILED_TEXT));
        messageBox.setPositionToParent(200, 200);
        messageBox.exec();
    }
        break;
    case 1:{
        if (msgId.isEmpty())
            return;
        bool isSameSession = false;
        if (_currentAdpter != NULL){
            isSameSession = QString::compare(_currentAdpter->getSessionId(),sessionId) == 0;
        }
        if (isSameSession){
            TNModelUserMessage *itemData = NULL;
            int index = _msgModel->findItemData(msgId, &itemData);
            if (itemData != NULL  && index != -1){
                //删除原始Item.
                _msgModel->removeData(index, 1);
                AppendRevokeWidget(pushInfo, (MESSAGE_TYPE)msgType, resultType, index);
            }
        }else{
            TNMessageListAdapter messageListAdapter(sessionId, msgType);
            messageListAdapter.setTime(msgTime);
            setSessionLastMsg((MESSAGE_TYPE)msgType, pushInfo, &messageListAdapter,false,false);
            emit activeSessionTop(messageListAdapter,false,true);
            //撤回消息消息条数减1
            //emit reduceUnreadNum(messageListAdapter.getSessionId(),-1);
        }
    }
        break;
    default:
        break;
    }
}
void NoticeDetailsArea::slotEditCtr(int position,int charsRemoved,int charsAdded)
{
    bool isGChat = false;
    if (_currentAdpter != NULL){
        isGChat = QString::compare(_currentAdpter->getSessionId().mid(0,2), "gc") == 0;
    }
    if (isGChat){
        /*
        int start = position;
        int end = ui->textEdit_Send->textCursor().position();
        QTextDocument* doc = ui->textEdit_Send->document();
        QTextBlock from = doc->findBlock(start);
        QTextBlock till = doc->findBlock(end);
        if (till.isValid()) till = till.next();

        for (QTextBlock b = from; b != till; b = b.next()) {
            for (QTextBlock::Iterator iter = b.begin(); !iter.atEnd(); ++iter) {
                QTextFragment fragment(iter.fragment());
                if (!fragment.isValid()) continue;

                int p = fragment.position(), e = (p + fragment.length());

                if (p >= end || e <= start) {
                    continue;
                }
                QTextCharFormat f = fragment.charFormat();
                if(f.isCharFormat()){
                    QString t(fragment.text());
                    if (p < start) {
                        t = t.mid(start - p, end - start);
                    } else if (e > end) {
                        t = t.mid(0, end - p);
                    }
                    if(t == "@"){
                        qDebug() << "@";
                    }
                }
            }
        }
        */
        QString plain_text = ui->textEdit_Send->document()->toPlainText();
        int pos = plain_text.lastIndexOf('@');
        if (pos != -1 && ui->textEdit_Send->_isActiveByKey == true)
        {
            ui->textEdit_Send->_isActiveByKey = false;
            QString text = plain_text.right(ui->textEdit_Send->textCursor().position()- pos - 1);
            qInfo() << "[Notice][NoticeDetailsArea]slotEditCtr @text:"<<text;

            int emoji_height = mapToParent(ui->widget->pos()).ry();
            int edit_Width = ui->textEdit_Send->width();
            QPoint p = mapToParent(ui->widget_emoji_file_pic->pos());

            QRect rect = ui->textEdit_Send->cursorRect();
            int itemCount = DoSearch(text, _currentAdpter->getSessionId(), _currentAdpter->getMyFeedId());

            int validX = 0,validY = 0;
            if ((rect.x() + LIST_AT_WIDTH) > edit_Width)
            {
                validX = edit_Width - LIST_AT_WIDTH + 10;
                validY = p.y() + emoji_height - LIST_AT_HEIGHT * (itemCount > 5 ? 5 : itemCount) + rect.y();
            }
            else
            {
                validX = p.x() + rect.x() + 20;
                validY = p.y() + emoji_height - LIST_AT_HEIGHT * (itemCount > 5 ? 5 : itemCount) + rect.y();
            }
            qInfo() << "[Notice][NoticeDetailsArea]slotEditCtr @ search Item count:" << itemCount;
            InitATSearchPage(validX, validY, itemCount);
            //_lastAtPosition = ui->textEdit_Send->textCursor().position();
            _bisAting = itemCount > 0 ? true:false;
            if (itemCount > 0)
            {
                _ATSearchArea->ShowDialog();
            }
        }
        else
        {
            _bisAting = false;
            if (!_ATSearchArea->isHidden())
                _ATSearchArea->hide();
        }
    }
}

void NoticeDetailsArea::SearchClickedSlot(QString name,QString feedId,QString nickName)
{
    Q_ASSERT(!name.isEmpty() && !feedId.isEmpty() && !nickName.isEmpty());
    insertTag(name, feedId, nickName);
}

void NoticeDetailsArea::insertTag(const QString &text, const QString &feedId,const QString& feedName)
{
    QTextCursor cursor = ui->textEdit_Send->textCursor();
    int pos = cursor.position();
    QTextDocument* doc = ui->textEdit_Send->document();
    QTextBlock block = doc->findBlock(pos);
    for(QTextBlock::Iterator iter = block.begin(); iter != block.end(); ++iter){
        QTextFragment fragment = iter.fragment();
        Q_ASSERT(fragment.isValid());
        int fragmentPosition = fragment.position();
        int fragmentEnd = fragmentPosition + fragment.length();
        if(fragmentPosition >= pos || fragmentEnd < pos)
            continue;

        QTextCharFormat format = fragment.charFormat();
        if(format.isImageFormat())
            continue;

        QString fragmentText = fragment.text();
        int atPos = fragmentText.lastIndexOf('@');
        if(atPos != -1){
            int movePos = fragmentText.mid(atPos).size();
            cursor.movePosition(QTextCursor::Left,QTextCursor::KeepAnchor,movePos);
            qDebug() << cursor.selectedText();
            cursor.removeSelectedText();

            QTextCharFormat format;
            format.setObjectType(TN::TO_ObjectAt);
            format.setProperty(TN::OP_Text, QVariant::fromValue("@" + text));
            format.setProperty(TN::OP_TextFont, QVariant::fromValue(ui->textEdit_Send->currentFont().toString()));
            format.setAnchor(true);
            QString tagId = "toon://feedid_" + feedId  + "#" + "feedName_" + feedName + "#" + "showText_" + text;
            format.setAnchorName(tagId);
            cursor.insertText(QString(QChar::ObjectReplacementCharacter), format);
            //将格式置回
            QTextCharFormat charFormat;
            charFormat.setAnchor(false);
            cursor.mergeCharFormat(charFormat);
            break;
        }
    }
    _bisAting = false;
    ui->textEdit_Send->setFocus();
}

void NoticeDetailsArea::reverseAtObject(int pos, QString atFeedId, QString atFeedName,QString showText)
{
    Q_UNUSED(pos);
    QTextCursor cursor = ui->textEdit_Send->textCursor();

    QTextCharFormat format;
    format.setObjectType(TN::TO_ObjectAt);
    format.setProperty(TN::OP_Text, QVariant::fromValue("@" + showText));
    format.setProperty(TN::OP_TextFont, QVariant::fromValue(ui->textEdit_Send->currentFont().toString()));
    format.setAnchor(true);
    QString tagId = "toon://feedid_" + atFeedId + "#" + "feedName_" + atFeedName + "#" + "showText_" + showText;
    format.setAnchorName(tagId);
    cursor.insertText(QString(QChar::ObjectReplacementCharacter), format);
    //将格式置回
    QTextCharFormat charFormat;
    charFormat.setAnchor(false);
    cursor.mergeCharFormat(charFormat);

    ui->textEdit_Send->setFocus();
}

void NoticeDetailsArea::InitATSearchPage(int x, int y, int itemCount)
{
	_ATSearchArea->hide();
	_ATSearchArea->move(x,y);
	_ATSearchArea->setSize(LIST_AT_WIDTH, LIST_AT_HEIGHT * (itemCount>5 ? 5 : itemCount));
	_ATSearchArea->setFixedWidth(LIST_AT_WIDTH+10);
	_ATSearchArea->setFixedHeight(LIST_AT_HEIGHT * (itemCount>5 ? 5 : itemCount)+4);
}
int NoticeDetailsArea::DoSearch(const QString &text,const QString &groupId,const QString &myFeed)
{
	QList<TNATSearchAdapter*> searchResult;
	QList<TNFriend> result = TNDataCache::GetInstance()->GetGroupChatMemberCache(groupId);

	for(TNFriend member:result)
	{
		if (member.m_friendFeedId == myFeed)
		{
			continue;
		}
		QString tempName = member.m_nickName;
		QString tempPy = member.m_pinYin;
		TNStructRemark sRemark = TNDataCache::GetInstance()->getFriendFeedReMarkWithPY(member.m_friendFeedId, myFeed);
		QString tempRemark = sRemark.remark;
		QString tempRemarkPY = sRemark.remarkPy;

		if (tempName.replace(" ", "").contains(text, Qt::CaseInsensitive) || tempPy.replace(" ", "").contains(text, Qt::CaseInsensitive)||
			tempRemark.replace(" ", "").contains(text, Qt::CaseInsensitive) || tempRemarkPY.replace(" ", "").contains(text, Qt::CaseInsensitive))
		{
			TNATSearchAdapter * tempAdapter = new TNATSearchAdapter();
			if (tempRemark.isEmpty())
				tempAdapter->setName(member.m_nickName);
			else
				tempAdapter->setName(tempRemark);

			tempAdapter->setNickName(member.m_nickName);
			tempAdapter->setDialogID(member.m_friendFeedId);
			QString avatarFileName = TNPathUtil::getFeedAvatarPath(member.m_friendFeedId);
			bool isForceRefreshAvator = false;
			if (!QFile::exists(avatarFileName))
			{
				isForceRefreshAvator = true;
				avatarFileName = (":/Resources/toolWidget/defaultAvatar.png");
			}
			tempAdapter->setAvatarUrl(member.m_avatarURL);
			tempAdapter->setIsForeceRefreshAvator(isForceRefreshAvator);
			tempAdapter->setPhotoResID(avatarFileName);
			searchResult.append(tempAdapter);
		}
	}

	if (searchResult.size() > 0)
	{
		_ATSearchArea->setSearchResult(searchResult);
	}
	return searchResult.size();
}

void NoticeDetailsArea::someoneAtme(const QString &name, const QString &msgId, int index)
{
    Q_ASSERT(!msgId.isEmpty() && !name.isEmpty());
    SomeOneAtData data(name,msgId,index);
    _someOneAtYouData.push_back(data);
    //显示someoneAtme
    showSomeoneAtme();
}

void NoticeDetailsArea::showSomeoneAtme()
{
    if(!moveSomeOneAtWidget())
        return;
    if(_tnDetailsUnreadWdiget){
        if(!_tnDetailsUnreadWdiget->isHidden()){
            _tnDetailsUnreadWdiget->hide();
        }
    }
    _someOneAtYouWidget->show();
    _someOneAtYouWidget->raise();
}

void NoticeDetailsArea::atMsgBoxCliecked(QString msgId, int index, bool isScroll)
{
    if(isScroll){
        if(index != -1){
            _tableView->scrollTo(_msgModel->index(index, 0),QAbstractItemView::PositionAtBottom);
        }else{
            //加载历史数据到@的msgId,并跳转
        }
    }
    _someOneAtYouData.pop_front();
    showSomeoneAtme();
}

void NoticeDetailsArea::on_manualModifyGroupName(QString sessionId, QString name)
{
	if (_currentAdpter != NULL){
		if (sessionId == _currentAdpter->getSessionId()){
            ui->pushButton_top_name->setText(wrapTitleLabelName(name));
		}
	}
}

void NoticeDetailsArea::feedCardUpdateFromCatche(const QString &feedId,
                                                 const QString &avatarId,
                                                 const QString &name,
                                                 const QString &subName,
                                                 const QString &userId,
                                                 const QString &namePy,
                                                 int sourceType)
{
    Q_UNUSED(avatarId);
    Q_UNUSED(subName);
    Q_UNUSED(userId);
    Q_UNUSED(namePy);
    Q_UNUSED(sourceType);
    if (_currentAdpter != NULL){
        if (feedId == _currentAdpter->getToFeed()){
            ui->pushButton_top_name->setText(wrapTitleLabelName(name));
        }
    }
}

//手动删除当前会话
void NoticeDetailsArea::on_manualRemoveCurrentSession(const QString& sessionId,bool isSelected)
{
    _membersWidget->hide();
	if (isSelected)
	{
		_currentAdpter = NULL;
		_msgModel->clearData();
		ui->stackedWidget->setCurrentIndex(2);
		if (_tnDetailsUnreadWdiget){
			showUnreadWidget(0, false, false, true);
		}
        if(_someOneAtYouWidget){
            _someOneAtYouWidget->hide();
            _someOneAtYouData.clear();
        }
	}
	_atActiveList.removeOne(sessionId);
}

void NoticeDetailsArea::on_notifySendHotKeyChanged(const QString &key)
{
    if (key == "Enter" || key == "Return")
    {
        _isSendNeedPressCtrl = false;
    }
    else
    {
        _isSendNeedPressCtrl = true;
    }
}
void NoticeDetailsArea::resizeEvent(QResizeEvent *event)
{
	if (_ATSearchArea != nullptr && !_ATSearchArea->isHidden())
	{
		int Width = 0;
		int Height = 0;
		_ATSearchArea->getSize(Width, Height);
		if (Width != 0 && Height != 0)
		{
			int emoji_height = mapToParent(ui->widget->pos()).ry();
			QPoint p = mapToParent(ui->widget_emoji_file_pic->pos());
			QRect rect = ui->textEdit_Send->cursorRect();
			_ATSearchArea->move(p.x() + rect.x() + 20, p.y() + emoji_height - Height + rect.y());
		}
	}
    // 重新设定群聊下拉框的位置
    // int x = ui->widget_top_add->geometry().right() - _membersWidget->width() + 1;
    int x = ui->tableView_details->geometry().right() - _membersWidget->width() + 1;
    int y = ui->widget_top_add->geometry().bottom() + 1;
    int w = _membersWidget->width();
    int h = this->height() - ui->widget_top_add->geometry().height();
    _membersWidget->setGeometry(x, y, w, h);

    TNChatDetailBase::resizeEvent(event);
}

bool NoticeDetailsArea::moveSomeOneAtWidget()
{
    Q_ASSERT(_someOneAtYouWidget);

    if(_someOneAtYouData.size() <= 0){
        _someOneAtYouWidget->hide();
        return false;
    }
    SomeOneAtData data = _someOneAtYouData.front();
    _someOneAtYouWidget->setText(data.atName + (" @你"));
    _someOneAtYouWidget->SetIndex(data.index);
    _someOneAtYouWidget->setMsgId(data.msgId);

    int width = _someOneAtYouWidget->width();
    int height = _someOneAtYouWidget->height();

    QPoint b_r = ui->widget_details->rect().bottomRight();
    _someOneAtYouWidget->setGeometry(b_r.x() - width + 2, b_r.y(), width, height);
    return true;
}

void NoticeDetailsArea::deleteMsgSlots(const QString &msgId)
{
	if (msgId.isEmpty())
		return;

	TNModelUserMessage *itemData = NULL;
	int index = _msgModel->findItemData(msgId, &itemData);
	if (itemData != NULL  && index != -1){
        QString sessionId = itemData->getSessionId();
		_msgModel->removeData(index, 1);
        Q_ASSERT(_currentAdpter);
        TNIMCoreClient::GetDBChat()->deleteMessage(_currentAdpter->getSessionId().toStdString().c_str(),msgId.toStdString().c_str());
        if (index - 1 > 0)
            _tableView->scrollTo(_msgModel->index(index - 1, 0));
        //删除会话最后一条消息
        if(_msgModel->rowCount() == index){
            emit updateSessionLastMsg(sessionId);
        }
	}
}

void NoticeDetailsArea::on_reSendData(TNModelUserMessage data)
{
    _currentAdpter->setTime(QDateTime::currentDateTime().toTime_t());
    setSessionLastMsg(data.GetMessageType(), data.GetUserMessage(), _currentAdpter,false,false);
    emit activeSessionTop(*_currentAdpter, true, true);
    _tableView->setScrollToBottom(true);//发送数据时，滚动条需要滚动到底部
}

QString NoticeDetailsArea::generateDraft()
{
    QJsonObject jsonObject;
    QJsonArray  draftArray;
    bool isHaveImage = false,isHaveObjectAt = false;
    //从富文本中生成数据
    std::list<edit_content> list_edit_content = TNConvertRichEdit::getText(ui->textEdit_Send->document(),0,-1);
    QString content;
    if(list_edit_content.size() <= 1){
        for(std::list<edit_content>::const_iterator itera = list_edit_content.begin();
            itera != list_edit_content.end(); ++itera){
            isHaveImage = (itera->type == edit_content::content_type_image);
            isHaveObjectAt = (itera->type == edit_content::content_type_objectAt);
            content = itera->content;
        }
        if((content.isEmpty()  || isAllSpace(content)) && !isHaveObjectAt){
            return "";
        }
    }

    int i = 0;
    for(std::list<edit_content>::const_iterator itera = list_edit_content.begin();
        itera != list_edit_content.end(); ++itera){
        if(itera->type == edit_content::content_type_objectAt){
            QJsonObject typeObject;
            QJsonObject atObject;
            atObject.insert("block",i);
            QString show_text = itera->content;
            QString feed_id = itera->at_feedId;
            QString feed_name = itera->at_feedName;
            atObject.insert("atFeedId",feed_id);
            atObject.insert("atFeedName",feed_name);
            atObject.insert("showText",show_text);
            atObject.insert("pos",itera->pos);
            typeObject.insert("at",atObject);
            draftArray.append(typeObject);
        }else if(itera->type == edit_content::content_type_text){
            QJsonObject typeObject;
            QJsonObject txtObject;
            content = itera->content;
            txtObject.insert("block",i);
            txtObject.insert("text",content);
            typeObject.insert("text",txtObject);
            draftArray.append(typeObject);
        }
        i++;
    }

    jsonObject.insert("draft",draftArray);
    QString draft;
    QJsonDocument doc(jsonObject);
    if(!doc.isEmpty()){
        draft = doc.toJson();
    }
    qDebug() << draft;
    return draft;
}

void NoticeDetailsArea::on_notifyCurrentFeedChanged(const QString &feedId)
{
    Q_UNUSED(feedId);
    _currentAdpter = NULL;
    ui->stackedWidget->setCurrentIndex(2);
    if(_tnDetailsUnreadWdiget){
        showUnreadWidget(0,false,false,true);
    }
    if(_someOneAtYouWidget){
        _someOneAtYouWidget->hide();
        _someOneAtYouData.clear();
    }
}

bool NoticeDetailsArea::isNoticeActive()
{
    return _tableView->isActiveWindow() &&
            _pluginParam->_currentSelectPage == MENU_NOTICE_ID;
}

void NoticeDetailsArea::noticeFocuseIn()
{
    if(_currentAdpter != NULL){
        if(!_currentAdpter->getActive()){
            _currentAdpter->setActive(true);
            std::map<QTimer*,TNMessageListAdapter>::const_iterator itera
                    = _focuseInTimer.begin();
            for(;itera != _focuseInTimer.end();++itera){
                if(itera->second.getSessionId() == _currentAdpter->getSessionId()){
                    return;
                }
            }
            QTimer* tempTimer = new QTimer(this);
            connect(tempTimer,SIGNAL(timeout()),this,SLOT(onFocuseInTimeOut()));
            _focuseInTimer[tempTimer] = *_currentAdpter;
            tempTimer->start(3000);
        }
    }
}

void NoticeDetailsArea::onFocuseInTimeOut()
{
    QTimer* tempTimer = qobject_cast<QTimer*>(sender());
    std::map<QTimer*,TNMessageListAdapter>::const_iterator itera =
            _focuseInTimer.find(tempTimer);
    if(itera != _focuseInTimer.end()){
        TNMessageListAdapter adapter = itera->second;
        if(adapter.getUnreadCount() > 0){
			//同时通知托盘停止闪烁
			emit updateTrayUnRead(adapter.getSessionId());
            emit readSessionUnreadNum(adapter.getSessionId(),0);
        }
        TNIMCoreClient::GetIMClient()->ReadSession(adapter.getSessionId());
        _focuseInTimer.erase(itera);
    }
    tempTimer->stop();
    delete tempTimer;
}

void NoticeDetailsArea::showUnreadWidget(int unread,bool up,bool isAdd,bool isClear)
{
    Q_ASSERT(_tnDetailsUnreadWdiget);
    if(_currentAdpter != NULL){
        if(_currentAdpter->getType() == MSG_BIZ_NOTIFY){
            return;
        }
    }
    if(isClear){
        _tnDetailsUnreadWdiget->setUpUnReadNum(0);
        _tnDetailsUnreadWdiget->setDownUnReadNum(0);
        _tnDetailsUnreadWdiget->hide();
        return;
    }
    if (!_someOneAtYouWidget->isHidden()){
		qDebug() << "@ message is exist,so don't show unread message";
		return;
	}
    if(!up){
        //down
        _tnDetailsUnreadWdiget->setUpAndDown(false);
        _tnDetailsUnreadWdiget->addDownUnreadNum();
        moveUnreadWidget(up);
        _tnDetailsUnreadWdiget->show();
    }else{
        //up
        if(isAdd && up){
            _tnDetailsUnreadWdiget->setUpAndDown(true);
            _tnDetailsUnreadWdiget->addUpUnreadNum();
            if(_tnDetailsUnreadWdiget->getUpUnreadNum() > PAGE_NUM){
                moveUnreadWidget(up);
                _tnDetailsUnreadWdiget->show();
            }
        }else if(unread > PAGE_NUM && up){
            _tnDetailsUnreadWdiget->setUpAndDown(true);
            _tnDetailsUnreadWdiget->setUpUnReadNum(unread);
            moveUnreadWidget(up);
            _tnDetailsUnreadWdiget->show();
        }
    }
}

void NoticeDetailsArea::moveUnreadWidget(bool up)
{
    Q_ASSERT(_tnDetailsUnreadWdiget);
    int width = _tnDetailsUnreadWdiget->width();
    int height = _tnDetailsUnreadWdiget->height();
    QPoint b_r;
    if(!up){
        b_r = ui->widget_details->rect().bottomRight();
        _tnDetailsUnreadWdiget->setGeometry(b_r.x() - width + 2, b_r.y(), width, height);
    }else{
        int x = ui->widget_details->rect().bottomRight().x();
        b_r = ui->widget_top_add->rect().bottomRight();
        _tnDetailsUnreadWdiget->setGeometry(x - width + 2, b_r.y() + 20, width, height);
    }
}

void NoticeDetailsArea::onUnreadWidgetDownClicked()
{
    int downUnreadNum = _tnDetailsUnreadWdiget->getDownUnreadNum();
    _tnDetailsUnreadWdiget->setDownUnReadNum(0);
    _tnDetailsUnreadWdiget->hide();
    //跳转
    int total = _msgModel->rowCount();
    int index = 0;
    if(downUnreadNum >= 4){
        index = total - downUnreadNum + 3;
        _tableView->scrollTo(_msgModel->index(index,0));
    }else{
        _tableView->scrollToBottom();
    }
}

void NoticeDetailsArea::onUnreadWidgetUpClicked()
{
    _tnDetailsUnreadWdiget->setUpUnReadNum(0);
    _tnDetailsUnreadWdiget->hide();
    //从数据库加载历史记录,并跳转
    QString firstUnreadMsgId = _tnDetailsUnreadWdiget->getFirstUnreadMsgId();
    if(firstUnreadMsgId.isEmpty())
        return;

    QModelIndex q_index = _msgModel->getMsgIndex(firstUnreadMsgId);
    if(q_index.isValid()){
        _tableView->scrollTo(q_index);
    }else{
        //没有在当前界面然后从数据库加载
        loadUpJumpMsg(firstUnreadMsgId);
    }
    //点击之后第一条未读消息置空
    _tnDetailsUnreadWdiget->setFirstUnreadMsgId("");
}

void NoticeDetailsArea::scrollBarValueChanged(int value)
{
    if(value == _tableView->verticalScrollBar()->maximum()
            && !_tnDetailsUnreadWdiget->getUpOrDown()){
        _tnDetailsUnreadWdiget->setDownUnReadNum(0);
        _tnDetailsUnreadWdiget->hide();
    }else{
        if(_tnDetailsUnreadWdiget->isHidden())
            return;
        int row = _tableView->rowAt(value);
        if(row == -1) return;
        QModelIndex q_index = _msgModel->index(row,0);
        TNModelUserMessage* itemData = (TNModelUserMessage*)_msgModel->data(q_index).toLongLong();
        if(itemData == NULL) return;
        if(itemData->GetMsgID() == _tnDetailsUnreadWdiget->getFirstUnreadMsgId()){
            _tnDetailsUnreadWdiget->setUpUnReadNum(0);
            _tnDetailsUnreadWdiget->hide();
            _tnDetailsUnreadWdiget->setFirstUnreadMsgId("");
        }
    }
}

bool NoticeDetailsArea::isAllSpace(const QString &content)
{
    //return content.trimmed().isEmpty();
    //正则表示式判断
    QRegExp rx;
    rx.setPattern("\\S+");
    int index= rx.indexIn(content);
    return index == -1;
}

void NoticeDetailsArea::on_notifyReMarkUpdate(const QString &from, const QString &to, const QString &remark, int sources)
{
    QString session_id = TNIMCoreClient::GetSessionId(from,to,MSG_BIZ_SINGLECHAT);
    if(!_currentAdpter) return;
    if (_currentAdpter->getSessionId() == session_id)
    {
        if (!remark.isEmpty())
            ui->pushButton_top_name->setText(remark);
        else
            ui->pushButton_top_name->setText(_currentAdpter->getName());
    }
    //备注后更新后,如果名片在当前群聊中,更新当前会话详情区的所有sendName
    if(_currentAdpter->getType() == MSG_BIZ_GROUPCHAT && TNDbUtil::isInGroupChat(_currentAdpter->getSessionId(),from) && TNDbUtil::isInGroupChat(_currentAdpter->getSessionId(),to)){
        _msgModel->updateSendName(from, remark);
    }
}

QString NoticeDetailsArea::wrapTitleLabelName(const QString &oldName)
{
    QString newName(oldName);

    if (_currentAdpter->getType() == MSG_BIZ_SINGLECHAT)
    {
        const QString belongFeedId = _currentAdpter->getMyFeedId();
        const QString feedId = _currentAdpter->getToFeed();
        if (TNDbUtil::isFriendRelation(belongFeedId, feedId))
        {
            QString remark = TNDataCache::GetInstance()->getFriendFeedReMark(feedId, belongFeedId);
            if (!remark.isEmpty())
                newName = remark;
        }
    }

    if (_currentAdpter->getType() == MSG_BIZ_GROUPCHAT)
    {
        QString groupChatId = _currentAdpter->getSessionId();

        int memberCount = 0;
        st_GroupInfoPtr groupInfo = TNDbUtil::getGroupChatInfo(groupChatId);
        if (groupInfo)
        {
            memberCount = groupInfo->GetCurrNum();
            qInfo() << "[Notice] [NoticeDetailsArea] wrapTitleLabelName GroupChatInfo-memberCount="<<memberCount;
        }
        else
        {
            qInfo() << "[Notice] [NoticeDetailsArea] wrapTitleLabelName-read member count from http";
            TNHttpObtainGroupChatInfoByGroupChatIdSyn obtainGroupChatInfoByGroupChatIdSyn;
            if (obtainGroupChatInfoByGroupChatIdSyn.obtainGroupChatInfo(_pluginParam, groupChatId.mid(3)))
            {
                memberCount = obtainGroupChatInfoByGroupChatIdSyn.getCurrNum();
                qInfo() << "[Notice] [NoticeDetailsArea] wrapTitleLabelName-read member count from http. memberCount="<<memberCount;
            }
        }
        newName += QString("(%1)").arg(memberCount);
    }

    QString elidedText = ui->pushButton_top_name->fontMetrics().elidedText(newName, Qt::ElideMiddle, 400, Qt::TextShowMnemonic);
    elidedText.replace('&',"&&");
    return elidedText;
}

void NoticeDetailsArea::onTurnPage(int page)
{
    _pluginParam->_currentSelectPage = page;
    if(page == MENU_NOTICE_ID){
        noticeFocuseIn();
    }
}

void NoticeDetailsArea::onDropUrlsSlot(QList<QUrl> urls)
{
    bool hasFolder = false;
    QStringList imageFileNames;
    QStringList fileNames;
    QList<QUrl>::const_iterator itera = urls.begin();
    for (; itera != urls.end(); ++itera){
        QString filePath = itera->toLocalFile();
        if (!filePath.isEmpty()){
            QFileInfo file_info(filePath);
            if (file_info.isDir())
                hasFolder = true;
            else if (TNImageCtr::isImageFile(filePath))
                imageFileNames.append(filePath);
            else
                fileNames.append(filePath);
        }
    }

    if (hasFolder){
        TNMessageBox messagebox(this);
        messagebox.setMsg(tr(QString(QStringLiteral("不能发送文件夹")).toUtf8().data()));
        messagebox.exec();
    }

    if (imageFileNames.size() == 1)
        dragImageSend(imageFileNames.first());
    else if (imageFileNames.size() > 1)
        dragImageBatchSend(imageFileNames);

    if (fileNames.size() == 1)
        dragFileSend(fileNames.first());
    else if (fileNames.size() > 1)
        dragFileBatchSend(fileNames);
}

void NoticeDetailsArea::jumpToMsgSlots(QString msgId)
{
    if (msgId.isEmpty())
        return;

    TNModelUserMessage *itemData = NULL;
    int index = _msgModel->findItemData(msgId, &itemData);
    if (itemData != NULL  && index != -1){
        Q_ASSERT(_currentAdpter);
        _tableView->scrollTo(_msgModel->index(index, 0));
    }
}
