#include "TNCreateGroupChatDialog.h"
#include "ui_TNCreateGroupChatDialog.h"

#include "TNUtil.h"
#include "TNDbUtil.h"
#include "TNUserDataHelper.h"
#include "TNDataCache.h"
#include "TNPathUtil.h"
#include "TNMessageBox.h"
#include "TNDefaultPage.h"
#include "TNNetAvatarDown.h"
#include "tncommondealavator.h"
#include "Search/QSearchLineText.h"

#include <QLineEdit>
#include <QHeaderView>

const QSize AvatarSize(30, 30);
const int LettrRowHeight = 24;
const int ContactRowHeight = 44;

TNCreateGroupChatDialog::TNCreateGroupChatDialog(QWidget *parent)
    : DropShadowWidget(parent)
    , ui(new Ui::TNCreateGroupChatDialog)
{
    ui->setupUi(this);

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
    m_searchLineEdit->setPlaceholderText(("搜索联系人"));
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
    pLayout->setContentsMargins(0, 0, 0, 5);
    ui->widget->setLayout(pLayout);
    ui->widget->setMinimumHeight(20);
    connect(m_searchLineEdit, SIGNAL(textChanged(QString)), this, SLOT(slotSearch(QString)));

    m_nullPage = new TNDefaultPage(ui->leftTableView);
    m_nullPage->setObjectName("NULLPageCardCase");

    initialTableViewSettings(ui->myStuffTableView);
    initialTableViewSettings(ui->leftTableView);
    initialTableViewSettings(ui->rightTableView);

    m_stuffContactModel = new TNContactModel();
    m_stuffContactModel->setEnabledBgColor(true);
    m_stuffContactModel->setElidedTextLength(110);
    m_leftContactModel = new TNContactModel();
    m_rightContactModel = new TNContactModel();

    connect(ui->myStuffTableView, SIGNAL(clicked(const QModelIndex &)), SLOT(slotCardItemClicked(const QModelIndex &)));
    connect(ui->leftTableView, SIGNAL(clicked(const QModelIndex &)), SLOT(slotLeftItemClicked(const QModelIndex &)));
    connect(ui->rightTableView, SIGNAL(clicked(const QModelIndex &)), SLOT(slotRightItemClicked(const QModelIndex &)));

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    initialStuffTableView();

    this->setWindowIcon(TOON_ICON);
    this->setWindowTitle(TOON_TITLE);

    m_searchLineEdit->setFocus();
    ui->okButton->setEnabled(false);
}

TNCreateGroupChatDialog::~TNCreateGroupChatDialog()
{
    delete ui;
}

void TNCreateGroupChatDialog::showNullPage(bool visible)
{
    int w = ui->leftTableView->width();
    if (w < 250)
        w = 250;
    int h = ui->leftTableView->height();
    if (h < 358)
        h = 358;
    int x = (w - m_nullPage->width())/2;
    int y = (h - m_nullPage->height())/2;
    m_nullPage->move(x, y);
    m_nullPage->setVisible(visible);
}

void TNCreateGroupChatDialog::initialStuffTableView()
{
    QString currentBelongFeedId = TNDataCache::GetInstance()->GetCurrentMyFeed();
    if (currentBelongFeedId == AVATAR_ALL_FEED)
    {
        QList<st_FeedPtr> myAllStuff;
        TNDataCache::GetInstance()->getMyStuff(myAllStuff);
        QList<ContactModelItem> contacts;
        for (st_FeedPtr aStuff : myAllStuff)
        {
            ContactModelItem contactItem;
            contactItem.isLetter = false;
            contactItem.nickName = aStuff->GetTitle();
            contactItem.nickNamePinYin = aStuff->GetTitlePinYin();
            contactItem.feedId = aStuff->GetFeedID();
            contactItem.btnState = ContactModelItem::InvalidState;

            if (contactItem.feedId.startsWith("o_") && !TNDataCache::GetInstance()->getOrgCommunicationStatus(contactItem.feedId))
                continue;

            contacts.push_back(contactItem);
        }

        m_stuffContactModel->setContactList(contacts);
        ui->myStuffTableView->setModel(m_stuffContactModel);
        ui->myStuffTableView->setColumnWidth(0, 6);
        ui->myStuffTableView->setColumnWidth(1, 156);
        ui->myStuffTableView->setColumnWidth(2, 30);
        ui->myStuffTableView->setObjectName("myStuffWidget");

        // 默认使用自己的第一张名片
        if (m_stuffContactModel->rowCount()>0)
        {
            m_belongToFeedId = m_stuffContactModel->getFeedId(0);
            m_stuffContactModel->updateButtonState(0, ContactModelItem::SelectedState);
        }
    }
    else
    {
        m_belongToFeedId = currentBelongFeedId;
        ui->myStuffCardLabel->hide();
        ui->myStuffTableView->hide();
        this->resize(580, 482);
    }

    Q_ASSERT(!m_belongToFeedId.isEmpty());
    initialTableWidget();
}

