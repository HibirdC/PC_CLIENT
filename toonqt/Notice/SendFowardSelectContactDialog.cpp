#include "SendFowardSelectContactDialog.h"
#include "ui_SendFowardSelectContactDialog.h"

#include "TNDbUtil.h"
#include "network/tnsendimsg.h"
#include "noticelistmodel.h"
#include "TNContactModel.h"
#include "TNUserDataHelper.h"
#include "TNDataCache.h"
#include "TNPathUtil.h"
#include "TNMessageBox.h"
#include "TNDefaultPage.h"

#include <QLineEdit>

SendFowardSelectContactDialog * SendFowardSelectContactDialog::s_pInstance = nullptr;
SendFowardSelectContactDialog * SendFowardSelectContactDialog::getInstance()
{
    if (s_pInstance == nullptr)
    {
        qInfo()<<"[Notice][SendFowardSelectContactDialog]I am a new SendFowardSelectContactDialog...";
        s_pInstance = new SendFowardSelectContactDialog(nullptr);
    }
    return s_pInstance;
}

SendFowardSelectContactDialog::SendFowardSelectContactDialog(QWidget *parent)
    : DropShadowWidget(parent)
    , ui(new Ui::SendFowardSelectContactDialog)
    , m_maxSelectedNum(20)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);
    _searchLineEdit = new QLineEdit();
    _searchLineEdit->setObjectName("contactSearchLineEdit");
    _searchLineEdit->setContextMenuPolicy(Qt::NoContextMenu);
    _searchLineEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
    QPushButton *searchButton = new QPushButton(this);
    searchButton->setObjectName("contactSearchButton");
    searchButton->setCursor(Qt::PointingHandCursor);
    searchButton->setToolTip(("搜索"));

    //防止文本框输入内容位于按钮之下
    QMargins margins = _searchLineEdit->textMargins();
    _searchLineEdit->setTextMargins(25, margins.top(), margins.right(), margins.bottom());
    _searchLineEdit->setPlaceholderText(("请输入搜索内容"));

    QHBoxLayout *pSearchLayout = new QHBoxLayout();
    pSearchLayout->addWidget(searchButton);
    pSearchLayout->addStretch();
    pSearchLayout->setSpacing(0);
#ifdef Q_OS_WIN
    pSearchLayout->setContentsMargins(4, 0, 0, 0);
#else
    pSearchLayout->setContentsMargins(10, 0, 0, 0);
#endif
    _searchLineEdit->setLayout(pSearchLayout);

    QHBoxLayout *pLayout = new QHBoxLayout();
    pLayout->addWidget(_searchLineEdit);
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(0, 5, 0, 5);
    ui->widget->setLayout(pLayout);
    //ui->widget->setMinimumHeight(30);
    connect(_searchLineEdit, SIGNAL(textChanged(QString)), this, SLOT(slotSearch(QString)));

    m_nullPage = new TNDefaultPage(ui->leftTableView);
    m_nullPage->setObjectName("NULLPageCardCase");

    initialTableViewSettings(ui->leftTableView);
    initialTableViewSettings(ui->rightTableView);

    m_leftContactModel = new TNContactModel();
    m_leftContactModel->setElidedTextLength(190);
    m_rightContactModel = new TNContactModel();
    m_rightContactModel->setElidedTextLength(190);

    connect(ui->leftTableView, SIGNAL(clicked(const QModelIndex &)), SLOT(slotLeftItemClicked(const QModelIndex &)));
    connect(ui->rightTableView, SIGNAL(clicked(const QModelIndex &)), SLOT(slotRightItemClicked(const QModelIndex &)));

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->dialogCloseButton, SIGNAL(clicked()), this, SLOT(reject()));

    this->setWindowFlags(Qt::FramelessWindowHint);

    this->setWindowIcon(TOON_ICON);
    this->setWindowTitle(TOON_TITLE);

    _searchLineEdit->setFocus();
    ui->okButton->setEnabled(false);
}

