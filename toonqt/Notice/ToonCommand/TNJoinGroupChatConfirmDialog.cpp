#include "TNJoinGroupChatConfirmDialog.h"
#include "ui_TNJoinGroupChatConfirmDialog.h"

#include "TNPathUtil.h"
#include "tncommondealavator.h"
#include "TNHttpCloudApi.h"
#include "TNUserDataHelper.h"
#include "TNNetAvatarDown.h"

TNJoinGroupChatConfirmDialog::TNJoinGroupChatConfirmDialog(const st_FeedPtr &card, st_GroupInfo groupChat, QWidget *parent) :
    /*QDialog*/DropShadowWidget(parent),
    ui(new Ui::TNJoinGroupChatConfirmDialog)
{
    ui->setupUi(this);

    ui->meToolButton->setObjectName("meToolButton");
    ui->meToolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->meToolButton->setIconSize(QSize(40, 40));
    QString elidedText = ui->meToolButton->fontMetrics().elidedText(card->GetTitle(), Qt::ElideMiddle, 90, Qt::TextShowMnemonic);
    ui->meToolButton->setText(elidedText);
    QString myAvatarFileName;
    const QString feedId = card->GetFeedID();
    Cust_Type myCustType = TNCommonDealAvator::getCustomType(feedId);
    if (TNPathUtil::isDownloadedAvatarPhoto(feedId, myAvatarFileName))
    {
        ui->meToolButton->setIcon(TNCommonDealAvator::getTypeQIcon(myAvatarFileName, QSize(40, 40), myCustType));
    }

    ui->groupChatToolButton->setObjectName("groupChatToolButton");
    ui->groupChatToolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->groupChatToolButton->setIconSize(QSize(40, 40));
    QString groupChatName = groupChat.GetName();
    QString groupChatMemberNum = QString::number(groupChat.GetCurrNum()) + tr(QStringLiteral("人").toUtf8().data());
    QString groupChatText = ui->groupChatToolButton->fontMetrics().elidedText(QString("%1(%2)").arg(groupChatName).arg(groupChatMemberNum), Qt::ElideMiddle, 90, Qt::TextShowMnemonic);
    ui->groupChatToolButton->setText(groupChatText);

    QString groupChatId = groupChat.GetGroupId();
    QString avatarFileName = TNPathUtil::getFeedAvatarPath(groupChatId);
    QString strAvatarURL = groupChat.GetHeaderImage();
    asynDownloadAvatar(strAvatarURL, groupChatId, avatarFileName);

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

TNJoinGroupChatConfirmDialog::~TNJoinGroupChatConfirmDialog()
{
    delete ui;
}

void TNJoinGroupChatConfirmDialog::asynDownloadAvatar(const QString& url, const QString& feedID, const QString& file_path)
{
    qInfo() << "[Notice][TNJoinGroupChatConfirmDialog] asynDownloadAvatar, url: " << url << " feedId:" << feedID;
	TNNetAvatarDown::GetInstance()->DownLoadFeedAvatar(feedID, url, TNHttpCloudApi::GetInstance()->GetCloudStoken(TNUserDataHelper::GetInstance()->_pluginParam), this);
}

void TNJoinGroupChatConfirmDialog::onAvatarDownLoadFinish(bool success, QString file_path, QString feedID)
{
    if (success)
    {
        Cust_Type custType = TNCommonDealAvator::getCustomType(feedID);
        ui->groupChatToolButton->setIcon(TNCommonDealAvator::getTypeQIcon(file_path, QSize(40, 40), custType));
    }
}
