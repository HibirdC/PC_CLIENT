#include "TNGroupChatMembersWidget.h"
#include "ui_TNGroupChatMembersWidget.h"
#include <QStyleOption>

#include "qpushbutton.h"
#include "TNUtil.h"
#include "TNDbUtil.h"
#include "TNDataCache.h"
#include "tnnotifycenter.h"
#include "TNUserVersionInfo.h"
#include "TNDataControlServer.h"
#include "TNDataStatistics.h"
#include "TNContactModel.h"
#include "TNIMCoreClient.h"
#include "TNUserDataHelper.h"
#include "TNMessageBox.h"
#include "frames/TNFrameViewer.h"
#include "TNProgressLoading.h"
#include "SelectContactDialog.h"
#include "TNRemoveGroupChatMemberDialog.h"
#include "TNExitGroupChatConfirmDialog.h"
#include "TNIMCoreClient.h"
#include "CTNDBAPI.h"
#include "TNDefaultPage.h"
#include "Search/QSearchLineText.h"

TNGroupChatMembersWidget::TNGroupChatMembersWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TNGroupChatMembersWidget)
    , m_occurredException(false)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);

    m_pluginParam = TNUserDataHelper::GetInstance()->_pluginParam;
    m_searchLineEdit = new QSearchLineText(this);
    m_searchLineEdit->setObjectName("contactSearchLineEdit");
    m_searchLineEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
    /*
    QPushButton *searchButton = new QPushButton(this);
    searchButton->setObjectName("contactSearchButton");
    searchButton->setCursor(Qt::PointingHandCursor);
    searchButton->setToolTip(("搜索"));

    //防止文本框输入内容位于按钮之下
    QMargins margins = m_searchLineEdit->textMargins();
    m_searchLineEdit->setTextMargins(25, margins.top(), margins.right(), margins.bottom());
    m_searchLineEdit->setPlaceholderText(("请输入搜索内容"));
    m_searchLineEdit->setContextMenuPolicy(Qt::NoContextMenu);
    m_searchLineEdit->setFocusPolicy(Qt::StrongFocus);
    m_searchLineEdit->setClearButtonEnabled(true);

    QHBoxLayout *pSearchLayout = new QHBoxLayout();
    pSearchLayout->addWidget(searchButton);
    pSearchLayout->addStretch();
    pSearchLayout->setSpacing(0);
#ifdef Q_OS_WIN
    pSearchLayout->setContentsMargins(4, 0, 0, 0);
#else
    pSearchLayout->setContentsMargins(10, 0, 0, 0);
#endif
    m_searchLineEdit->setLayout(pSearchLayout);
    */

    QHBoxLayout *pLayout = new QHBoxLayout();
    pLayout->addWidget(m_searchLineEdit);
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(15, 5, 15, 5);
    ui->widget->setLayout(pLayout);
    ui->widget->setMinimumHeight(30);
    connect(m_searchLineEdit, SIGNAL(textChanged(QString)), this, SLOT(slotSearch(QString)));

    m_progressLoading = new TNProgressLoading(TNUtil::getMainWidget());

    m_nullPage = new TNDefaultPage(ui->leftTableView);
    m_nullPage->setObjectName("NULLPageCardCase");
    m_nullPage->setTextTitle(("没有相关的内容"));
    m_nullPage->setBackPic("searchnullico", QSize(60, 60));

    initialTableViewSettings();

    TNNotifyCenter::instance()->connectNotifyReMarkUpdate(this);
    connect(ui->leftTableView, SIGNAL(clicked(const QModelIndex &)), SLOT(slotMemberFrame(const QModelIndex &)));
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(slotExitGroupChat()));

    this->setWindowIcon(TOON_ICON);
    this->setWindowTitle(TOON_TITLE);
}

TNGroupChatMembersWidget::~TNGroupChatMembersWidget()
{
    delete ui;
}

void TNGroupChatMembersWidget::resetSession(TNMessageListAdapter *currentAdpter)
{
    qInfo() << "[Notice][TNGroupChatMembersWidget]resetSession-SessionId=" << currentAdpter->getSessionId();
    m_currentAdpter = *currentAdpter;
    m_groupChatMembers.clear();
    m_finishedGroupMemberDBGroupIds.clear();
    m_searchLineEdit->clear();

    if (m_occurredException)
    {
        m_occurredException = false;
        updateTableWidget();
    }
    else
    {
        ui->leftTableView->scrollToTop();
        this->hide();
    }
}