void SendFowardSelectContactDialog::setData(const QString &belongMyFeedId)
{
    m_belongToFeedId = belongMyFeedId;

    m_maxSelectedNum = 20;

    initialTableWidget();
}

SendFowardSelectContactDialog::~SendFowardSelectContactDialog()
{
    s_pInstance = nullptr;
    delete ui;
}

void SendFowardSelectContactDialog::showNullPage(bool visible)
{
    int w = ui->leftTableView->width();
    if (w < 250)
        w = 250;
    int h = ui->leftTableView->height();
    if (h < 300)
        h = 300;
    int x = (w - m_nullPage->width())/2;
    int y = (h - m_nullPage->height())/2;
    m_nullPage->move(x, y);
    m_nullPage->setVisible(visible);
}

void SendFowardSelectContactDialog::initialTableViewSettings(QTableView *tableView)
{
    tableView->setShowGrid(false);
    tableView->setIconSize(QSize(30, 30));
    tableView->horizontalHeader()->setDefaultSectionSize(248);
    tableView->verticalHeader()->setDefaultSectionSize(40);
    tableView->horizontalHeader()->setVisible(false);
    tableView->verticalHeader()->setVisible(false);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::NoSelection);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableView->setFocusPolicy(Qt::NoFocus);
}

void SendFowardSelectContactDialog::slotLeftItemClicked(const QModelIndex &index)
{
    if (m_maxSelectedNum == 0)
    {
        return;
    }

    if (m_maxSelectedNum > 0)
    {
        m_maxSelectedNum--;
    }

    ui->leftTableView->setRowHidden(index.row(), true);
    m_rightContactModel->appendContact(m_leftContactModel->getContact(index));

    ui->okButton->setEnabled(m_rightContactModel->rowCount()>0);
}

void SendFowardSelectContactDialog::slotRightItemClicked(const QModelIndex &index)
{
    if (m_maxSelectedNum >= 0)
    {
        m_maxSelectedNum++;
    }

    ContactModelItem aContact = m_rightContactModel->getContact(index);
    int row = m_leftContactModel->getRowByFeedId(aContact.feedId);
    ui->leftTableView->setRowHidden(row, false);
    m_rightContactModel->removeContact(aContact);

    ui->okButton->setEnabled(m_rightContactModel->rowCount()>0);
}

void SendFowardSelectContactDialog::initialTableWidget()
{
    copySessionCacheToMap();
    copyFriendCacheToMap();
    copyColleagueCacheToMap();
    copyGroupChatCacheToMap();

    for (auto iter = m_feedIdToFriendMap.begin(); iter != m_feedIdToFriendMap.end(); iter++)
    {
        ContactModelItem contactItem;
        contactItem.isLetter = false;
        contactItem.nickName = iter->m_nickName;
        contactItem.nickNamePinYin = iter->m_pinYin;
        contactItem.feedId = iter->m_friendFeedId;

        TNStructRemark stRemark = TNDataCache::GetInstance()->getFriendFeedReMarkWithPY(contactItem.feedId, m_belongToFeedId);
        if (!stRemark.remark.isEmpty())
            contactItem.remark = stRemark.remark;
        if (!stRemark.remarkPy.isEmpty())
            contactItem.remarkPinYin = stRemark.remarkPy;

        contactItem.strAvatarURL = iter->m_avatarURL;

        QString pinYin = contactItem.remarkPinYin;
        if (pinYin.isEmpty())
            pinYin = contactItem.nickNamePinYin;
        m_friendItems.insert(pinYin, contactItem);
    }

    QList<ContactModelItem> contacts;
    for (auto iter = m_sessionItems.begin(); iter != m_sessionItems.end(); iter++)
    {
        contacts.push_back(*iter);
    }

    for (auto iter = m_GroupChatItems.begin(); iter != m_GroupChatItems.end(); iter++)
    {
        contacts.push_back(iter.value());
    }

    for (auto iter = m_friendItems.begin(); iter != m_friendItems.end(); iter++)
    {
        contacts.push_back(iter.value());
    }
    m_leftContactModel->setContactList(contacts);
    ui->leftTableView->setModel(m_leftContactModel);
    ui->leftTableView->setColumnWidth(0, 6);
    ui->leftTableView->setColumnWidth(1, 236);
    ui->leftTableView->setColumnWidth(2, 0);

    ui->rightTableView->setModel(m_rightContactModel);
    ui->rightTableView->setColumnWidth(0, 6);
    ui->rightTableView->setColumnWidth(1, 236);
    ui->rightTableView->setColumnWidth(2, 0);

    resetLeftViewRowHidden();

    m_nullPage->setTextTitle(("暂无联系人"));
    m_nullPage->setBorderImage(TNVersionInfo::GetNullPageRes_cardcase());
    showNullPage(contacts.isEmpty());
}

