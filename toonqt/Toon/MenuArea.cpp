#include <QStyle>
#include <QPointer>
#include <QStyleOption>
#include <QDebug>

#include "XmlSingleton.h"
#include "MenuArea.h"
#include "TNAvatarChoice.h"
#include "TNDataCache.h"
#include "TNDataControlServer.h"
#include "TNPathUtil.h"
#include "tnnotifycenter.h"
#include "TNIMCoreClient.h"
#include "CTNDBAPI.h"

#include <QApplication>
#include <QDesktopWidget>
#include "TNZoomFactor.h"
MenuArea::MenuArea(TNPluginParamPtr pluginParam, QWidget *parent)
	: QWidget(parent)
	, _pluginParam(pluginParam)
	, _choiceWidget(nullptr)
	, _avatarButton(nullptr)
	, _lastestSelectedFeed(AVATAR_ALL_FEED)
	, _isUnReadNotify(false)
{
	Init();
	_isShowunReadMap.clear();
    this->setFocusPolicy(Qt::ClickFocus);
}

void MenuArea::Init()
{
#ifdef Q_OS_WIN
	setMaximumHeight(TNZoomFactor::GetMaxFrameHeight());
#endif
	signal_clickMapper = new QSignalMapper(this);
	signal_doubleClickMapper = new QSignalMapper(this);
	topLayout = new QVBoxLayout();
	centerLayout = new QVBoxLayout();
	bottomLayout = new QVBoxLayout();

	QVBoxLayout *mainlayout = new QVBoxLayout();

	mainlayout->addLayout(topLayout);
	mainlayout->addLayout(centerLayout);
	mainlayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
	mainlayout->addLayout(bottomLayout);

    topLayout->setContentsMargins(0, 38, 0, 12);
	topLayout->setSpacing(0);
	centerLayout->setContentsMargins(0, 0, 0, 0);
	centerLayout->setSpacing(0);
    bottomLayout->setContentsMargins(0, 0, 0, 0);
	bottomLayout->setSpacing(0);
	this->translateLanguage();
	this->setObjectName("MenuArea");
	mainlayout->setContentsMargins(0, 0, 0, 0);
	setLayout(mainlayout);

	connect(signal_clickMapper, SIGNAL(mapped(QString)), this, SLOT(turnPage(QString)));
	connect(signal_doubleClickMapper, SIGNAL(mapped(QString)), this, SLOT(doubleClickPage(QString)));

	_choiceWidget = new TNAvatarChoice(_pluginParam, this);
	_choiceWidget->raise();
	_choiceWidget->hide();
	connect(_choiceWidget, SIGNAL(ItemClicked(const QString &, const QString&, const QString&, const QString&)), this, SLOT(ChoiceClickedSlot(const QString &, const QString &, const QString&, const QString&)));
	TNDataCache::GetInstance()->InstallCatcheFeedUpdateNotify(this);
	TNNotifyCenter::instance()->connectNotifyRefreshAddressList(this);
    connect(TNNotifyCenter::instance(), SIGNAL(signalShowHomePageButton()), this, SLOT(slotShowHomePageButton()));
}

