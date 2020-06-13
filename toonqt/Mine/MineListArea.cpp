#include <QHBoxLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QEvent>

#include "MineListArea.h"
#include "tnnotifycenter.h"
#include "TNDataControlServer.h"
#include "TNUserVersionInfo.h"
#include "TNDataCache.h"
#include "TNPathUtil.h"
#include "TNNetAvatarDown.h"
#include "TNNameSpace.h"

MineListArea::MineListArea(int id, TNPluginParamPtr pluginParam, QWidget *parent)
    : ListAreaBase(id, parent)
	, _MineModel(nullptr)
	, _MineDelegate(nullptr)
	, _MineListWidgt(nullptr)
	, _httpObtainFeedList(nullptr)
	, _pluginParam(pluginParam)
	, _currentSelectedPage(-1)
{
	QVBoxLayout *pMainLayout = new QVBoxLayout();
	setLayout(pMainLayout);

	pMainLayout->setSpacing(0);
	pMainLayout->setContentsMargins(0, 0, 0, 0);

	_MineListWidgt = new TNQListView(this);
	_MineListWidgt->setObjectName("myCardListWidget");
	_MineListWidgt->setAttribute(Qt::WA_MacShowFocusRect, 0);
	_MineDelegate = new TNMineDelegate();
	_MineListWidgt->setItemDelegate(_MineDelegate);
	_MineListWidgt->setMouseTracking(true);
	_MineListWidgt->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	_MineListWidgt->setSelectionMode(QAbstractItemView::SingleSelection);
	connect(_MineDelegate, SIGNAL(downLoadAvatar(const QString &, const QString &, int)), this,
		SLOT(needToDownLoadAvatar(const QString &, const QString &, int)), Qt::QueuedConnection);


	_MineListWidgt->setContentsMargins(0, 0, 0, 0);
	_MineListWidgt->setSpacing(0);
	pMainLayout->addWidget(_MineListWidgt);

	connect(_MineListWidgt, SIGNAL(clicked(const QModelIndex &)), this, SLOT(OnListAreaClickedSlot(const QModelIndex &)));
	
	_httpObtainFeedList = std::make_shared<TNHttpObtainFeedList>();

    TNNotifyCenter::instance()->connectNotifyRefreshAddressList(this);
	TNDataCache::GetInstance()->InstallCatcheFeedUpdateNotify(this); 
	TNNotifyCenter::instance()->connectNotifyKeyEventDis(this);
	_MineListWidgt->installEventFilter(this);
	loadData();
}

MineListArea::~MineListArea()
{

}

void MineListArea::loadData()
{
	qInfo() << "[Mine][MineListArea]loadData start";

	QList<st_FeedPtr> myAllStuff;
	TNDataCache::GetInstance()->getMyStuff(myAllStuff);
	QList<TNMineAdapter *> cardList;
	for (auto iter = myAllStuff.begin(); iter != myAllStuff.end(); iter++)
    {
		TNMineAdapter * adapter = new TNMineAdapter();
		Q_ASSERT(adapter != nullptr);
		adapter->setAvatarURL((*iter)->GetAvatarID());
		adapter->setLatestAvatarURL((*iter)->GetAvatarID());
		adapter->setFeedId((*iter)->GetFeedID());
		adapter->setSubTitle((*iter)->GetSubTile());
		adapter->setTitle((*iter)->GetTitle());
		adapter->setTitlePy((*iter)->GetTitlePinYin());
		QString avatarFileName = TNPathUtil::getFeedAvatarPath((*iter)->GetFeedID());
		bool isForceUpdate = false;
		if (!QFile::exists(avatarFileName))
		{
			isForceUpdate = true;
		}
		adapter->setPhotoResourceID(avatarFileName);
		adapter->setIsForceRefreshAvatar(isForceUpdate);
		cardList.append(adapter);
    }

	if (_MineModel != nullptr)
		_MineModel->resetModel();
	else
		_MineModel = new TNMineModel(this);

	_MineListWidgt->setModel(_MineModel);

	if (cardList.size() > 0)
	{
		_MineModel->appendData(cardList);
		//selectedDefaultPage();
	}
	qInfo() << "[Mine][MineListArea]loadData end";
}

