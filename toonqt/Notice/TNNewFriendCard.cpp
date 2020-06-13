#include "TNNewFriendCard.h"
#include "ui_TNNewFriendCard.h"

#include "TNUtil.h"
#include "TNDbUtil.h"
#include "TNPathUtil.h"
#include "TNUserDataHelper.h"
#include "TNDataControlServer.h"
#include "TNMessageListAdapter.h"
#include "TNSimpleBrowser.h"
#include "TNMessageBox.h"
#include "tncommondealavator.h"
#include "TNWebEnginePage.h"
#include "TNNetAvatarDown.h"
#include "frames/TNFrameViewer.h"

#include <QPainter>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonDocument>

TNNewFriendCard::TNNewFriendCard(TNPluginParamPtr param, const st_NoticeInfo &aNotice, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::TNNewFriendCard),
	m_pluginParam(param),
	m_noticeInfo(aNotice)
{
	ui->setupUi(this);

	ui->finishedMarkLabel->setText(QString::null);
	ui->finishedMarkLabel->setVisible(false); 

	ui->herNickNameLabel->setElideMode(Qt::ElideMiddle);
	ui->herSubTitleLabel->setElideMode(Qt::ElideMiddle);
	//ui->summeryLabel->setElideMode(Qt::ElideMiddle);
	//ui->textLabel->setElideMode(Qt::ElideMiddle);
	ui->resourceLabel->setElideMode(Qt::ElideMiddle);

	m_httpFriendRequest = std::make_shared<TNHttpFriendRequest>();
	m_httpNewCardRequest = std::make_shared<TNHttpNewCardRequest>();
	m_httpOrgCardRequest = std::make_shared<TNHttpOrgCardRequest>();

	m_groupRequestPtr = std::make_shared<TNHttpGroupRequest>();
		
	initialCard(aNotice);
}

TNNewFriendCard::~TNNewFriendCard()
{
	delete ui;
}

bool TNNewFriendCard::isSameNotice(const st_NoticeInfo &aNotice)  const
{
	return aNotice.bizId == m_noticeInfo.bizId;
}