void TNCreateGroupChatDialog::initialTableViewSettings(QTableView *tableView)
{
    tableView->setShowGrid(false);
    tableView->setIconSize(AvatarSize);
    tableView->verticalHeader()->setDefaultSectionSize(ContactRowHeight);
    tableView->horizontalHeader()->setVisible(false);
    tableView->verticalHeader()->setVisible(false);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::NoSelection);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableView->setFocusPolicy(Qt::NoFocus);
}

void TNCreateGroupChatDialog::slotLeftItemClicked(const QModelIndex &index)
{
    bool isLetter = m_leftContactModel->data(index, Qt::UserRole + 1).toBool();
    if (isLetter)
    {
        return;
    }

    ContactModelItem::ButtonState oldBtnState = ContactModelItem::ButtonState(m_leftContactModel->data(index, Qt::UserRole + 3).toInt());
    qDebug()<<"oldBtnState="<<oldBtnState;
    if (oldBtnState == ContactModelItem::DisableState)
    {
        return;
    }

    if (oldBtnState == ContactModelItem::NormalState)
    {
        m_leftContactModel->updateButtonState(index.row(), ContactModelItem::SelectedState);
        ContactModelItem aContact = m_leftContactModel->getContact(index);
        aContact.btnState = ContactModelItem::RemovableState;
        m_rightContactModel->appendContact(aContact);
        m_cacheSelectedFriendItems[m_belongToFeedId].append(aContact);
    }
    else if (oldBtnState == ContactModelItem::SelectedState)
    {
        m_leftContactModel->updateButtonState(index.row(), ContactModelItem::NormalState);
        ContactModelItem aContact = m_leftContactModel->getContact(index);
        m_rightContactModel->removeContact(aContact);
        m_cacheSelectedFriendItems[m_belongToFeedId].removeOne(aContact);
    }

    ui->okButton->setEnabled(m_rightContactModel->rowCount()>=2);
}

void TNCreateGroupChatDialog::slotRightItemClicked(const QModelIndex &index)
{
    if (index.column() == 2)
    {
        ContactModelItem aContact = m_rightContactModel->getContact(index);
        int row = m_leftContactModel->getRowByFeedId(aContact.feedId);
        m_leftContactModel->updateButtonState(row, ContactModelItem::NormalState);
        m_rightContactModel->removeContact(aContact);
        m_cacheSelectedFriendItems[m_belongToFeedId].removeOne(aContact);

        ui->okButton->setEnabled(m_rightContactModel->rowCount()>=2);
    }
}