/*
组织名片： 已测试，发送AVATAR_ALL_FEED通知
员工名片更新完毕后会发送 feedID 为ALL 的消息，已测试
个人名片以实际消息为主
*/
void MineListArea::on_notifyRefresh(int type, QList<UINotifyData> data)
{
	if (type == RefreshTypeUI_MyCard && 
		_MineModel != nullptr)
    {
		qInfo() << "[Mine][MineListArea]on_notifyRefresh start";
		foreach(UINotifyData uiMsg, data)
		{
			if (uiMsg.feedId == AVATAR_ALL_FEED) //组织名片通知
			{
				//重新刷新数据
				TNDataCache::GetInstance()->UpdateMyStuffCache();
				loadData();
				break;
			}
			switch (uiMsg.operateType)
			{
			case UI_OPERATE_ADD:
				if (!TNDataCache::GetInstance()->IsInMyStuff(uiMsg.feedId))
				{
					QList<st_FeedPtr> myAllStuff;
					TNDataCache::GetInstance()->UpdateMyStuffCache();
					TNDataCache::GetInstance()->getMyStuff(myAllStuff);

					foreach(st_FeedPtr feed, myAllStuff)
					{
						if (feed->GetFeedID() == uiMsg.feedId)
						{
							qInfo() << "[Mine][MineListArea]Insert Item ,feed:" << uiMsg.feedId;
							TNMineAdapter * adapter = new TNMineAdapter();
							Q_ASSERT(adapter != nullptr);
							adapter->setAvatarURL(feed->GetAvatarID());
							adapter->setLatestAvatarURL(feed->GetAvatarID());
							adapter->setFeedId(feed->GetFeedID());
							adapter->setSubTitle(feed->GetSubTile());
							adapter->setTitle(feed->GetTitle());
							adapter->setTitlePy(feed->GetTitlePinYin());
							QString avatarFileName = TNPathUtil::getFeedAvatarPath(feed->GetFeedID());
							bool isForceUpdate = false;
							if (!QFile::exists(avatarFileName))
							{
								isForceUpdate = true;
							}
							adapter->setPhotoResourceID(avatarFileName);
							adapter->setIsForceRefreshAvatar(isForceUpdate);
							_MineModel->insertItem(adapter);
						}
					}
				}
				break;
			case UI_OPERATE_DEL:
				qInfo() << "[Mine][MineListArea]delete Item ,feed:" << uiMsg.feedId;
				_MineModel->removeItem(uiMsg.feedId);
				break;
			}
		}
		if (!m_selected.isEmpty())
			emit CloseDetailPage(m_selected, m_selected);
		qInfo() << "[Mine][MineListArea]on_notifyRefresh end";
    }
}
void MineListArea::feedCardUpdateFromCatche(const QString &feedId,
											const QString &avatarId,
											const QString &name,
											const QString &subName,
											const QString &userId,
											const QString &namePy,
											int sourceType)
{
	qInfo() << "[Mine][MineListArea]feedCardUpdateFromCatche :" << feedId 
		<< " sourceType:" << sourceType;

	if (sourceType != TN::UpdateSource::Mine &&
		TNDataCache::GetInstance()->IsInMyStuff(feedId))
	{
		if (_MineModel != nullptr)
		{
			st_FeedPtr feed = std::make_shared<st_Feed>();
			feed->SetAvatarID(avatarId);
			feed->SetSubTile(subName);
			feed->SetTitle(name);
			feed->SetFeedID(feedId);
			_MineModel->UpdateItemBaseInfo(feed);
		}
	}
}
void MineListArea::OnListAreaClickedSlot(const QModelIndex & index)
{
	TNMineAdapter *adapter = (TNMineAdapter*)index.data().toLongLong();
	if (adapter != nullptr)
	{
		m_selected = adapter->getFeedId();
		//更新feed信息
		QVector<QString> baseInfo;
		baseInfo.push_back(adapter->getFeedId());
		baseInfo.push_back(adapter->getTitle());
		baseInfo.push_back(adapter->getTitlePy());
		baseInfo.push_back(adapter->getSubTitle());
		baseInfo.push_back(adapter->getAvatarURL());
		dynamicUpdateFeedInfo(adapter->getFeedId(), baseInfo, 0);
		emit ListMineToDetailEvent(index);
	}
}
void MineListArea::dynamicUpdateFeedInfo(QString feedId, QVector<QString>baseInfo,int iType)
{
	Q_ASSERT(!feedId.isEmpty());
	qInfo() << "[Mine][MineListArea]DynamicUpdateFeedInfo :" << feedId;
	if (_httpObtainFeedList == nullptr)
	{
		qInfo() << "[Mine][MineListArea]DynamicUpdateFeedInfo _httpObtainFeedList is invalid";
		return;
	}
	QSet<QString> feedList;
	feedList.insert(feedId);

	std::vector<QVariant> extern_params;
	extern_params.push_back(iType);
	for (int i = 0; i < baseInfo.size(); i++)
	{
		extern_params.push_back(baseInfo[i]);
	}
	QList<UINotifyData> extData;
	_httpObtainFeedList->GetJson([&](bool success, QJsonObject jsonObject, QList<UINotifyData> extData, TNHttpObtainFeedList* httpFeed,
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

				bool baseInfoUpdate = false;
				if (params[1].toString() == stFeed->GetFeedID())
				{
					if (params[2].toString() != stFeed->GetTitle() ||
						params[3].toString() != stFeed->GetTitlePinYin() ||
						params[4].toString() != stFeed->GetSubTile() ||
						params[5].toString() != stFeed->GetAvatarID())
					{
						baseInfoUpdate = true;
						qInfo() << "[Mine][MineListArea]DynamicUpdateFeedInfo baseInfo is changed,will update,feed:" << stFeed->GetFeedID();
					}
				}
				if (baseInfoUpdate)
				{
					qInfo() << "[Mine][MineListArea]DynamicUpdateFeedInfo,info is changed,so update.";
					stFeedList.append(std::dynamic_pointer_cast<TableBase>(stFeed));
					downLoadAvatar(stFeed->GetFeedID(), stFeed->GetAvatarID(), false);
					//更新缓存
					TNDataCache::GetInstance()->SynUpdateFeedCache(stFeed, type, TN::UpdateSource::Mine);
					//更新UI
					dynamicUpdateFeedUI(stFeed, type);
				}
			}
			if (stFeedList.size() > 0)
			{
				TNDataControlServer::GetInstance()->InsertDatas(stFeedList, INSERT_FEED, DBTYPE_USER);
			}
		}
	}, _pluginParam, feedList.toList(), extData, extern_params);
}
void MineListArea::downLoadAvatar(QString feedId, QString url, bool isOriginal)
{
	qInfo() << "[Mine][MineListArea]DownLoadAvatar, url: " << url << " feedId:" << feedId;
	TNNetAvatarDown::GetInstance()->DownLoadFeedAvatar(feedId, url, TNHttpCloudApi::GetInstance()->GetCloudStoken(_pluginParam), this, isOriginal);
}
void MineListArea::dynamicUpdateFeedUI(st_FeedPtr feed, int type)
{
	Q_ASSERT(feed);
	Q_UNUSED(type);
	if (_MineModel != nullptr)
		_MineModel->UpdateItemBaseInfo(feed);
}
void MineListArea::onAvatarDownLoadFinish(bool success, QString url, QString feedId)
{
	Q_UNUSED(url);
	if (success && _MineModel != nullptr)
		_MineModel->refreshItem(feedId);
}
void MineListArea::needToDownLoadAvatar(const QString &feedId, const QString &url, int type)
{
	qInfo() << "[Mine][MineListArea]needToDownLoadAvatar, feedId: " << feedId << " URL:" << url;
	Q_ASSERT(!feedId.isEmpty());
	Q_ASSERT(!url.isEmpty());
	if (!url.isEmpty() && !feedId.isEmpty())
	{
		downLoadAvatar(feedId, url, false);
	}
}
void MineListArea::on_notifyKeyEventDis(int keyEvent)
{
	if (_currentSelectedPage == MENU_MINE_ID)
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
			break;
		default:
			break;
		}
	}
}
bool MineListArea::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == _MineListWidgt && _currentSelectedPage == MENU_MINE_ID){
		if (event->type() == QEvent::KeyPress){
			QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(event);
			if (keyEvent != nullptr){
				if (keyEvent->key() == Qt::Key_Up){
					upSelected();
				}
				else if (keyEvent->key() == Qt::Key_Down){
					downSelected();
				}
			}
		}
	}
	return QWidget::eventFilter(watched, event);
}
void MineListArea::downSelected()
{
	if (_MineModel != nullptr
		&&_MineModel->rowCount() > 0)
	{
		QModelIndex oldIndex = _MineListWidgt->selectionModel()->currentIndex();
		if (oldIndex.isValid())
		{
			_MineListWidgt->selectionModel()->select(oldIndex, QItemSelectionModel::Clear);
		}
		_MineListWidgt->selectionModel()->setCurrentIndex(_MineModel->getNextIndex(oldIndex), QItemSelectionModel::Select);
		enterSelected();
	}
}
void MineListArea::upSelected()
{
	if (_MineModel->rowCount() > 0)
	{
		QModelIndex oldIndex = _MineListWidgt->selectionModel()->currentIndex();
		if (oldIndex.isValid())
		{
			_MineListWidgt->selectionModel()->select(oldIndex, QItemSelectionModel::Clear);
		}
		_MineListWidgt->selectionModel()->setCurrentIndex(_MineModel->getPreIndex(oldIndex), QItemSelectionModel::Select);
		enterSelected();
	}
}
void MineListArea::enterSelected()
{
	QModelIndex oldIndex = _MineListWidgt->selectionModel()->currentIndex();
	if (oldIndex.isValid())
	{
		OnListAreaClickedSlot(oldIndex);
	}
}
void MineListArea::selectedDefaultPage()
{
	/*
	默认选中第一条记录
	*/
	QModelIndex nullIndex;
	QModelIndex oldIndex = _MineListWidgt->selectionModel()->currentIndex();
	if (oldIndex.isValid())
	{
		_MineListWidgt->selectionModel()->select(oldIndex, QItemSelectionModel::Clear);
	}
	_MineListWidgt->selectionModel()->setCurrentIndex(_MineModel->getPreIndex(nullIndex), QItemSelectionModel::Select);
	enterSelected();
}
void MineListArea::currentSelectedPage(int page)
{
	_currentSelectedPage = page;
}