void TNNewFriendCard::initialCard(const st_NoticeInfo &aNotice)
{
	// 时间区: 必须有
	ui->timeLabel->setText(TNUtil::handleTimeForDetailArea(aNotice.timestmp_s));

	// 标题区: 必须有
	ui->subCatalogLabel->setText(aNotice.subCatalog);

	// 头像区: 可能没有
	if (aNotice.headFlag == 0)
	{
		ui->avatarWidget->setMaximumHeight(0);
		ui->avatarWidget->hide();
	}
	if ((aNotice.headFlag == 1) || (aNotice.headFlag == 2))
	{// 显示左边头像
		ui->avatarWidget->show();
		if (aNotice.headFlag == 1)
		{
			ui->mineAvatarButton->hide();
		}

		QString herFeedId = aNotice.leftFeed;
		st_FeedPtr feedInfo;
		QString herSubTitle;
		QString herAvatarURL;
		TNUserDataHelper::GetInstance()->GetFeedInfo(herFeedId, feedInfo);
		if (feedInfo)
		{
			herSubTitle = feedInfo->GetSubTile();
			herAvatarURL = feedInfo->GetAvatarID();
		}

		ui->herAvatarButton->setText(QString::null);
		//ui->herAvatarButton->setIconSize(QSize(40, 40)); 
		ui->herAvatarButton->setCustType(TNCommonDealAvator::getCustomType(herFeedId));
		
		QString hereAvatarFileName;
		if (TNPathUtil::isDownloadedAvatarPhoto(herFeedId, hereAvatarFileName))
		{
			ui->herAvatarButton->setAvatorImagePath(hereAvatarFileName);
		}
		else
		{
            ui->herAvatarButton->setIcon(QIcon((":/Resources/toolWidget/defaultAvatar.png")));

            asynDownloadAvatar(herAvatarURL, herFeedId, hereAvatarFileName);
		}
		ui->herNickNameLabel->setText(aNotice.upFeedTitle);
		ui->herSubTitleLabel->setText(herSubTitle);

		if (isGroupAvatar(aNotice))
			connect(ui->herAvatarButton, SIGNAL(clicked()), this, SLOT(slotAccept()));
        else
            connect(ui->herAvatarButton, SIGNAL(clicked()), this, SLOT(slotShowHerFrame()));
	}

	if (aNotice.headFlag == 2)
	{// 显示右边头像
		QString mineFeedId = aNotice.rightFeed;
		st_FeedPtr mineFeedInfo;
		QString mineAvatarURL;
		TNUserDataHelper::GetInstance()->GetFeedInfo(mineFeedId, mineFeedInfo);
		if (mineFeedInfo)
		{
			mineAvatarURL = mineFeedInfo->GetAvatarID();
		}

		ui->mineAvatarButton->setText(QString::null);
		//ui->mineAvatarButton->setIconSize(QSize(40, 40));
		ui->mineAvatarButton->setCustType(TNCommonDealAvator::getCustomType(mineFeedId));

		QString mineAvatarFileName;
		if (TNPathUtil::isDownloadedAvatarPhoto(mineFeedId, mineAvatarFileName))
		{
			ui->mineAvatarButton->setAvatorImagePath(mineAvatarFileName);
		}
		else
		{
			ui->mineAvatarButton->setIcon(QIcon((":/Resources/toolWidget/defaultAvatar.png")));

            asynDownloadAvatar(mineAvatarURL, mineFeedId, mineAvatarFileName);
		}

        connect(ui->mineAvatarButton, SIGNAL(clicked()), this, SLOT(slotShowMineFrame()));
	}

	// 内容标题：可能没有
	if (aNotice.summary.isEmpty())
	{
		ui->summeryLabel->setMaximumHeight(0);
		ui->summeryLabel->hide();
	}
	else
	{
		ui->summeryLabel->show();
		ui->summeryLabel->setWordWrap(true);
		ui->summeryLabel->setText(aNotice.summary);
		ui->summeryLabel->adjustSize();
	}
	
	// 内容文本：可能没有, 内容分行显示
	if (aNotice.msgContent.isEmpty())
	{
		ui->textLabel->setMaximumHeight(0);
		ui->textLabel->hide();
	}
	else
	{
		ui->textLabel->show();
        QString text = aNotice.msgContent/*.simplified()*/.trimmed();
        //qDebug()<<"text="<<text;
        // 企业管理：text= "您发起的补签申请已审批通过\r\n\r\n缺勤原因：其他\r\n补签日期：2018-01-05\r\n补签类型：补签上午"
        // 社区消息：text= "第16期活动开奖啦，快来看看是哪位幸运的小伙伴~~\n\n听说智趣星球横空出世，\n\n话剧票大奖也随之又来了！！！\n\n快来看看吧~??????"
		ui->textLabel->setWordWrap(true);
		ui->textLabel->setText(text);
		ui->textLabel->adjustSize();
	}

	// 资源：可能没有
	if (aNotice.resource.isEmpty())
	{
		ui->resourceLabel->setMaximumHeight(0);
		ui->resourceLabel->hide();
	}
	else
	{
		ui->resourceLabel->show();
		ui->resourceLabel->setText(aNotice.resource);
	}	

	// 按钮区: 可能没有
	if (showCustomButton(aNotice))
	{// 原生的自定义按钮
		ui->buttonNameButton->hide();
		ui->acceptButton->setCursor(Qt::PointingHandCursor);
		ui->rejectButton->setCursor(Qt::PointingHandCursor);
		connect(ui->acceptButton, SIGNAL(clicked()), this, SLOT(slotAccept()));
		connect(ui->rejectButton, SIGNAL(clicked()), this, SLOT(slotReject()));
	}
	else if (showToonButton(aNotice))
	{// Toon的URL按钮
		ui->acceptButton->hide();
		ui->rejectButton->hide();
		ui->buttonNameButton->setCursor(Qt::PointingHandCursor);
		ui->buttonNameButton->setText(aNotice.buttonName);
		connect(ui->buttonNameButton, SIGNAL(clicked()), this, SLOT(slotShowUrl()));
	}
	else
	{
		ui->buttonWidget->setMaximumHeight(0);
		ui->buttonWidget->hide();
	}

	// “已完成”盖章戳
	if (showFinishedMarkLabel(aNotice))
	{
		ui->finishedMarkLabel->setObjectName("noticeFinished");
		//ui->finishedMarkLabel->setStyleSheet("border-image: url(:/Resources/toolWidget/NoticeFinished.png);");
		showMarkLabel();
	}

	// “已失效”盖章戳
	if (showExpiredMarkLabel(aNotice))
	{
		ui->finishedMarkLabel->setObjectName("noticeExpired");
		//ui->finishedMarkLabel->setStyleSheet("border-image: url(:/Resources/toolWidget/NoticeExpired.png);");
		showMarkLabel();
	}

	//this->adjustSize();
	this->resize(this->sizeHint());
}

