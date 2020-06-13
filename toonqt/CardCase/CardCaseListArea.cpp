#include <QHBoxLayout>
#include <QPushButton>
#include <QUrlQuery>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QHeaderView>
#include <QFile>
#include <QMap>
#include <QEventLoop>
#include <QLineEdit>
#include <QMargins>
#include <qthread.h>

#include "CardCaseListArea.h"
#include "QCoreApplication"
#include "QDir"
#include "../LocalStorage/TNDataControlServer.h"
#include "TNCardCaseTreeItem.h"
#include "Colleague/TNCompanyItem.h"
#include "Colleague/TNDepartmentItem.h"
#include "Colleague/TNStaffItem.h"
#include "TNPathUtil.h"
#include "time.h"
#include "TNPathUtil.h"
#include "TNHttpDownCloud.h"
#include "tnnotifycenter.h"
#include "TNDataCache.h"
#include "TNNameSpace.h"
#include "TNDataSearch.h"
#include "TNNetAvatarDown.h"
#include "TNQLineEdit.h"
#include "TNDataCache.h"
#include "TNIMCoreClient.h"
#include "TNNewFriendUtil.h"
#include "TNDataStatistics.h"
#include "TNUserDataHelper.h"
#include "Colleague/TNCoTreeView.h"
#include "TNCHNHelper.h"
#include "TNSimpleBrowser.h"

CardCaseListArea::CardCaseListArea(int id, TNPluginParamPtr pluginParam, QWidget *parent)
	: ListAreaBase(id, parent)
	, _pluginParam(pluginParam)
	, _strAvatarDir("")
	, _currentSelectedCard(-1)
	, _listCardCaseModel(nullptr)
	, _ColleagueModel(nullptr)
	, _GroupModel(nullptr)
	, _GroupChatModel(nullptr)
	, _searchMode(false)
	, _httpObtainFeedList(nullptr)
	, _httpObtainGroupInfo(nullptr)
	, _nullPageStatus(false)
	, _nullPage(nullptr)
	, _currentSelectedPage(-1)
{
	InitAvatarDir();
	InitWidget();
	
	memset(&_subCardStatus, -1, sizeof(int)* 4);
	connect(_CardCaselistWidgt, SIGNAL(clicked(const QModelIndex &)), this, SIGNAL(ListAreaClicked(const QModelIndex &)));
	connect(this, SIGNAL(ListAreaClicked(const QModelIndex &)), this, SLOT(OnListAreaClickedSlot(const QModelIndex &)));

	connect(_ColleagueListWidgt, SIGNAL(clicked(const QModelIndex &)), this, SIGNAL(ColleagueListAreaClicked(const QModelIndex &)));
	connect(this, SIGNAL(ColleagueListAreaClicked(const QModelIndex &)), this, SLOT(OnColleagueListAreaSlot(const QModelIndex &)));

	connect(_GroupListWidgt, SIGNAL(clicked(const QModelIndex &)), this, SIGNAL(GroupListAreaClicked(const QModelIndex &)));
	connect(this, SIGNAL(GroupListAreaClicked(const QModelIndex &)), this, SLOT(OnGroupListAreaSlot(const QModelIndex &)));

	connect(_GroupChatListWidgt, SIGNAL(clicked(const QModelIndex &)), this, SIGNAL(GroupChatListAreaClicked(const QModelIndex &)));
	connect(this, SIGNAL(GroupChatListAreaClicked(const QModelIndex &)), this, SLOT(OnGroupChatListAreaSlot(const QModelIndex &)));

	connect(_CardCaselistWidgt, SIGNAL(doubleClicked(const QModelIndex &)), this, SIGNAL(ListAreaDoubleClicked(const QModelIndex &)));
	connect(this, SIGNAL(UpdateColleagueCacheSignal()), TNDataCache::GetInstance(), SLOT(UpdateColleagueSlot()));
	connect(this, SIGNAL(UpdateOrgGroupAndRelationSignal()), TNIMCoreClient::GetIMClient(), SLOT(UpdateOrgGroupAndRelationSlots()));
	connect(this, SIGNAL(UpdateFriendReMark(const QString &, const QString &)), TNIMCoreClient::GetIMClient(), SLOT(UpdateFriendReMarkSlots(const QString &, const QString &)), Qt::QueuedConnection);

	TNNotifyCenter::instance()->connectNotifyRefreshAddressList(this);
	TNNotifyCenter::instance()->connnectNotifyCurrentFeedChanged(this);
    TNNotifyCenter::instance()->connectNotifyRefresh(this);
    TNNotifyCenter::instance()->connectNotifyRefreshSession(this);
	TNNotifyCenter::instance()->connectNotifyReMarkUpdate(this);
	TNNotifyCenter::instance()->connectNotifyKeyEventDis(this);
	TNDataCache::GetInstance()->InstallCatcheFeedUpdateNotify(this);

	_httpObtainFeedList = std::make_shared<TNHttpObtainFeedList>();
	_httpObtainGroupInfo = std::make_shared<TNHttpObtainGroupChatInfoByGroupChatId>();
	_httpObtainGroupMember = std::make_shared<TNHttpObtainGroupMembersByGroupId>();
}

CardCaseListArea::~CardCaseListArea()
{
}


/*
COMMON
*/
void CardCaseListArea::InitWidget()
{
	_searchWidget = new QWidget(this);
	_searchWidget->setObjectName("searchWidget");
	_searchLineEdit = new QSearchLineText(this);
	_searchLineEdit->setObjectName("cardcaseSearch");
	_searchWidget->setContentsMargins(0,20,0,0);

	QHBoxLayout *pLayout = new QHBoxLayout();
	pLayout->addWidget(_searchLineEdit);
	pLayout->setSpacing(0);
    pLayout->setContentsMargins(15, 0, 15, 0);
	_searchWidget->setLayout(pLayout);
	connect(_searchLineEdit, SIGNAL(textChanged(QString)), this, SLOT(slotSearch(QString)));

	_topWidget = new QWidget(this);
	_topWidget->setObjectName("CardListTopWidget");
	_buttonFriend = new QPushButton(this);
	_buttonFriend->setText(("好友"));
	_buttonFriend->setObjectName("CardListTopText");
	_buttonFriend->setCheckable(true);
	_buttonFriend->setCursor(Qt::PointingHandCursor);
	_buttonColleague = new QPushButton(this);
	_buttonColleague->setText(("同事"));
	_buttonColleague->setObjectName("CardListTopText");
	_buttonColleague->setCheckable(true);
	_buttonColleague->setCursor(Qt::PointingHandCursor);
	_buttonGroupChat = new QPushButton(this);
	_buttonGroupChat->setText(("群聊"));
	_buttonGroupChat->setObjectName("CardListTopText");
	_buttonGroupChat->setCheckable(true);
	_buttonGroupChat->setCursor(Qt::PointingHandCursor);
	_buttonGroup = new QPushButton(this);
	_buttonGroup->setText(("社区"));
	_buttonGroup->setObjectName("CardListTopText");
	_buttonGroup->setCheckable(true);
	_buttonGroup->setCursor(Qt::PointingHandCursor);

	QHBoxLayout *layout = new QHBoxLayout(this);
	layout->addWidget(_buttonFriend, 0, Qt::AlignVCenter);
	layout->addWidget(_buttonColleague, 0, Qt::AlignVCenter);
	layout->addWidget(_buttonGroupChat, 0, Qt::AlignVCenter);
	layout->addWidget(_buttonGroup, 0, Qt::AlignVCenter);
	layout->setContentsMargins(0, 0, 0, 0);
	_topWidget->setLayout(layout);

	connect(_buttonFriend, SIGNAL(clicked()), this, SLOT(OnButtonFriendSlot()));
	connect(_buttonColleague, SIGNAL(clicked()), this, SLOT(OnButtonColleagueSlot()));
	connect(_buttonGroupChat, SIGNAL(clicked()), this, SLOT(OnButtonGroupChatSlot()));
	connect(_buttonGroup, SIGNAL(clicked()), this, SLOT(OnButtonGroupSlot()));

	_stackedWidget = new QStackedWidget;
	
	_CardCaselistWidgt = new TNQListView(this);
    _CardCaselistWidgt->setObjectName("CardCaselistWidgt");
    _CardCaselistWidgt->setAttribute(Qt::WA_MacShowFocusRect, 0);
	_stackedWidget->addWidget(_CardCaselistWidgt);
	_CardCaselistWidgt->setMouseTracking(true);
	_CardCaseListDelegate = new TNCardCaseListFriendItemDelegate();
	_CardCaselistWidgt->setItemDelegate(_CardCaseListDelegate);
	_CardCaselistWidgt->setSelectionMode(QAbstractItemView::SingleSelection);
    _CardCaselistWidgt->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	connect(_CardCaseListDelegate, SIGNAL(downLoadAvatar(const QString &, const QString &, int)), this,
		SLOT(needToDownLoadAvatar(const QString &, const QString &, int)), Qt::QueuedConnection);

	// 同事列表
	_ColleagueListWidgt = new TNCoTreeView();
	_ColleagueListWidgt->setObjectName("ColleagueListWidgt");
    _ColleagueListWidgt->setAttribute(Qt::WA_MacShowFocusRect, 0);
	_stackedWidget->addWidget(_ColleagueListWidgt);
	_ColleagueDelegate = new TNCardCaseCODelegate(_ColleagueListWidgt);
	_ColleagueListWidgt->setItemDelegate(_ColleagueDelegate);
	_ColleagueListWidgt->setHeaderHidden(true);
	_ColleagueListWidgt->setIndentation(0);
	_ColleagueListWidgt->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	connect(_ColleagueListWidgt, SIGNAL(clicked(QModelIndex)), this, SLOT(setCODepartItemExpanded(QModelIndex)));
	connect(_ColleagueDelegate, SIGNAL(downLoadAvatar(const QString &, const QString &, int)), this, 
		SLOT(needToDownLoadAvatar(const QString &, const QString &, int )),Qt::QueuedConnection);

	// 群组列表
	_GroupListWidgt = new TNQListView(this);
	_GroupListWidgt->setObjectName("GroupListWidgt");
    _GroupListWidgt->setAttribute(Qt::WA_MacShowFocusRect, 0);
	_stackedWidget->addWidget(_GroupListWidgt);
	_GroupDelegate = new TNCardCaseGroupDelegate();
	_GroupListWidgt->setItemDelegate(_GroupDelegate);
	_GroupListWidgt->setMouseTracking(true);
	_GroupListWidgt->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	_GroupListWidgt->setSelectionMode(QAbstractItemView::SingleSelection);
	connect(_GroupDelegate, SIGNAL(downLoadAvatar(const QString &, const QString &, int)), this,
		SLOT(needToDownLoadAvatar(const QString &, const QString &, int)), Qt::QueuedConnection);


	// 群聊列表
	_GroupChatListWidgt = new TNQListView(this);
	_GroupChatListWidgt->setObjectName("GroupChatListWidgt");
    _GroupChatListWidgt->setAttribute(Qt::WA_MacShowFocusRect, 0);
	_stackedWidget->addWidget(_GroupChatListWidgt);
	_GroupChatDelegate = new TNCardCaseGroupChatDelegate();
	_GroupChatListWidgt->setItemDelegate(_GroupChatDelegate);
	_GroupChatListWidgt->setMouseTracking(true);
	_GroupChatListWidgt->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	_GroupChatListWidgt->setSelectionMode(QAbstractItemView::SingleSelection);
	connect(_GroupChatDelegate, SIGNAL(downLoadAvatar(const QString &, const QString &, int)), this,
		SLOT(needToDownLoadAvatar(const QString &, const QString &, int)), Qt::QueuedConnection);

	QVBoxLayout * main_layout = new QVBoxLayout(this);
	main_layout->addWidget(_searchWidget);
	main_layout->addWidget(_topWidget);
	main_layout->addWidget(_stackedWidget);
	main_layout->setSpacing(0);
	main_layout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(main_layout);

	//Search Area
	_searchArea = new TNSearchAreaV2(_pluginParam, this);
	_searchArea->hide();
	_searchArea->setObjectName("tnsearcharea");
	connect(_searchArea, SIGNAL(ClickedSearchItem(const QString &, const QString &, const QString &)), this, SLOT(SearchClickedSlot(const QString &, const QString &, const QString &)));

	_nullPage = new TNDefaultPage(this);
	_nullPage->setObjectName("NULLPageCardCase");
	_nullPage->setTextTitle(("暂无联系人"));
    _nullPage->setBackPic("cardcasenullico", QSize(60, 60));

	InitMyStuffAvatar();
	_CardCaselistWidgt->installEventFilter(this);
	_ColleagueListWidgt->installEventFilter(this);
	_GroupListWidgt->installEventFilter(this);
	_GroupChatListWidgt->installEventFilter(this);
}
void CardCaseListArea::InitAvatarDir()
{
	_strAvatarDir = TNPathUtil::getFeedAvatarPath();
}
void CardCaseListArea::needToDownLoadAvatar(const QString &feedId, const QString &url, int type)
{
	qInfo() << "[CardCase][CardCaseListArea]needToDownLoadAvatar, feedId: " << feedId << " URL:" << url;
	Q_ASSERT(!feedId.isEmpty());
	Q_ASSERT(!url.isEmpty());
	if (!url.isEmpty() && !feedId.isEmpty())
	{
		bool isOriginal = false;
		if (type == GroupChatCard && feedId.startsWith("gc_"))
		{
			isOriginal = true;
		}
		DownLoadAvatar(feedId, url, isOriginal);
	}
}