void SendFowardSelectContactDialog::resetLeftViewRowHidden()
{
    if (m_sessionItems.size() > 10)
    {
        for (int i=m_sessionItems.size(); i<m_leftContactModel->rowCount(); ++i)
        {
            ui->leftTableView->setRowHidden(i, true);
        }
    }
    else
    {
        for (int i=0; i<m_sessionItems.size(); ++i)
        {
            ui->leftTableView->setRowHidden(i, true);
        }
    }
}

bool SendFowardSelectContactDialog::shouldExclude(const QString &feedId, int *sessionIndex) const
{
    for (int i = 0; i < m_sessionItems.size(); ++i)
    {
        if (m_sessionItems.at(i).feedId == feedId)
        {
            *sessionIndex = i;
            return true;
        }
    }
    return false;
}

QList<TNMessageListAdapter> SendFowardSelectContactDialog::getSelectedSessions() const
{
    QList<TNMessageListAdapter> selectSessions;
    for (int i = 0; i < m_rightContactModel->rowCount(); i++)
    {
        QString feedId = m_rightContactModel->getFeedId(i);
        QMap<QString/*feedID*/, TNMessageListAdapter>::const_iterator iter = m_feedIdToSessionMap.find(feedId);
        if (iter != m_feedIdToSessionMap.end())
        {
            selectSessions.append(m_feedIdToSessionMap[feedId]);
        }
    }

    return selectSessions;
}

QList<TNFriend> SendFowardSelectContactDialog::getSelectedContact() const
{
    QList<TNFriend> selectContacts;
    for (int i = 0; i < m_rightContactModel->rowCount(); i++)
    {
        QString feedId = m_rightContactModel->getFeedId(i);
        QMap<QString/*feedID*/, TNFriend>::const_iterator iter = m_feedIdToFriendMap.find(feedId);
        if (iter != m_feedIdToFriendMap.end())
        {
            selectContacts.append(m_feedIdToFriendMap[feedId]);
        }
    }

    return selectContacts;
}

QList<TNStructGroupChat> SendFowardSelectContactDialog::getSelectedGroupChats() const
{
    QList<TNStructGroupChat> selectContacts;
    for (int i = 0; i < m_rightContactModel->rowCount(); i++)
    {
        QString feedId = m_rightContactModel->getFeedId(i);
        QMap<QString, TNStructGroupChat>::const_iterator iter = m_feedIdToGroupChatMap.find(feedId);
        if (iter != m_feedIdToGroupChatMap.end())
        {
            selectContacts.push_back(iter.value());
        }
    }

    return selectContacts;
}

