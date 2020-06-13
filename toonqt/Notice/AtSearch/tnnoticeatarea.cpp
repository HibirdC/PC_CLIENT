#include "tnnoticeatarea.h"
#include "TNDataControlServer.h"
#include "TNIMCoreClient.h"
#include "TNPathUtil.h"
#include "TNDebugLog.h"
#include "tnnotifycenter.h"
#include "TNDataCache.h"
#include "tnnotifycenter.h"
#include "TNHttpCloudApi.h"
#include "tnatlistitemwidget.h"
#include "TNNetAvatarDown.h"

#include <QtMath>
#include <QToolButton>
#include <QJsonObject>
#include <qlayout.h>

tnnoticeatarea::tnnoticeatarea(TNPluginParamPtr param, QWidget *parent)
: QWidget(parent), m_pluginParam(param)
	,_parentHeight(0)
	, _parentWidth(0)
	, _needSelectedItem(0)
	, _WidgeWidth(0)
	, _WidgeHeight(0)
	, _SelectedResult(nullptr)
{
	ui.setupUi(this);

	setWindowFlags(Qt::FramelessWindowHint |Qt::NoDropShadowWindowHint | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground, true);
	setAttribute(Qt::WA_DeleteOnClose);

	_SearchlistWidgt = new QTableView(this);
	_SearchlistWidgt->setObjectName("AtSearchlistWidgt");
	_SearchlistWidgt->setShowGrid(false);
	_SearchlistWidgt->setMouseTracking(true);
	_SearchlistWidgt->setEditTriggers(QAbstractItemView::AllEditTriggers);
	_SearchlistWidgt->setSelectionMode(QAbstractItemView::SingleSelection);
	_SearchlistWidgt->setSelectionBehavior(QAbstractItemView::SelectItems);
	//默认选中第一个Item
	_SearchlistWidgt->selectRow(0);
	_SearchlistWidgt->setFocusPolicy(Qt::NoFocus);
	_SearchDelegate = new TNATSearchListItemDelegate(_SearchlistWidgt);
	_SearchDelegate->setParentWidget(this);
	_SearchlistWidgt->setItemDelegate(_SearchDelegate);
	_listSearchModel = new TNATSearchListModel(this);
	_listSearchModel->setTableView(_SearchlistWidgt);
	_SearchlistWidgt->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
	_SearchlistWidgt->setModel(_listSearchModel);
	_SearchlistWidgt->verticalHeader()->setDefaultSectionSize(LIST_AT_HEIGHT); 
	_SearchlistWidgt->horizontalHeader()->setDefaultSectionSize(LIST_AT_WIDTH);
	_SearchlistWidgt->horizontalHeader()->setVisible(false);// 水平不可见
	_SearchlistWidgt->verticalHeader()->setVisible(false);// 垂直不可见

	connect(_SearchlistWidgt, SIGNAL(clicked(const QModelIndex &)), this, SLOT(OnListAreaClickedSlot(const QModelIndex &)));
	connect(_SearchDelegate, SIGNAL(createWidgetFinished(const QModelIndex&)), this, SLOT(onItemCreateFinished(const QModelIndex&)), Qt::QueuedConnection);


	QVBoxLayout *main_layout = new QVBoxLayout(this);
	main_layout->addWidget(_SearchlistWidgt);
	main_layout->setSpacing(0);
	main_layout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(main_layout);
}