void CardCaseListArea::DownLoadAvatar(QString feedId, QString url, bool isOriginal)
{
	qInfo() << "[CardCase][CardCaseListArea]DownLoadAvatar, url: " << url << " feedId:" << feedId;
	TNNetAvatarDown::GetInstance()->DownLoadFeedAvatar(feedId, url, TNHttpCloudApi::GetInstance()->GetCloudStoken(_pluginParam), this, isOriginal);
}

void CardCaseListArea::onAvatarDownLoadFinish(bool success, QString url, QString feedId)
{
	switch (_currentSelectedCard)
	{
	case FriendCard:
		_listCardCaseModel->refreshItem(feedId);
		break;
	case ColleagueCard:
		_ColleagueModel->refreshItem(feedId);
		break;
	case GroupCard:
		_GroupModel->refreshItem(feedId);
		break;
	case GroupChatCard:
		_GroupChatModel->refreshItem(feedId);
		break;
	default:
		break;
	}
	//通知会话列表去更新头像
	if (feedId.startsWith("gc_"))
	{
		UINotifyData data;
		data.feedId = feedId;
		data.operateType = UI_OPERATE_ADD;
		QList<UINotifyData> dataList;
		dataList.append(data);
		emit notifySessionList(dataList, true);
	}
}

void CardCaseListArea::on_notifyRefresh(int type, QList<UINotifyData> dataList)
{
	qInfo() << "[CardCase][CardCaseListArea]Update UI(on_notifyRefresh) thread ID:" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0')) << " Type:" << type;
	switch (type)
	{
	case RefreshTypeUI_Myfriend:
		UpdateFriendUI(dataList);
		break;
	case RefreshTypeUI_Colleague:
		UpdateColleagueUI(dataList);
		break;
	case RefreshTypeUI_Group:
		UpdateGroupUI(dataList);
		break;
	case RefreshTypeUI_GroupChat:
		UpdateGroupChatUI(dataList);
		break;
	case RefreshTypeUI_GroupMember:
		UpdateGroupChatMemberUI(dataList);
		break;
	case RefreshTypeUI_Search:
		break;
	case RefreshTypeUI_Newfriend:
		refreshNewFriendPage();
		break;
	default:
		break;
	}
}

void CardCaseListArea::DynamicUpdateFeedUI(st_FeedPtr feed, int type)
{
	Q_ASSERT(feed);
	qInfo() << "[CardCase][CardCaseListArea]DynamicUpdateFeedUI feed: " << feed->GetFeedID() << " name:" << feed->GetTitle();
	QString feedId = feed->GetFeedID();
	QString name = feed->GetTitle();
	QString namePy = feed->GetTitlePinYin();
	QString subName = feed->GetSubTile();
	QString avatarURL = feed->GetAvatarID();
	QString userId = feed->GetUserID();
	QString file = TNPathUtil::getFeedAvatarPath(feedId);
	if (type == FriendCard || type == ColleagueCard)
	{
		if (_listCardCaseModel != nullptr)
			_listCardCaseModel->updateFriendItemInfo(feedId, file, name, namePy,subName, avatarURL);
		if (feedId.startsWith("s_") && _ColleagueModel != nullptr)
		{
			_ColleagueModel->updateColleagueItemInfo(feedId, file, name, namePy, userId, subName, avatarURL);
		}
	}
	else if (type == GroupCard)
	{
		if (_GroupModel != nullptr)
		{
			_GroupModel->UpdateItemBaseInfo(feed);
		}
	}
	else
	{
		if (_listCardCaseModel != nullptr)
			_listCardCaseModel->updateFriendItemMyInfo(feedId, name);
		if (feedId.startsWith("s_") && _ColleagueModel != nullptr)
			_ColleagueModel->updateColleagueItemInfo(feedId, file, name, namePy, userId, subName, avatarURL);
	}
}
void CardCaseListArea::InitMyStuffAvatar()
{
	QList<st_FeedPtr> myAllStuff;
	TNDataCache::GetInstance()->getMyStuff(myAllStuff);
	for (st_FeedPtr feed : myAllStuff)
	{
		DownLoadAvatar(feed->GetFeedID(), feed->GetAvatarID(), false);
		qInfo() << "[CardCase][CardCaseListArea]InitMyStuffAvatar init my stuff avatar,feed: " << feed->GetFeedID();
	}
}

void CardCaseListArea::showNullPage(bool status, int type)
{
	if (_nullPage != nullptr)
	{
		int h = _nullPage->height();
		int w = _nullPage->width();
		if (type == FriendCard)
		{
			int ph = _CardCaselistWidgt->height();
			_nullPage->move((LIST_AREA_WIDTH - w) / 2, (ph - h) / 2 + 70);
			_nullPage->setTextTitle(("暂无联系人"));
		}
		else if (type == ColleagueCard)
		{
			int ph = _ColleagueListWidgt->height();
			_nullPage->move((LIST_AREA_WIDTH - w) / 2, (ph - h) / 2);
			_nullPage->setTextTitle(("暂无联系人"));
		}
		else if (type == GroupCard)
		{
			int ph = _GroupListWidgt->height();
			_nullPage->move((LIST_AREA_WIDTH - w) / 2, (ph - h) / 2);
			_nullPage->setTextTitle(("暂无社区"));
		}
		else if (type == GroupChatCard)
		{
			int ph = _GroupChatListWidgt->height();
			_nullPage->move((LIST_AREA_WIDTH - w) / 2, (ph - h) / 2);
			_nullPage->setTextTitle(("暂无群聊"));
		}
		_nullPageStatus = status;
		status ? _nullPage->show() : _nullPage->hide();
	}
}
void CardCaseListArea::LoadDefaultPage()
{
	switch (_currentSelectedCard)
	{
	case FriendCard:
		OnButtonFriendSlot();
		break;
	case ColleagueCard:
		OnButtonColleagueSlot();
		break;
	case GroupCard:
		OnButtonGroupSlot();
		break;
	case GroupChatCard:
		OnButtonGroupChatSlot();
		break;
	default:
		OnButtonFriendSlot();
		break;
	}
	//emit ListAreaClicked(_listCardCaseModel->index(1, 0));
}
void CardCaseListArea::ResetOldSelectedStatus(int type)
{
	switch (type)
	{
	case RefreshTypeUI_Myfriend:
		break;
	case RefreshTypeUI_GroupChat:
		break;
	case RefreshTypeUI_Colleague:
		break;
	case RefreshTypeUI_Group:
		break;
	case RefreshTypeUI_RefreshAll:
		/*
		待测试
		*/
		memset(&_subCardStatus, -1, sizeof(int)* 4);
		break;
	default:
		break;
	}
}

