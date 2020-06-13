#include "TNRemoveGroupChatMemberDialog.h"
#include "ui_TNRemoveGroupChatMemberDialog.h"

#include "TNUtil.h"
#include "TNDataCache.h"
#include "TNVersionInfo.h"
#include "TNUserDataHelper.h"
#include "TNDataControlServer.h"
#include "TNMessageBox.h"
#include "TNDefaultPage.h"
#include "Search/QSearchLineText.h"
#include <QLineEdit>
#include <QDebug>

TNRemoveGroupChatMemberDialog::TNRemoveGroupChatMemberDialog(QWidget *parent)
    : DropShadowWidget(parent)
    , ui(new Ui::TNRemoveGroupChatMemberDialog)
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
    pLayout->setContentsMargins(0, 5, 0, 5);
    ui->widget->setLayout(pLayout);
    ui->widget->setMinimumHeight(20);
    connect(m_searchLineEdit, SIGNAL(textChanged(QString)), this, SLOT(slotSearch(QString)));

    m_nullPage = new TNDefaultPage(ui->leftTableView);
    m_nullPage->setObjectName("NULLPageCardCase");

    initialTableViewSettings(ui->leftTableView);
    initialTableViewSettings(ui->rightTableView);

    m_leftContactModel = new TNContactModel();
    m_rightContactModel = new TNContactModel();

    connect(ui->leftTableView, SIGNAL(clicked(const QModelIndex &)), SLOT(slotLeftItemClicked(const QModelIndex &)));
    connect(ui->rightTableView, SIGNAL(clicked(const QModelIndex &)), SLOT(slotRightItemClicked(const QModelIndex &)));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    this->setWindowIcon(TOON_ICON);
    this->setWindowTitle(TOON_TITLE);

    m_searchLineEdit->setFocus();
    ui->okButton->setEnabled(false);
}

void TNRemoveGroupChatMemberDialog::setData(const QString &belongToFeedId, const QList<TNFriend> &groupChatMembers)
{
    m_belongToFeedId = belongToFeedId;
    m_groupChatMembers = groupChatMembers;

    initialTableWidget();
}

TNRemoveGroupChatMemberDialog::~TNRemoveGroupChatMemberDialog()
{
    delete ui;
}

void TNRemoveGroupChatMemberDialog::initialTableViewSettings(QTableView *tableView)
{
    tableView->setShowGrid(false);
    tableView->setIconSize(QSize(30, 30));
    //tableView->horizontalHeader()->setDefaultSectionSize(248);
    tableView->verticalHeader()->setDefaultSectionSize(40);
    tableView->horizontalHeader()->setVisible(false);
    tableView->verticalHeader()->setVisible(false);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::NoSelection);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setFocusPolicy(Qt::NoFocus);
}

void TNRemoveGroupChatMemberDialog::slotLeftItemClicked(const QModelIndex &index)
{
    ContactModelItem::ButtonState oldBtnState = ContactModelItem::ButtonState(m_leftContactModel->data(index, Qt::UserRole + 3).toInt());
    qDebug()<<"TNRemoveGroupChatMemberDialog-oldBtnState="<<oldBtnState;
    if (oldBtnState == ContactModelItem::NormalState)
    {
        m_leftContactModel->updateButtonState(index.row(), ContactModelItem::SelectedState);
        ContactModelItem aContact = m_leftContactModel->getContact(index);
        aContact.btnState = ContactModelItem::RemovableState;
        m_rightContactModel->appendContact(aContact);
    }
    else if (oldBtnState == ContactModelItem::SelectedState)
    {
        m_leftContactModel->updateButtonState(index.row(), ContactModelItem::NormalState);
        ContactModelItem aContact = m_leftContactModel->getContact(index);
        m_rightContactModel->removeContact(aContact);
    }

    ui->okButton->setEnabled(m_rightContactModel->rowCount()>0);
}

void TNRemoveGroupChatMemberDialog::slotRightItemClicked(const QModelIndex &index)
{
    if (index.column() == 2)
    {
        ContactModelItem aContact = m_rightContactModel->getContact(index);
        int row = m_leftContactModel->getRowByFeedId(aContact.feedId);
        m_leftContactModel->updateButtonState(row, ContactModelItem::NormalState);
        m_rightContactModel->removeContact(aContact);

        ui->okButton->setEnabled(m_rightContactModel->rowCount()>0);
    }
}

void TNRemoveGroupChatMemberDialog::showNullPage(bool visible)
{
    int x = (ui->leftTableView->width() - m_nullPage->width())/2;
    int y = (ui->leftTableView->height() - m_nullPage->height())/2;
    m_nullPage->move(x, y);
    m_nullPage->setVisible(visible);
}

void TNRemoveGroupChatMemberDialog::initialTableWidget()
{
    QList<ContactModelItem> contacts;
    for (auto iter = m_groupChatMembers.begin(); iter != m_groupChatMembers.end(); iter++)
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
        if (TNDataControlServer::GetInstance()->isMySelf(contactItem.feedId))
            contactItem.btnState = ContactModelItem::InvalidState;
        else
            contactItem.btnState = ContactModelItem::NormalState;

        contacts.push_back(contactItem);
    }

    m_leftContactModel->setContactList(contacts);
    ui->leftTableView->setModel(m_leftContactModel);
    ui->leftTableView->setColumnWidth(0, 6);
    ui->leftTableView->setColumnWidth(1, 206);
    ui->leftTableView->setColumnWidth(2, 30);

    ui->rightTableView->setModel(m_rightContactModel);
    ui->rightTableView->setColumnWidth(0, 6);
    ui->rightTableView->setColumnWidth(1, 206);
    ui->rightTableView->setColumnWidth(2, 30);

    ui->leftTableView->setObjectName("unselectWidget");
    ui->rightTableView->setObjectName("selectWidget");

    m_nullPage->setTextTitle(("暂无联系人"));
    m_nullPage->setBorderImage(TNVersionInfo::GetNullPageRes_cardcase());
    showNullPage(contacts.isEmpty());
}

TNFriend TNRemoveGroupChatMemberDialog::getGroupChatOwner() const
{
    Q_ASSERT(!m_groupChatMembers.isEmpty());
    return m_groupChatMembers.first(); // 群主在首位
}

QList<TNFriend> TNRemoveGroupChatMemberDialog::getSelectedContact() const
{
    QList<TNFriend> selectContacts;
    for (int i = 0; i < m_rightContactModel->rowCount(); i++)
    {
        QString feedId = m_rightContactModel->getFeedId(i);
        selectContacts.append(getFriendEntity(feedId));
    }

    qInfo()<<"[Notice][TNRemoveGroupChatMemberDialog]getSelectedContact-selectContacts.size="<<selectContacts.size();
    return selectContacts;
}

TNFriend TNRemoveGroupChatMemberDialog::getFriendEntity(const QString &feedId) const
{
    for (auto iter = m_groupChatMembers.begin(); iter != m_groupChatMembers.end(); iter++)
    {
        if (feedId == iter->m_friendFeedId)
            return *iter;
    }

    Q_ASSERT("never come to here!");
    qInfo()<<"[Notice][TNRemoveGroupChatMemberDialog]getFriendEntity-error! There no find member. feedId="<<feedId;
    return TNFriend();
}

void TNRemoveGroupChatMemberDialog::accept()
{
    QList<TNFriend> selectContacts = getSelectedContact();
    if (selectContacts.isEmpty())
    {
        return;
    }

    QDialog::accept();
}

void TNRemoveGroupChatMemberDialog::slotSearch(const QString &text)
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