void TNGroupChatMembersWidget::updateTableWidget()
{
    qInfo() << "[Notice][TNGroupChatMembersWidget]updateTableWidget-begin-m_groupChatMembers.size()=" << m_groupChatMembers.size();
    if (m_groupChatMembers.isEmpty())
    {
        if (isSingleChat())
        {
            // 单聊
            ui->groupChatNameLabel->hide(); // 隐藏单聊名称
            ui->widget->hide(); // 隐藏搜索框
            ui->exitButton->hide();  // 隐藏[退出群聊]按钮

            // 先加入我
            TNFriend mySelf;
            mySelf = TNDbUtil::getFriend(m_currentAdpter.getMyFeedId());
            m_groupChatMembers.append(mySelf);

            // 再加入他
            TNFriend myFriend;
            myFriend.m_belongFeedId = m_currentAdpter.getMyFeedId();
            myFriend.m_userId = m_currentAdpter.getUserId();
            QString tag = m_currentAdpter.getTag();
            if (!tag.isEmpty())
            {
                QStringList friendTags = tag.split(",");
                myFriend.m_tags = friendTags;
            }
            myFriend.m_nickName = m_currentAdpter.getName();
            myFriend.m_subTitle = m_currentAdpter.getName();
            myFriend.m_friendFeedId = m_currentAdpter.getToFeed();
            myFriend.m_avatarURL = m_currentAdpter.getAvatarPhotoUrl();
            myFriend.m_avatarResourceFile = m_currentAdpter.getPhotoResID();

            m_groupChatMembers.append(myFriend);
        }
        else
        {
            // 群聊
            ui->groupChatNameLabel->show(); // 显示群聊名称
            ui->widget->show(); // 显示搜索框
            ui->exitButton->show();  // 显示[退出群聊]按钮

            // 获取群聊的所有成员
            QString groupId = m_currentAdpter.getToFeed();
            qInfo() << "[Notice][TNGroupChatMembersWidget]updateTableWidget-groupId="<<groupId;
            Q_ASSERT(groupId.startsWith("gc_"));
            if (!groupId.startsWith("gc_"))
            {
                qInfo()<<"[Notice][TNGroupChatMembersWidget]error! groupId有问题！";
            }
            else
            {
                m_groupChatMembers = TNDataCache::GetInstance()->GetGroupChatMemberCache(groupId);
                qInfo()<<"[Notice][TNGroupChatMembersWidget]cache-m_groupChatMembers.size="<<m_groupChatMembers.size();
                if (m_groupChatMembers.isEmpty())
                {
                    /*
                    st_GroupInfoPtr stGroupInfo = getGroupChatInfoFromHttp(groupId);
                    Q_ASSERT(stGroupInfo);
                    if (stGroupInfo)
                    {
                        TNDataControlServer::GetInstance()->InsertDatas(stGroupInfo, DBTYPE_USER);
                        qInfo() << "[Notice][TNGroupChatMembersWidget]-m_groupChatMembers isEmpty in DB. I am updating again...";
                        TNIMCoreClient::GetIMClient()->SynicGroupChatMember(groupId.mid(3));
                    }
                    */

                    qInfo() << "[Notice][TNGroupChatMembersWidget]-m_groupChatMembers isEmpty. I am updating again...";
                    TNIMCoreClient::GetIMClient()->SynicGroupChat();
                    m_occurredException = true;
                }
            }
        }

        QTime time;
        time.start();
        initialTableWidget();
        qInfo() << "[Notice][TNGroupChatMembersWidget]initialTableWidget()-time=" << time.elapsed();
    }
    qInfo() << "[Notice][TNGroupChatMembersWidget]updateTableWidget-end-m_groupChatMembers.size()=" << m_groupChatMembers.size();
}

st_GroupInfoPtr TNGroupChatMembersWidget::getGroupChatInfoFromHttp(const QString &groupChatId)
{
    TNHttpObtainGroupChatInfoByGroupChatIdSyn obtainGroupChatInfoByGroupChatIdSyn;
    if (obtainGroupChatInfoByGroupChatIdSyn.obtainGroupChatInfo(m_pluginParam, groupChatId.mid(3)))
    {
        st_GroupInfoPtr stGroupInfo = std::make_shared<st_GroupInfo>();
        QString createFeedId = obtainGroupChatInfoByGroupChatIdSyn.getCreateFeedId();
        int currNum = obtainGroupChatInfoByGroupChatIdSyn.getCurrNum();
        int maxNum = obtainGroupChatInfoByGroupChatIdSyn.getMaxNum();
        QString groupChatName = obtainGroupChatInfoByGroupChatIdSyn.getGroupChatName();
        QString myFeedId = obtainGroupChatInfoByGroupChatIdSyn.getMyFeedId();
        QString groupChatHeadImage = obtainGroupChatInfoByGroupChatIdSyn.getGroupChatHeadImage();
        QString topic = obtainGroupChatInfoByGroupChatIdSyn.getTopic();

        stGroupInfo->SetCreatorFeedId(createFeedId);
        stGroupInfo->SetCurrNum(currNum);
        stGroupInfo->SetGroupId(groupChatId);
        stGroupInfo->SetHeaderImage(groupChatHeadImage);
        stGroupInfo->SetMaxNum(maxNum);
        stGroupInfo->SetMyFeedId(myFeedId);
        stGroupInfo->SetName(groupChatName);
        stGroupInfo->SetTopic(topic);

        return stGroupInfo;
    }

    return st_GroupInfoPtr();
}