void CardCaseListArea::on_notifyReMarkUpdate(const QString &from, const QString &to, const QString &remark,int sources)
{
	/*
	从H5通知过来，需要更新数据库
	*/
	Q_ASSERT(!from.isEmpty());
	Q_ASSERT(!to.isEmpty());

	//同步通知，不需要更新
	if (sources){

		qInfo() << "[CardCase][CardCaseListArea]on_notifyReMarkUpdate recieve,from:" << from << " remark:" << remark;
		/*
		更新数据库
		*/
		TNDataControlServer::GetInstance()->updateFeedRemark(from + "_" + to, remark, TNCHNHelper::GetPinyins(remark));
		/*
		更新缓存
		*/
		TNDataCache::GetInstance()->updateFriendFeedReMark(from, to, remark);

		if (!_listCardCaseModel){
			qInfo() << "[CardCase][CardCaseListArea]on_notifyReMarkUpdate recieve,but don't need update";
			return;
		}
		/*
		更新UI
		*/
		int item = -1;
		_listCardCaseModel->updateFriendItemReMark(from, remark, to);
		if ((item = _listCardCaseModel->setSearchSelected(from, to)) >= 0)
		{
			QModelIndex index = _listCardCaseModel->index(item, 0);
			if (index.isValid())
			{
				_CardCaselistWidgt->scrollTo(index, QAbstractItemView::PositionAtCenter);
				QModelIndex oldIndex = _CardCaselistWidgt->selectionModel()->currentIndex();
				if (oldIndex.isValid())
				{
					_CardCaselistWidgt->selectionModel()->select(oldIndex, QItemSelectionModel::Clear);
				}
				_CardCaselistWidgt->selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);
			}
		}
	}
}
void CardCaseListArea::on_notifyKeyEventDis(int keyEvent)
{
	qInfo() << "[CardCase][CardCaseListArea]on_notifyKeyEventDis ,keyEvent:" << keyEvent;
	if (_searchArea != nullptr &&
		!_searchArea->isHidden())
	{
		_searchArea->keyboadEventMgr(keyEvent);
	}
	else
	{
		if (_currentSelectedPage == MENU_CARDCASE_ID)
		{
			switch (keyEvent)
			{
			case Qt::Key_Down:
				downSelected(_currentSelectedCard);
				break;
			case Qt::Key_Up:
				upSelected(_currentSelectedCard);
				break;
			case Qt::Key_Return:
			case Qt::Key_Enter:
				break;
			default:
				break;
			}
		}
	}
}
bool CardCaseListArea::eventFilter(QObject *watched, QEvent *event)
{
	if (_currentSelectedPage == MENU_CARDCASE_ID &&
		watched == _CardCaselistWidgt){
		if (event->type() == QEvent::KeyPress){
			QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(event);
			if (keyEvent != nullptr){
				if (keyEvent->key() == Qt::Key_Up){
					upSelected(FriendCard);
				}
				else if (keyEvent->key() == Qt::Key_Down){
					downSelected(FriendCard);
				}
			}
		}
	}
	else if (_currentSelectedPage == MENU_CARDCASE_ID && 
		watched == _ColleagueListWidgt)
	{
		if (event->type() == QEvent::KeyPress){
			QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(event);
			if (keyEvent != nullptr){
				if (keyEvent->key() == Qt::Key_Up){
					upSelected(ColleagueCard);
				}
				else if (keyEvent->key() == Qt::Key_Down){
					downSelected(ColleagueCard);
				}
			}
		}
	}
	else if (_currentSelectedPage == MENU_CARDCASE_ID &&
		watched == _GroupListWidgt)
	{
		if (event->type() == QEvent::KeyPress){
			QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(event);
			if (keyEvent != nullptr){
				if (keyEvent->key() == Qt::Key_Up){
					upSelected(GroupCard);
				}
				else if (keyEvent->key() == Qt::Key_Down){
					downSelected(GroupCard);
				}
			}
		}
	}
	else if (_currentSelectedPage == MENU_CARDCASE_ID && 
		watched == _GroupChatListWidgt)
	{
		if (event->type() == QEvent::KeyPress){
			QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(event);
			if (keyEvent != nullptr){
				if (keyEvent->key() == Qt::Key_Up){
					upSelected(GroupChatCard);
				}
				else if (keyEvent->key() == Qt::Key_Down){
					downSelected(GroupChatCard);
				}
			}
		}
	}
	return QWidget::eventFilter(watched, event);
}
void CardCaseListArea::downSelected(int type)
{
	if (type == FriendCard)
	{
		if (_listCardCaseModel != nullptr
			&&_listCardCaseModel->rowCount() > 0)
		{
			QModelIndex oldIndex = _CardCaselistWidgt->selectionModel()->currentIndex();
			if (oldIndex.isValid())
			{
				_CardCaselistWidgt->selectionModel()->select(oldIndex, QItemSelectionModel::Clear);
			}
			_CardCaselistWidgt->selectionModel()->setCurrentIndex(_listCardCaseModel->getNextIndex(oldIndex), QItemSelectionModel::Select);
			enterSelected(type);
		}
	}
	else if (type == ColleagueCard)
	{
		if (_ColleagueModel->rowCount() > 0)
		{
			QModelIndex oldIndex = _ColleagueListWidgt->selectionModel()->currentIndex();
			if (oldIndex.isValid())
			{
				_ColleagueListWidgt->selectionModel()->select(oldIndex, QItemSelectionModel::Clear);
			}
			_ColleagueListWidgt->selectionModel()->setCurrentIndex(_ColleagueModel->getNextIndex(oldIndex), QItemSelectionModel::Select);
			enterSelected(type);
		}
	}
	else if (type == GroupCard)
	{
		if (_GroupModel->rowCount() > 0)
		{
			QModelIndex oldIndex = _GroupListWidgt->selectionModel()->currentIndex();
			if (oldIndex.isValid())
			{
				_GroupListWidgt->selectionModel()->select(oldIndex, QItemSelectionModel::Clear);
			}
			_GroupListWidgt->selectionModel()->setCurrentIndex(_GroupModel->getNextIndex(oldIndex), QItemSelectionModel::Select);
			enterSelected(type);
		}
	}
	else if (type == GroupChatCard)
	{
		if (_GroupChatModel->rowCount() > 0)
		{
			QModelIndex oldIndex = _GroupChatListWidgt->selectionModel()->currentIndex();
			if (oldIndex.isValid())
			{
				_GroupChatListWidgt->selectionModel()->select(oldIndex, QItemSelectionModel::Clear);
			}
			_GroupChatListWidgt->selectionModel()->setCurrentIndex(_GroupChatModel->getNextIndex(oldIndex), QItemSelectionModel::Select);
			enterSelected(type);
		}
	}
}
void CardCaseListArea::upSelected(int type)
{
	if (type == FriendCard)
	{
		if (_listCardCaseModel->rowCount() > 0)
		{
			QModelIndex oldIndex = _CardCaselistWidgt->selectionModel()->currentIndex();
			if (oldIndex.isValid())
			{
				_CardCaselistWidgt->selectionModel()->select(oldIndex, QItemSelectionModel::Clear);
			}
			_CardCaselistWidgt->selectionModel()->setCurrentIndex(_listCardCaseModel->getPreIndex(oldIndex), QItemSelectionModel::Select);
			enterSelected(type);
		}
	}
	else if (type == ColleagueCard)
	{
		if (_ColleagueModel->rowCount() > 0)
		{
			QModelIndex oldIndex = _ColleagueListWidgt->selectionModel()->currentIndex();
			if (oldIndex.isValid())
			{
				_ColleagueListWidgt->selectionModel()->select(oldIndex, QItemSelectionModel::Clear);
			}
			_ColleagueListWidgt->selectionModel()->setCurrentIndex(_ColleagueModel->getPreIndex(oldIndex), QItemSelectionModel::Select);
			enterSelected(type);
		}
	}
	else if (type == GroupCard)
	{
		if (_GroupModel->rowCount() > 0)
		{
			QModelIndex oldIndex = _GroupListWidgt->selectionModel()->currentIndex();
			if (oldIndex.isValid())
			{
				_GroupListWidgt->selectionModel()->select(oldIndex, QItemSelectionModel::Clear);
			}
			_GroupListWidgt->selectionModel()->setCurrentIndex(_GroupModel->getPreIndex(oldIndex), QItemSelectionModel::Select);
			enterSelected(type);
		}
	}
	else if (type == GroupChatCard)
	{
		if (_GroupChatModel->rowCount() > 0)
		{
			QModelIndex oldIndex = _GroupChatListWidgt->selectionModel()->currentIndex();
			if (oldIndex.isValid())
			{
				_GroupChatListWidgt->selectionModel()->select(oldIndex, QItemSelectionModel::Clear);
			}
			_GroupChatListWidgt->selectionModel()->setCurrentIndex(_GroupChatModel->getPreIndex(oldIndex), QItemSelectionModel::Select);
			enterSelected(type);
		}
	}
}
void CardCaseListArea::enterSelected(int type)
{
	if (type == FriendCard)
	{
		QModelIndex oldIndex = _CardCaselistWidgt->selectionModel()->currentIndex();
		if (oldIndex.isValid())
		{
			OnListAreaClickedSlot(oldIndex);
		}
	}
	else if (type == ColleagueCard)
	{
		QModelIndex oldIndex = _ColleagueListWidgt->selectionModel()->currentIndex();
		if (oldIndex.isValid())
		{
			OnColleagueListAreaSlot(oldIndex);
		}
	}
	else if (type == GroupCard)
	{
		QModelIndex oldIndex = _GroupListWidgt->selectionModel()->currentIndex();
		if (oldIndex.isValid())
		{
			OnGroupListAreaSlot(oldIndex);
		}
	}
	else if (type == GroupChatCard)
	{
		QModelIndex oldIndex = _GroupChatListWidgt->selectionModel()->currentIndex();
		if (oldIndex.isValid())
		{
			OnGroupChatListAreaSlot(oldIndex);
		}
	}
}
void CardCaseListArea::currentSelectedPage(int page)
{
	_currentSelectedPage = page;
}
/*
新学员
*/
void CardCaseListArea::refreshNewFriendPage()
{
	updateNewFriendUnReadCount();
	emit updateNewFriendPage();
}

