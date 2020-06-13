#include "tnsearcharea.h"
#include "ui_tnsearcharea.h"
#include "TNDataControlServer.h"
#include "TNIMCoreClient.h"
#include "TNPathUtil.h"
#include "TNDebugLog.h"
#include "tnnotifycenter.h"
#include "Search/TNSearchAdapter.h"
#include "TNDataCache.h"
#include "tnnotifycenter.h"
#include "searchtableview.h"
#include "TNHttpCloudApi.h"
#include "TNNetAvatarDown.h"
#include <QtMath>
#include <QToolButton>
#include <QJsonObject>
#include <QVBoxLayout>

tnsearcharea::tnsearcharea(TNPluginParamPtr param, QWidget *parent)
	: QWidget(parent), m_pluginParam(param),
	ui(new Ui::tnsearcharea),
	_parentHeight(0),
	_parentWidth(0)
{
	ui->setupUi(this);

	_SearchlistWidgt = new searchTableView(this);
	_SearchlistWidgt->setObjectName("SearchlistWidgt");
	_SearchlistWidgt->setShowGrid(false);
	_SearchlistWidgt->setSelectionBehavior(QAbstractItemView::SelectItems);
	_SearchlistWidgt->setMouseTracking(true);
	_SearchlistWidgt->setEditTriggers(QAbstractItemView::AllEditTriggers);
	_SearchDelegate = new TNSearchListItemDelegate(_SearchlistWidgt);
	_SearchDelegate->setParentWidget(this);
	_SearchlistWidgt->setItemDelegate(_SearchDelegate);
	_listSearchModel = new TNCardCaseSearchListModel(this);
	_listSearchModel->setTableView(_SearchlistWidgt);
	_SearchlistWidgt->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	_SearchlistWidgt->setModel(_listSearchModel);
	_SearchlistWidgt->verticalHeader()->setDefaultSectionSize(LIST_SEARCH_HEIGHT); //在 Delegate 里面设置
	_SearchlistWidgt->horizontalHeader()->setDefaultSectionSize(LIST_SEARCH_WIDTH);
	_SearchlistWidgt->horizontalHeader()->setVisible(false);// 水平不可见
	_SearchlistWidgt->verticalHeader()->setVisible(false);// 垂直不可见

	_SearchAreaBottom = new tnsearchbottom(this);
	_SearchAreaBottom->setObjectName("CardCaseSearchBottom");
	_SearchAreaBottom->setStyleSheet("background:rgba(0,0,0,0.5);");
	connect(_SearchlistWidgt, SIGNAL(clicked(const QModelIndex &)), this, SLOT(OnListAreaClickedSlot(const QModelIndex &)));
	connect(_SearchDelegate, SIGNAL(showButtonClickedIntag(QModelIndex,int,bool)), this, SLOT(buttonShowAll(QModelIndex,int, bool)));
	connect(_SearchDelegate, SIGNAL(createWidgetFinished(const QModelIndex&, int)), this, SLOT(onItemCreateFinished(const QModelIndex&, int)), Qt::QueuedConnection);
	connect(_SearchDelegate, SIGNAL(photoButtonClicked(const QModelIndex &)), this, SLOT(OnListAreaClickedSlot(const QModelIndex &)));

	QVBoxLayout *main_layout = new QVBoxLayout(this);
	main_layout->addWidget(_SearchlistWidgt);
	/*
	暂时不需要阴影部分
	*/
	//main_layout->addWidget(_SearchAreaBottom);
	main_layout->setSpacing(0);
	main_layout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(main_layout);
}

