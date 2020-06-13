#include "TNChooseCardDialog.h"
#include "ui_TNChooseCardDialog.h"

#include "TNPathUtil.h"
#include "TNDataCache.h"
#include "tncommondealavator.h"
#include "TNHttpCloudApi.h"
#include "TNUserDataHelper.h"
#include "TNNetAvatarDown.h"

#include <QTextCursor>
#include <QtMath>
#include <QTimer>

TNChooseCardDialog::TNChooseCardDialog(bool canCancel, QWidget *parent) :
    /*QDialog*/DropShadowWidget(parent),
    ui(new Ui::TNChooseCardDialog)
{
    ui->setupUi(this);

    m_myAllStuff.clear();
    TNDataCache::GetInstance()->getMyStuff(m_myAllStuff);
    Q_ASSERT(m_myAllStuff.size()>=1);

    m_expiredTipLabel = new QPushButton(tr(QStringLiteral("好友申请失效了哟 重新交换吧").toUtf8().data()), this);
    m_expiredTipLabel->setObjectName("expiredTipLabel");
    m_expiredTipLabel->setFixedWidth(240);
    m_expiredTipLabel->setFlat(true);
    m_expiredTipLabel->setVisible(false);

    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(OnTimerSlot()));
    m_pTimer->start(3*1000);

    connect(ui->commentTextEdit, SIGNAL(textChanged()), this, SLOT(slotMaxLength()));
    setCommentTextEditVisible(false);
    ui->commentTextEdit->setPlaceholderText(tr(QStringLiteral("想要交换名片").toUtf8().data()));
    ui->cancelButton->setVisible(false);
    initialTableWidget();

    connect(m_expiredTipLabel, SIGNAL(clicked()), this, SLOT(slotClickedExpiredTipLabel()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
    if (canCancel)
    {
        ui->cancelButton->setVisible(true);
        connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    }
}

TNChooseCardDialog::~TNChooseCardDialog()
{
    delete ui;
}

void TNChooseCardDialog::setTitleLabelText(const QString &text)
{
	ui->chooseCardTitleLabel->setText(text);
}

void TNChooseCardDialog::setCommentTextEditVisible(bool visible)
{
    ui->commentLabel->setVisible(visible);
    ui->commentTextEdit->setVisible(visible);
    if (visible)
    {
        m_expiredTipLabel->move(80, 220);
        m_expiredTipLabel->setVisible(true);
        m_expiredTipLabel->raise();
        this->resize(400, 500);
    }
    else
    {
        this->resize(360, 328);
    }
}

void TNChooseCardDialog::slotClickedExpiredTipLabel()
{
    m_expiredTipLabel->setVisible(false);
}

void TNChooseCardDialog::OnTimerSlot()
{
    m_expiredTipLabel->setVisible(false);
}

void TNChooseCardDialog::setChooseCardLabelText(const QString &text)
{
    ui->chooseCardLabel->setText(text);
}

QString TNChooseCardDialog::getComment() const
{
    return ui->commentTextEdit->toPlainText();
}

st_FeedPtr TNChooseCardDialog::getCard() const
{
    foreach(st_FeedPtr card, m_myAllStuff)
    {
        if (card->GetFeedID() == m_currentCardFeedId)
            return card;
    }

    Q_ASSERT("!never come to here");
    return st_FeedPtr();
}

QString TNChooseCardDialog::getCardFeedId() const
{
    return m_currentCardFeedId;
}

void TNChooseCardDialog::accept()
{
    if (m_currentCardFeedId.isEmpty())
    {
        return;
    }

    QDialog::accept();
}

void TNChooseCardDialog::slotMaxLength()
{
    const int maxLength = 50;
    QString strText = ui->commentTextEdit->toPlainText();
    int length = strText.count();
    if(length > maxLength)
    {
        int position = ui->commentTextEdit->textCursor().position();
        strText.remove(position-(length-maxLength), length-maxLength);
        ui->commentTextEdit->setText(strText);

        QTextCursor cursor = ui->commentTextEdit->textCursor();
        cursor.setPosition(position-(length-maxLength));
        ui->commentTextEdit->setTextCursor(cursor);
    }
}

void TNChooseCardDialog::initialTableWidget()
{
    ui->cardTableWidget->setShowGrid(false);
    ui->cardTableWidget->setFixedSize(352,182);
    ui->cardTableWidget->horizontalHeader()->setVisible(false);
    ui->cardTableWidget->verticalHeader()->setVisible(false);
    ui->cardTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->cardTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->cardTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->cardTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->cardTableWidget->setFocusPolicy(Qt::NoFocus);

    int colNum = 5;
    int rowNum = qCeil(m_myAllStuff.size() / double(colNum));
    if (rowNum>1)
        this->setMinimumHeight(328);

    ui->cardTableWidget->setRowCount(rowNum);
    ui->cardTableWidget->setColumnCount(colNum);
    m_feedIdToButtonMap.clear();
    for (int iRow = 0; iRow < rowNum; iRow++)
    {
        for (int iCol = 0; iCol < colNum; iCol++)
        {
            int index = iRow*colNum + iCol;
            if (index < 0 || index >= m_myAllStuff.size())
                continue;

            CheckToolButton *cardButton = new CheckToolButton();
            cardButton->setObjectName("cardButton");
            cardButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            cardButton->setIconSize(QSize(40, 40));
            QString elidedText = cardButton->fontMetrics().elidedText(m_myAllStuff.at(index)->GetTitle(), Qt::ElideMiddle, 60, Qt::TextShowMnemonic);
            cardButton->setText(elidedText);
            connect(cardButton, SIGNAL(clicked()), this, SLOT(slotChooseCard()));

            QString feedID = m_myAllStuff.at(index)->GetFeedID();
            m_feedIdToButtonMap[feedID] = cardButton; // 记录用于异步更新头像
            if (index == 0)
            {
                cardButton->setChooseFlag(true);
                m_currentCardFeedId = feedID;
            }

            QString avatarFileName;
            Cust_Type custType = TNCommonDealAvator::getCustomType(feedID);
            if (TNPathUtil::isDownloadedAvatarPhoto(feedID, avatarFileName))
            {
                cardButton->setIcon(TNCommonDealAvator::getTypeQIcon(avatarFileName, QSize(40, 40), custType));
            }
            else
            {
                avatarFileName = (":/Resources/toolWidget/defaultNullAvatar.png");
                cardButton->setIcon(TNCommonDealAvator::getTypeQIcon(avatarFileName, QSize(40, 40), custType));

                QString strAvatarURL = m_myAllStuff.at(index)->GetAvatarID();
                asynDownloadAvatar(strAvatarURL, feedID, avatarFileName);
            }

            ui->cardTableWidget->setCellWidget(iRow, iCol, cardButton);
            ui->cardTableWidget->setColumnWidth(iCol, 70);
        }
        ui->cardTableWidget->setRowHeight(iRow, 90);
    }
}

void TNChooseCardDialog::slotChooseCard()
{
    CheckToolButton *cardButton = qobject_cast<CheckToolButton *>(sender());
    if (cardButton == nullptr)
        return;

    cardButton->setChooseFlag(true);
    m_currentCardFeedId = m_feedIdToButtonMap.key(cardButton);
    foreach(const QString &feedId, m_feedIdToButtonMap.keys())
    {
        CheckToolButton *curCardButton = m_feedIdToButtonMap.value(feedId);
        if (curCardButton && (curCardButton != cardButton))
        {
            curCardButton->setChooseFlag(false);
        }
    }
}

void TNChooseCardDialog::asynDownloadAvatar(const QString& url, const QString& feedID, const QString& file_path)
{
	qDebug() << "[TNMVD][TNChooseCardDialog] asynDownloadAvatar, url: " << url << " feedId:" << feedID;
	bool isOrigin = false;
	if (feedID.startsWith("gc_"))
		isOrigin = true;
	TNNetAvatarDown::GetInstance()->DownLoadFeedAvatar(feedID, url, TNHttpCloudApi::GetInstance()->GetCloudStoken(TNUserDataHelper::GetInstance()->_pluginParam), this, isOrigin);
}

void TNChooseCardDialog::onAvatarDownLoadFinish(bool success, QString file_path, QString feedID)
{
    if (success)
    {
        if (m_feedIdToButtonMap.contains(feedID))
        {
            Cust_Type custType = TNCommonDealAvator::getCustomType(feedID);
            m_feedIdToButtonMap[feedID]->setIcon(TNCommonDealAvator::getTypeQIcon(file_path, QSize(40, 40), custType));
        }
    }
}