void CardCaseListArea::updateNewFriendUnReadCount()
{
	if (!_listCardCaseModel)
		return;
	_listCardCaseModel->updateNewFriendUnRead(TNNewFriendUtil::getUnReadCount());
}
/*
好友
*/
void CardCaseListArea::OnButtonFriendSlot()
{
	_buttonFriend->setChecked(true);
	_buttonColleague->setChecked(false);
	_buttonGroupChat->setChecked(false);
	_buttonGroup->setChecked(false);
	Q_ASSERT(_stackedWidget->count() > 0);
	_stackedWidget->setCurrentIndex(0);
	_currentSelectedCard = FriendCard;
	showNullPage(false, _currentSelectedCard);
	TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_Address_Friend, _pluginParam);

	QList<TNStructFriend> friendList;
	TNDataCache::GetInstance()->GetFriendCache(friendList);
	if (_subCardStatus[0] != 1)
	{
		LoadFriend(friendList);
	}
	_CardCaselistWidgt->setFocus();
	showNullPage(friendList.size() == 0, _currentSelectedCard);
}
void CardCaseListArea::LoadFriend(QList<TNStructFriend> friendList)
{
	QMutexLocker lock(&_mutex);
	_subCardStatus[0] = 1;
	QList<TNCardCaseListAdapter*> adatpterList;
	QMap<QChar, QMultiMap<QString, TNCardCaseListAdapter*> > firstLetterToFriendMap;
	QMap<QChar, QMultiMap<QString, TNCardCaseListAdapter*> > firstSCharToFriendMap;

	QList<st_FeedPtr> needUpdateAvatarList;
	for (QList<TNStructFriend>::iterator iter = friendList.begin(); iter != friendList.end(); iter++)
	{
		QString belongFeedId = (*iter).m_belongFeedId;

		st_FeedPtr feed = (*iter).m_Feed;
		/*
		在model中， remove item 时delete 内存
		*/
		TNCardCaseListAdapter * tempAdapter = new TNCardCaseListAdapter(TNCardCaseListAdapter::FriendItem);
		if ((*iter).remark.isEmpty())
		{
			tempAdapter->setIsShowReMark(false);
			tempAdapter->setName(feed->GetTitle());
			tempAdapter->setTitlePinYin(feed->GetTitlePinYin());
		}
		else
		{
			tempAdapter->setIsShowReMark(true);
			tempAdapter->setName((*iter).remark);
			tempAdapter->setTitlePinYin((*iter).remarkpy);
		}
		tempAdapter->setSex(feed->GetSex());
		tempAdapter->setBelongFeedId(belongFeedId);
		tempAdapter->setUserId(feed->GetUserID());
		const QString birthStr(feed->GetBirthday());
		if (birthStr.isNull() || birthStr.isEmpty())
		{
			tempAdapter->setAge(-1);
		}
		else
		{
			QDate birthDate(QDate::fromString(birthStr, Qt::ISODate));
			int mouth = QDate::currentDate().month() - birthDate.month();
			if (mouth<0)
				tempAdapter->setAge(QDate::currentDate().year() - birthDate.year()-1);
			else
				tempAdapter->setAge(QDate::currentDate().year() - birthDate.year());
		}
		QString tag = feed->GetTag();
		if (!tag.isEmpty())
		{
			QStringList temptag = tag.split(",");
			tempAdapter->setTag(temptag);
		}

		tempAdapter->setSubTitle(feed->GetSubTile());
		tempAdapter->setDialogID(feed->GetFeedID());
		QString strAvatarURL = feed->GetAvatarID();
		tempAdapter->setAvatarUrl(strAvatarURL);
		tempAdapter->setLatestAvatarUrl(strAvatarURL);
		tempAdapter->setStaticTitle(feed->GetTitle()); //永远都存title
		tempAdapter->setStaticTitlePy(feed->GetTitlePinYin()); //永远都存titlePy
		/*
		头像在paint 的时候下载
		*/
		QString avatarFileName = TNPathUtil::getFeedAvatarPath(feed->GetFeedID());
		tempAdapter->setPhotoResID(avatarFileName);
		if (TNDataCache::GetInstance()->GetCurrentMyFeed() == AVATAR_ALL_FEED)
		{
			QString myTitle = TNDataCache::GetInstance()->GetMyTitle(belongFeedId);
			if (myTitle.isEmpty())
				continue;
			tempAdapter->setMyTitle(myTitle);
			if ((*iter).dupCount >1)
				tempAdapter->setIsShowMyInfo(true);
		}
		if (!tempAdapter->getTitlePinYin().isEmpty())
		{
			QString py = tempAdapter->getTitlePinYin().replace(" ","").toLower();
			QChar firstLetter = py.at(0).toUpper();
			if (isalpha(firstLetter.toLatin1()))
			{
				firstLetterToFriendMap[firstLetter].insert(py, tempAdapter);
			}
			else
			{
				firstSCharToFriendMap['#'].insert(py, tempAdapter);
			}
		}
	}
	TNCardCaseListAdapter * newFriendAdapter = new TNCardCaseListAdapter(TNCardCaseListAdapter::NewFriend);
    newFriendAdapter->setName(("新学员"));
	newFriendAdapter->setPhotoResID((":/Resources/new_friend.png"));
	newFriendAdapter->setDialogID(AVATAR_ALL_FEED);
	adatpterList.append(newFriendAdapter);

	foreach(const QChar &firstLetter, firstLetterToFriendMap.keys())
	{
		TNCardCaseListAdapter *firstLetterAdapter = new TNCardCaseListAdapter(TNCardCaseListAdapter::FriendLetter);
		firstLetterAdapter->setName(QString(firstLetter));
		adatpterList.append(firstLetterAdapter);
		foreach(TNCardCaseListAdapter *adapter, firstLetterToFriendMap.value(firstLetter).values())
		{
			adatpterList.append(adapter);
		}
	}
	foreach(const QChar &firstLetter, firstSCharToFriendMap.keys())
	{
		TNCardCaseListAdapter *firstLetterAdapter = new TNCardCaseListAdapter(TNCardCaseListAdapter::FriendLetter);
		firstLetterAdapter->setName(QString(firstLetter));
		adatpterList.append(firstLetterAdapter);
		foreach(TNCardCaseListAdapter *adapter, firstSCharToFriendMap.value(firstLetter).values())
		{
			adatpterList.append(adapter);
		}
	}

	/*
	Reset model
	*/
	if (_listCardCaseModel != nullptr)
		_listCardCaseModel->resetModel();
	else
		_listCardCaseModel = new TNCardCaseListModel(this);

	_CardCaselistWidgt->setModel(_listCardCaseModel);

	if (adatpterList.size()> 0)
		_listCardCaseModel->appendData(adatpterList);

	//初始化新学员未读数
	updateNewFriendUnReadCount();
}
void CardCaseListArea::UpdateFriendUI(QList<UINotifyData> dataList)
{
	if (_listCardCaseModel == nullptr)
	{
		/*
		Update all card cahche OK
		*/
		qInfo() << "[CardCase][CardCaseListArea]UpdateFriendUI: maybe _listCardCaseModel is null" << " datalist: " << dataList.size();
		TNDataCache::GetInstance()->UpdateInStepCache(dataList, RefreshTypeUI_Myfriend);
		/*
		需要发一个通知，通知其他业务更新，此时缓存应该更新完毕
		*/
		foreach(UINotifyData uiMsg, dataList)
		{
			QString feedId, belongId;
			int pos = uiMsg.feedId.indexOf("_", 2);
			if (pos == -1)
			{
				qInfo() << "[CardCase][CardCaseListArea]UpdateFriendUI error:" << uiMsg.feedId;
				continue;
			}
			feedId = uiMsg.feedId.mid(0, pos);
			belongId = uiMsg.feedId.mid(pos + 1, uiMsg.feedId.length() - pos - 1);
			//如果是好友已经存在，且type 是UI_OPERATE_ADD说明收到同步通知更新备注 
			if (IsExistbyFriendFeedId(uiMsg.feedId) && uiMsg.operateType == UI_OPERATE_ADD){
				QString remark = TNDataCache::GetInstance()->getFriendFeedReMark(feedId, belongId);
				TNNotifyCenter::instance()->postNotifyReMarkUpdate(feedId, belongId, remark, false);
			}
		}
		return;
	}
	qInfo() << "[CardCase][CardCaseListArea]Update UpdateFriendUI thread ID:" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0')) << " datalist: " + dataList.size();
	foreach(UINotifyData uiMsg, dataList)
	{
		QString feedId, belongId;
		int pos = uiMsg.feedId.indexOf("_", 2);
		if (pos == -1)
		{
			qInfo() << "[CardCase][CardCaseListArea]UpdateFriendUI error:" << uiMsg.feedId;
			continue;
		}
		feedId = uiMsg.feedId.mid(0, pos);
		belongId = uiMsg.feedId.mid(pos + 1, uiMsg.feedId.length() - pos - 1);

		switch (uiMsg.operateType)
		{
		case UI_OPERATE_ADD:
			/*
			是否在当前名片的好友列表中
			*/
			if (!IsExistbyFriendFeedId(uiMsg.feedId))
			{
				qInfo() << "[CardCase][CardCaseListArea]UI_OPERATE_ADD : " << uiMsg.feedId << " is not exist in :" << uiMsg.belongId;
				TNStructFriend myFriend;
				TableBaseVec tempMyTableBaseVec;
				TNDataCache::GetInstance()->UpdateFriendCachebyId(feedId, belongId, CacheFOp::frAdd, myFriend);
				st_FeedPtr feed = myFriend.m_Feed;
				/*
				仅更新当前名片好友UI
				*/
				if (feed == nullptr || !TNDataCache::GetInstance()->IsCurrentCardCache(belongId))
				{
					qInfo() << "[CardCase][CardCaseListArea]Add friend end, not update UI ,belong Id:" << belongId << " feed: " + uiMsg.feedId;
					return;
				}
				TNCardCaseListAdapter * tempAdapter = new TNCardCaseListAdapter(TNCardCaseListAdapter::FriendItem);
				tempAdapter->setTitlePinYin(feed->GetTitlePinYin());
				tempAdapter->setSex(feed->GetSex());
				tempAdapter->setBelongFeedId(belongId);
				tempAdapter->setUserId(feed->GetUserID());
				const QString birthStr(feed->GetBirthday());
				if (birthStr.isNull() || birthStr.isEmpty())
				{
					tempAdapter->setAge(-1);
				}
				else
				{
					QDate birthDate(QDate::fromString(birthStr, Qt::ISODate));
					int mouth = QDate::currentDate().month() - birthDate.month();
					if (mouth<0)
						tempAdapter->setAge(QDate::currentDate().year() - birthDate.year() - 1);
					else
						tempAdapter->setAge(QDate::currentDate().year() - birthDate.year());
				}
				QString tag = feed->GetTag();
				if (!tag.isEmpty())
				{
					QStringList temptag = tag.split(",");
					tempAdapter->setTag(temptag);
				}

				tempAdapter->setName(feed->GetTitle());
				tempAdapter->setSubTitle(feed->GetSubTile());
				tempAdapter->setDialogID(feed->GetFeedID());
				QString strAvatarURL = feed->GetAvatarID();
				tempAdapter->setAvatarUrl(strAvatarURL);
				tempAdapter->setLatestAvatarUrl(strAvatarURL);

				QString avatarFileName = TNPathUtil::getFeedAvatarPath(feed->GetFeedID());
				if (!QFile::exists(avatarFileName))
				{
					DownLoadAvatar(feed->GetFeedID(), feed->GetAvatarID(), false);
				}
				tempAdapter->setPhotoResID(avatarFileName);
				/*
				获取共同的好友数量
				*/
				int count = TNDataCache::GetInstance()->GetSpecialFriendCount(feedId);
				if (count > 1)
				{
					tempAdapter->setIsShowMyInfo(true);
					QString myTitle = TNDataCache::GetInstance()->GetMyTitle(belongId);
					if (myTitle.isEmpty())
						continue;
					tempAdapter->setMyTitle(myTitle);
					_listCardCaseModel->updateFriendBelong(feedId, count, true);
				}
				showNullPage(false, FriendCard);
				_listCardCaseModel->insertItem(tempAdapter);
				qInfo() << "[CardCase][CardCaseListArea]Add friend thread ID:" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0')) << " feed: " << uiMsg.feedId;
			}
			else
			{
				//修改好友信息,目前只有备注会发同步更新
				TNStructFriend myFriend;
				TableBaseVec tempMyTableBaseVec;
				TNDataCache::GetInstance()->UpdateFriendCachebyId(feedId, belongId, CacheFOp::frModify, myFriend);
				st_FeedPtr feed = myFriend.m_Feed;
				/*
				仅更新当前名片好友UI
				*/
				if (feed == nullptr || !TNDataCache::GetInstance()->IsCurrentCardCache(belongId))
				{
					qInfo() << "[CardCase][CardCaseListArea]Modify friend end, not update UI ,belong Id:" << belongId << " feed: " + uiMsg.feedId;
					return;
				}
				QString file = TNPathUtil::getFeedAvatarPath(feedId);
				_listCardCaseModel->updateFriendItemInfo(feedId, file, feed->GetTitle(),feed->GetTitlePinYin(),feed->GetSubTile(),feed->GetAvatarID());
				_listCardCaseModel->updateFriendItemReMark(feedId, myFriend.remark, myFriend.m_belongFeedId);
				TNNotifyCenter::instance()->postNotifyReMarkUpdate(feedId, belongId, myFriend.remark, false);
				qInfo() << "[CardCase][CardCaseListArea]Modify friend thread ID:" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0')) << " feed: " << uiMsg.feedId;
			}
			break;
		case UI_OPERATE_DEL:
			if (!uiMsg.feedId.isEmpty())
			{
				TNStructFriend myFriend;
				TNDataCache::GetInstance()->UpdateFriendCachebyId(feedId, belongId, CacheFOp::frDel, myFriend);
				if (TNDataCache::GetInstance()->IsCurrentCardCache(belongId))
				{
					int count = TNDataCache::GetInstance()->GetSpecialFriendCount(feedId);
					if (count == 1)
					{
						_listCardCaseModel->updateFriendBelong(feedId, count, false);
					}
					_listCardCaseModel->removeItem(feedId, belongId);
					if (_listCardCaseModel->rowCount() == 1)
						showNullPage(true, FriendCard);
					/*
					删除单聊会话
					*/
					emit RemoveSessionInSessionList(TNIMCoreClient::GetIMClient()->GetSessionId(feedId, belongId, MSG_BIZ_SINGLECHAT));
					emit CloseDetailPageEvent(feedId, belongId);
				}
				qInfo() << "[CardCase][CardCaseListArea]Del friend thread ID:" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0')) << " feed: " + uiMsg.feedId;
			}
			break;
		default:
			break;
		}
	}
}
bool CardCaseListArea::IsExistbyFriendFeedId(const QString &feedId)
{
	bool result = false;
	QList<TNStructFriend> friendInfoList;
	TNDataCache::GetInstance()->GetFriendCache(friendInfoList, AVATAR_ALL_FEED);
	for (QList<TNStructFriend>::iterator iter = friendInfoList.begin(); iter != friendInfoList.end(); iter++)
	{
		TNStructFriend Info = (*iter);
		st_FeedPtr feed = Info.m_Feed;
		QString subString = feed->GetFeedID() + "_" + iter->m_belongFeedId;
		if (subString == feedId)
		{
			result = true;
			break;
		}
	}
	return result;
}
void CardCaseListArea::OnListAreaClickedSlot(const QModelIndex & index)
{
	TNCardCaseListAdapter *adapter = (TNCardCaseListAdapter*)index.data().toLongLong();
	if (adapter != nullptr)
	{
		if (adapter->getType() == TNCardCaseListAdapter::FriendItem)
		{
			//更新feed信息
			QVector<QString> baseInfo;
			baseInfo.push_back(adapter->getDialogID());
			baseInfo.push_back(adapter->getStaticTitle());
			baseInfo.push_back(adapter->getStaticTitlePy());
			baseInfo.push_back(adapter->getSubTitle());
			baseInfo.push_back(adapter->getAvatarUrl());
			DynamicUpdateFeedInfo(adapter->getDialogID(), adapter->getBelongFeedId(), baseInfo, FriendCard);
			emit ListFriendToDetailEvent(index);
		}
		else if (adapter->getType() == TNCardCaseListAdapter::NewFriend)
		{
			TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_Address_NewFriend, _pluginParam);

			emit clickedNewFriendItem();
			emit messageNumberChanged(0);

			TNNewFriendUtil::clearUnReadStatus();
			updateNewFriendUnReadCount();
		}
		_listCardCaseModel->updateKeyStartFlag(true);
	}
}
void CardCaseListArea::DynamicUpdateFeedInfo(QString feedId, QString belongFeedId, QVector<QString>baseInfo, int iType)
{
	Q_ASSERT(!feedId.isEmpty());

	qInfo() << "[CardCase][CardCaseListArea]UpdateFeedInfo :" << feedId << " Type:" << iType;
	if (_httpObtainFeedList == nullptr)
	{
		qInfo() << "[CardCase][CardCaseListArea]UpdateFeedInfo _httpObtainFeedList is invalid";
		return;
	}
	QSet<QString> feedList;
	feedList.insert(feedId);
	if (iType == FriendCard){
		feedList.insert(belongFeedId);
	}

	std::vector<QVariant> extern_params;
	extern_params.push_back(iType);
	for (int i = 0; i < baseInfo.size();i++)
	{
		extern_params.push_back(baseInfo[i]);
	}
	QList<UINotifyData> extData;
	_httpObtainFeedList->GetJson([&](bool success, QJsonObject jsonObject,QList<UINotifyData> extData, TNHttpObtainFeedList* httpFeed,
		std::vector<QVariant> params)
	{
		if (success)
		{
			int type = params[0].toInt();
			QList<TableBasePtr> stFeedList;
			QJsonArray feeds = jsonObject.value("data").toArray();
			for (int m = 0; m < feeds.size(); m++)
			{
				st_FeedPtr stFeed = std::make_shared<st_Feed>();
				stFeed->SetBirthday(feeds.at(m).toObject().value("birthday").toString());
				stFeed->SetComID(feeds.at(m).toObject().value("comId").toString());
				stFeed->SetConsumeLevel(feeds.at(m).toObject().value("consumeLevel").toString());
				stFeed->SetKeyWord(feeds.at(m).toObject().value("keyword").toString());
				stFeed->SetFeedID(feeds.at(m).toObject().value("feedId").toString());
				stFeed->SetServiceLevel(feeds.at(m).toObject().value("serviceLevel").toString());
				stFeed->SetSex(feeds.at(m).toObject().value("sex").toString());
				stFeed->SetSocialLevel(feeds.at(m).toObject().value("socialLevel").toString());
				stFeed->SetTitle(feeds.at(m).toObject().value("title").toString());
				stFeed->SetSubTile(feeds.at(m).toObject().value("subtitle").toString());
				stFeed->SetTitlePinYin(feeds.at(m).toObject().value("titlePinYin").toString());
				stFeed->SetUserID(feeds.at(m).toObject().value("userId").toString());
				stFeed->SetVersion(feeds.at(m).toObject().value("version").toString());
				stFeed->SetTag(feeds.at(m).toObject().value("tag").toString());
				stFeed->SetAvatarID(feeds.at(m).toObject().value("avatarId").toString());

				bool isMySelf = false;
				bool baseInfoUpdate = false;
				if (TNDataCache::GetInstance()->IsInMyStuff(stFeed->GetFeedID())){
					isMySelf = true;
					baseInfoUpdate = true;
					qInfo() << "[CardCase][CardCaseListArea]UpdateFeedInfo update my card,feed:" << stFeed->GetFeedID();
				}
				else {
					switch (params[0].toInt())
					{
					case FriendCard:
						if (params[1].toString() == stFeed->GetFeedID())
						{
							if (params[2].toString() != stFeed->GetTitle() ||
								params[3].toString() != stFeed->GetTitlePinYin() ||
								params[4].toString() != stFeed->GetSubTile() ||
								params[5].toString() != stFeed->GetAvatarID())
							{
								baseInfoUpdate = true;
								qInfo() << "[CardCase][CardCaseListArea]UpdateFeedInfo baseInfo is changed,will update,feed:" << stFeed->GetFeedID();
							}
						}
						break;
					case ColleagueCard:
						if (params[1].toString() == stFeed->GetFeedID())
						{
							if (params[2].toString() != stFeed->GetTitle() ||
								params[3].toString() != stFeed->GetTitlePinYin() ||
								params[4].toString() != stFeed->GetSubTile() ||
								params[5].toString() != stFeed->GetAvatarID()||
								params[6].toString() != stFeed->GetUserID())
							{
								baseInfoUpdate = true;
								qInfo() << "[CardCase][CardCaseListArea]UpdateFeedInfo baseInfo is changed,will update,feed:" << stFeed->GetFeedID();
							}
						}
						break;
					case GroupCard:
						if (params[1].toString() == stFeed->GetFeedID())
						{
							QString object;
							QString tag = stFeed->GetTag();
							if (!tag.isEmpty())
							{
								QStringList temptag = tag.split(",");
								object = temptag[0];
							}
							if (params[2].toString() != stFeed->GetTitle() ||
								params[3].toString() != stFeed->GetTitlePinYin() ||
								params[4].toString() != stFeed->GetSubTile() ||
								params[5].toString() != stFeed->GetAvatarID() ||
								params[6].toString() != object)
							{
								baseInfoUpdate = true;
								qInfo() << "[CardCase][CardCaseListArea]UpdateFeedInfo baseInfo is changed,will update,feed:" << stFeed->GetFeedID();
							}
						}
						break;
					default:
						break;
					}
				}
				if (baseInfoUpdate)
				{
					stFeedList.append(std::dynamic_pointer_cast<TableBase>(stFeed));
					//下载头像
					DownLoadAvatar(stFeed->GetFeedID(), stFeed->GetAvatarID(), false);
					//更新缓存
					TNDataCache::GetInstance()->SynUpdateFeedCache(stFeed, type, TN::UpdateSource::CardView);
					if (isMySelf)
					{
						//仅仅更新我的数据
						DynamicUpdateFeedUI(stFeed, -1);
					}
					else
					{
						//更新UI
						DynamicUpdateFeedUI(stFeed, type);
					}
				}
			}
			if (stFeedList.size() > 0)
			{
				TNDataControlServer::GetInstance()->InsertDatas(stFeedList, INSERT_FEED, DBTYPE_USER);
			}
		}
	}, _pluginParam, feedList.toList(), extData, extern_params);
}
void CardCaseListArea::feedCardUpdateFromCatche(const QString &feedId,
												const QString &avatarId,
												const QString &name,
												const QString &subName,
												const QString &userId,
												const QString &namePy,
												int sourceType)
{
	Q_ASSERT(!feedId.isEmpty() && !avatarId.isEmpty() 
		&& !name.isEmpty() && !subName.isEmpty() && 
		!userId.isEmpty() && !namePy.isEmpty());

	qInfo() << "[CardCase][CardCaseListArea]feedCardUpdateFromCatche :" << feedId << " sourceType:" << sourceType;
	if (sourceType != TN::UpdateSource::CardView){
		st_FeedPtr stFeed = std::make_shared<st_Feed>();
		stFeed->SetFeedID(feedId);
		stFeed->SetTitle(name);
		stFeed->SetSubTile(subName);
		stFeed->SetTitlePinYin(namePy);
		stFeed->SetUserID(userId);
		stFeed->SetAvatarID(avatarId);

		if (sourceType == TN::UpdateSource::SessionList){
			//更新好友名片,如果是个人名片，不更新同事。
			if (!feedId.startsWith("c_")){
				DynamicUpdateFeedUI(stFeed, ColleagueCard);
			}
			DynamicUpdateFeedUI(stFeed, FriendCard);
		}
		else if (sourceType == TN::UpdateSource::Mine){
			//更新我的信息
			DynamicUpdateFeedUI(stFeed, -1);
		}
	}
}	
/*
同事
*/
void CardCaseListArea::OnButtonColleagueSlot()
{
	_buttonFriend->setChecked(false);
	_buttonColleague->setChecked(true);
	_buttonGroupChat->setChecked(false);
	_buttonGroup->setChecked(false);
	Q_ASSERT(_stackedWidget->count() > 1);
	_stackedWidget->setCurrentIndex(1);
	_currentSelectedCard = ColleagueCard;
	showNullPage(false, _currentSelectedCard);
	TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_Address_Colleage, _pluginParam);

	QList<TNStructCompany> companyList;
	TNDataCache::GetInstance()->GetColleagueCache(companyList);
	if (_subCardStatus[1] != 1)
	{
		LoadColleague(companyList);
	}
	_ColleagueListWidgt->setFocus();
	showNullPage(companyList.size() == 0, _currentSelectedCard);
	emit UpdateOrgGroupAndRelationSignal();
}
void CardCaseListArea::LoadColleague(QList<TNStructCompany> companyList)
{
	QMutexLocker locker(&_mutex);
	_subCardStatus[1] = 1;
	TNCardCaseTreeItem *ColleagueRoot = new TNCardCaseTreeItem(QList<QVariant>() << ("思源集团"));

	for (QList<TNStructCompany>::iterator iter = companyList.begin(); iter != companyList.end(); iter++)
	{
		TNStructCompany tempInfo = *iter;
		qInfo() << "[CardCase][CardCaseListArea]LoadColleague companyName:" << tempInfo.m_companyName;
		TNCompanyItem * aCompanyItem = new TNCompanyItem(tempInfo.m_companyName, ColleagueRoot);
		ColleagueRoot->appendChild(aCompanyItem);

		//插入没有组织的人员 
		foreach(st_FeedPtr feed, tempInfo.m_noGroupfeed)
		{
			TNStaffItem * aStaffItem = new TNStaffItem(feed->GetTitle(), aCompanyItem);
			BuildStaffItem(tempInfo, feed, &aStaffItem);
			aCompanyItem->appendChild(aStaffItem);
		}
		foreach(QString departName, tempInfo.m_groupList)
		{
			TNDepartmentItem * aDepartItem = new TNDepartmentItem(departName, aCompanyItem);
			if (tempInfo.m_feed.count(departName) == 0)
				continue;
			qInfo() << "[CardCase][CardCaseListArea]LoadColleague departName:" << departName;
			aCompanyItem->appendChild(aDepartItem);
			for (QMap<QString, QMultiMap<int, st_FeedPtr>>::iterator dpIter = tempInfo.m_feed.begin(); dpIter != tempInfo.m_feed.end(); dpIter++)
			{
				if (dpIter.key() == departName)
				{
					foreach(st_FeedPtr staffFeed, dpIter.value())
					{
						st_FeedPtr feed = staffFeed;
						TNStaffItem * aStaffItem = new TNStaffItem(feed->GetTitle(), aDepartItem);
						BuildStaffItem(tempInfo, staffFeed, &aStaffItem);
						aDepartItem->appendChild(aStaffItem);
					}
				}
			}
		}
	}
	if (_ColleagueModel != nullptr)
	{
		delete _ColleagueModel;
		_ColleagueModel = nullptr;
	}

	_ColleagueModel = new TNCardCaseCOModel(ColleagueRoot);
	_ColleagueListWidgt->setModel(_ColleagueModel);
	_ColleagueModel->setColleagueListView(_ColleagueListWidgt);
	_ColleagueListWidgt->expandToDepth(0);
}
void CardCaseListArea::BuildStaffItem(TNStructCompany company, st_FeedPtr feed, TNStaffItem ** Staff)
{
	/*
	Build Staff 应该统一放在这里 ，即将修改。
	*/
	if (feed == nullptr || Staff == nullptr)
		return;
	QString tag = feed->GetTag();
	if (!tag.isEmpty())
	{
		QStringList temptag = tag.split(",");
		(*Staff)->setTag(temptag);
	}
	(*Staff)->setBelongFeedId(company.m_belongId);
	QString memberFeedId = feed->GetFeedID();
	(*Staff)->setDialogID(memberFeedId);
	QString strAvatarURL = feed->GetAvatarID();
	(*Staff)->setAvatarURL(strAvatarURL);
	(*Staff)->setLatestAvatarURL(strAvatarURL);
	(*Staff)->setSubTitle(feed->GetSubTile());
	(*Staff)->setUserId(feed->GetUserID());
	(*Staff)->setTitlePy(feed->GetTitlePinYin());

	bool forceRefresh = false;
	QString avatarFileName = TNPathUtil::getFeedAvatarPath(memberFeedId);
	if (!QFile::exists(avatarFileName))
	{
		forceRefresh = true;
	}
	(*Staff)->setIsForeceRefreshAvator(forceRefresh);
	(*Staff)->setPhotoResourceID(avatarFileName);
	(*Staff)->setCompanyId(company.m_companyId);
	(*Staff)->setCompanyName(company.m_companyName);
	(*Staff)->setCompanyLogoUrl(company.m_companyUrl);
	(*Staff)->setCompanyLogoText(company.m_companyLogoText);
	(*Staff)->setCompanyExt(company.m_companyFeedId + "," + company.m_companyEmail + "," + company.m_companyTel);
}
void CardCaseListArea::setCODepartItemExpanded(const QModelIndex & index)
{
	if (_ColleagueListWidgt != nullptr && _ColleagueModel != nullptr)
	{
		bool status = !_ColleagueListWidgt->isExpanded(index);
		qInfo() << "[CardCase][CardCaseListArea]setCODepartItemExpanded status:" << status;
		_ColleagueModel->setItemStatus(index, status);
		_ColleagueListWidgt->setExpanded(index, status);
	}
}
void CardCaseListArea::UpdateColleagueUI(QList<UINotifyData> dataList)
{
	qInfo() << "[CardCase][CardCaseListArea]update UpdateColleagueUI thread ID:" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0')) << " dataList: " << dataList.size();
	if (dataList.size() == 0)
	{
		return;
	}
	_mutex.lock();
	_subCardStatus[1] = -1;
	_mutex.unlock();
	/*
	更新同事缓存
	*/
	emit UpdateColleagueCacheSignal();
	if (_ColleagueModel != nullptr)
	{
		ResetOldSelectedStatus(RefreshTypeUI_Colleague);
	}
}
void CardCaseListArea::OnColleagueListAreaSlot(const QModelIndex & index)
{
	TNCardCaseTreeItem *childItem = static_cast<TNCardCaseTreeItem*>(index.internalPointer());
	if (childItem != nullptr && childItem->parentItem() != nullptr && childItem->childCount() == 0 &&
		childItem->parentItem()->parentItem()) //判断父节点的parent是否为空
	{
		TNStaffItem *adapter = static_cast<TNStaffItem*>(index.internalPointer());
		if (adapter != nullptr)
		{
			QVector<QString> baseInfo;
			baseInfo.push_back(adapter->getDialogID());
			baseInfo.push_back(adapter->getTitle());
			baseInfo.push_back(adapter->getTitlePy());
			baseInfo.push_back(adapter->getSubTitle());
			baseInfo.push_back(adapter->getAvatarURL());
			baseInfo.push_back(adapter->getUserId());
			DynamicUpdateFeedInfo(adapter->getDialogID(), adapter->getBelongFeedId(),baseInfo, ColleagueCard);
		}
		emit ListColleagueToDetailEvent(index);
		_ColleagueModel->updateKeyStartFlag(true);
	}
}