void TNNewFriendCard::showMarkLabel()
{
	ui->horizontalLayout_8->removeWidget(ui->finishedMarkLabel);
	ui->finishedMarkLabel->raise();
	ui->finishedMarkLabel->setVisible(true);
	int x = getXPosition();
	int y = getYPosition();
	ui->finishedMarkLabel->setGeometry(x, y, 58, 64);
}

bool TNNewFriendCard::isGroupAvatar(const st_NoticeInfo &aNotice)
{
	 if ((aNotice.subNoticeType == SubCatalogType_JoinGroupSuc) && aNotice.leftFeed.startsWith("g_"))
		return true;
	 if ((aNotice.subNoticeType == SubCatalogType_JoinGroup) && aNotice.leftFeed.startsWith("g_"))
		return true;

	return false;
}

bool TNNewFriendCard::showCustomButton(const st_NoticeInfo &aNotice)
{
    if (aNotice.actionType == Action_APP)
        return false;

	// 当subcatalogId=1,3,4,5,6时显示，这些都是关系建立，固定显示接受和拒绝，和actiontype无关
	if ((aNotice.subNoticeType == SubCatalogType_ApplyJoinGroup) && !aNotice.bIsFinished)
		return true;
	if ((aNotice.subNoticeType == SubCatalogType_ChangeCard) && !aNotice.bIsFinished)
		return true;
	if ((aNotice.subNoticeType == SubCatalogType_PhoneChangeCard) && !aNotice.bIsFinished)
		return true;
	if ((aNotice.subNoticeType == SubCatalogType_GrantCard) && !aNotice.bIsFinished)
		return true;
	if ((aNotice.subNoticeType == SubCatalogType_CompandyAttorm) && !aNotice.bIsFinished)
		return true;
	
	return false;
}

bool TNNewFriendCard::showToonButton(const st_NoticeInfo &aNotice)
{
	if (!aNotice.buttonName.isEmpty())
		return true;

	return false;
}

bool TNNewFriendCard::showFinishedMarkLabel(const st_NoticeInfo &aNotice)
{
	return aNotice.bIsFinished;
}

bool TNNewFriendCard::showExpiredMarkLabel(const st_NoticeInfo &aNotice)
{
    if (aNotice.bIsFinished)
        return false;

    if (aNotice.actionType == Action_APP)
        return false;

    // 对关系建立，不处理失效性
    if (showCustomButton(aNotice))
        return false;

    // 对社区消息-邀请加入，不处理失效性
    if ((aNotice.noticeType == CATALOG_GROUP_INVITEJOIN) && (aNotice.subNoticeType == SubCatalogType_JoinGroupSuc))
        return false;

    qlonglong currTime_s = QDateTime::currentMSecsSinceEpoch();
    if (QString::number(qlonglong(aNotice.expireTime_s)).length()<11) // 服务器返回的过期时间单位为秒
        currTime_s = currTime_s*0.001;
    if ((aNotice.expireTime_s > 0) && (aNotice.expireTime_s < currTime_s))
        return true;

    return false;
}

int TNNewFriendCard::getXPosition() const
{
	return ui->mainWidget->geometry().right() - 140;
}

int TNNewFriendCard::getYPosition() const
{
	switch (m_noticeInfo.headFlag)
	{
	case 0:
		return 40;

	default:
		break;
	}

	return 60;
}

void TNNewFriendCard::slotAccept()
{
	switch (m_noticeInfo.subNoticeType)
	{
	case SubCatalogType_GrantCard:
		acceptNewCard();
		break;

	case SubCatalogType_CompandyAttorm:
		acceptOrgCard();
		break;

	case SubCatalogType_JoinGroup:
	case SubCatalogType_JoinGroupSuc:
		if (alreadyJoinGroup())
		{
			QString groupId = m_noticeInfo.leftFeed;
            QString belongFeedId = m_noticeInfo.rightFeed;
            viewGroupInfo(groupId, belongFeedId);
		}
		else
		{
			inviteJoinGroup();
		}
		break;

	case SubCatalogType_ChangeCard:
		acceptNewFriend();
		break;

	case SubCatalogType_ApplyJoinGroup:
		acceptJoinGroup();
		break;

	default:
		break;
	}
}

