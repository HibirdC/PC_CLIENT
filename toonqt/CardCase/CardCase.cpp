#include <memory>

#include "CardCase.h"
#include "TNNewFriendUtil.h"
#include "TNIMCoreClient.h"
#include "tnnotifycenter.h"
#include "TNToonCommandManager.h"
#include "ToonCommand/TNChooseCardCommand.h"

CardCase::CardCase(TNPluginParamPtr pluginParam, QWidget *parent)
:PluginExportBase(pluginParam, parent)
, _ID(MENU_CARDCASE_ID)
{
	_CardCaseMenuArea = new MenuAreaBase(_ID, (""), MENU_SHOW_TYPE_CARDCASE);
	_CardCaseMenuArea->setText(QStringLiteral(""));
	_CardCaseMenuArea->setObjectName("Menu_CardCase");
    _CardCaseMenuArea->setToolTip(("通讯录"));
	_CardCaseMenuArea->setCheckable(true);
    TNNotifyCenter::instance()->connectNotifyRefreshAddressList(this);
    TNNotifyCenter::instance()->connectNotifyRefresh(this);
    TNNotifyCenter::instance()->connectNotifyRefreshSession(this);

	_CardCaseListArea = new CardCaseListArea(_ID, pluginParam, this);
	_CardCaseDetailsArea = new CardCaseDetailsArea(_ID, pluginParam, this);

    int unReadCount = TNNewFriendUtil::getUnReadCount();
    _CardCaseMenuArea->setMessageNumber(unReadCount);
    connect(_CardCaseListArea, SIGNAL(messageNumberChanged(int)),
        _CardCaseMenuArea, SLOT(setMessageNumber(int)));
    connect(_CardCaseListArea, SIGNAL(clickedNewFriendItem()), _CardCaseDetailsArea,
        SLOT(slotShowNewFriendNotice()));
    connect(_CardCaseListArea, SIGNAL(updateNewFriendPage()), SLOT(slotUpdateNewFriendPage()));
	connect(_CardCaseListArea, SIGNAL(ListFriendToDetailEvent(const QModelIndex &)), _CardCaseDetailsArea,
		SLOT(OnListAreaClickedSlot(const QModelIndex &)));
	connect(_CardCaseListArea, SIGNAL(ListColleagueToDetailEvent(const QModelIndex &)), _CardCaseDetailsArea,
		SLOT(OnColleagueListAreaSlot(const QModelIndex &)));
	connect(_CardCaseListArea, SIGNAL(ListGroupToDetailEvent(const QModelIndex &)), _CardCaseDetailsArea,
		SLOT(OnGroupListAreaSlot(const QModelIndex &)));
	connect(_CardCaseListArea, SIGNAL(ListGroupChatToDetailEvent(const QModelIndex &)), _CardCaseDetailsArea,
		SLOT(OnGroupChatListAreaSlot(const QModelIndex &)));

	//For MODIFY
	connect(_CardCaseListArea, SIGNAL(ListGroupChatModifyEvent(const QModelIndex &)), _CardCaseDetailsArea,
        SLOT(slotModifiedGroupChatInfos(const QModelIndex &)));

	connect(_CardCaseListArea, SIGNAL(CloseDetailPageEvent(const QString &, const QString&)), _CardCaseDetailsArea, SLOT(CloseDetailPage(const QString &, const QString&)));
}

CardCase::~CardCase()
{

}


QPointer<MenuAreaBase> CardCase::GetMenu()
{
	return _CardCaseMenuArea;
}

QPointer<ListAreaBase> CardCase::GetList()
{
	return _CardCaseListArea;
}

QPointer<DetailsAreaBase> CardCase::GetDetails()
{
	return _CardCaseDetailsArea;
}

int CardCase::GetID()
{
	return _ID;
}

void CardCase::registerToonCommand()
{
	TNToonCommandManager::instance()->registerToonCommand(QString("card/chooseCard"), TNAbstractToonCommandPtr(new TNChooseCardCommand()));
}

void CardCase::on_notifyRefresh(int type, QList<UINotifyData> dataListo)
{
    if (type == RefreshTypeUI_Newfriend)
    {
        int unReadCount = TNNewFriendUtil::getUnReadCount();
        _CardCaseMenuArea->setMessageNumber(unReadCount);
    }
}

void CardCase::slotUpdateNewFriendPage()
{
    CardCaseDetailsArea* cardCaseDetail = static_cast<CardCaseDetailsArea*>(_CardCaseDetailsArea.data());
    if (cardCaseDetail == nullptr)
        return;

    // 只要新学员页为当前页（不一定是激活页）就及时刷新新学员列表
    if (cardCaseDetail->getCurrentPage() == 0)
    {
        cardCaseDetail->slotShowNewFriendNotice();
    }

    CardCaseListArea* cardCaseList = static_cast<CardCaseListArea*>(_CardCaseListArea.data());
    if (cardCaseList == nullptr)
        return;

    // 只有当新学员页为当前页且程序没有睡眠时才刷新新学员未读社区数目
    if ((cardCaseDetail->isRunning()) && (_CardCaseMenuArea->isChecked()) && (cardCaseDetail->getCurrentPage() == 0))
    {
        qDebug()<<"I am no sleeping";
        TNNewFriendUtil::clearUnReadStatus();
        cardCaseList->updateNewFriendUnReadCount();
        _CardCaseMenuArea->setMessageNumber(0);
    }
}

CardCase* getMenu(TNPluginParamPtr pluginParam, QWidget *parent)
{
	return new CardCase(pluginParam, parent);
}