/*
群聊
*/
/*
GroupChat Sort regulation: As the Join group chat/Create group chat time .
*/
void CardCaseListArea::OnButtonGroupChatSlot()
{
	_buttonFriend->setChecked(false);
	_buttonColleague->setChecked(false);
	_buttonGroupChat->setChecked(true);
	_buttonGroup->setChecked(false);
	Q_ASSERT(_stackedWidget->count() > 3);
	_stackedWidget->setCurrentIndex(3);
	_currentSelectedCard = GroupChatCard;
	showNullPage(false, _currentSelectedCard);
	TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_Address_GroupChat, _pluginParam);

	QList<TNStructGroupChat> groupChatList;
	TNDataCache::GetInstance()->GetGroupChatCache(groupChatList);
	if (_subCardStatus[3] != 1)
	{
		LoadGroupChat(groupChatList);
	}
	_GroupChatListWidgt->setFocus();
	showNullPage(groupChatList.size() == 0, _currentSelectedCard);
}

void CardCaseListArea::LoadGroupChat(QList<TNStructGroupChat> groupChatInfoList)
{
	QMutexLocker locker(&_mutex);
	_subCardStatus[3] = 1;

	QList<TNCardCaseGroupChatAdapter *> groupChatMyList;
	QList<TNCardCaseGroupChatAdapter *> groupChatJoinList;

	for (QList<TNStructGroupChat>::iterator iter = groupChatInfoList.begin(); iter != groupChatInfoList.end(); iter++)
	{
		TNStructGroupChat groupChatInfo = (*iter);
		st_GroupInfoPtr gcInfo = groupChatInfo.m_groupChatFeed;

		/*
		这里验证影响速度
		*/
		//int inFactMemberCount = TNDataCache::GetInstance()->GetGroupChatMemberCache(gcInfo->GetGroupId()).size();
		//if (inFactMemberCount == 0)
		//{
		//	//实际成员为0，忽略此群
		//	qDebug() << "[CardCaseListArea]LoadGroupChat member count is 0, ignore the grouchat. " << gcInfo->GetGroupId();
		//	continue;
		//}
		/*
		Need to check if it is in my stuff .
		*/
		TNCardCaseGroupChatAdapter * item = new TNCardCaseGroupChatAdapter();
		item->setTitle(gcInfo->GetName());
		item->setGroupChatId(gcInfo->GetGroupId());
		item->setBelongFeedId(gcInfo->GetMyFeedId());
		item->setAvatarURL(gcInfo->GetHeaderImage());
		item->setLatestAvatarURL(gcInfo->GetHeaderImage());
		item->setMemberCount(gcInfo->GetCurrNum());
		item->setTopic(gcInfo->GetTopic());

		QString avatarFileName = TNPathUtil::getFeedAvatarPath(gcInfo->GetGroupId()) + "_org";
		bool forceRefresh = false;
		if (!QFile::exists(avatarFileName))
		{
			forceRefresh = true;
		}

		item->setIsForceRefreshAvatar(forceRefresh);
		item->setPhotoResourceID(avatarFileName);

		if (groupChatInfo.m_flag == 0)
		{
			item->setIsCreator(true);
			groupChatMyList.append(item);
		}
		else
		{
			item->setIsCreator(false);
			groupChatJoinList.append(item);
		}
	}

	if (_GroupChatModel != nullptr)
		_GroupChatModel->resetModel();
	else
		_GroupChatModel = new TNCardCaseGroupChatModel(this);

	_GroupChatModel->appendData(groupChatMyList);
	_GroupChatModel->appendData(groupChatJoinList);
	_GroupChatListWidgt->setModel(_GroupChatModel);
}
void CardCaseListArea::UpdateGroupChatUI(QList<UINotifyData> dataList)
{
	if (_GroupChatModel == nullptr)
	{
		qInfo() << "[CardCase][CardCaseListArea]UpdateGroupChatUI maybe _GroupChatModel is null" << " datalist: " + dataList.size();
		TNDataCache::GetInstance()->UpdateInStepCache(dataList, RefreshTypeUI_GroupChat);
		/*
		通知会话列表  更新下载头像
		*/
		if (dataList.size() > 0)
			emit notifySessionList(dataList, false);
		return;
	}
	qInfo() << "[CardCase][CardCaseListArea]UpdateGroupChatUI thread ID:" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0')) << " dataList: " + dataList.size();
	QList<TNStructGroupChat> groupChatList;
	foreach(UINotifyData uiMsg, dataList)
	{
		switch (uiMsg.operateType)
		{
		case UI_OPERATE_ADD:
			//the GroupChat is exist ,only change the member or others info .
			if (IsExistbyGroupChatId(uiMsg.feedId))
			{
				//Update
				groupChatList.clear();
				TNStructGroupChat groupChat;
				TNDataCache::GetInstance()->UpdateGroupChatCachebyId(groupChatList, uiMsg.feedId, CacheGCOp::gcModify, groupChat);
				st_GroupInfoPtr myStuff = groupChat.m_groupChatFeed;
				if (myStuff == nullptr)
				{
					qInfo() << "[CardCase][CardCaseListArea]UpdateGroupChatUI Modify GroupChat ,error return";
					return;
				}
				QString avatarFileName = TNPathUtil::getFeedAvatarPath(myStuff->GetGroupId()) + "_org";
				if (!TNDataCache::GetInstance()->IsCurrentCardCache(uiMsg.belongId))
				{
					qInfo() << "[CardCase][CardCaseListArea]UpdateGroupChatUI Modify GroupChat ,but not update UI, feed :" << uiMsg.feedId << " belongFeed: " << uiMsg.belongId;
					return;
				}
				//需要决定是否更新头像
				if (_GroupChatModel->isUpdateHeadImage(myStuff->GetGroupId(), myStuff->GetHeaderImage()))
				{
					DownLoadAvatar(myStuff->GetGroupId(), myStuff->GetHeaderImage(), true);
				}
				QModelIndex Index = _GroupChatModel->updateGroupChatItemInfo(myStuff->GetGroupId(), myStuff->GetName(), avatarFileName, myStuff->GetCurrNum(), myStuff->GetHeaderImage());
				if (Index.isValid())
					emit ListGroupChatModifyEvent(Index);
				qInfo() << "[CardCase][CardCaseListArea]UpdateGroupChatUI Modify GroupChat thread ID:" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0')) << " feed: " + uiMsg.feedId;
			}
			else
			{
				//1. 更新缓存  2. 判断是创建还是加入 
				groupChatList.clear();
				TNDataCache::GetInstance()->UpdateGroupChatCachebyId(groupChatList, uiMsg.feedId, CacheGCOp::gcAdd);
				if (!TNDataCache::GetInstance()->IsCurrentCardCache(uiMsg.belongId))
				{
					qInfo() << "[CardCase][CardCaseListArea]UpdateGroupChatUI Add GroupChat ,but not update UI, feed :" << uiMsg.feedId << " belongFeed: " << uiMsg.belongId;
					return;
				}
				TNStructGroupChat groupChat;
				TNDataCache::GetInstance()->UpdateGroupChatCachebyId(groupChatList, uiMsg.feedId, CacheGCOp::gcModify, groupChat);
				st_GroupInfoPtr groupInfo = groupChat.m_groupChatFeed;
				if (groupInfo == nullptr)
					return;
				TNCardCaseGroupChatAdapter * item = new TNCardCaseGroupChatAdapter();
				item->setTitle(groupInfo->GetName());
				item->setGroupChatId(groupInfo->GetGroupId());
				item->setBelongFeedId(groupInfo->GetMyFeedId());
				item->setAvatarURL(groupInfo->GetHeaderImage());
				item->setLatestAvatarURL(groupInfo->GetHeaderImage());
				item->setMemberCount(groupInfo->GetCurrNum());
				item->setTopic(groupInfo->GetTopic());

				QString avatarFileName = TNPathUtil::getFeedAvatarPath(groupInfo->GetGroupId()) + "_org";
				bool forceRefresh = false;
				if (!QFile::exists(avatarFileName))
				{
					forceRefresh = true;
				}

				item->setIsForceRefreshAvatar(forceRefresh);
				item->setPhotoResourceID(avatarFileName);
				item->setIsCreator(groupChat.m_flag == 0);
				DownLoadAvatar(groupInfo->GetGroupId(), groupInfo->GetHeaderImage(), true);
				showNullPage(false, GroupChatCard);
				_GroupChatModel->insertItem(item);
				qInfo() << "[CardCase][CardCaseListArea]UpdateGroupChatUI Add GroupChat thread ID:" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0')) << " feed: " + uiMsg.feedId;
			}
			break;
		case UI_OPERATE_DEL:
			groupChatList.clear();
			TNDataCache::GetInstance()->UpdateGroupChatCachebyId(groupChatList, uiMsg.feedId, CacheGCOp::gcDel);
			if (TNDataCache::GetInstance()->IsCurrentCardCache(uiMsg.belongId))
			{
				_GroupChatModel->removeItem(uiMsg.feedId, uiMsg.belongId);
				if (_GroupChatModel->rowCount() == 0)
					showNullPage(true, GroupChatCard);
				emit CloseDetailPageEvent(uiMsg.feedId, uiMsg.belongId);
			}
			qInfo() << "[CardCase][CardCaseListArea]UpdateGroupChatUI Del GroupChat thread ID:" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0')) << " feed: " + uiMsg.feedId;
			break;
		default:
			break;
		}
	}
}
void CardCaseListArea::UpdateGroupChatMemberUI(QList<UINotifyData> dataList)
{
	/*
	群聊成员变化，仅仅更新缓存，不需要更新UI。
	*/
	qInfo() << "[CardCase][CardCaseListArea]UpdateGroupChatMemberUI datalist: " << dataList.size();
	QList<TNStructGroupChat> groupChatList;
	foreach(UINotifyData uiMsg, dataList)
	{
		//此时在缓存中，群聊一定是存在的， 不管是添加成员，删除成员都是更新成员
		groupChatList.clear();
		TNDataCache::GetInstance()->UpdateGroupChatCachebyId(groupChatList, uiMsg.feedId, CacheGCOp::gcModify);
	}
}
void CardCaseListArea::OnGroupChatListAreaSlot(const QModelIndex & index)
{
	TNCardCaseGroupChatAdapter * adapter = (TNCardCaseGroupChatAdapter*)index.data().toLongLong();
	if (adapter == NULL)
		return;
	DynamicUpdateGroupChatInfo(adapter->getGroupChatId());
	emit ListGroupChatToDetailEvent(index);
	_GroupChatModel->updateKeyStartFlag(true);
}
bool CardCaseListArea::IsExistbyGroupChatId(QString feedId)
{
	bool result = false;
	QList<TNStructGroupChat> groupChatInfoList;
	TNDataCache::GetInstance()->GetGroupChatCache(groupChatInfoList, AVATAR_ALL_FEED);
	for (QList<TNStructGroupChat>::iterator iter = groupChatInfoList.begin(); iter != groupChatInfoList.end(); iter++)
	{
		TNStructGroupChat groupChatInfo = (*iter);
		st_GroupInfoPtr myStuff = groupChatInfo.m_groupChatFeed;
		if (myStuff->GetGroupId() == feedId)
		{
			result = true;
			break;
		}
	}
	return result;
}
void CardCaseListArea::DynamicUpdateGroupChatInfo(QString feedId)
{
	Q_ASSERT(!feedId.isEmpty());
	qInfo() << "[CardCase][CardCaseListArea]DynamicUpdateGroupInfo :" << feedId;
	if (_httpObtainGroupInfo == nullptr)
	{
		qInfo() << "[CardCase][CardCaseListArea]DynamicUpdateGroupInfo _httpObtainGroupInfo is invalid";
		return;
	}
	_httpObtainGroupInfo->GetJson([&](bool success, QJsonObject jsonObject)
	{
		if (success)
		{
			qInfo() << "[CardCase][CardCaseListArea]DynamicUpdateGroupInfo _httpObtainGroupInfo: " << QString(QJsonDocument(jsonObject).toJson());
			QJsonObject dataObject = jsonObject["data"].toObject();
			QString creatorFeedId = dataObject["creatorFeedId"].toString();
			QString groupChatName = dataObject["groupChatName"].toString();
			QString myFeedId = dataObject["myFeedId"].toString();
			QString groupChatHeadImage = dataObject["groupChatHeadImage"].toString();
			int currNum = dataObject["currNum"].toInt();
			int maxNum = dataObject["maxNum"].toInt();
			QString topic = dataObject["topic"].toString();

			QString groupNamePY = TNCHNHelper::GetPinyins(groupChatName);
			st_GroupInfoPtr stGroupInfo = std::make_shared<st_GroupInfo>();
			stGroupInfo->SetMyFeedId(myFeedId);

			stGroupInfo->SetCreatorFeedId(creatorFeedId);
			stGroupInfo->SetCurrNum(currNum);
			stGroupInfo->SetGroupId(topic);
			stGroupInfo->SetHeaderImage(groupChatHeadImage);
			stGroupInfo->SetMaxNum(maxNum);
			stGroupInfo->SetName(groupChatName);
			stGroupInfo->SetTopic(topic);
			stGroupInfo->SetNamePinyin(groupNamePY);

			
			if (_GroupChatModel &&_GroupChatModel->isUpdateGroupInfo(topic, groupChatName, stGroupInfo->GetHeaderImage(),
				currNum))
			{
				qInfo() << "[CardCase][CardCaseListArea]DynamicUpdateGroupInfo info is changed,so update";
				//获取群聊免打扰状态
				int disStatus = 0;
				TableBaseVec oldGroupInfo;
				TNDataControlServer::GetInstance()->Query(oldGroupInfo, "GroupInfo", "groupId", topic, DBTYPE_USER);
				if (oldGroupInfo.size() >0)
				{
					st_GroupInfoPtr oldGroupInfoPtr = std::dynamic_pointer_cast<st_GroupInfo>(oldGroupInfo[0]);
					Q_ASSERT(oldGroupInfoPtr);
					disStatus = oldGroupInfoPtr->GetDisturbStatus();
				}
				stGroupInfo->SetDisturbStatus(disStatus);

				//下载头像
				DownLoadAvatar(stGroupInfo->GetGroupId(), stGroupInfo->GetHeaderImage(), true);
				//更新数据库
				TNDataControlServer::GetInstance()->InsertDatas(std::dynamic_pointer_cast<TableBase>(stGroupInfo), DBTYPE_USER);
				//更新缓存
				TNDataCache::GetInstance()->SynUpdateGroupChatCache(stGroupInfo);
				//更新UI
				DynamicUpdateGroupChatUI(stGroupInfo);
			}
		}
	}, _pluginParam, feedId.mid(3));
}
void CardCaseListArea::DynamicUpdateGroupChatUI(st_GroupInfoPtr group)
{
	Q_ASSERT(group);
	if (_GroupChatModel != nullptr)
	{
		QString avatarFileName = TNPathUtil::getFeedAvatarPath(group->GetGroupId()) + "_org";
		_GroupChatModel->updateGroupChatItemInfo(group->GetGroupId(), group->GetName(), avatarFileName, group->GetCurrNum(), group->GetHeaderImage());
	}
}
/*
社区
*/
/*
Group Sort regulation: As the Join group/Create group time .
*/
void CardCaseListArea::OnButtonGroupSlot()
{
	_buttonFriend->setChecked(false);
	_buttonColleague->setChecked(false);
	_buttonGroupChat->setChecked(false);
	_buttonGroup->setChecked(true);
	Q_ASSERT(_stackedWidget->count() > 2);
	_stackedWidget->setCurrentIndex(2);
	_currentSelectedCard = GroupCard;
	showNullPage(false, _currentSelectedCard);
	TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_Address_Group, _pluginParam);

	QList<TNStructGroup> groupList;
	TNDataCache::GetInstance()->GetGroupCache(groupList);

	if (_subCardStatus[2] != 1)
	{
		LoadGroup(groupList);
	}
	_GroupListWidgt->setFocus();
	showNullPage(groupList.size() == 0, _currentSelectedCard);
}
void CardCaseListArea::LoadGroup(QList<TNStructGroup>& groupInfoList)
{
	QMutexLocker locker(&_mutex);
	_subCardStatus[2] = 1;

	QList<TNCardCaseGroupAdapter *> creatorList;
	QList<TNCardCaseGroupAdapter *> adminList;
	QList<TNCardCaseGroupAdapter *> joinList;

	for (QList<TNStructGroup>::iterator iter = groupInfoList.begin(); iter != groupInfoList.end(); iter++)
	{
		TNStructGroup groupInfo = *iter;
		TNCardCaseGroupAdapter * adapter = new TNCardCaseGroupAdapter();
		Q_ASSERT(adapter != nullptr);

		st_FeedPtr feed = groupInfo.m_groupFeed;
		adapter->setTitle(feed->GetTitle());
		adapter->setSubTitle(feed->GetSubTile());
		adapter->setGroupId(feed->GetFeedID());
		adapter->setBelongFeedId(groupInfo.m_belongId);
		adapter->setAvatarURL(feed->GetAvatarID());
		adapter->setLatestAvatarURL(feed->GetAvatarID());
		adapter->setTitlePy(feed->GetTitlePinYin());

		int memberSize = groupInfo.m_memberCount;
		if (memberSize <= 0)
		{
			memberSize = 999; //Exception value
		}
		adapter->setMemberCount(memberSize);
		QString tag = feed->GetTag();
		if (!tag.isEmpty())
		{
			QStringList temptag = tag.split(",");
			adapter->setGroupSubject(temptag[0]);
			adapter->setGroupTag(temptag);
		}

		bool forceRefresh = false;
		QString avatarFileName = TNPathUtil::getFeedAvatarPath(feed->GetFeedID());
		if (!QFile::exists(avatarFileName))
		{
			forceRefresh = true;
		}
		adapter->setIsForceRefreshAvatar(forceRefresh);
		adapter->setPhotoResourceID(avatarFileName);
		if (groupInfo.m_flag == 1) //版本
		{
			adapter->setIsCreator(true);
			creatorList.append(adapter);
		}
		else if (groupInfo.m_flag == 2) //管理员
		{
			adapter->setIsAdmin(true);
			adminList.append(adapter);
		}
		else
		{
			joinList.append(adapter);
		}
	}
	if (_GroupModel != nullptr)
		_GroupModel->resetModel();
	else
		_GroupModel = new TNCardCaseGroupModel(this);
	_GroupListWidgt->setModel(_GroupModel);

	_GroupModel->appendData(creatorList);
	_GroupModel->appendData(adminList);
	_GroupModel->appendData(joinList);
}
void CardCaseListArea::UpdateGroupUI(QList<UINotifyData> dataList)
{
	qInfo() << "[CardCase][CardCaseListArea]UpdateGroupUI start thread ID:" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0')) << " dataList: " + dataList.size();
	if (_GroupModel == nullptr)
	{
		qInfo() << "[CardCase][CardCaseListArea]UpdateGroupUI maybe _GroupModel is null, data size : " << dataList.size();
		TNDataCache::GetInstance()->UpdateInStepCache(dataList, RefreshTypeUI_Group);
		return;
	}
	TNStructGroup currentGroup;
	QList<TNStructGroup> groupList;
	foreach(UINotifyData uiMsg, dataList)
	{
		switch (uiMsg.operateType)
		{
		case UI_OPERATE_ADD:
			//the GroupChat is exist ,only change the member or others info .
			if (IsExistbyGroupId(uiMsg.feedId,currentGroup))
			{
				//Update
				groupList.clear();
				TNStructGroup group;
				TNDataCache::GetInstance()->UpdateGroupCachebyId(groupList, uiMsg.feedId, CacheGOp::grModify,group);
				if (!TNDataCache::GetInstance()->IsCurrentCardCache(uiMsg.belongId))
				{
					qInfo() << "[CardCase][CardCaseListArea]UpdateGroupUI Modify Group, but not update UI, feed : " << uiMsg.feedId << " belong feed:" << uiMsg.belongId;
					return;
				}
				QString avatarFileName = TNPathUtil::getFeedAvatarPath(uiMsg.feedId);
				QString tag = group.m_groupFeed->GetTag();
				QString sunject;
				if (!tag.isEmpty())
				{
					QStringList temptag = tag.split(",");
					sunject = temptag[0]; //第一个
				}

				_GroupModel->updateGroupItemInfo(uiMsg.feedId, group.m_groupFeed->GetTitle(), avatarFileName, sunject, currentGroup,group);
				qInfo() << "[CardCase][CardCaseListArea]UpdateGroupUI Modify Group thread ID:" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0')) << " feed: " + uiMsg.feedId;
			}
			else
			{
				//1. 更新缓存  2. 判断是创建还是加入 
				groupList.clear();
				TNStructGroup group;
				TNDataCache::GetInstance()->UpdateGroupCachebyId(groupList, uiMsg.feedId, CacheGOp::grAdd, group);
				if (!TNDataCache::GetInstance()->IsCurrentCardCache(uiMsg.belongId))
				{
					qInfo() << "[CardCase][CardCaseListArea]UpdateGroupUI Add Group, but not update UI, feed : " << uiMsg.feedId << " belong feed:" << uiMsg.belongId;
					return;
				}
				TNCardCaseGroupAdapter *adapter = new TNCardCaseGroupAdapter();
				if (adapter != nullptr)
				{
					showNullPage(false, GroupCard);
					BuildGroupItem(group, &adapter);
					_GroupModel->insertItem(adapter);
				}
				qInfo() << "[CardCase][CardCaseListArea]UpdateGroupUI Add Group thread ID:" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0')) << " feed: " + uiMsg.feedId;
			}
			break;
		case UI_OPERATE_DEL:
			groupList.clear();
			TNDataCache::GetInstance()->UpdateGroupCachebyId(groupList, uiMsg.feedId, CacheGOp::grDel);
			if (TNDataCache::GetInstance()->IsCurrentCardCache(uiMsg.belongId))
			{
				_GroupModel->removeItem(uiMsg.feedId, uiMsg.belongId);
				if (_GroupModel->rowCount() == 0)
					showNullPage(true, GroupCard);
				emit CloseDetailPageEvent(uiMsg.feedId, uiMsg.belongId);
			}
			qInfo() << "[CardCase][CardCaseListArea]UpdateGroupUI delete Group thread ID:" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0')) << " feed: " + uiMsg.feedId;
			break;
		default:
			break;
		}
	}
}
void CardCaseListArea::BuildGroupItem(TNStructGroup group, TNCardCaseGroupAdapter ** groupItem)
{
	if (_GroupModel == nullptr || groupItem == nullptr || *groupItem == nullptr)
		return;
	st_FeedPtr feed = group.m_groupFeed;
	if (feed != nullptr)
	{
		(*groupItem)->setGroupId(feed->GetFeedID());
		(*groupItem)->setTitle(feed->GetTitle());
		(*groupItem)->setBelongFeedId(group.m_belongId);
		(*groupItem)->setSubTitle(feed->GetSubTile());
		(*groupItem)->setAvatarURL(feed->GetAvatarID());
		(*groupItem)->setLatestAvatarURL(feed->GetAvatarID());
		(*groupItem)->setMemberCount(group.m_memberCount);
		QString tag = feed->GetTag();
		if (!tag.isEmpty())
		{
			QStringList temptag = tag.split(",");
			(*groupItem)->setGroupTag(temptag);
			(*groupItem)->setGroupSubject(temptag[0]);
		}
		bool forceRefresh = false;
		QString avatarFileName = TNPathUtil::getFeedAvatarPath(feed->GetFeedID());
		if (!QFile::exists(avatarFileName))
		{
			forceRefresh = true;
		}
		(*groupItem)->setIsForceRefreshAvatar(forceRefresh);
		(*groupItem)->setPhotoResourceID(avatarFileName);
		(*groupItem)->setIsCreator(group.m_flag == 1);
		(*groupItem)->setIsAdmin(group.m_flag == 2);
	}
}
void CardCaseListArea::OnGroupListAreaSlot(const QModelIndex & index)
{
	TNCardCaseGroupAdapter * adapter = (TNCardCaseGroupAdapter*)index.data().toLongLong();
	if (adapter != nullptr)
	{
		DynamicUpdateGroupMember(adapter->getGroupId());
		QVector<QString> baseInfo;
		baseInfo.push_back(adapter->getGroupId());
		baseInfo.push_back(adapter->getTitle());
		baseInfo.push_back(adapter->getTitlePy());
		baseInfo.push_back(adapter->getSubTitle());
		baseInfo.push_back(adapter->getAvatarURL());
		baseInfo.push_back(adapter->getGroupSubject());

		DynamicUpdateFeedInfo(adapter->getGroupId(), adapter->getBelongFeedId(),baseInfo, GroupCard);
		emit ListGroupToDetailEvent(index);
		_GroupModel->updateKeyStartFlag(true);
	}
}
bool CardCaseListArea::IsExistbyGroupId(QString feedId, TNStructGroup &currentGroup)
{
	bool result = false;
	QList<TNStructGroup> groupInfoList;
	TNDataCache::GetInstance()->GetGroupCache(groupInfoList, AVATAR_ALL_FEED);
	for (QList<TNStructGroup>::iterator iter = groupInfoList.begin(); iter != groupInfoList.end(); iter++)
	{
		TNStructGroup groupInfo = (*iter);
		st_FeedPtr myStuff = groupInfo.m_groupFeed;
		if (myStuff->GetFeedID() == feedId)
		{
			result = true;
			currentGroup = groupInfo;
			break;
		}
	}
	return result;
}
void CardCaseListArea::DynamicUpdateGroupMember(QString groupId)
{
	Q_ASSERT(!groupId.isEmpty());
	qInfo() << "[CardCase][CardCaseListArea]DynamicUpdateGroupMember :" << groupId;
	if (_httpObtainGroupMember == nullptr)
	{
		qInfo() << "[CardCase][CardCaseListArea]DynamicUpdateGroupMember _httpObtainGroupMember is invalid";
		return;
	}
	_httpObtainGroupMember->GetJson([&](bool success, QString retFeedId, QJsonObject jsonObject)
	{
		if (success)
		{
			qInfo() << "[CardCase][CardCaseListArea]DynamicUpdateGroupMember _httpObtainGroupMember : " << QString(QJsonDocument(jsonObject).toJson());
			int count = jsonObject.value("data").toObject().value("groupMemberCount").toInt();
			if (count > 0)
			{
				//更新数据库
				TNDataControlServer::GetInstance()->UpdateSetValueByField("MyStuff", "ext1", QString::number(count, 10), "feedId", retFeedId, DBTYPE_USER);
				//更新缓存
				TNDataCache::GetInstance()->updateGroupMemberCount(retFeedId, count);
				//更新UI
				DynamicUpdateGroupMemberUI(retFeedId, count);
			}
		}
	}, _pluginParam, groupId, "0");
}
void CardCaseListArea::DynamicUpdateGroupMemberUI(QString groupId, int count)
{
	Q_ASSERT(!groupId.isEmpty());
	if (_GroupModel != nullptr)
	{
		_GroupModel->UpdateGroupMemberCount(groupId,count);
	}
}
/*
搜索
*/
void CardCaseListArea::InitSearchPage()
{
	_searchMode = false;
	_searchArea->hide();
	/*
	MAC 可能需要微调，这块先这么写~
	*/
#ifndef Q_OS_WIN
    _searchArea->move(0, _topWidget->height()+15);
#else
    _searchArea->move(0, _topWidget->height() + 15);
#endif
	_searchArea->setFixedWidth(_stackedWidget->width());
	_searchArea->setFixedHeight(_searchWidget->height() + _topWidget->height() + _stackedWidget->height() - 50);
}
void CardCaseListArea::slotSearch(const QString &text)
{
	if (_nullPageStatus && _nullPage!= nullptr)
	{
		_nullPage->hide();
	}
	InitSearchPage();
	QString key = text;
	SearchContent(key.replace(" ", ""));
}
void CardCaseListArea::SearchContent(QString text)
{
	if (text.isEmpty())
	{
		if (_nullPageStatus && _nullPage != nullptr)
		{
			_nullPage->show();
		}
		return;
	}
	_searchArea->ExcuteSearch(text,TNSearchAreaV2::CardCase);
}
void CardCaseListArea::SearchClickedSlot(const QString & type, const QString & feed, const QString & belongFeed)
{
	if (!_searchArea->isHidden())
	{
		_searchArea->hide();
	}
	_searchLineEdit->clear();
	if (type == "AFriend")
	{
		if (_currentSelectedCard != FriendCard)
		{
			OnButtonFriendSlot();
		}
		int item = -1;
		if ((item = _listCardCaseModel->setSearchSelected(feed, belongFeed)) >= 0)
		{
			QModelIndex index = _listCardCaseModel->index(item, 0);
			if (index.isValid())
			{
				_CardCaselistWidgt->scrollTo(index, QAbstractItemView::PositionAtTop);
				QModelIndex oldIndex = _CardCaselistWidgt->selectionModel()->currentIndex();
				if (oldIndex.isValid())
				{
					_CardCaselistWidgt->selectionModel()->select(oldIndex, QItemSelectionModel::Clear);
				}
				_CardCaselistWidgt->selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);
				emit ListFriendToDetailEvent(index);
			}
		}
	}
	else if (type == "BColleague")
	{
		if (_currentSelectedCard != ColleagueCard)
		{
			OnButtonColleagueSlot();
		}
		QModelIndex parentIndex;
		QModelIndex index = _ColleagueModel->setColleagueSearchSelected(feed, belongFeed, parentIndex);
		if (index.isValid())
		{
			_ColleagueListWidgt->scrollTo(index, QAbstractItemView::PositionAtTop);
			QModelIndex oldIndex = _ColleagueListWidgt->selectionModel()->currentIndex();
			if (oldIndex.isValid())
			{
				_ColleagueListWidgt->selectionModel()->select(oldIndex, QItemSelectionModel::Clear);
			}
			_ColleagueListWidgt->selectionModel()->select(index, QItemSelectionModel::Select);
			if (parentIndex.isValid())
				_ColleagueModel->setSecondNodeStatus(parentIndex, true, Colleague);
			emit ListColleagueToDetailEvent(index);
		}
	}
	else if (type == "CGroup")
	{
		if (_currentSelectedCard != GroupCard)
		{
			OnButtonGroupSlot();
		}
		int index = _GroupModel->setSearchSelected(feed, belongFeed);
		if (index >= 0)
		{
			QModelIndex q_index = _GroupModel->index(index,0);
			if (q_index.isValid())
			{
				_GroupListWidgt->scrollTo(q_index, QAbstractItemView::PositionAtTop);
				QModelIndex oldIndex = _GroupListWidgt->selectionModel()->currentIndex();
				if (oldIndex.isValid())
				{
					_GroupListWidgt->selectionModel()->select(oldIndex, QItemSelectionModel::Clear);
				}
				_GroupListWidgt->selectionModel()->setCurrentIndex(q_index, QItemSelectionModel::Select);
				emit ListGroupToDetailEvent(q_index);
			}
		}
	}
	else if (type == "DGroupChat")
	{
		if (_currentSelectedCard != GroupChatCard)
		{
			OnButtonGroupChatSlot();
		}
		int index = _GroupChatModel->setSearchSelected(feed, belongFeed);
		if (index >= 0)
		{
			QModelIndex q_index = _GroupChatModel->index(index, 0);
			if (q_index.isValid())
			{
				_GroupChatListWidgt->scrollTo(q_index, QAbstractItemView::PositionAtTop);
				QModelIndex oldIndex = _GroupChatListWidgt->selectionModel()->currentIndex();
				if (oldIndex.isValid())
				{
					_GroupChatListWidgt->selectionModel()->select(oldIndex, QItemSelectionModel::Clear);
				}
				_GroupChatListWidgt->selectionModel()->select(q_index, QItemSelectionModel::Select);
				emit ListGroupChatToDetailEvent(q_index);
			}
		}
	}
}
void CardCaseListArea::hideSearchArea(bool status)
{
	if (_searchLineEdit != nullptr)
	{
		_searchLineEdit->clear();
	}
}