void TNGroupChatMembersWidget::stopLoading(const QString& groupChatId)
{
    if (groupChatId.startsWith("gc_"))
    {
        m_finishedGroupMemberDBGroupIds.append(groupChatId);
        doStopLoading();
    }
}

void TNGroupChatMembersWidget::doStopLoading()
{
    if (m_finishedGroupMemberDBGroupIds.contains(m_newCreateGroupChatIdCallback))
    {
        m_progressLoading->stop();
        m_finishedGroupMemberDBGroupIds.clear();
        m_newCreateGroupChatIdCallback = QString::null;
    }
}

void TNGroupChatMembersWidget::showNullPage(bool visible)
{
    int x = (ui->leftTableView->width() - m_nullPage->width())/2;
    int y = (ui->leftTableView->height() - m_nullPage->height())/2;
    m_nullPage->move(x, y);
    m_nullPage->setVisible(visible);
}

void TNGroupChatMembersWidget::initialTableViewSettings()
{
    ui->leftTableView->setObjectName("memberListWidget");
    ui->leftTableView->setShowGrid(false);
    ui->leftTableView->setIconSize(QSize(30, 30));
    ui->leftTableView->horizontalHeader()->setDefaultSectionSize(234);
    ui->leftTableView->verticalHeader()->setDefaultSectionSize(44);
    ui->leftTableView->horizontalHeader()->setVisible(false);
    ui->leftTableView->verticalHeader()->setVisible(false);
    ui->leftTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->leftTableView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->leftTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->leftTableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->leftTableView->setFocusPolicy(Qt::NoFocus);

    m_groupChatMemberModel = new TNContactModel();
    m_groupChatMemberModel->setElidedTextLength(160);
    ui->leftTableView->setModel(m_groupChatMemberModel);
    ui->leftTableView->setColumnWidth(0, 0);
    ui->leftTableView->setColumnWidth(1, 234);
    ui->leftTableView->setColumnWidth(2, 0);
}

void TNGroupChatMembersWidget::initialTableWidget()
{
    ui->groupChatNameLabel->setText(wrapTitleLabelName(m_currentAdpter.getName()));

    QList<ContactModelItem> contacts;
    QString belongFeedId = getMyFeedId();
    if (shouldShowAddButton())
    {
        //+
        ContactModelItem addContactItem;
        addContactItem.isLetter = false;
        addContactItem.nickName = ("添加成员");
        addContactItem.iconFile = QString(":/sysButton/Resources/img/sysButton/group/member-add.png");
        //addContactItem.pinYin = ;
        //addContactItem.feedId = ;
        //addContactItem.strAvatarURL = ;
        addContactItem.btnState = ContactModelItem::InvalidState;
        contacts.append(addContactItem);
    }

    if (shouldShowRemoveButton())
    {
        //-
        ContactModelItem addContactItem;
        addContactItem.isLetter = false;
        addContactItem.nickName = ("删除成员");
        addContactItem.iconFile = QString(":/sysButton/Resources/img/sysButton/group/member-delete.png");
        //addContactItem.pinYin = ;
        //addContactItem.feedId = ;
        //addContactItem.strAvatarURL = ;
        addContactItem.btnState = ContactModelItem::InvalidState;
        contacts.append(addContactItem);
    }

    for (auto iter = m_groupChatMembers.begin(); iter != m_groupChatMembers.end(); iter++)
    {
        ContactModelItem contactItem;
        contactItem.isLetter = false;
        contactItem.nickName = iter->m_nickName;
        contactItem.nickNamePinYin = iter->m_pinYin;
        contactItem.feedId = iter->m_friendFeedId;

        TNStructRemark stRemark = TNDataCache::GetInstance()->getFriendFeedReMarkWithPY(contactItem.feedId, belongFeedId);
        if (!stRemark.remark.isEmpty())
            contactItem.remark = stRemark.remark;
        if (!stRemark.remarkPy.isEmpty())
            contactItem.remarkPinYin = stRemark.remarkPy;

        contactItem.strAvatarURL = iter->m_avatarURL;
        contactItem.btnState = ContactModelItem::InvalidState;
        contacts.append(contactItem);
    }
    m_groupChatMemberModel->setContactList(contacts);

    showNullPage(contacts.isEmpty());
}