void SendFowardSelectContactDialog::accept()
{
    QList<TNMessageListAdapter> selectSessions = getSelectedSessions();
    QList<TNFriend> selectContacts = getSelectedContact();
    QList<TNStructGroupChat> selectGroupChats = getSelectedGroupChats();
    qDebug()<<"selectSessions.size="<<selectSessions.size()<<" selectContacts.size="<<selectContacts.size()<<" selectGroupChats.size="<<selectGroupChats.size();
    if (selectSessions.isEmpty() && selectContacts.isEmpty() && selectGroupChats.isEmpty())
    {
        return;
    }

    QDialog::accept();

    emit selectFinished(selectSessions, selectContacts, selectGroupChats);
}

void SendFowardSelectContactDialog::slotSearch(const QString &text)
{
    if (text.isEmpty())
    {
        m_nullPage->setTextTitle(("暂无联系人"));
        m_nullPage->setBorderImage(TNVersionInfo::GetNullPageRes_cardcase());
        showNullPage(false);
        for (int i = 0; i < m_leftContactModel->rowCount(); i++)
        {
            const QString feedId = m_leftContactModel->getFeedId(i);
            if (m_rightContactModel->getRowByFeedId(feedId) != -1)
                ui->leftTableView->setRowHidden(i, true);
            else
                ui->leftTableView->setRowHidden(i, false);
        }

        resetLeftViewRowHidden();
    }
    else
    {
        int visibleCount = 0;
        for (int i = 0; i < m_leftContactModel->rowCount(); i++)
        {
            const QString feedId = m_leftContactModel->getFeedId(i);
            if (m_leftContactModel->startsWith(i, text.trimmed()) && (m_rightContactModel->getRowByFeedId(feedId) == -1))
            {
                visibleCount++;
                ui->leftTableView->setRowHidden(i, false);
            }
            else
            {
                ui->leftTableView->setRowHidden(i, true);
            }
        }

        m_nullPage->setTextTitle(("没有相关的内容"));
        m_nullPage->setBorderImage(TNVersionInfo::GetNullPageRes_search());
        showNullPage(visibleCount == 0);
    }
}

void SendFowardSelectContactDialog::copySessionCacheToMap()
{
    QList<TNMessageListAdapter> sessionList = TNSendIMsg::getInstance()->getListMsgModel()->getSessionList();
    if (sessionList.isEmpty())
    {
        qInfo() << "[Notice][SendFowardSelectContactDialog] copySessionCacheToMap getSessionList is null";
        return;
    }

    for (auto iter = sessionList.begin(); iter != sessionList.end(); iter++)
    {
        if (m_belongToFeedId == iter->getMyFeedId())
        {
            ContactModelItem contactItem;
            contactItem.isLetter = false;
            contactItem.nickName = iter->getName();
            //contactItem.pinYin = ...; // 在排重时会将其补全，保证查找搜索时能用拼音匹配

            contactItem.feedId = iter->getToFeed();
            contactItem.strAvatarURL = iter->getAvatarPhotoUrl();
            m_sessionItems.append(contactItem);
            m_feedIdToSessionMap[contactItem.feedId] = *iter;
        }
    }

    if (m_sessionItems.size() <= 10)
    {
        m_sessionItems.clear();
        m_feedIdToSessionMap.clear();
    }
}