tnsearcharea::~tnsearcharea()
{
	delete ui;
}
void tnsearcharea::setSearchResult(QMap<QString,QList<TNSearchAdapter*>> result)
{
	_SearchResult = result;
	_listSearchModel->clearData();
	QList<TNSearchAdapter*> adatpterList;
	/*
	Now, don't show the type tag . 
	*/
	int tagCount = result.size();
	int allItemCount = 0;
	for(const QString &type: result.keys())
	{
		TNSearchAdapter *labelAdapter = new TNSearchAdapter(TNSearchAdapter::FriendLetter);
		labelAdapter->setName(QString(type));
		labelAdapter->setShowButtonName(("显示全部"));
		int itemCount = result.value(type).size();
		labelAdapter->setItemCount(itemCount);
		adatpterList.append(labelAdapter);
		itemCount = itemCount > SEARCH_SHOW_COUNT ? SEARCH_SHOW_COUNT : itemCount;
		for (int i = 0; i< itemCount; i++)
		{
			allItemCount++;
			qDebug() << "Search Result: " << type << result.value(type)[i]->getName();
			adatpterList.append(result.value(type)[i]);
		}
	}
	InitBottomPage(tagCount,allItemCount);
	if (adatpterList.size() > 0)
	{
		_listSearchModel->appendData(adatpterList);
	}
}
void tnsearcharea::OnListAreaClickedSlot(const QModelIndex & index)
{
	TNSearchAdapter *adapter = (TNSearchAdapter*)index.data().toLongLong();

	if ((adapter == NULL) || (adapter->getType() == TNSearchAdapter::FriendLetter))
		return;
	_SelectedResult.clear();

	foreach(TNSearchAdapter *adapterInResult, _SearchResult.value(adapter->getTypeString()))
	{
		if (adapterInResult->getDialogID() == adapter->getDialogID() && adapterInResult->getType() == adapter->getType()
			&& adapterInResult->getBelongFeedId() == adapter->getBelongFeedId())
		{
			qDebug() << "Clicked search result: " << adapter->getTypeString() << "  Name: " << adapter->getName();
			_SelectedResult[adapter] = adapter->getTypeString();
			break;
		}
	}
	if (_SelectedResult.size() > 0)
	{
		QList<UINotifyData> dataList;
		TNNotifyCenter::instance()->postNotifyRefresh(RefreshTypeUI_Search, dataList);
	}
}
void tnsearcharea::buttonShowAll(const QModelIndex &index, const QString &tagString,const QString &buttonName, bool showType)
{
	qDebug() << tagString;
	emit ShowButtonClickedSignal(tagString,buttonName);
}
void tnsearcharea::InitBottomPage(int tagCount, int itemCount)
{
	int factH = _parentHeight - tagCount * 24 - LIST_AREA_HEIGHT *itemCount;
	_SearchAreaBottom->setButtomFixedHeight(factH < LIST_AREA_HEIGHT *2.5 ? LIST_AREA_HEIGHT *2.5:factH);
	_SearchAreaBottom->setButtomFixedWidth(_parentWidth);
	_SearchAreaBottom->hide();
}
void tnsearcharea::setShowAllResult(const QString &tag,const QMap<QString, QList<TNSearchAdapter*>> &result)
{
	qDebug() << tag;
	if (result.size() == 0)
	{
		return;
	}
	_SearchResult = result;
	_listSearchModel->ResetModel();
	QList<TNSearchAdapter*> adatpterList;

	int tagCount = 1;
	int allItemCount = 0;
	for (const QString &type : result.keys())
	{
		if (type.mid(1, type.length() - 1) == tag)
		{
			TNSearchAdapter *labelAdapter = new TNSearchAdapter(TNSearchAdapter::FriendLetter);
			labelAdapter->setName(QString(type));
			labelAdapter->setShowButtonName(("收起"));
			allItemCount = result.value(type).size();
			labelAdapter->setItemCount(allItemCount);
			adatpterList.append(labelAdapter);
			for (int i = 0; i < allItemCount; i++)
			{
				TNSearchAdapter *itemAdapter = new TNSearchAdapter(TNSearchAdapter::FriendItem);
				itemAdapter->setTitlePinYin(result.value(type)[i]->getTitlePinYin());
				itemAdapter->setSex(result.value(type)[i]->getSex());
				itemAdapter->setBelongFeedId(result.value(type)[i]->getBelongFeedId());
				itemAdapter->setName(result.value(type)[i]->getName());
				itemAdapter->setDialogID(result.value(type)[i]->getDialogID());
				itemAdapter->setUserId(result.value(type)[i]->getUserId());
				itemAdapter->setAvatarUrl(result.value(type)[i]->getAvatarUrl());
				itemAdapter->setAge(result.value(type)[i]->getAge());
				itemAdapter->setPhotoResID(result.value(type)[i]->getPhotoResID());
				itemAdapter->SetType(result.value(type)[i]->getType());
				itemAdapter->setIsForeceRefreshAvator(result.value(type)[i]->getIsForeceRefreshAvator());
				itemAdapter->setShowBelongStatus(result.value(type)[i]->getShowBelongStatus());
				itemAdapter->setBelongPhotoResID(result.value(type)[i]->getBelongPhotoResID());
				adatpterList.append(itemAdapter);
			}
			break;
		}
	}
	InitBottomPage(tagCount, allItemCount);
	if (adatpterList.size() > 0)
	{
		_listSearchModel->appendData(adatpterList);
	}
	this->show();
}
void tnsearcharea::onItemCreateFinished(const QModelIndex& index, int type)
{
	if (type == TNSearchAdapter::FriendItem)
	{
		TNSearchAdapter *adapter = (TNSearchAdapter*)index.data().toLongLong();
		if (adapter == NULL)
			return;
		if (adapter->getPhotoResID() == (":/Resources/toolWidget/defaultAvatar.png") || adapter->getIsForeceRefreshAvator())
		{
			DownLoadAvatarForSearch(adapter->getDialogID(), adapter->getAvatarUrl());
		}
	}
}
void tnsearcharea::DownLoadAvatarForSearch(QString feedId, QString url)
{
	qDebug() << "[tnsearcharea] DownLoadAvatarForSearch, url: " << url << " feedId:" << feedId;
	bool isOrigin = false;
	if (feedId.startsWith("gc_"))
		isOrigin = true;
	TNNetAvatarDown::GetInstance()->DownLoadFeedAvatar(feedId, url, TNHttpCloudApi::GetInstance()->GetCloudStoken(m_pluginParam), this, isOrigin);
}
void tnsearcharea::onAvatarDownLoadFinish(bool success, QString url, QString feedId)
{
	_listSearchModel->UpdateItemAvatar(url, feedId);
}
void tnsearcharea::showDialog()
{
	if (_SearchlistWidgt != nullptr && _listSearchModel != nullptr)
		_SearchlistWidgt->scrollTo(_listSearchModel->index(0, 0));
	this->show();
}