void TNGroupChatMembersWidget::slotSearch(const QString &text)
{
    if (text.isEmpty())
    {
        showNullPage(false);
        ui->exitButton->setVisible(true);
        for (int i = 0; i < m_groupChatMemberModel->rowCount(); i++)
        {
            ui->leftTableView->setRowHidden(i, false);
        }
    }
    else
    {
        ui->exitButton->setVisible(false);
        int visibleCount = 0;
        for (int i = 0; i < m_groupChatMemberModel->rowCount(); i++)
        {
            if (m_groupChatMemberModel->startsWith(i, text.trimmed()))
            {
                visibleCount++;
                ui->leftTableView->setRowHidden(i, false);
            }
            else
            {
                ui->leftTableView->setRowHidden(i, true);
            }
        }

        showNullPage(visibleCount == 0);
    }
}

void TNGroupChatMembersWidget::slotSelectContactDialog()
{
    TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_NoticeDetail_AddMember, m_pluginParam);
    QString belongFeedId = m_currentAdpter.getMyFeedId();
    QList<TNFriend> allGroupChatMembers(m_groupChatMembers);
    Q_ASSERT(!belongFeedId.isEmpty());
    if (belongFeedId.isEmpty())
        qInfo()<<"[Notice][TNGroupChatMembersWidget]slotSelectContactDialog-error! belongFeedId is null";
    Q_ASSERT(!m_groupChatMembers.isEmpty());
    if (m_groupChatMembers.isEmpty())
        qInfo()<<"[Notice][TNGroupChatMembersWidget]slotSelectContactDialog-error! m_groupChatMembers is empty";

    SelectContactDialog selectContactDialog;
    TNUtil::moveCenterInMainWidget(&selectContactDialog);
    selectContactDialog.setData(belongFeedId, allGroupChatMembers);
    selectContactDialog.setObjectName("selectContactDialog");
    if (selectContactDialog.exec() == QDialog::Accepted)
    {
        QList<TNFriend> selectFriends = selectContactDialog.getSelectedContact();
        slotSelectFinished(selectFriends);
    }
}

void TNGroupChatMembersWidget::slotRemoveGroupChatMemberDialog()
{
    TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_NoticeDetail_DelMember, m_pluginParam);
    QString belongFeedId = m_currentAdpter.getMyFeedId();
    QList<TNFriend> allGroupChatMembers(m_groupChatMembers);
    Q_ASSERT(!belongFeedId.isEmpty());
    if (belongFeedId.isEmpty())
    {
        qInfo()<<"[Notice][TNGroupChatMembersWidget]slotRemoveGroupChatMemberDialog-error! belongFeedId is null";
        return;
    }
    Q_ASSERT(!m_groupChatMembers.isEmpty());
    if (m_groupChatMembers.isEmpty())
    {
        qInfo()<<"[Notice][TNGroupChatMembersWidget]slotRemoveGroupChatMemberDialog-error! m_groupChatMembers is empty";
        return;
    }

    TNRemoveGroupChatMemberDialog memberDialog;
    TNUtil::moveCenterInMainWidget(&memberDialog);
    memberDialog.setData(belongFeedId, allGroupChatMembers);
    memberDialog.setObjectName("memberDialog");
    if (memberDialog.exec() == QDialog::Accepted)
    {
        TNFriend groupChatOwner = memberDialog.getGroupChatOwner();
        QList<TNFriend> selectFriends = memberDialog.getSelectedContact();
        removeMemberFromGroupChat(groupChatOwner, selectFriends);
    }
}

void TNGroupChatMembersWidget::slotSelectFinished(QList<TNFriend> selectFriends)
{
    if (isSingleChat())
    {
        // 加入我和他
        Q_ASSERT(m_groupChatMembers.size() == 2);
        if (!m_groupChatMembers.isEmpty())
            selectFriends.prepend(m_groupChatMembers.first());
        if (!m_groupChatMembers.isEmpty())
            selectFriends.append(m_groupChatMembers.last());

        createGroupChat(selectFriends);
    }
    else
    {
        addMemberToGroupChat(selectFriends);
    }
    emit widgetHided();
}