void SendFowardSelectContactDialog::copyFriendCacheToMap()
{
    if (m_belongToFeedId.isEmpty())
    {
        qInfo() << "[Notice][SendFowardSelectContactDialog] copyFriendCacheToMap m_belongMyFeedId is null";
        return;
    }
    QList<TNStructFriend> friendList;
    TNDataCache::GetInstance()->GetFriendCache(friendList, m_belongToFeedId);
    if (friendList.size() == 0)
    {
        qInfo() << "[Notice][SendFowardSelectContactDialog] copyFriendCacheToMap GetFriendCache is null";
        return;
    }
    QList<TNStructFriend>::const_iterator itera = friendList.begin();
    for (; itera != friendList.end(); ++itera)
    {
        int sessionIndex = -1;
        if (shouldExclude(itera->m_Feed->GetFeedID(), &sessionIndex))
        {
            if (sessionIndex>=0 && sessionIndex<m_sessionItems.size())
            {
                m_sessionItems[sessionIndex].nickNamePinYin = itera->m_Feed->GetTitlePinYin();

                TNStructRemark stRemark = TNDataCache::GetInstance()->getFriendFeedReMarkWithPY(m_sessionItems[sessionIndex].feedId, m_belongToFeedId);
                if (!stRemark.remark.isEmpty())
                    m_sessionItems[sessionIndex].remark = stRemark.remark;
                if (!stRemark.remarkPy.isEmpty())
                    m_sessionItems[sessionIndex].remarkPinYin = stRemark.remarkPy;
            }
            continue;
        }

        QString pinyin = itera->m_Feed->GetTitlePinYin();
        if (!pinyin.isEmpty())
        {
            TNFriend tnfriend;
            tnfriend.m_avatarURL = itera->m_Feed->GetAvatarID();
            tnfriend.m_belongFeedId = itera->m_belongFeedId;
            tnfriend.m_friendFeedId = itera->m_Feed->GetFeedID();
            tnfriend.m_gender = itera->m_Feed->GetSex();
            tnfriend.m_nickName = itera->m_Feed->GetTitle();
            tnfriend.m_pinYin = itera->m_Feed->GetTitlePinYin();
            tnfriend.m_subTitle = itera->m_Feed->GetSubTile();
            tnfriend.m_tags.append(itera->m_Feed->GetTag());
            tnfriend.m_userId = itera->m_Feed->GetUserID();
            m_feedIdToFriendMap[tnfriend.m_friendFeedId] = tnfriend;
        }
    }
}

void SendFowardSelectContactDialog::copyGroupChatCacheToMap()
{
    if (m_belongToFeedId.isEmpty())
    {
        qInfo() << "[Notice][SendFowardSelectContactDialog] copyGroupChatCacheToMap m_belongMyFeedId is null";
        return;
    }

    QList<TNStructGroupChat> groupChatList;
    TNDataCache::GetInstance()->GetGroupChatCache(groupChatList, m_belongToFeedId);
    if (groupChatList.isEmpty())
    {
        qInfo() << "[Notice][SendFowardSelectContactDialog] copyGroupChatCacheToMap GetGroupChatCache is null";
        return;
    }

    for (auto iter = groupChatList.begin(); iter != groupChatList.end(); iter++)
    {
        int sessionIndex = -1;
        if (shouldExclude(iter->m_groupChatFeed->GetGroupId(), &sessionIndex))
        {
            if (sessionIndex>=0 && sessionIndex<m_sessionItems.size())
                m_sessionItems[sessionIndex].nickNamePinYin = iter->m_groupChatFeed->GetNamePinyin();
            continue;
        }

        ContactModelItem contactItem;
        contactItem.isLetter = false;
        contactItem.nickName = iter->m_groupChatFeed->GetName();
        contactItem.nickNamePinYin = iter->m_groupChatFeed->GetNamePinyin();

        contactItem.feedId = iter->m_groupChatFeed->GetGroupId();
        contactItem.strAvatarURL = iter->m_groupChatFeed->GetHeaderImage();
        m_GroupChatItems.insert(contactItem.nickName, contactItem);
        m_feedIdToGroupChatMap[contactItem.feedId] = *iter;
    }
}