void TNNewFriendCard::slotReject()
{
	switch (m_noticeInfo.subNoticeType)
	{
	case SubCatalogType_GrantCard:
		rejectNewCard();
		break; 

	case SubCatalogType_CompandyAttorm:
		rejectOrgCard();
		break;

	case SubCatalogType_JoinGroup:
		Q_ASSERT(!"never come to here");
		break;

	case SubCatalogType_ChangeCard:
		rejectNewFriend();
		break;

	case SubCatalogType_ApplyJoinGroup:
		rejectJoinGroup();
		break;

	default:
		break;
	}
}

void TNNewFriendCard::acceptNewCard()
{
	handleNewCard(true);
}

void TNNewFriendCard::rejectNewCard()
{
	handleNewCard(false);
}

void TNNewFriendCard::handleExchangeCard(bool accept)
{
    QTime time;
    time.start();
    qInfo()<<"[Notice][TNNewFriendCard]handleExchangeCard begin... accept="<<accept;
    if (m_noticeInfo.leftFeed.isEmpty())
    {
        qInfo()<<"[Notice][TNNewFriendCard]handleExchangeCard-m_noticeInfo.leftFeed.isEmpty";
        return;
    }

    QString friendUserId;
    st_FeedPtr friendFeedInfo;
    TNUserDataHelper::GetInstance()->GetFeedInfo(m_noticeInfo.leftFeed, friendFeedInfo);
    if (friendFeedInfo)
        friendUserId = friendFeedInfo->GetUserID();
    if (friendUserId.isEmpty())
    {
        qInfo()<<"[Notice][TNNewFriendCard]handleExchangeCard-friendUserId is null. feedId="<<m_noticeInfo.leftFeed;
        return;
    }

    m_httpFriendRequest->SetFriendInfo(m_noticeInfo.rightFeed, m_noticeInfo.leftFeed, m_noticeInfo.upFeedTitle, friendUserId, m_noticeInfo.downFeedTitle);

    auto acceptNewFriendFinished = [&](bool success, QString retFeedId, QJsonObject jsonObject)
    {
        if (success)
        {
            QString debugText = QString(QJsonDocument(jsonObject).toJson());
            qInfo()<<"[Notice][TNNewFriendCard]handleExchangeCard-debugText="<<debugText;
            // 不再手动新建一个会话，把会话数据传递给会话列表区
            int retCode = jsonObject["meta"].toObject().value("code").toInt();
            if (retCode != 0)
            {
                QString message = jsonObject.value("meta").toObject().value("message").toString();
                TNMessageBox messageBox(this);
                messageBox.setMsg(message);
                messageBox.exec();
            }
        }
        else
        {
            TNMessageBox messageBox(QApplication::activeWindow());
            messageBox.setMsg(("操作失败，请检查您的网络状态"));
            messageBox.exec();
        }
    };

    m_httpFriendRequest->GetJson(acceptNewFriendFinished, m_pluginParam, accept);
    qInfo()<<"[Notice][TNNewFriendCard]handleExchangeCard end. Time="<<time.elapsed();
}

void TNNewFriendCard::handleNewCard(bool accept)
{
    QTime time;
    time.start();
    qInfo()<<"[Notice][TNNewFriendCard]handleNewCard begin... accept="<<accept;
	if (m_noticeInfo.leftFeed.isEmpty())
    {
        qInfo()<<"[Notice][TNNewFriendCard]handleNewCard-m_noticeInfo.leftFeed.isEmpty";
        return;
    }

	m_httpNewCardRequest->SetStaffInfo(m_noticeInfo.leftFeed, m_pluginParam->strTnUserID);

	auto acceptNewCardFinished = [&](bool success, QJsonObject jsonObject)
	{
		if (success)
		{
            QString debugText = QString(QJsonDocument(jsonObject).toJson());
            qInfo()<<"[Notice][TNNewFriendCard]acceptNewCardFinished-debugText="<<debugText;
            int retCode = jsonObject["meta"].toObject().value("code").toInt();
            if (retCode != 0)
            {
                QString message = jsonObject.value("meta").toObject().value("message").toString();
                TNMessageBox messageBox(this);
                messageBox.setMsg(message);
                messageBox.exec();
            }
		}
        else
        {
            TNMessageBox messageBox(QApplication::activeWindow());
            messageBox.setMsg(("操作失败，请检查您的网络状态"));
            messageBox.exec();
        }
	};

	m_httpNewCardRequest->GetJson(acceptNewCardFinished, m_pluginParam, accept);
    qInfo()<<"[Notice][TNNewFriendCard]handleNewCard end. Time="<<time.elapsed();
}