bool TNGroupChatMembersWidget::shouldShowAddButton() const
{
    // 1. 群聊时，显示 + 按钮
    if (isGroupChat())
        return true;

    // 2. 单聊时，如果是好友或者同事则显示 + 按钮
    if (isSingleChat())
    {
        if (TNDbUtil::isFriendRelation(getMyFeedId(), getToFeedId()) || TNDbUtil::isColleageRelation(getMyFeedId(), getToFeedId()))
            return true;
    }

    return false;
}

bool TNGroupChatMembersWidget::shouldShowRemoveButton() const
{
    // 1. 单聊时，不显示 - 按钮
    if (isSingleChat())
        return false;

    // 2. 群聊时，如果群主是自己则显示 - 按钮
    if (isGroupChat())
    {
        Q_ASSERT(!m_groupChatMembers.isEmpty());
        if (m_groupChatMembers.isEmpty())
        {
            qInfo()<<"[Notice][TNGroupChatMembersWidget]error! m_groupChatMembers is empty.";
            return false;
        }
        if ((m_groupChatMembers.first().permissionType == "1") || (m_groupChatMembers.first().permissionType == "2"))
        {
            QString ownerFeedId = m_groupChatMembers.first().m_friendFeedId;
            bool isMySelf = TNDataControlServer::GetInstance()->isMySelf(ownerFeedId);
            return isMySelf;
        }
    }

    return false;
}

bool TNGroupChatMembersWidget::isSingleChat() const
{
    return (m_currentAdpter.getType() == MSG_BIZ_SINGLECHAT);
}

bool TNGroupChatMembersWidget::isGroupChat() const
{
    return (m_currentAdpter.getType() == MSG_BIZ_GROUPCHAT);
}

void TNGroupChatMembersWidget::createGroupChat(const QList<TNFriend> &selectContacts)
{
    if (selectContacts.isEmpty())
        return;

    qInfo()<<"[Notice][TNGroupChatMembersWidget]createGroupChat begin...";
    TNFriend aFriend = selectContacts.first();
    QString feedId = aFriend.m_friendFeedId;
    QString feedAvatartId = aFriend.m_avatarURL;
    QString feedTitle = aFriend.m_nickName;
    m_httpCreateGroupChat.SetCreateFeed(feedAvatartId, feedId, feedTitle);
    qInfo()<<"[Notice][TNGroupChatMembersWidget]createGroupChat-oooo-myFeedId="<<feedId;
    Q_ASSERT(!feedId.isEmpty());

    for (int i = 0; i < selectContacts.size(); i++)
    {
        QString memberAvatartId = selectContacts.at(i).m_avatarURL;
        QString memberFeedId = selectContacts.at(i).m_friendFeedId;
        QString memberFeedTitle = selectContacts.at(i).m_nickName;
        QString userId = selectContacts.at(i).m_userId;
        m_httpCreateGroupChat.AddGroupMember(memberAvatartId, memberFeedId, memberFeedTitle, userId);
    }

    auto writeGroupChatInfoDB = [&](bool success, QString cBelongFeedId, QJsonObject jsonObject)
    {
        qInfo()<<"[Notice][TNGroupChatMembersWidget]createGroupChat-callback begin...";
        if (success)
        {
            QString debugText = QJsonDocument(jsonObject).toJson();
            qInfo()<<"[Notice][TNGroupChatMembersWidget]createGroupChat-debugText="<<debugText;
            int retCode = jsonObject["meta"].toObject().value("code").toInt();
            if (retCode == 0)
            {
                QVariantMap mapResp = jsonObject.toVariantMap();
                QVariant metaInfo = mapResp["meta"];
                QVariantMap metaInfoMap = metaInfo.toMap();

                QVariant groupInfo = mapResp["data"];
                QVariantMap mapGroup = groupInfo.toMap();
                int maxNum = mapGroup["maxNum"].toInt();
                int currNum = mapGroup["currNum"].toInt();
                QString topic = mapGroup["topic"].toString();
                QString groupchatId = topic;
                QString groupChatName = mapGroup["groupChatName"].toString();
                QString createFeedId = mapGroup["creatorFeedId"].toString();
                QString groupChatHeadImage = mapGroup["groupChatHeadImage"].toString();

                Q_ASSERT(groupchatId.startsWith("gc_"));

                QString from = cBelongFeedId;
                QString to   = groupchatId;
                QString sessionId = TNIMCoreClient::GetSessionId(from, to, MSG_BIZ_GROUPCHAT);
                // 新建session
                TNMessageListAdapter session(sessionId, MSG_BIZ_GROUPCHAT);
                session.setAvatarPhotoUrl(groupChatHeadImage);
                qInfo() << "[Notice][TNGroupChatMembersWidget]createGroupChat avatarPhotoUrl:" << groupChatHeadImage;
                session.setMyFeedId(from);
                session.setToFeed(to);
                session.setName(groupChatName);
                session.setTime(QDateTime::currentDateTime().toTime_t());
                emit createGroupChatFinished(session);

                m_newCreateGroupChatIdCallback = groupchatId;
                doStopLoading();
            }
            else
            {
                QString content = jsonObject.value("meta").toObject().value("message").toString();
                qInfo() << "[Notice][TNGroupChatMembersWidget]createGroupChat failed. retCode=" << retCode << " content=" << content;
                TNMessageBox messageBox(this);
                messageBox.setMsg(content);
                messageBox.exec();
            }
        }
        else
        {
            TNMessageBox messageBox(this);
            messageBox.setMsg(("操作失败，请检查您的网络状态"));
            messageBox.exec();
        }
        qInfo()<<"[Notice][TNGroupChatMembersWidget]createGroupChat-callback end.";
    };

    m_httpCreateGroupChat.requestCreateGroupChat(writeGroupChatInfoDB, m_pluginParam, getMyFeedId());
    m_progressLoading->start();
    qInfo()<<"[Notice][TNGroupChatMembersWidget]createGroupChat end.";
}