void SendFowardSelectContactDialog::copyColleagueCacheToMap()
{
    if (m_belongToFeedId.isEmpty())
    {
        qInfo() << "[Notice][SendFowardSelectContactDialog] copyColleagueCacheToMap m_belongMyFeedId is null";
        return;
    }
    QList<TNStructCompany> companyList;
    TNDataCache::GetInstance()->GetColleagueCache(companyList, m_belongToFeedId);
    if (companyList.size() == 0)
    {
        qInfo() << "[Notice][SendFowardSelectContactDialog] copyColleagueCacheToMap GetColleagueCache is null";
        return;
    }
    QList<TNStructCompany>::const_iterator itera = companyList.begin();
    for (; itera != companyList.end(); ++itera)
    {
        //无组织架构同事
        QMap<QString, st_FeedPtr> noGroupfeed = itera->m_noGroupfeed;
        QMap<QString, st_FeedPtr>::const_iterator iteraNoGroup = noGroupfeed.begin();
        for (; iteraNoGroup != noGroupfeed.end(); ++iteraNoGroup)
        {
            int sessionIndex = -1;
            if (shouldExclude(iteraNoGroup.value()->GetFeedID(), &sessionIndex))
            {
                if (sessionIndex>=0 && sessionIndex<m_sessionItems.size())
                    m_sessionItems[sessionIndex].nickNamePinYin = iteraNoGroup.value()->GetTitlePinYin();
                continue;
            }

            QString pinyin = iteraNoGroup.value()->GetTitlePinYin();
            if (!pinyin.isEmpty())
            {
                TNFriend colleague;
                colleague.m_userId = iteraNoGroup.value()->GetUserID();
                if (colleague.m_userId != TNUserDataHelper::GetInstance()->_pluginParam->strTnUserID)
                {
                    colleague.m_belongFeedId = itera->m_belongId;
                    colleague.m_avatarURL = iteraNoGroup.value()->GetAvatarID();
                    colleague.m_friendFeedId = iteraNoGroup.value()->GetFeedID();
                    colleague.m_gender = iteraNoGroup.value()->GetSex();
                    colleague.m_nickName = iteraNoGroup.value()->GetTitle();
                    colleague.m_pinYin = iteraNoGroup.value()->GetTitlePinYin();
                    colleague.m_subTitle = iteraNoGroup.value()->GetSubTile();
                    colleague.m_tags.append(iteraNoGroup.value()->GetTag());
                    m_feedIdToFriendMap[colleague.m_friendFeedId] = colleague;
                }
            }
        }
        //有组织架构同事
        QMap<QString, QMultiMap<int, st_FeedPtr>> groupFeed = itera->m_feed;
        QMap<QString, QMultiMap<int, st_FeedPtr>>::const_iterator groupItera = groupFeed.begin();
        for (; groupItera != groupFeed.end(); ++groupItera)
        {
            QMultiMap<int, st_FeedPtr> tempMap = groupItera.value();
            QMultiMap<int, st_FeedPtr>::const_iterator tempItera = tempMap.begin();
            for (; tempItera != tempMap.end(); ++tempItera)
            {
                int sessionIndex = -1;
                if (shouldExclude(tempItera.value()->GetFeedID(), &sessionIndex))
                {
                    if (sessionIndex>=0 && sessionIndex<m_sessionItems.size())
                        m_sessionItems[sessionIndex].nickNamePinYin = tempItera.value()->GetTitlePinYin();
                    continue;
                }

                QString pinyin = tempItera.value()->GetTitlePinYin();
                if (!pinyin.isEmpty())
                {
                    TNFriend colleague;
                    colleague.m_userId = tempItera.value()->GetUserID();
                    if (colleague.m_userId != TNUserDataHelper::GetInstance()->_pluginParam->strTnUserID)
                    {
                        colleague.m_belongFeedId = itera->m_belongId;
                        colleague.m_belongFeedId = itera->m_belongId;
                        colleague.m_avatarURL = tempItera.value()->GetAvatarID();
                        colleague.m_friendFeedId = tempItera.value()->GetFeedID();
                        colleague.m_gender = tempItera.value()->GetSex();
                        colleague.m_nickName = tempItera.value()->GetTitle();
                        colleague.m_pinYin = tempItera.value()->GetTitlePinYin();
                        colleague.m_subTitle = tempItera.value()->GetSubTile();
                        colleague.m_tags.append(tempItera.value()->GetTag());
                        m_feedIdToFriendMap[colleague.m_friendFeedId] = colleague;
                    }
                }
            }
        }
    }
}