void TNCreateGroupChatDialog::initialTableWidget()
{
    m_friendItems.clear();
    m_feedIdToFriendMap.clear();
    m_leftContactModel->clearModelData();
    m_rightContactModel->clearModelData();

    copyFriendCacheToMap();
    copyColleagueCacheToMap();

    // 排序
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
        contactItem.btnState = isInHistory(contactItem.feedId) ? ContactModelItem::SelectedState : ContactModelItem::NormalState;

        QString pinYin;
        QChar firstLetter;
        if (!contactItem.remarkPinYin.isEmpty())
        {
            pinYin = contactItem.remarkPinYin;
            firstLetter = pinYin.at(0).toUpper();
        }
        else if (!contactItem.nickNamePinYin.isEmpty())
        {
            pinYin = contactItem.nickNamePinYin;
            firstLetter = pinYin.at(0).toUpper();
        }
        else
        {
            qInfo()<<"[Notice][TNCreateGroupChatDialog]pinyin is empty! feedId="<<contactItem.feedId<<" nickName="<<contactItem.nickName;
        }
        if (!firstLetter.isNull())
        {
            if (firstLetter.isLetter())
            {
                m_friendItems[firstLetter].insert(pinYin.toLower(), contactItem);
            }
            else
            {
                m_friendItems[ContactModelItem::wellSymbolLetter()].insert(pinYin.toLower(), contactItem);
            }
        }
    }

    QList<ContactModelItem> wellSymbolContacts;
    QList<ContactModelItem> contacts;
    foreach(const QChar &firstLetter, m_friendItems.keys())
    {
        if (firstLetter == ContactModelItem::wellSymbolLetter())
        {
            wellSymbolContacts.append(ContactModelItem::makeLetterItem(firstLetter));
            foreach(const ContactModelItem &contactItem, m_friendItems.value(firstLetter).values())
            {
                wellSymbolContacts.append(contactItem);
            }
        }
        else
        {
            contacts.append(ContactModelItem::makeLetterItem(firstLetter));
            foreach(const ContactModelItem &contactItem, m_friendItems.value(firstLetter).values())
            {
                contacts.append(contactItem);
            }
        }
    }
    contacts.append(wellSymbolContacts); // 将井号下的联系人添加到最后
    m_leftContactModel->setContactList(contacts);
    ui->leftTableView->setModel(m_leftContactModel);
    ui->leftTableView->setColumnWidth(0, 6);
    ui->leftTableView->setColumnWidth(1, 206);
    ui->leftTableView->setColumnWidth(2, 30);
    ui->leftTableView->setObjectName("unselectWidget");

    for (int i = 0; i < m_leftContactModel->rowCount(); i++)
    {
        if (m_leftContactModel->isLetterItem(i))
            ui->leftTableView->setRowHeight(i, LettrRowHeight);
        else
            ui->leftTableView->setRowHeight(i, ContactRowHeight);
    }

    m_rightContactModel->setContactList(m_cacheSelectedFriendItems[m_belongToFeedId]);
    ui->rightTableView->setModel(m_rightContactModel);
    ui->rightTableView->setColumnWidth(0, 6);
    ui->rightTableView->setColumnWidth(1, 206);
    ui->rightTableView->setColumnWidth(2, 30);
    ui->rightTableView->setObjectName("selectWidget");

    m_nullPage->setTextTitle(("暂无联系人"));
    m_nullPage->setBorderImage(TNVersionInfo::GetNullPageRes_cardcase());
    showNullPage(contacts.isEmpty());
}

bool TNCreateGroupChatDialog::isInHistory(const QString &feedId)
{
    const QList<ContactModelItem> contacts(m_cacheSelectedFriendItems[m_belongToFeedId]);
    foreach (const ContactModelItem &var, contacts)
    {
        if (var.feedId == feedId)
            return true;
    }

    return false;
}

QString TNCreateGroupChatDialog::getBelongFeedId() const
{
    return m_belongToFeedId;
}

QList<TNFriend> TNCreateGroupChatDialog::getSelectedContact() const
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

void TNCreateGroupChatDialog::accept()
{
    QList<TNFriend> selectContacts = getSelectedContact();
    if (selectContacts.size()<2)
    {
        TNMessageBox messageBox(this);
        messageBox.setMsg(("除自己外至少还需要选择两位联系人创建群聊"));
        messageBox.exec();
        return;
    }

    QDialog::accept();
}