void TNGroupChatMembersWidget::addMemberToGroupChat(const QList<TNFriend> &selectContacts)
{
    if (selectContacts.isEmpty())
        return;

    qInfo()<<"[Notice][TNGroupChatMembersWidget]addMemberToGroupChat begin...";
    QString feedId = selectContacts.first().m_belongFeedId;
    QString groupId = getCurrentGroupChatId();
    INVIT_SOURCE type = SOURCE_TYPE_INVIT;

    QString title;
    st_FeedPtr feedInfo;
    TNUserDataHelper::GetInstance()->GetFeedInfo(feedId, feedInfo);
    if (feedInfo)
        title = feedInfo->GetTitle();

    m_httpAddGroupChatMember.setAddGroupChatInfo(feedId, title, groupId, type);

    bool hasRecyclingCard = false;
    QString recycledCardFeedId;
    for (int i = 0; i < selectContacts.size(); i++)
    {
        QString memberAvatartId = selectContacts.at(i).m_avatarURL;
        QString memberFeedId = selectContacts.at(i).m_friendFeedId;
        QString memberFeedTitle = selectContacts.at(i).m_nickName;
        QString userId = selectContacts.at(i).m_userId;
        if (!TNUserDataHelper::GetInstance()->GetSingleCardStatus(memberFeedId))
        {
            hasRecyclingCard = true;
            recycledCardFeedId = memberFeedId;
        }
        else
        {
            hasRecyclingCard = false;
            recycledCardFeedId.clear();
            m_httpAddGroupChatMember.addGroupMember(userId, memberFeedId, memberFeedTitle, memberAvatartId);
        }
    }

    if (hasRecyclingCard && !recycledCardFeedId.isEmpty())
    {
        QString content = recycledCardFeedId.startsWith("c_") ? ("该名片已被删除") : ("该名片已被回收");
        TNMessageBox messageBox(this);
        messageBox.setMsg(content);
        messageBox.exec();
        return;
    }

    auto writeGroupChatMemberDB = [&](bool success, QJsonObject jsonObject, QStringList memberNames)
    {
        qInfo()<<"[Notice][TNGroupChatMembersWidget]addMemberToGroupChat-callback begin...";
        if (success)
        {
            QString debugText = QJsonDocument(jsonObject).toJson();
            qInfo()<<"[Notice][TNGroupChatMembersWidget]addMemberToGroupChat-debugText="<<debugText;
            int retCode = jsonObject["meta"].toObject().value("code").toInt();
            if (retCode == 0)
            {
                qInfo() << "[Notice][TNGroupChatMembersWidget]addMemberToGroupChat success.";
            }
            else
            {
                //QString content = jsonObject.value("meta").toObject().value("message").toString();
                QString content(("操作失败"));
                if (retCode == 118110)
                {
                    content = ("超出群聊人数上限（500人）");
                }
                if (retCode == 118007)
                {
                    QString memberNameStr = memberNames.mid(0, 3).join(QChar(','));
                    if (memberNames.size()>3)
                        memberNameStr += ("等");
                    content = QString(("%1已有名片在群聊中，无法加入群聊")).arg(memberNameStr);
                }

                qInfo() << "[Notice][TNGroupChatMembersWidget]addMemberToGroupChat failed. retCode=" << retCode << " content=" << content;
                TNMessageBox messageBox(this);
                messageBox.setMsg(content);
                messageBox.exec();
            }
        }
        else
        {
            TNMessageBox messageBox(this);
            messageBox.setMsg(("操作失败，请检查您的网络状态"));
            messageBox.exec();
        }
        qInfo()<<"[Notice][TNGroupChatMembersWidget]addMemberToGroupChat-callback end.";
    };

    QStringList contactNames;
    foreach (const TNFriend &aContact, selectContacts)
    {
        contactNames.append(aContact.m_nickName);
    }
    m_httpAddGroupChatMember.requestAddGroupChatMember(writeGroupChatMemberDB, m_pluginParam, contactNames);
    qInfo()<<"[Notice][TNGroupChatMembersWidget]addMemberToGroupChat end.";
}

