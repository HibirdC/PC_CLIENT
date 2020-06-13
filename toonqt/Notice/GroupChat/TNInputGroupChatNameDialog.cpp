#include "TNInputGroupChatNameDialog.h"
#include "ui_TNInputGroupChatNameDialog.h"
#include "TNSettingData.h"
#include "TNMessageBox.h"
#include "TNVersionInfo.h"
TNInputGroupChatNameDialog::TNInputGroupChatNameDialog(const QString &groupChatName, QWidget *parent) :
/*QDialog*/DropShadowWidget(parent),
    ui(new Ui::TNInputGroupChatNameDialog)
{
    ui->setupUi(this);

	ui->groupNameOkButton->setFocus();
	ui->groupNameOkButton->setDefault(true);

    ui->groupChatLineEdit->setContextMenuPolicy(Qt::NoContextMenu);

	connect(ui->groupChatLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(slotCheckNameLength(const QString &)));
    if (groupChatName.isEmpty())
    {
        ui->confirmTitleLabel->setText(tr((QStringLiteral("修改群聊名称")).toUtf8().data()));
        ui->groupChatLineEdit->setPlaceholderText(tr(QString(QStringLiteral("请输入修改后的群名称")).toUtf8().data()));
        ui->groupNameOkButton->setEnabled(false);
        ui->groupNameOkButton->setStyleSheet("#groupNameOkButton{background: #F8F8F8;border:1px solid #EBEDF0;color:#8E8E93;}");
    }
    else
    {
        ui->confirmTitleLabel->setText(tr(QString(QStringLiteral("群聊名称")).toUtf8().data()));
        ui->groupChatLineEdit->setText(groupChatName);
        ui->groupChatLineEdit->selectAll();
    }

	connect(ui->dialogCloseButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui->groupNameOkButton, SIGNAL(clicked()), this, SLOT(accept()));

	// ui->dialogCloseButton->setText(QString::null);
	this->setWindowFlags(Qt::FramelessWindowHint);

    this->setWindowIcon(TOON_ICON);
    this->setWindowTitle(TOON_TITLE);
}

TNInputGroupChatNameDialog::~TNInputGroupChatNameDialog()
{
    delete ui;
}

QString TNInputGroupChatNameDialog::getGroupChatName() const
{
    return ui->groupChatLineEdit->text().trimmed();
}

void TNInputGroupChatNameDialog::accept()
{
    if (!validateParameters())
    {
        return;
    }

    QDialog::accept();
}

void TNInputGroupChatNameDialog::slotCheckNameLength(const QString &text)
{
    if (text.trimmed().isEmpty())
	{
		ui->groupNameOkButton->setEnabled(false);
		ui->groupNameOkButton->setStyleSheet("#groupNameOkButton{background: #F8F8F8;border:1px solid #EBEDF0;color:#8E8E93;}");
	}
	else
	{
		ui->groupNameOkButton->setEnabled(true);
		QString themeStyle;
		if(!TNVersionInfo::IsBaseToonVersion())
			themeStyle = QString("#groupNameOkButton {background-color:#DF3031;border:1px solid #DF3031;color:#ffffff;}");
        else
            themeStyle = QString("#groupNameOkButton {background-color: %1;border:1px solid %1;color:#ffffff;}").arg(TNSettingData::instance()->GetCurrentThemeSkin());
        ui->groupNameOkButton->setStyleSheet(themeStyle);
	}
}

bool TNInputGroupChatNameDialog::validateParameters()
{
	const QString groupChatName = getGroupChatName();
	if (groupChatName.isEmpty())
    {
        TNMessageBox messageBox(this);
        messageBox.setMsg(tr(QString(QStringLiteral("无效的群聊名称")).toUtf8().data()));
        messageBox.exec();
        return false;
    }
	if (existInDB(groupChatName))
    {
        return false;
    }

    return true;
}

bool TNInputGroupChatNameDialog::existInDB(const QString &groupChatName)
{
    return false;
}
