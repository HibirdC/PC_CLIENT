#include <QJsonObject>
#include <QJsonArray>
#include <QProcess>

#include "Common.h"
#include "TNAboutUsWidget.h"
#include "TNVersionInfo.h"
#include "TNFeedBackProposalDialog.h"
#include "TNHttpApi.h"
#include "TNPathUtil.h"
#include "TNHttpUpdateVersion.h"
#include "LocalStorageCommon.h"
#include "TNDataControlServer.h"
#include "TNPromptSignLabel.h"
#include "TNUpgradeMangement.h"
#include "TNSettingData.h"
#include "tnnotifycenter.h"
#include "common_global.h"
#define TOON_CLIENT ""
TNAboutUsWidget::TNAboutUsWidget(TNPluginParamPtr pluginParam, QWidget *parent)
	: QWidget(parent)
	, _pluginParam(pluginParam)
    , _upgradePromptLabel(nullptr)
{
	ui.setupUi(this);
	ui.aboutUsLogoLabel->setText(QString::null);
    ui.aboutUsVersionLabel->setText(QString("%1(Build %2)").arg(TNVersionInfo::appVersion()).arg(TNVersionInfo::buildNo()));
    ui.aboutUsSoftNameLabel->setText(TOON_TITLE);

	connect(ui.aboutUsCheckUpdateButton, SIGNAL(clicked()), this, SLOT(slotCheckUpdateButtonDialog()));
	connect(ui.aboutUsFeedBackButton, SIGNAL(clicked()), this, SLOT(slotFeedBackProposalDialog()));
	ui.aboutUsCompanyLabel->setText(APP_COPYRIGHT);
    TNNotifyCenter::instance()->connectNotifyCheckVersionFinished(this);
    if (!TNSettingData::instance()->isNewestVersion())
    {
        _upgradePromptLabel = new TNPromptSignLabel(ui.aboutUsCheckUpdateButton, TNPromptSignLabel::TopRight);
    }
}

TNAboutUsWidget::~TNAboutUsWidget()
{

}

void TNAboutUsWidget::slotCheckUpdateButtonDialog()
{
    ui.aboutUsCheckUpdateButton->setEnabled(false);
    TNUpgradeMangement::instance()->checkNewVersion(_pluginParam, TNUpgradeMangement::ctUser);
    ui.aboutUsCheckUpdateButton->setEnabled(true);
}

void TNAboutUsWidget::slotFeedBackProposalDialog()
{
	TNFeedBackProposalDialog *feedBackProposalDlg = new TNFeedBackProposalDialog();
	feedBackProposalDlg->setObjectName("feedBackProposalDlg");
	//feedBackProposalDlg->setAttribute(Qt::WA_DeleteOnClose);
	if (feedBackProposalDlg->exec() == QDialog::Accepted)
	{

	}

	delete feedBackProposalDlg;
	feedBackProposalDlg = NULL;
}

void TNAboutUsWidget::on_notifyCheckVersionFinished(
    bool isNeedUpgrade,
    bool isForceUpgrade,
    QString downLoadURL,
    int nCheckType,
    QString versionDecs
    )
{
    if (nullptr == _upgradePromptLabel)
    {
        if (isNeedUpgrade)
        {
            _upgradePromptLabel = new TNPromptSignLabel(ui.aboutUsCheckUpdateButton, TNPromptSignLabel::TopRight);
            _upgradePromptLabel->relocate();
        }
    }
}