void TNGroupChatMembersWidget::removeMemberFromGroupChat(const TNFriend &groupChatOwner, const QList<TNFriend> &selectContacts)
{
    if (selectContacts.isEmpty())
        return;

    qInfo()<<"[Notice][TNGroupChatMembersWidget]removeMemberFromGroupChat begin...";
    QString groupChatId = getCurrentGroupChatId();
    m_httpRemoveGroupChatMember.setRemoveGroupChatInfo(groupChatOwner.m_friendFeedId, groupChatOwner.m_nickName, groupChatId);

    for (int i = 0; i < selectContacts.size(); i++)
    {
        QString memberFeedId = selectContacts.at(i).m_friendFeedId;
        QString memberFeedTitle = selectContacts.at(i).m_nickName;
        QString userId = selectContacts.at(i).m_userId;

        m_httpRemoveGroupChatMember.appendRemovedGroupMember(userId, memberFeedId, memberFeedTitle);
    }

    auto removeGroupChatMemberFinished = [&](bool success, QJsonObject jsonObject)
    {
        qInfo()<<"[Notice][TNGroupChatMembersWidget]removeMemberFromGroupChat-callback begin...";
        if (success)
        {
            QString debugText = QJsonDocument(jsonObject).toJson();
            qInfo()<<"[Notice][TNGroupChatMembersWidget]removeMemberFromGroupChat-debugText="<<debugText;
            int retCode = jsonObject["meta"].toObject().value("code").toInt();
            if (retCode == 0)
            {
                qInfo() << "[Notice][TNGroupChatMembersWidget]removeMemberFromGroupChat success.";
                emit widgetHided();
            }
            else
            {
                QString content = jsonObject.value("meta").toObject().value("message").toString();
                TNMessageBox messageBox(this);
                messageBox.setMsg(content);
                messageBox.exec();
            }
        }
        else
        {
            TNMessageBox messageBox(this);
            messageBox.setMsg(("操作失败，请检查您的网络状态"));
            messageBox.exec();
        }
        qInfo()<<"[Notice][TNGroupChatMembersWidget]removeMemberFromGroupChat-callback end.";
    };

    m_httpRemoveGroupChatMember.removeGroupChatMember(removeGroupChatMemberFinished, m_pluginParam);
    qInfo()<<"[Notice][TNGroupChatMembersWidget]removeMemberFromGroupChat end.";
}

void TNGroupChatMembersWidget::slotExitGroupChat()
{
    TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_NoticeDetail_QuitChat, m_pluginParam);
    TNExitGroupChatConfirmDialog exitGroupChatConfirmDialog(this);
    if (exitGroupChatConfirmDialog.exec() == QDialog::Accepted)
    {
        exitGroupChat();
    }
}

