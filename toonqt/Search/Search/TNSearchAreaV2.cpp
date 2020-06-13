#include "TNSearchAreaV2.h"
#include "ui_TNSearchAreaV2.h"
#include "TNDataControlServer.h"
#include "TNIMCoreClient.h"
#include "TNPathUtil.h"
#include "TNDebugLog.h"
#include "tnnotifycenter.h"
#include "TNDataCache.h"
#include "tnnotifycenter.h"
#include "searchtableview.h"
#include "TNHttpCloudApi.h"
#include "TNNetAvatarDown.h"
#include "TNSearchTypeItem.h"
#include "TNSearchNameItem.h"
#include "TNDataSearch.h"
#include "TNSearchDataItemWidget.h"
#include "TNDataStatistics.h"
#include "TNDefaultPage.h"
#include "tnnotifycenter.h"

#include <QtMath>
#include <QToolButton>
#include <QJsonObject>
#include <QVBoxLayout>
#include <QKeyEvent>

TNSearchAreaV2::TNSearchAreaV2(TNPluginParamPtr param, QWidget *parent)
: QWidget(parent), m_pluginParam(param),
	ui(new Ui::TNSearchAreaV2),
	_listSearchModel(nullptr),
	_SearchDelegate(nullptr),
	_SearchlistWidgt(nullptr),
	_nullPage(nullptr),
	_SearchMode(-1)
{
	ui->setupUi(this);
	_SearchlistWidgt = new TNSearchViewV2();
	_SearchlistWidgt->setObjectName("SearchlistWidgt");
	_SearchlistWidgt->setAttribute(Qt::WA_MacShowFocusRect, 0);

	_SearchDelegate = new TNSearchListItemDelegateV2();
	_SearchlistWidgt->setItemDelegate(_SearchDelegate);
	_SearchlistWidgt->setHeaderHidden(true);
	_SearchlistWidgt->setIndentation(0);
	_SearchlistWidgt->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	_SearchlistWidgt->setFocus();

	_nullPage = new TNDefaultPage(this);
	_nullPage->setObjectName("NULLPageSearch");
    _nullPage->setTextTitle(("没有相关的内容"));
    _nullPage->setBackPic("searchnullico",QSize(60,60));

	connect(_SearchlistWidgt, SIGNAL(clicked(const QModelIndex &)), this, SLOT(OnListAreaClickedSlot(const QModelIndex &)));
	connect(_SearchDelegate, SIGNAL(showButtonClickedIntag(QModelIndex, int, bool)), this, SLOT(buttonShowAll(QModelIndex, int, bool)));
	connect(_SearchDelegate, SIGNAL(downLoadAvatar(const QString &, const QString &, int)), this,
		SLOT(needToDownLoadAvatar(const QString &, const QString &, int)), Qt::QueuedConnection);
	connect(this, SIGNAL(resetShowAll()), _SearchDelegate, SLOT(resetShowAllStatus()));

	
	QVBoxLayout *main_layout = new QVBoxLayout(this);
	main_layout->addWidget(_SearchlistWidgt);
	main_layout->setSpacing(0);
	main_layout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(main_layout);

	_SearchlistWidgt->installEventFilter(this);
}