void TNCreateGroupChatDialog::slotCardItemClicked(const QModelIndex &index)
{
    ContactModelItem::ButtonState oldBtnState = ContactModelItem::ButtonState(m_stuffContactModel->data(index, Qt::UserRole + 3).toInt());
    qDebug()<<"slotCardItemClicked-oldBtnState="<<oldBtnState;
    if (oldBtnState == ContactModelItem::SelectedState)
    {
        return;
    }

    int selectRow = index.row();
    for (int i = 0; i < m_stuffContactModel->rowCount(); i++)
    {
        if (i == selectRow)
        {
            m_belongToFeedId = m_stuffContactModel->getFeedId(i);
            m_stuffContactModel->updateButtonState(i, ContactModelItem::SelectedState);
        }
        else
        {
            m_stuffContactModel->updateButtonState(i, ContactModelItem::InvalidState);
        }
    }

    initialTableWidget();

    ui->okButton->setEnabled(m_rightContactModel->rowCount()>=2);
}

void TNCreateGroupChatDialog::slotSearch(const QString &text)
{
    if (text.isEmpty())
    {
        m_nullPage->setTextTitle(("暂无联系人"));
        m_nullPage->setBorderImage(TNVersionInfo::GetNullPageRes_cardcase());
        showNullPage(m_leftContactModel->rowCount() == 0);
        for (int i = 0; i < m_leftContactModel->rowCount(); i++)
        {
            ui->leftTableView->setRowHidden(i, false);
        }
    }
    else
    {
        int visibleCount = 0;
        for (int i = 0; i < m_leftContactModel->rowCount(); i++)
        {
            if (m_leftContactModel->isLetterItem(i))
            {
                ui->leftTableView->setRowHidden(i, true);
            }
            else
            {
                if (m_leftContactModel->startsWith(i, text.trimmed()))
                {
                    visibleCount++;
                    ui->leftTableView->setRowHidden(i, false);
                }
                else
                {
                    ui->leftTableView->setRowHidden(i, true);
                }
            }
        }

        m_nullPage->setTextTitle(("没有相关的内容"));
        m_nullPage->setBorderImage(TNVersionInfo::GetNullPageRes_search());
        showNullPage(visibleCount == 0);
    }
}

void TNCreateGroupChatDialog::copyFriendCacheToMap()
{
    if (m_belongToFeedId.isEmpty())
    {
        qInfo() << "[Notice][TNCreateGroupChatDialog] copyFriendCacheToMap m_belongMyFeedId is null";
        return;
    }

    QList<TNStructFriend> friendList;
    TNDataCache::GetInstance()->GetFriendCache(friendList, m_belongToFeedId);
    if (friendList.size() == 0)
    {
        qInfo() << "[Notice][TNCreateGroupChatDialog] copyFriendCacheToMap GetFriendCache is null";
        return;
    }
    QList<TNStructFriend>::const_iterator itera = friendList.begin();
    for (; itera != friendList.end(); ++itera)
    {
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

void TNCreateGroupChatDialog::copyColleagueCacheToMap()
{
    QList<TNStructCompany> companyList;
    TNDataCache::GetInstance()->GetColleagueCache(companyList, "");
    if (companyList.size() == 0)
    {
        qInfo() << "[Notice][TNCreateGroupChatDialog] copyColleagueCacheToMap GetColleagueCache is null";
        return;
    }
    QList<TNStructCompany>::const_iterator itera = companyList.begin();
    for (; itera != companyList.end(); ++itera)
    {
        if (m_belongToFeedId == itera->m_belongId)
        {
            //无组织架构同事
            QMap<QString, st_FeedPtr> noGroupfeed = itera->m_noGroupfeed;
            QMap<QString, st_FeedPtr>::const_iterator iteraNoGroup = noGroupfeed.begin();
            for (; iteraNoGroup != noGroupfeed.end(); ++iteraNoGroup)
            {
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
            QMap<QString, QMultiMap<int, st_FeedPtr>>::const_iterator groupItera =
                    groupFeed.begin();
            for (; groupItera != groupFeed.end(); ++groupItera)
            {
                QMultiMap<int, st_FeedPtr> tempMap = groupItera.value();
                QMultiMap<int, st_FeedPtr>::const_iterator tempItera = tempMap.begin();
                for (; tempItera != tempMap.end(); ++tempItera)
                {
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
}