void TNGroupChatMembersWidget::exitGroupChat()
{
    qInfo()<<"[Notice][TNGroupChatMembersWidget]exitGroupChat begin...";
    const QString feedId = getMyFeedId();

    QString feedTitle;
    st_FeedPtr feedInfo;
    TNUserDataHelper::GetInstance()->GetFeedInfo(feedId, feedInfo);
    if (feedInfo)
        feedTitle = feedInfo->GetTitle();

    const QString groupId = getCurrentGroupChatId();
    const QString userId = getUserId();

    m_httpQuitGroupChat.SetQuitGroupInfo(feedId, feedTitle, groupId, userId);

    auto exitGroupChatFinishedDB = [&](bool success, QString groupChatId, QJsonObject jsonObject)
    {
        qInfo()<<"[Notice][TNGroupChatMembersWidget]exitGroupChat-callback begin...";
        if (success)
        {
            QString debugText = QJsonDocument(jsonObject).toJson();
            qInfo()<<"[Notice][TNGroupChatMembersWidget]exitGroupChat-debugText="<<debugText;
            int retCode = jsonObject["meta"].toObject().value("code").toInt();
            if (retCode == 0)
            {
                // 退出群聊，操作数据库
                TNDbUtil::operateDBWhenExitGroupChat(groupChatId);
                TNIMCoreClient::GetIMClient()->GetDBChat()->deleteSession(groupChatId.toUtf8().data());
				//请勿reset version
                //TNUserVersionInfo::GetInstance()->ResetUpdateVersion(UPDATE_TYPE_GroupChat);
                TNUserVersionInfo::GetInstance()->ResetUpdateVersion(groupChatId);

                emit widgetHided();

                QString sessionId = groupChatId;
                TNMessageListAdapter tempMessageListAdapter(sessionId, MSG_BIZ_GROUPCHAT);
#ifdef Q_OS_WIN
                QList<UINotifyData> groupList;
                UINotifyData data;
                data.feedId = sessionId;
                data.belongId = getMyFeedId();
                data.operateType = UI_OPERATE_DEL;
                groupList.append(data);
                TNNotifyCenter::instance()->postNotifyRefresh(RefreshTypeUI_GroupChat, groupList);
#endif
                emit exitGroupChatFinished(tempMessageListAdapter);
            }
            else
            {
                QString content = jsonObject.value("meta").toObject().value("message").toString();
                qInfo() << "[Notice][TNGroupChatMembersWidget]exitGroupChat failed. retCode=" << retCode << " content=" << content;
                TNMessageBox messageBox(this);
                messageBox.setMsg(content);
                messageBox.exec();
            }
        }
        else
        {
            TNMessageBox messageBox(this);
            messageBox.setMsg(("操作失败，请检查您的网络状态"));
            messageBox.exec();
        }
        qInfo()<<"[Notice][TNGroupChatMembersWidget]exitGroupChat-callback end.";
    };

    m_httpQuitGroupChat.GetJson(exitGroupChatFinishedDB, m_pluginParam);
    qInfo()<<"[Notice][TNGroupChatMembersWidget]exitGroupChat end.";
}

void TNGroupChatMembersWidget::slotMemberFrame(const QModelIndex &index)
{
    if (shouldShowAddButton() && (index.row() == 0))
    {
        slotSelectContactDialog();
    }
    else if (shouldShowRemoveButton() && (index.row() == 1))
    {
        slotRemoveGroupChatMemberDialog();
    }
    else
    {
        QString currentFeedId = index.data(Qt::UserRole + 2).toString();
        QString belongFeedId  = getMyFeedId();
        TNFrameViewer::instance()->showFrame(currentFeedId, belongFeedId);
    }
}

void TNGroupChatMembersWidget::on_notifyReMarkUpdate(const QString &from, const QString &to, const QString &remark, int sources)
{
    if (isSingleChat() && (getMyFeedId() == to))
    {
        m_groupChatMemberModel->updateRemarkName(from, remark);
    }

    if (isGroupChat() && TNDbUtil::isInGroupChat(getCurrentGroupChatId(), to))
    {
        m_groupChatMemberModel->updateRemarkName(from, remark);
    }
}

QString TNGroupChatMembersWidget::getCurrentGroupChatId() const
{
    return m_currentAdpter.getToFeed();
}

QString TNGroupChatMembersWidget::getCurrentGroupChatName() const
{
    return m_currentAdpter.getName();
}

QString TNGroupChatMembersWidget::getMyFeedId() const
{
    return m_currentAdpter.getMyFeedId();
}

QString TNGroupChatMembersWidget::getToFeedId() const
{
    return m_currentAdpter.getToFeed();
}

QString TNGroupChatMembersWidget::getUserId() const
{
    return m_currentAdpter.getUserId();
}

void TNGroupChatMembersWidget::paintEvent(QPaintEvent * event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QString TNGroupChatMembersWidget::wrapTitleLabelName(const QString &oldName)
{
    QString newName(oldName);

    if (m_currentAdpter.getType() == MSG_BIZ_SINGLECHAT)
    {
        const QString belongFeedId = m_currentAdpter.getMyFeedId();
        const QString feedId = m_currentAdpter.getToFeed();
        if (TNDbUtil::isFriendRelation(belongFeedId, feedId))
        {
            QString remark = TNDataCache::GetInstance()->getFriendFeedReMark(feedId, belongFeedId);
            if (!remark.isEmpty())
                newName = remark;
        }
    }

    QString elidedText = ui->groupChatNameLabel->fontMetrics().elidedText(newName, Qt::ElideMiddle, 220, Qt::TextShowMnemonic);
    elidedText.replace('&',"&&");
    return elidedText;
}