TNSearchAreaV2::~TNSearchAreaV2()
{
	if (_SearchlistWidgt != nullptr)
	{
		delete _SearchlistWidgt;
		_SearchlistWidgt = nullptr;
	}
	if (_SearchDelegate != nullptr)
	{
		delete _SearchDelegate;
		_SearchDelegate = nullptr;
	}
	if (_listSearchModel != nullptr)
	{
		delete _listSearchModel;
		_listSearchModel = nullptr;
	}
	if (_nullPage != nullptr)
	{
		delete _nullPage;
		_nullPage = nullptr;
	}
}
void TNSearchAreaV2::GetSearchResultForSession(const QString &searchType, const QString &feed, const QString &belongFeed, TNSearchNameItem &resultItem)
{
	foreach(QString type, _searchResult.keys())
	{
		for (int i = 0; i< _searchResult.value(type).size(); i++)
		{
			TNSearchNameItem * nameItem = _searchResult.value(type)[i];
			if (nameItem->getFeedID() == feed && nameItem->getBelongFeedId() == belongFeed)
			{
				resultItem.setUserId(nameItem->getUserId());
				resultItem.setBelongFeedId(nameItem->getBelongFeedId());
				resultItem.setFeedID(nameItem->getFeedID());
				resultItem.setPhotoResourceID(nameItem->getPhotoResourceID());
				resultItem.setAvatarURL(nameItem->getAvatarURL());
				resultItem.setTitle(nameItem->getTitle());
				resultItem.SetType(nameItem->getType());
				break;
			}
		}
	}
}
void TNSearchAreaV2::OnListAreaClickedSlot(const QModelIndex & index)
{
	TNSearchTreeItemV2 *item = static_cast<TNSearchTreeItemV2*>(index.internalPointer());
	if (item == NULL ||item->getItemGrade() == TNSearchTreeItemV2::Type)
		return;
	TNSearchNameItem *nameItem = static_cast<TNSearchNameItem*>(item);
	if (nameItem != nullptr){
		TNDamSearchData upData;
		upData.keyWord = _keyText;
		upData.number = QString::number(index.row());
		QString typeString = nameItem->getTypeString();
		if (typeString == "AFriend"){
			upData.type = SERACH_TYPE_Friend;
		}
		else if (typeString == "BColleague"){
			upData.type = SERACH_TYPE_Colleage;
		}
		else if (typeString == "CGroup"){
			upData.type = SEARCH_TYPE_Group;
		}
		else if (typeString == "DGroupChat"){
			upData.type = SEARCH_TYPE_GroupChat;
		}
		else if (typeString == "ENotifyMsg"){
			upData.type = SEARCH_TYPE_GroupChat;
		}
		upData.dataId = nameItem->getFeedID();
		switch (_SearchMode)
		{
		case CardCase:
			TNDataStatistics::RecordSearchStaticsData(FUNC_TYPE_Address_Search, m_pluginParam, upData);
			break;
		case Session:
			TNDataStatistics::RecordSearchStaticsData(FUNC_TYPE_Notice_Search, m_pluginParam, upData);
			break;
		default:
			break;
		}
		emit ClickedSearchItem(nameItem->getTypeString(), nameItem->getFeedID(), nameItem->getBelongFeedId());
	}
}
void TNSearchAreaV2::buttonShowAll(const QModelIndex &index, int tag, bool showType)
{
	qInfo() << "[Search][TNSearchAreaV2]buttonShowAll " << tag;
	if (tag == 1)
	{
		if (showType)
		{
			QList<TNSearchTreeItemV2 *> othersList;
			for (int i = SEARCH_SHOW_COUNT; i< _searchResult.value("AFriend").size(); i++)
			{
				TNSearchNameItem * nameItem = _searchResult.value("AFriend")[i];
				othersList.append(nameItem);
			}
			_listSearchModel->insertItem(index, othersList, TNSearchNameItem::FriendItem);
		}
		else
		{
			_listSearchModel->removeItem(index, _searchResult.value("AFriend").size(), TNSearchNameItem::FriendItem);
		}
	}
	else if (tag == 2)
	{
		if (showType)
		{
			QList<TNSearchTreeItemV2 *> othersList;
			for (int i = SEARCH_SHOW_COUNT; i< _searchResult.value("BColleague").size(); i++)
			{
				TNSearchNameItem * nameItem = _searchResult.value("BColleague")[i];
				othersList.append(nameItem);
			}
			_listSearchModel->insertItem(index, othersList, TNSearchNameItem::ColleagueItem);
		}
		else
		{
			_listSearchModel->removeItem(index, _searchResult.value("BColleague").size(), TNSearchNameItem::ColleagueItem);
		}
	}
	else if (tag == 3)
	{
		if (showType)
		{
			QList<TNSearchTreeItemV2 *> othersList;
			for (int i = SEARCH_SHOW_COUNT; i< _searchResult.value("CGroup").size(); i++)
			{
				TNSearchNameItem * nameItem = _searchResult.value("CGroup")[i];
				othersList.append(nameItem);
			}
			_listSearchModel->insertItem(index, othersList, TNSearchNameItem::GroupItem);
		}
		else
		{
			_listSearchModel->removeItem(index, _searchResult.value("CGroup").size(), TNSearchNameItem::GroupItem);
		}
	}
	else if (tag == 4)
	{
		if (showType)
		{
			QList<TNSearchTreeItemV2 *> othersList;
			for (int i = SEARCH_SHOW_COUNT; i< _searchResult.value("DGroupChat").size(); i++)
			{
				TNSearchNameItem * nameItem = _searchResult.value("DGroupChat")[i];
				othersList.append(nameItem);
			}
			_listSearchModel->insertItem(index, othersList, TNSearchNameItem::GroupChatItem);
		}
		else
		{
			_listSearchModel->removeItem(index, _searchResult.value("DGroupChat").size(), TNSearchNameItem::GroupChatItem);
		}
	}
	else if (tag == 5)
	{
		if (showType)
		{
			QList<TNSearchTreeItemV2 *> othersList;
			for (int i = SEARCH_SHOW_COUNT; i< _searchResult.value("ENotifyMsg").size(); i++)
			{
				TNSearchNameItem * nameItem = _searchResult.value("ENotifyMsg")[i];
				othersList.append(nameItem);
			}
			_listSearchModel->insertItem(index, othersList, TNSearchNameItem::NotifyItem);
		}
		else
		{
			_listSearchModel->removeItem(index, _searchResult.value("ENotifyMsg").size(), TNSearchNameItem::NotifyItem);
		}
	}
}
void TNSearchAreaV2::DownLoadAvatarForSearch(QString feedId, QString url, bool isOriginal)
{
	qInfo() << "[Search][TNSearchAreaV2]DownLoadAvatarForSearch, url: " << url << " feedId:" << feedId;
	TNNetAvatarDown::GetInstance()->DownLoadFeedAvatar(feedId, url, TNHttpCloudApi::GetInstance()->GetCloudStoken(m_pluginParam), this, isOriginal);
}
void TNSearchAreaV2::onAvatarDownLoadFinish(bool success, QString url, QString feedId)
{
	qInfo() << "[Search][TNSearchAreaV2]onAvatarDownLoadFinish, url: " << url << " feedId:" << feedId;
	_listSearchModel->updateSearchAvatar(feedId,url);
}
void TNSearchAreaV2::showDialog()
{
	this->show();
}
void TNSearchAreaV2::ExcuteSearch(QString text,int searchMode)
{
	qInfo() << "[Search][TNSearchAreaV2]ExcuteSearch, key: " << text;
	_searchResult.clear();
	QList<TNStructSearch> result;
	_keyText = text;
	_SearchMode = searchMode;
	switch (_SearchMode)
	{
	case CardCase:
		TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_Address_Search, m_pluginParam);
		TNDataSearch::GetInstance()->Search(0, "11110", text, result);
		break;
	case Session:
		TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_Notice_Search, m_pluginParam);
		/*
		如果当前feed不是All,不搜索通知
		*/
		if (TNDataCache::GetInstance()->GetCurrentMyFeed() == AVATAR_ALL_FEED)
			TNDataSearch::GetInstance()->Search(0, "11111", text, result);
		else
			TNDataSearch::GetInstance()->Search(0, "11110", text, result);
		break;
	default:
		break;
	}
	TNSearchTreeItemV2 *root = new TNSearchTreeItemV2(QList<QVariant>() << ("搜索结果"), 0);
	foreach(TNStructSearch search, result)
	{
		TNSearchNameItem * tempItem = nullptr;
		switch (search.m_flag)
		{
		case 0:
			tempItem = new TNSearchNameItem(search.m_Feed->GetTitle());
			if (search.m_count > 1 && TNDataCache::GetInstance()->GetCurrentMyFeed() == AVATAR_ALL_FEED)
			{
				tempItem->setShowBelongStatus(true);
				tempItem->setBelongPhotoResID(TNPathUtil::getFeedAvatarPath(search.m_belongFeedId));
			}
			tempItem->SetType(TNSearchNameItem::FriendItem);
			if (search.m_hitType == 0) //备注名 hit
			{
				tempItem->setTitle(search.m_extString);
			}
			else if (search.m_hitType == 1)
			{
				if (search.m_extString.isEmpty())
					tempItem->setTitle(search.m_Feed->GetTitle());
				else
				{
					tempItem->setNickName(search.m_Feed->GetTitle());
					tempItem->setTitle(search.m_extString);
				}
			}
			_searchResult["AFriend"].append(tempItem);
			break;
		case 1:
			tempItem = new TNSearchNameItem(search.m_Feed->GetTitle());
			tempItem->SetType(TNSearchNameItem::ColleagueItem);
			if (search.m_count > 1 && TNDataCache::GetInstance()->GetCurrentMyFeed() == AVATAR_ALL_FEED)
			{
				tempItem->setShowBelongStatus(true);
				tempItem->setBelongPhotoResID(TNPathUtil::getFeedAvatarPath(search.m_belongFeedId));
			}
			tempItem->setTitle(search.m_Feed->GetTitle());
			_searchResult["BColleague"].append(tempItem);
			break;
		case 2:
			if (_SearchMode == Session)
			{
				continue;
			}
			tempItem = new TNSearchNameItem(search.m_Feed->GetTitle());
			tempItem->SetType(TNSearchNameItem::GroupItem);
			tempItem->setTitle(search.m_Feed->GetTitle());
			_searchResult["CGroup"].append(tempItem);
			break;
		case 3:
			tempItem = new TNSearchNameItem(search.m_Feed->GetTitle());
			tempItem->SetType(TNSearchNameItem::GroupChatItem);
			tempItem->setTitle(search.m_Feed->GetTitle());
			if (search.m_hitType == 2)
				tempItem->setNickName(search.m_extString);
			_searchResult["DGroupChat"].append(tempItem);
			break;
		case 4:
			if (_SearchMode == CardCase)
			{
				continue;
			}
			tempItem = new TNSearchNameItem(search.m_Feed->GetTitle());
			tempItem->SetType(TNSearchNameItem::NotifyItem);
			tempItem->setTitle(search.m_Feed->GetTitle());
			_searchResult["ENotifyMsg"].append(tempItem);
			break;
		default:
			break;
		}
		if (tempItem != nullptr){
			tempItem->setSearchHitType(search.m_hitType);
			tempItem->setSearchHitKey(search.m_hitString);
			tempItem->setBelongFeedId(search.m_belongFeedId);
			tempItem->setFeedID(search.m_Feed->GetFeedID());
			tempItem->setAvatarURL(search.m_Feed->GetAvatarID());
			tempItem->setUserId(search.m_Feed->GetUserID());

			QString avatarFileName = TNPathUtil::getFeedAvatarPath(search.m_Feed->GetFeedID());
			bool isForceRefreshAvator = false;
			if (!QFile::exists(avatarFileName))
			{
				isForceRefreshAvator = true;
			}
			tempItem->setIsForeceRefreshAvator(isForceRefreshAvator);
			if (search.m_flag == 3)
				avatarFileName += "_org";
			tempItem->setPhotoResourceID(avatarFileName);
		}
	}
	for (const QString &type : _searchResult.keys())
	{
		int itemCount = _searchResult.value(type).size();
		TNSearchTypeItem * typeItem = new TNSearchTypeItem(type, itemCount, root);
		root->appendChild(typeItem);

		int showCount = itemCount > SEARCH_SHOW_COUNT ? SEARCH_SHOW_COUNT : itemCount;
		for (int i = 0; i< itemCount; i++)
		{
			TNSearchNameItem * nameItem = _searchResult.value(type)[i];
			nameItem->setParent(typeItem);
			if (i <showCount)
				typeItem->appendChild(nameItem);
		}
	}
	qInfo() << "[Search][TNSearchAreaV2]ExcuteSearch prepare data ok";

	if (_listSearchModel != nullptr)
	{
		delete _listSearchModel;
		_listSearchModel = nullptr;
	}

	emit resetShowAll();
	_listSearchModel = new TNSearchListModelV2(root);
	_SearchlistWidgt->setModel(_listSearchModel);
	_listSearchModel->setSearchListView(_SearchlistWidgt);
	_SearchlistWidgt->expandToDepth(1);
	_SearchlistWidgt->scrollTo(_listSearchModel->index(0, 0));
	this->show();
	selectedDefaultPage();
	showNullPage(root->childCount()==0);
	qInfo() << "[Search][TNSearchAreaV2]ExcuteSearch end";
}
void TNSearchAreaV2::showNullPage(bool status)
{
	if (_nullPage != nullptr)
	{
		int h = _nullPage->height();
		int w = _nullPage->width();
		int ph = this->height();

		_nullPage->move((LIST_AREA_WIDTH - w) / 2, (ph-h)/3);
		_nullPage->raise();
		status ?_nullPage->show():_nullPage->hide();
	}
}
void TNSearchAreaV2::needToDownLoadAvatar(const QString &feedId, const QString &url, int type)
{
	qInfo() << "[Search][TNSearchAreaV2]needToDownLoadAvatar, feedId: " << feedId << " URL:" << url;
	Q_ASSERT(!feedId.isEmpty());
	Q_ASSERT(!url.isEmpty());
	if (!url.isEmpty() && !feedId.isEmpty())
	{
		bool isOriginal = false;
		if (feedId.startsWith("gc_"))
		{
			isOriginal = true;
		}
		DownLoadAvatarForSearch(feedId, url, isOriginal);
	}
}
void TNSearchAreaV2::keyboadEventMgr(int keyEvent)
{
	switch (keyEvent)
	{
	case Qt::Key_Down:
		downSelected();
		break;
	case Qt::Key_Up:
		upSelected(); 
		break;
	case Qt::Key_Return:
	case Qt::Key_Enter:
		enterSelected();
		break;
	default:
		break;
	}
}
void TNSearchAreaV2::downSelected()
{
	Q_ASSERT(_SearchlistWidgt);
	Q_ASSERT(_listSearchModel);

	int count = _listSearchModel->rowCount();
	if (count > 0)
	{
		QModelIndex oldIndex = _SearchlistWidgt->selectionModel()->currentIndex();
		if (oldIndex.isValid())
		{
			_SearchlistWidgt->selectionModel()->select(oldIndex, QItemSelectionModel::Clear);
		}
		_SearchlistWidgt->selectionModel()->setCurrentIndex(_listSearchModel->getNextIndex(oldIndex), QItemSelectionModel::Select);
	}
}
void TNSearchAreaV2::upSelected()
{
	Q_ASSERT(_SearchlistWidgt);
	Q_ASSERT(_listSearchModel);

	int count = _listSearchModel->rowCount();
	if (count > 0)
	{
		QModelIndex index;
		QModelIndex oldIndex = _SearchlistWidgt->selectionModel()->currentIndex();
		if (oldIndex.isValid())
		{
			_SearchlistWidgt->selectionModel()->select(oldIndex, QItemSelectionModel::Clear);
		}
		_SearchlistWidgt->selectionModel()->setCurrentIndex(_listSearchModel->getPreIndex(oldIndex), QItemSelectionModel::Select);
	}
}
bool TNSearchAreaV2::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == _SearchlistWidgt){
		if (event->type() == QEvent::KeyPress){
			QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(event);
			if (keyEvent != nullptr){
				if (keyEvent->key() == Qt::Key_Up){
					upSelected();
				}
				else if (keyEvent->key() == Qt::Key_Down){
					downSelected();
				}
				else if (keyEvent->key() == Qt::Key_Enter ||
					keyEvent->key() == Qt::Key_Return)
				{
					enterSelected();
				}
			}
		}
	}
	return QWidget::eventFilter(watched, event);
}
void TNSearchAreaV2::selectedDefaultPage()
{
	/*
	默认选中第一条记录
	*/
	QModelIndex nullIndex;
	QModelIndex oldIndex = _SearchlistWidgt->selectionModel()->currentIndex();
	if (oldIndex.isValid())
	{
		_SearchlistWidgt->selectionModel()->select(oldIndex, QItemSelectionModel::Clear);
	}
	_SearchlistWidgt->selectionModel()->setCurrentIndex(_listSearchModel->getPreIndex(nullIndex), QItemSelectionModel::Select);
}
void TNSearchAreaV2::enterSelected()
{
	QModelIndex currentIndex = _SearchlistWidgt->selectionModel()->currentIndex();
	if (currentIndex.isValid())
	{
		emit _SearchlistWidgt->clicked(currentIndex);
	}
}