/*
名片切换
*/
void CardCaseListArea::on_notifyCurrentFeedChanged(const QString & feedID)
{
	qInfo() << "[CardCase][CardCaseListArea]on_notifyCurrentFeedChanged RECIEVE signal ,card change. Current feed:" << feedID;
	if (feedID.isEmpty())
		return;
	UpdateFriendUIByChangeCard(feedID);
	UpdateColleagueUIByChangeCard(feedID);
	UpdateGroupUIByChangeCard(feedID);
	UpdateGroupChatUIByChangeCard(feedID);
	emit CloseDetailPageEvent(AVATAR_ALL_FEED, AVATAR_ALL_FEED);  //此处feed 无意义
}

void CardCaseListArea::UpdateFriendUIByChangeCard(const QString &feedID)
{
	qInfo() << "[CardCase][CardCaseListArea]UpdateFriendUIByChangeCard ,Current feed:" << feedID;
	/*
	The friend page is not create
	*/
	if (_listCardCaseModel == nullptr)
	{
		return;
	}
	/*
	The current select page is not friend, need to init _subCardStatus[0] again;
	*/
	if (_currentSelectedCard != FriendCard)
	{
		_subCardStatus[0] = -1;
		return;
	}
	/*
	If the current page is friend,reload
	*/
	showNullPage(false, _currentSelectedCard);
	QList<TNStructFriend> friendList;
	TNDataCache::GetInstance()->GetFriendCache(friendList, feedID);
	LoadFriend(friendList);
	showNullPage(friendList.size() == 0, _currentSelectedCard);
}
void CardCaseListArea::UpdateColleagueUIByChangeCard(const QString &feedID)
{
	/*
	Logic is same with friend
	*/
	if (_ColleagueModel == nullptr)
	{
		return;
	}
	if (_currentSelectedCard != ColleagueCard)
	{
		_subCardStatus[1] = -1;
		return;
	}
	showNullPage(false, _currentSelectedCard);
	QList<TNStructCompany> companyList;
	TNDataCache::GetInstance()->GetColleagueCache(companyList, feedID);
	LoadColleague(companyList);
	showNullPage(companyList.size() == 0, _currentSelectedCard);
}
void CardCaseListArea::UpdateGroupUIByChangeCard(const QString &feedID)
{
	/*
	Logic is same with friend
	*/
	if (_GroupModel == nullptr)
	{
		return;
	}
	if (_currentSelectedCard != GroupCard)
	{
		_subCardStatus[2] = -1;
		return;
	}
	showNullPage(false, _currentSelectedCard);
	QList<TNStructGroup> groupList;
	TNDataCache::GetInstance()->GetGroupCache(groupList, feedID);
	LoadGroup(groupList);
	showNullPage(groupList.size() == 0, _currentSelectedCard);
}
void CardCaseListArea::UpdateGroupChatUIByChangeCard(const QString &feedID)
{
	/*
	Logic is same with friend
	*/
	if (_GroupChatModel == nullptr)
	{
		return;
	}
	if (_currentSelectedCard != GroupChatCard)
	{
		_subCardStatus[3] = -1;
		return;
	}
	showNullPage(false, _currentSelectedCard);
	QList<TNStructGroupChat> groupChatList;
	TNDataCache::GetInstance()->GetGroupChatCache(groupChatList, feedID);
	LoadGroupChat(groupChatList);
	showNullPage(groupChatList.size() == 0, _currentSelectedCard);
}