void TNNewFriendCard::acceptOrgCard()
{
	handleOrgCard(true);
}

void TNNewFriendCard::rejectOrgCard()
{
	handleOrgCard(false);
}

void TNNewFriendCard::handleOrgCard(bool accept)
{
    QTime time;
    time.start();
    qInfo()<<"[Notice][TNNewFriendCard]handleOrgCard begin... accept="<<accept;
	if (m_noticeInfo.leftFeed.isEmpty())
    {
        qInfo()<<"[Notice][TNNewFriendCard]handleOrgCard-m_noticeInfo.leftFeed.isEmpty";
        return;
    }

	m_httpOrgCardRequest->SetOrgCardFeedId(m_noticeInfo.leftFeed);

	auto acceptOrgCardFinished = [&](bool success, QJsonObject jsonObject)
	{
		if (success)
		{
            QString debugText = QString(QJsonDocument(jsonObject).toJson());
            qInfo()<<"[Notice][TNNewFriendCard]acceptOrgCardFinished-debugText="<<debugText;
            int retCode = jsonObject["meta"].toObject().value("code").toInt();
            if (retCode != 0)
            {
                QString message = jsonObject.value("meta").toObject().value("message").toString();
                TNMessageBox messageBox(this);
                messageBox.setMsg(message);
                messageBox.exec();
            }
		}
        else
        {
            TNMessageBox messageBox(QApplication::activeWindow());
            messageBox.setMsg(("操作失败，请检查您的网络状态"));
            messageBox.exec();
        }
	};

	m_httpOrgCardRequest->GetJson(acceptOrgCardFinished, m_pluginParam, accept);
    qInfo()<<"[Notice][TNNewFriendCard]handleOrgCard end. Time="<<time.elapsed();
}

void TNNewFriendCard::acceptNewFriend()
{    
    handleExchangeCard(true);
}

void TNNewFriendCard::acceptJoinGroup()
{
	handleJoinGroupRequest(true);
}

void TNNewFriendCard::rejectJoinGroup()
{
	handleJoinGroupRequest(false);
}

void TNNewFriendCard::handleJoinGroupRequest(bool accept)
{
    QTime time;
    time.start();
    qInfo()<<"[Notice][TNNewFriendCard]handleJoinGroupRequest begin... accept="<<accept;
	if (m_noticeInfo.leftFeed.isEmpty())
		return;

    QString friendUserId;
    st_FeedPtr friendFeedInfo;
    TNUserDataHelper::GetInstance()->GetFeedInfo(m_noticeInfo.leftFeed, friendFeedInfo);
    if (friendFeedInfo)
        friendUserId = friendFeedInfo->GetUserID();
    if (friendUserId.isEmpty())
    {
        qInfo()<<"[Notice][TNNewFriendCard]handleJoinGroupRequest-friendUserId is null. feedId="<<m_noticeInfo.leftFeed;
        return;
    }

	QString bizId = m_noticeInfo.bizId;
	int pos = bizId.lastIndexOf("_");
	QString groupId = bizId.right(bizId.length()-pos+1).simplified();

	m_groupRequestPtr->SetGroupReqInfo(m_noticeInfo.leftFeed, m_noticeInfo.upFeedTitle, friendUserId, groupId);

	auto acceptJoinGroupFinished = [&](bool success, QJsonObject jsonObject)
	{
		if (success)
		{
            QString debugText = QString(QJsonDocument(jsonObject).toJson());
            qInfo()<<"[Notice][TNNewFriendCard]acceptJoinGroupFinished-debugText="<<debugText;
            int retCode = jsonObject["meta"].toObject().value("code").toInt();
            if (retCode != 0)
            {
                QString message = jsonObject.value("meta").toObject().value("message").toString();
                TNMessageBox messageBox(this);
                messageBox.setMsg(message);
                messageBox.exec();
            }
		}
        else
        {
            TNMessageBox messageBox(QApplication::activeWindow());
            messageBox.setMsg(("操作失败，请检查您的网络状态"));
            messageBox.exec();
        }
	};

	m_groupRequestPtr->GetJson(acceptJoinGroupFinished, m_pluginParam, accept);
    qInfo()<<"[Notice][TNNewFriendCard]handleJoinGroupRequest end. Time="<<time.elapsed();
}

