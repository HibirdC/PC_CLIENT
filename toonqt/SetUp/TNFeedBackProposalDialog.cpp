#include "TNFeedBackProposalDialog.h"
#include "ui_TNFeedBackProposalDialog.h"

#include <QJsonObject>
#include <QTimer>
#include <QJsonArray>

#include "TNHttpFeedBack.h"
#include "TNDataCache.h"
#include "TNUserDataHelper.h"
#include "TNVersionInfo.h"

#define FEEDBACK_LINEEDITMAXLENGTH 150
TNFeedBackProposalDialog::TNFeedBackProposalDialog(QWidget *parent) :
    /*QDialog*/DropShadowWidget(parent),
    ui(new Ui::TNFeedBackProposalDialog)
{
    ui->setupUi(this);

    m_httpFeedBack = std::make_shared<TNHttpFeedBack>();
    m_httpGetListCard = std::make_shared<TNHttpGetListCard>();

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->dialogCloseButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->feedBackTextEdit, SIGNAL(textChanged()), this, SLOT(onMaxLength()));

    this->setWindowFlags(Qt::FramelessWindowHint);

    this->setWindowIcon(TOON_ICON);
    this->setWindowTitle(TOON_TITLE);
}

TNFeedBackProposalDialog::~TNFeedBackProposalDialog()
{
    delete ui;
}

void TNFeedBackProposalDialog::accept()
{
    QString issue_type = "ProductUseage";
    QString issue_descrition = getProposalContent();
    if (issue_descrition.isEmpty())
        return;

    st_FeedPtr selfFeed = TNDataCache::GetInstance()->getMyFirstPersonalCard();
    if (selfFeed == nullptr)
        return;

    QString feedid = selfFeed->GetFeedID();
    QString phone_num = TNUserDataHelper::GetInstance()->_pluginParam->strMobile;

    ui->okButton->setDisabled(true);
    QEventLoop loop;
    
    auto getListCardFinished = [&](bool success, QJsonObject json)
    {
        QString debugText = QJsonDocument(json).toJson();
        qInfo()<<"TNFeedBackProposalDialog::getListCardFinished-debugText="<<debugText;
        QJsonArray jsonArray = json.value("data").toArray();
        Q_ASSERT(jsonArray.size() == 1);
        if (jsonArray.size() == 1)
        {
            QString title = jsonArray.at(0).toObject().value("title").toString();
            QString card_num = jsonArray.at(0).toObject().value("cardNumber").toString();
            //qInfo()<<"TNFeedBackProposalDialog::getListCardFinished-title="<<title<<" card_num="<<card_num;
            m_httpFeedBack->FeedBack([&](bool success, QJsonObject jsonObject)
            {
                //无论是否成功，均不提示
                loop.quit();
            },
            TNUserDataHelper::GetInstance()->_pluginParam,
            title,
            issue_type,
            issue_descrition,
            card_num,
            phone_num
            );
        }
    };

    //取得名片号
    m_httpGetListCard->GetJson(getListCardFinished, TNUserDataHelper::GetInstance()->_pluginParam, QStringList()<<feedid);

    QTimer::singleShot(3000, &loop, SLOT(quit()));
    loop.exec();
    ui->okButton->setDisabled(false);
    QDialog::accept();
}

QString TNFeedBackProposalDialog::getProposalContent() const
{
    return ui->feedBackTextEdit->toPlainText();
}

void TNFeedBackProposalDialog::onMaxLength()
{
    QString strText = ui->feedBackTextEdit->toPlainText();
    int length = strText.count();
    if (length > FEEDBACK_LINEEDITMAXLENGTH)
    {
        int position = ui->feedBackTextEdit->textCursor().position();
        strText.remove(position - (length - FEEDBACK_LINEEDITMAXLENGTH), length - FEEDBACK_LINEEDITMAXLENGTH);
        ui->feedBackTextEdit->setPlainText(strText);
        QTextCursor cursor = ui->feedBackTextEdit->textCursor();
        cursor.setPosition(position - (length - FEEDBACK_LINEEDITMAXLENGTH));
        ui->feedBackTextEdit->setTextCursor(cursor);
    }
}