void MenuArea::paintEvent(QPaintEvent * event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void MenuArea::LoadMenuLibrary(PluginExportBase *tempMenu, int Dimension)
{
	Q_ASSERT(topLayout);
	Q_ASSERT(centerLayout);
	Q_ASSERT(bottomLayout);
	Q_ASSERT(signal_clickMapper);
	Q_ASSERT(signal_doubleClickMapper);
	Q_ASSERT(tempMenu);
	
	if (tempMenu->GetID() == MENU_AVATAR_ID)
		_avatarButton = tempMenu->GetMenu();
	button_list.append(tempMenu->GetMenu());
	connect(tempMenu->GetMenu(), SIGNAL(clicked()), signal_clickMapper, SLOT(map()));
	connect(tempMenu->GetMenu(), SIGNAL(doubleClicked()), signal_doubleClickMapper, SLOT(map()));
	signal_clickMapper->setMapping(tempMenu->GetMenu(), QString::number(tempMenu->GetID(), 10));
	signal_doubleClickMapper->setMapping(tempMenu->GetMenu(), QString::number(tempMenu->GetID(), 10));
	switch (Dimension)
	{
		case DIMENSION_MENUTOP:
			topLayout->addWidget(tempMenu->GetMenu(), 1, Qt::AlignHCenter);
			break;
		case DIMENSION_MENUCENTER:
			centerLayout->addWidget(tempMenu->GetMenu(), 1, Qt::AlignHCenter);
			break;
		case DIMENSION_MENUBOTTOM:
			bottomLayout->addWidget(tempMenu->GetMenu(), 1, Qt::AlignHCenter);
			break;
		default:
			break;
	}
}

void MenuArea::translateLanguage()
{
	/*version_title->setText(("title") + QString("9.2"));
	skin_button->setToolTip(("change skin"));
	main_menu_button->setToolTip(("main menu"));
	min_button->setToolTip(("minimize"));
	feedback_button->setToolTip(("feedback"));
	close_button->setToolTip(("close"));

	button_list.at(0)->setText(("power"));
	button_list.at(1)->setText(("mummy"));
	button_list.at(2)->setText(("repair"));
	button_list.at(3)->setText(("clear"));
	button_list.at(4)->setText(("optimize"));
	button_list.at(5)->setText(("expert"));
	button_list.at(6)->setText(("hole"));
	button_list.at(7)->setText(("software"));

	safe_360_label->setText(("360"));
	safe_label->setText(("safe"));*/
}

void MenuArea::slotTurnPage(int pageIndex)
{
	for (int i = 0; i < button_list.count(); i++)
	{
		QPointer<MenuAreaBase> tool_button = button_list.at(i);
		if (pageIndex == tool_button->GetID())
		{
			tool_button->setMousePress(true);
			tool_button->setChecked(true);
		}
		else
		{
			tool_button->setMousePress(false);
			tool_button->setChecked(false);
		}
	}

	emit turnPage(pageIndex);
}
void MenuArea::doubleClickPage(QString current_page)
{
	/*
	目前双击操作暂时取消， 后面100%会使用。 因此代码不删除
	*/
	//bool ok;
	//emit doubleClickPage(current_page.toInt(&ok, 10));
}
void MenuArea::turnPage(QString current_page)
{
	bool ok;  
	int current_index = current_page.toInt(&ok, 10);

	for(int i=0; i<button_list.count(); i++)
	{
		QPointer<MenuAreaBase> tool_button = button_list.at(i);
		if (current_index == tool_button->GetID())
        {
            if (current_index == MENU_AVATAR_ID)
                ShowAvatarChoiceWidget(true);
            if (current_index != MENU_AVATAR_ID)
                tool_button->setChecked(true);
        }
		else
		{
            if (current_index != MENU_AVATAR_ID)
                tool_button->setChecked(false);
		}
	}

    _pluginParam->_currentSelectPage = current_index;
    emit turnPage(current_index);
}
void MenuArea::mouseDoubleClickEvent(QMouseEvent*)
{
	emit maxMinSet(true);
}
void MenuArea::unReadCountSlot(const QString &feedID, int ,int type)
{
	if (type == MSG_BIZ_GROUPNOTIFY || type == MSG_BIZ_NOTIFY)
	{
		if ((feedID == "" || feedID != AVATAR_ALL_FEED) && TNDataCache::GetInstance()->GetCurrentMyFeed() != AVATAR_ALL_FEED)
		{
			_isUnReadNotify = true;
			_avatarButton->showRedPoint(true, MENU_SHOW_TYPE_AVATAR);
		}
	}
	else
	{
		if (feedID != TNDataCache::GetInstance()->GetCurrentMyFeed() && feedID != AVATAR_ALL_FEED 
			&& TNDataCache::GetInstance()->GetCurrentMyFeed() != AVATAR_ALL_FEED 
			&& _avatarButton != nullptr && feedID != "")
		{
			_isShowunReadMap.insert(feedID, true);
			_avatarButton->showRedPoint(true, MENU_SHOW_TYPE_AVATAR);
		}
	}
}
bool MenuArea::isShowUnReadStatus(const QString &feedId)
{
	bool ret = false;
	foreach(QString feed , _isShowunReadMap.keys())
	{
		if (feed == feedId && _isShowunReadMap[feed] == true)
		{
			ret = true;
			break;
		}
	}
	return ret;
}
bool MenuArea::loadData()
{
	bool result = false;
	QList<TNAvatarChoiceAdapter *> stuffList;
	TableBaseVec myStuffTableBaseVec;
	QString currentFeed = TNDataCache::GetInstance()->GetCurrentMyFeed();
	TNAvatarChoiceAdapter *adapter = new TNAvatarChoiceAdapter();
	adapter->setName(AVATAR_ALL_NAME);
	adapter->setAvatarUrl(QStringLiteral(""));
	adapter->setDialogID(AVATAR_ALL_FEED);
    adapter->setPhotoResID(QStringLiteral(":/sysButton/Resources/img/sysButton/allDefaultAvatar.png"));
	adapter->setIsForeceRefreshAvator(false);
	if (currentFeed == AVATAR_ALL_FEED)
		adapter->setIsCurrentCard(true);
	adapter->SetUnreadCount(_isUnReadNotify?1:0); 
	stuffList.append(adapter);

	QList<st_FeedPtr> myAllStuff;
	TNDataCache::GetInstance()->UpdateMyStuffCache();
	TNDataCache::GetInstance()->getMyStuff(myAllStuff);
	for (st_FeedPtr feed : myAllStuff)
	{
		TNAvatarChoiceAdapter *adapter = new TNAvatarChoiceAdapter();
		adapter->setName(feed->GetTitle());
		adapter->setAvatarUrl(feed->GetAvatarID());
		adapter->setDialogID(feed->GetFeedID());
		
		QString avatarFileName = TNPathUtil::getFeedAvatarPath(feed->GetFeedID());
		bool isForceRefreshAvator = false;
		if (!QFile::exists(avatarFileName))
		{
			isForceRefreshAvator = true;
			avatarFileName = QStringLiteral(":/Resources/toolWidget/defaultAvatar.png");
		}
		adapter->setPhotoResID(avatarFileName);
		adapter->setIsForeceRefreshAvator(isForceRefreshAvator);
		if (currentFeed == feed->GetFeedID())
			adapter->setIsCurrentCard(true);
		
		int unRead = TNIMCoreClient::GetDBChat()->getUnreadCount(feed->GetFeedID().toStdString().c_str(),""); //不以数据库消息为基础
		if (unRead == 0)
		{
			for (QMap<QString, bool>::iterator it = _isShowunReadMap.begin(); it != _isShowunReadMap.end(); it++)
			{
				if (it.key() == feed->GetFeedID())
				{
					_isShowunReadMap.erase(it);
					break;
				}
			}
		}

		if (currentFeed != feed->GetFeedID() && unRead>0) /* if current feed is known, ignore unread*/
		{
			if (isShowUnReadStatus(feed->GetFeedID()) && currentFeed != AVATAR_ALL_FEED)
				adapter->SetUnreadCount(unRead);
		}
		stuffList.append(adapter);
	}
	if (stuffList.size() > 1 && _choiceWidget != NULL)
	{
		InitAvatarChoicePage(stuffList.size());
		_choiceWidget->setChoiceResult(stuffList);
		result = true;
	}
	return result;
}
void MenuArea::InitAvatarChoicePage(int itemCount)
{
	if (_choiceWidget != nullptr)
	{
		QPoint win = mapToGlobal(this->pos());
        _choiceWidget->move(win.x() + MENU_AREA_WIDTH - 9, win.y() + 40);
		_choiceWidget->setFixedWidth(LIST_AVATARCHOICE_WIDTH + 5);
        _choiceWidget->setFixedHeight(LIST_AVATARCHOICE_HEIGHT * (itemCount>AVATAR_SHOW_COUNT ? AVATAR_SHOW_COUNT : itemCount) + 14);
	}
}
void MenuArea::ShowAvatarChoiceWidget(bool isShow)
{
	if (_choiceWidget != nullptr && loadData())
		_choiceWidget->showWidget(isShow);
}
void MenuArea::ChoiceClickedSlot(const QString & type, const QString &feedId, const QString& res, const QString&avatar)
{
	if (type.isEmpty() || feedId.isEmpty() || res.isEmpty() || _lastestSelectedFeed == feedId)
		return;
	if (feedId == AVATAR_ALL_FEED)
	{
		_isShowunReadMap.clear();
	}
	qInfo() << "[Toon][MenuArea]ChoiceClickedSlot Choice card:" << feedId;
	if (_avatarButton != nullptr)
	{
		_lastestSelectedFeed = feedId;
		_avatarButton->setFeedType(feedId);
		_avatarButton->setAvatarPath(feedId == AVATAR_ALL_FEED ? QStringLiteral(":/Resources/default_feed_avatar.png") : res);
		if (_isUnReadNotify)
			_isUnReadNotify = feedId == AVATAR_ALL_FEED ? false : true;
		/*
		1. 当前_isShowunReadMap的size 为1 ，且切换的名片就是此名片， Avatar 不显示红点,且删除此feed。
		2. 当前名片在_isShowunReadMap 中， 且其他名片有未读消息（_isShowunReadMap.size()>1）,avatar 显示红点，
		3. 当当前名片为全部时， _isShowunReadMap 重新初始化。
		*/
		bool isShow = false;
		if (_isUnReadNotify ||_isShowunReadMap.size() > 1 || (!isShowUnReadStatus(feedId) && _isShowunReadMap.size()>0))
		{
			isShow = true;
		}
		else if (isShowUnReadStatus(feedId))
		{
			for (QMap<QString, bool>::iterator it = _isShowunReadMap.begin(); it != _isShowunReadMap.end(); it++)
			{
				if (it.key() == feedId)
				{
					_isShowunReadMap.erase(it);
					break;
				}
			}
		}
		_avatarButton->showRedPoint(isShow, MENU_SHOW_TYPE_AVATAR);
		TNDataCache::GetInstance()->SwitchCurrentMyFeed(feedId);
		TNNotifyCenter::instance()->postNotifyCurrentFeedChanged(feedId);
	}
}
void MenuArea::feedCardUpdateFromCatche(const QString &feedId,
										const QString &avatarId,
										const QString &name,
										const QString &subName,
										const QString &userId,
										const QString &namePy,
										int sourceType)
{
	Q_UNUSED(avatarId);
	Q_UNUSED(name);
	Q_UNUSED(subName);
	Q_UNUSED(userId);
	Q_UNUSED(namePy);

	qInfo() << "[Toon][MenuArea]feedCardUpdateFromCatche :" << feedId << " sourceType:" << sourceType;
	if (sourceType == TN::UpdateSource::Mine){
		QString file = TNPathUtil::getFeedAvatarPath(feedId);
		if (_avatarButton != nullptr && _lastestSelectedFeed != AVATAR_ALL_FEED &&feedId == _lastestSelectedFeed)
		{
			if (_choiceWidget != nullptr &&!_choiceWidget->isHidden())
			{
				_choiceWidget->hide();
			}
			_avatarButton->setAvatarPath(file);
		}
	}
}
void MenuArea::on_notifyRefresh(int type, QList<UINotifyData> data)
{
	if (type == RefreshTypeUI_MyCard)
	{
		//如果选中的是当前名片， 且被删除会执行这里，自动选中所有名片
		qInfo() << "[Toon][MenuArea] on_notifyRefresh";
		if (_lastestSelectedFeed != AVATAR_ALL_FEED && !TNDataCache::GetInstance()->IsInMyStuffFromDB(_lastestSelectedFeed))
		{
			if (_avatarButton != nullptr)
			{
				if (_choiceWidget != nullptr &&!_choiceWidget->isHidden())
				{
					_choiceWidget->hide();
				}
				ChoiceClickedSlot(AVATAR_ALL_NAME, AVATAR_ALL_FEED, QStringLiteral(":/Resources/default_feed_avatar.png"), QStringLiteral(":/Resources/default_feed_avatar.png"));
			}
		}
	}
}

void MenuArea::slotShowHomePageButton()
{
    qInfo()<<"[Toon][MenuArea]slotShowHomePageButton------------------------";
    for (int i = 0; i < button_list.count(); i++)
    {
        if (button_list[i]->GetID() == MENU_HOMEPAGE_ID)
        {
            button_list[i]->show();
        }
    }
}