tnnoticeatarea::~tnnoticeatarea()
{

}
void tnnoticeatarea::setSearchResult(QList<TNATSearchAdapter*> result)
{
	_SearchResult = result;
	_listSearchModel->clearData();
	QList<TNATSearchAdapter*> adatpterList;
	for (TNATSearchAdapter *tempAdapter : result)
	{
		adatpterList.append(tempAdapter);
	}
	if (adatpterList.size() > 0)
	{
		_listSearchModel->appendData(adatpterList);
	}
}
void tnnoticeatarea::OnListAreaClickedSlot(const QModelIndex & index)
{
	TNATSearchAdapter *adapter = (TNATSearchAdapter*)index.data().toLongLong();

	if ((adapter == NULL))
		return;
	for (TNATSearchAdapter *adapterInResult : _SearchResult)
	{
		if (adapterInResult->getDialogID() == adapter->getDialogID())
		{
			_SelectedResult = adapterInResult;
			break;
		}
	}
	emit ItemClicked(_SelectedResult->getName(), _SelectedResult->getDialogID(), _SelectedResult->getNickName());
}
void tnnoticeatarea::onItemCreateFinished(const QModelIndex& index)
{
	TNATSearchAdapter *adapter = (TNATSearchAdapter*)index.data().toLongLong();
	if (adapter == NULL)
		return;
	if (index.row() == _needSelectedItem)
	{
		/*
		注意;如果需要修改默认选中项，必须等Item创建完成
		*/
		setSelected(true, _needSelectedItem);
	}
	if (adapter->getPhotoResID() == (":/Resources/toolWidget/defaultAvatar.png") || adapter->getIsForeceRefreshAvator())
	{
		DownLoadAvatarForNoticeAt(adapter->getDialogID(), adapter->getAvatarUrl());
	}
}
void tnnoticeatarea::DownLoadAvatarForNoticeAt(QString feedId, QString url)
{
	qDebug() << "[tnnoticeatarea] DownLoadAvatarForNoticeAt, url: " << url << " feedId:" << feedId;
	TNNetAvatarDown::GetInstance()->DownLoadFeedAvatar(feedId, url, TNHttpCloudApi::GetInstance()->GetCloudStoken(m_pluginParam), this);
}
void tnnoticeatarea::onAvatarDownLoadFinish(bool success, QString url, QString feedId)
{
	_listSearchModel->UpdateItemAvatar(url, feedId);
}
QModelIndex tnnoticeatarea::getSelectedModelIndex()
{
	int count = _listSearchModel->rowCount();
	for (int i = 0; i<count; i++){
		QModelIndex index = _listSearchModel->index(i, 0);
		TNATListItemWidget* itemWidget = static_cast<TNATListItemWidget*>
			(_SearchlistWidgt->indexWidget(index));
		if (itemWidget != NULL){
			if (itemWidget->getSelected())
				return index;
		}
	}
	return _listSearchModel->index(0, 0);
}

void tnnoticeatarea::upSelection()
{
	int count = _listSearchModel->rowCount();
	if (count == 0){
		return;
	}
	QModelIndex index = getSelectedModelIndex();
	if (index.row() > 0)
	{
		setSelected(false, index.row());
		setSelected(true,index.row()-1);
	}
}

void tnnoticeatarea::downSelection()
{
	int count = _listSearchModel->rowCount();
	if (count == 0){
		return;
	}
	QModelIndex index = getSelectedModelIndex();
	if (index.row() >= 0 && index.row()<count-1)
	{
		setSelected(false, index.row());
		setSelected(true,index.row() + 1);
	}
}
void tnnoticeatarea::enterKey()
{
	int count = _listSearchModel->rowCount();
	if (count == 0){
		return;
	}
	QModelIndex index = getSelectedModelIndex();
	if (index.row() >= 0)
		emit _SearchlistWidgt->clicked(index.sibling(index.row(), index.column()));
}
void tnnoticeatarea::setSelected(bool select, int i)
{
	QModelIndex index = _listSearchModel->index(i, 0);
	TNATListItemWidget* itemWidget = static_cast<TNATListItemWidget*>
		(_SearchlistWidgt->indexWidget(index));
	if (itemWidget != NULL){
		if (select)
			_SearchlistWidgt->scrollTo(_listSearchModel->index(i, 0));
		itemWidget->setSelected(select);
	}
	else
	{
		_SearchlistWidgt->scrollTo(_listSearchModel->index(i+1,0));
		_needSelectedItem = i;
	}
}
void tnnoticeatarea::ShowDialog()
{
	if (_SearchlistWidgt != nullptr && _listSearchModel != nullptr)
		_SearchlistWidgt->scrollTo(_listSearchModel->index(0, 0));
	show();
}