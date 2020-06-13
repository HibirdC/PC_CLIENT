#include <QJsonObject>
#include "TNExitLoginWidget.h"

#include "TNUtil.h"
#include "TNExitLoginConfirmDialog.h"
#include "TNNetDetecter.h"
#include "tnnotifycenter.h"
#include "TNHttpApi.h"
#include "TNDataStatistics.h"

TNExitLoginWidget::TNExitLoginWidget(TNPluginParamPtr pluginParam, QWidget *parent)
	: QWidget(parent)
	, _pluginParam(pluginParam)
    , _netStatus(NetStatusConnect)
{
	ui.setupUi(this);

	ui.exitAvatarLabel->setText(QString::null);
	ui.exitUserNameLabel->setText(_pluginParam->strMobile);
	connect(ui.exitPushButton, SIGNAL(clicked()), this, SLOT(slotExitLoginDialog()));
    TNNotifyCenter::instance()->connectNotifyNetStatus(this);
}

TNExitLoginWidget::~TNExitLoginWidget()
{

}

void TNExitLoginWidget::on_notifyNetStatus(int netstatus)
{
    _netStatus = netstatus;
}

void TNExitLoginWidget::slotExitLoginDialog()
{
	TNExitLoginConfirmDialog *exitConfirmDialog = new TNExitLoginConfirmDialog(0);
    TNUtil::moveCenterInMainWidget(exitConfirmDialog);
	exitConfirmDialog->setObjectName("exitConfirmDialog");
	exitConfirmDialog->setContentsMargins(0, 0, 0, 0);
	exitConfirmDialog->setAttribute(Qt::WA_DeleteOnClose);
	if (exitConfirmDialog->exec() == QDialog::Accepted)
	{ 
        TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_Setup_Logout_OK, _pluginParam);
		TNHttpApiPtr _httpExitLogin = std::make_shared<TNHttpApi>();
		st_LoginWithPasswordHttpBody body;
        body.strDeviceName  = QSysInfo::productType();
        body.strDeviceToken = _pluginParam->strMacAddress;
		body.strIdfa = "";
		body.strImei = "";
		body.strMacAddress = _pluginParam->strMacAddress;
		body.strUuid = _pluginParam->strMacAddress;

		QJsonObject object;
        int nRet = 0;
        if (_netStatus == NetStatusConnect)
        {
            nRet = _httpExitLogin->Logout(_pluginParam, body, object);
        }
		if (nRet == 0)
		{
			emit SendQuitSignal();
		} 
		else
		{
		}
	}
    else
    {
        TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_Setup_Logout_Cancel, _pluginParam);
    }
}