void TNNewFriendCard::rejectNewFriend()
{    
    handleExchangeCard(false);
}

void TNNewFriendCard::inviteJoinGroup()
{
    // 对于已完成的邀请入群，应该显示群组信息
    if (m_noticeInfo.bIsFinished)
        return;

    TNFrameViewer::instance()->showFrame(m_noticeInfo.leftFeed, m_noticeInfo.rightFeed);
}

void TNNewFriendCard::slotShowUrl()
{
    qInfo()<<"[Notice][TNNewFriendCard]slotShowUrl-url="<<m_noticeInfo.Url;
	// 群组公告[去群组]要单独处理
	if (m_noticeInfo.noticeType == CATALOG_GROUPNOTIFY)
	{
		QString groupId = m_noticeInfo.sessonId;
        viewGroupInfo(groupId, m_noticeInfo.rightFeed);
	}
	/*else if (m_noticeInfo.noticeType == CATALOG_COMPANY_MANAGER)
	{
		TNSimpleBrowser::getInstance()->clear();
		TNSimpleBrowser::getInstance()->setUrl(m_noticeInfo.Url);
		TNSimpleBrowser::getInstance()->showOnTop();
	}*/
    else if (m_noticeInfo.Url.startsWith(("toon://"), Qt::CaseInsensitive))
    {
        TNWebEnginePage::handleToonProtocol(m_noticeInfo.Url);
    }
	else
	{
		TNSimpleBrowser::getInstance()->setUrl(m_noticeInfo.Url);
		TNSimpleBrowser::getInstance()->showOnTop();
	}
}

void TNNewFriendCard::slotShowHerFrame()
{
    if (m_noticeInfo.rightFeed.startsWith("g_"))
        TNFrameViewer::instance()->showFrame(m_noticeInfo.leftFeed);
    else
        TNFrameViewer::instance()->showFrame(m_noticeInfo.leftFeed, m_noticeInfo.rightFeed);
}

void TNNewFriendCard::slotShowMineFrame()
{
    if (m_noticeInfo.rightFeed.startsWith("g_"))
        TNFrameViewer::instance()->showFrame(m_noticeInfo.rightFeed);
    else
        TNFrameViewer::instance()->showFrame(m_noticeInfo.rightFeed, m_noticeInfo.rightFeed);
}

void TNNewFriendCard::viewGroupInfo(const QString &groupId, const QString &belongFeedId)
{
    TNFrameViewer::instance()->showFrame(groupId, belongFeedId);
}

bool TNNewFriendCard::alreadyJoinGroup() const
{
	QString groupId = m_noticeInfo.leftFeed;
	QString cardFeedId = m_noticeInfo.rightFeed;

    return TNDbUtil::isInGroup(cardFeedId, groupId);
}

void TNNewFriendCard::asynDownloadAvatar(const QString& url, const QString& feedID, const QString& file_path)
{    
    qInfo() << "[Notice][TNNewFriendCard] asynDownloadAvatar, url: " << url << " feedId:" << feedID;
    TNNetAvatarDown::GetInstance()->DownLoadFeedAvatar(feedID, url, TNHttpCloudApi::GetInstance()->GetCloudStoken(m_pluginParam), this);
}

void TNNewFriendCard::onAvatarDownLoadFinish(bool success, QString file_path, QString feedID)
{
    if (success)
    {
        if (feedID == m_noticeInfo.leftFeed)
            ui->herAvatarButton->setAvatorImagePath(file_path);
        else if (feedID == m_noticeInfo.rightFeed)
            ui->mineAvatarButton->setAvatorImagePath(file_path);
    }
}

void TNNewFriendCard::resizeEvent(QResizeEvent *event)
{
	if (showFinishedMarkLabel(m_noticeInfo) || showExpiredMarkLabel(m_noticeInfo))
	{
		int x = getXPosition();
		int y = getYPosition();
		ui->finishedMarkLabel->setGeometry(x, y, 58, 64);
	}

	QWidget::resizeEvent(event);
}
