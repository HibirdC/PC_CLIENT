#include "TNShortCutSettingDialog.h"
#include "ui_TNShortCutSettingDialog.h"

#include "TNShortCutKeyTextMap.h"
#include "TNVersionInfo.h"
#include <QDebug>

TNShortCutSettingDialog::TNShortCutSettingDialog(const QString &shortCutText, QWidget *parent) :
    /*QDialog*/DropShadowWidget(parent),
    ui(new Ui::TNShortCutSettingDialog)
{
    ui->setupUi(this);

    m_screenHotKey = TNShortCutKeyTextMap::getTextByUiText(shortCutText);
    if (m_screenHotKey.isEmpty())
    {
        ui->tipsLabel->setText(tr(QString(QStringLiteral("无")).toUtf8().data()));
    }
    else
    {
        ui->tipsLabel->setText(shortCutText);
    }

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowIcon(TOON_ICON);
    this->setWindowTitle(TOON_TITLE);
}

TNShortCutSettingDialog::~TNShortCutSettingDialog()
{
    delete ui;
}

QString TNShortCutSettingDialog::getShortCutText() const
{
    return m_screenHotKey;
}

void TNShortCutSettingDialog::keyPressEvent(QKeyEvent *event)
{
    DropShadowWidget::keyPressEvent(event);
    qInfo()<<"[SetUp][TNShortCutSettingDialog]event->key="<<event->key()<<" event->modifiers="<<event->modifiers()<<" keyPressEvent="<<event->text();
    QString mkeyText = TNShortCutKeyTextMap::getTextByMKey(event->modifiers());
    QString keyText = TNShortCutKeyTextMap::getTextByKey(event->key());

    if (mkeyText.isEmpty() || keyText.isEmpty())
    {
        m_screenHotKey = QString::null;
        ui->tipsLabel->setText(tr(QString(QStringLiteral("无")).toUtf8().data()));
    }
    else
    {
        m_screenHotKey = mkeyText + "+" + keyText;
        QString uiTextByText = TNShortCutKeyTextMap::getUiTextByText(m_screenHotKey);
        ui->tipsLabel->setText(uiTextByText);
    }
}
