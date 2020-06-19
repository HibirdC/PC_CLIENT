#include "TNLoginWidget.h"
#include "ui_TNLoginWidget.h"

#include <QString>
#include <QComboBox>
#include <QApplication>
#include <QtConcurrent/QtConcurrent> 

#ifdef Q_OS_WIN
#include <Windows.h>
#endif

#include "ui_LoginForm.h"
#include "ui_NewDeviceLoginForm.h"
#include "ui_ResetPasswordForm01.h"
#include "ui_ResetPasswordForm02.h"
#include "ui_ResetPasswordForm03.h"
#include "ui_QRCodeScanForm01.h"
#include "ui_QRCodeScanForm02.h"

#include "LocalStorageCommon.h"
#include "TNJoinStuff.h"
#include "TNDataControlServer.h"
#include "TNIMCoreClient.h"
#include "TNPathUtil.h"
#include "TNCheckUpdateInfoDialog.h"
#include "TNHttpUpdateVersion.h"
#include "TNSettingData.h"
#include "TNConfig.h"
#include "TNUpgradeMangement.h"
#include "tnnotifycenter.h"
#include "TNDataCache.h"
#include "TNDataStatistics.h"
#include "TNUtil.h"
#include "TNVersionInfo.h"
#include "TNHttpCloudApi.h"
#include "TNToonCommandManager.h"
#include "TNLoginUtil.h"
#include "TNUserDataUtil.h"
#include "TNIdCodeTimer.h"
#include "TNOpForgetPsdTipDialog.h"

TNLoginWidget::TNLoginWidget(bool isAutoLogin, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TNLoginWidget)
    , loginFormUi(new Ui::LoginForm)
    , resetPsdForm01Ui(new Ui::ResetPasswordForm01)
    , resetPsdForm02Ui(new Ui::ResetPasswordForm02)
    , resetPsdForm03Ui(new Ui::ResetPasswordForm03)
    , qrCodeForm01Ui(new Ui::QRCodeScanForm01)
    , qrCodeForm02Ui(new Ui::QRCodeScanForm02)
    , _bottomMovie(NULL)
    , _scanLogin(NULL)
    , _bIsFirstLogin(false)
    , _bIsEnableAutoLogin(isAutoLogin)
    , _bInitNetRoute(false)
    , _userInfo(nullptr)
{
    ui->setupUi(this);

    _pluginParam = std::make_shared<PluginParam>();
	
    InitRouterList();

    initMainForm();

    initLoginForm(); // 0

    initResetPasswordForm01(); // 1
    initResetPasswordForm02(); // 2
    initResetPasswordForm03(); // 3
    initQRCodeScanForm01();    // 5
    initQRCodeScanForm02();    // 6

    InitUiDataIfAutoLogin();

    loginFormUi->mobileLineEdit->installEventFilter(this);
    loginFormUi->passwordLineEdit->installEventFilter(this);

    resetPsdForm01Ui->mobileLineEdit->installEventFilter(this);
    resetPsdForm01Ui->idCodeLineEdit->installEventFilter(this);

    resetPsdForm02Ui->passwordLineEdit_1->installEventFilter(this);
    resetPsdForm02Ui->passwordLineEdit_2->installEventFilter(this);
}

TNLoginWidget::~TNLoginWidget()
{
    if (_bottomMovie)
    {
        _bottomMovie->stop();
        delete _bottomMovie;
        _bottomMovie = NULL;
    }
    _scanLogin->deleteLater();

    delete ui;
}

QPushButton* TNLoginWidget::GetMinBtn()
{
    return ui->btn_min;
}

QPushButton* TNLoginWidget::GetCloseBtn()
{
    return ui->btn_close;
}
int TNLoginWidget::getCurrentPage()
{
	return ui->stackedWidget->currentIndex();
}
void TNLoginWidget::exeAutoLogin(st_LoginUserPtr loginUser)
{
    loginFormUi->loginPushButton->setText(("登录中"));
    loginFormUi->loginPushButton->setEnabled(false);
    QString teleCode;
    QString mobile;
    QString errorContent;
    if (TNLoginUtil::parseMobileFromLoginUser(loginUser, &teleCode, &mobile, &errorContent))
    {
        QString strPassword;
        TNLoginUtil::TokenCode(loginUser->GetToken(), strPassword, loginUser->GetLogState(), 1);
        LoginOKByPassword(mobile, strPassword, true);
    }
    else
    {
        ShowMessage(errorContent);
    }
    loginFormUi->loginPushButton->setEnabled(true);
    loginFormUi->loginPushButton->setText(("登录"));
}

void TNLoginWidget::slotExeAutoLogin()
{
#ifdef DAOTOON
    return;
#endif
	if ((_bIsEnableAutoLogin && _userInfo && (_userInfo->GetCheckState() == 1))
		||TNConfig::instance()->getFixedErrStatus()!= 0) // 如果上次勾选了[自动登录]或者从修复模式进来
	{
		exeAutoLogin(_userInfo);
	}
}

void TNLoginWidget::LoginThreadStart()
{
    _mutex.lock();
    connect(this, SIGNAL(LoginSignal()), this, SLOT(slotExeAutoLogin()));
    emit LoginSignal();
    _mutex.unlock();

    //允许自动登录时（即第一次登录时，要检查更新)
    if (_bIsEnableAutoLogin)
    {
        checkUpgrade();
    }
}

void TNLoginWidget::initMainForm()
{
#ifndef Q_OS_MAC
    ui->btn_min->setObjectName("loginMin");
    ui->btn_close->setObjectName("loginClose");
    ui->btn_min->setGeometry(268, 0, 18, 18);
    ui->btn_close->setGeometry(286, 0, 18, 18);
#else
    ui->btn_min->setObjectName("macMin");
    ui->btn_close->setObjectName("macClose");
    ui->btn_min->setGeometry(40, 10, 18, 18);
    ui->btn_close->setGeometry(20, 10, 18, 18);
    ui->btn_qrcode->setGeometry(284,10, 16, 16);
#endif
    ui->btn_min->setToolTip(("最小化"));
    ui->btn_close->setToolTip(("关闭"));


    _bottomMovie = new QMovie(TNVersionInfo::GetLoginWaveRes());
    _bottomMovie->setScaledSize(QSize(298, 46));
    ui->label_bottom->setGeometry(11, 365, 298, 46);
    ui->label_bottom->setMovie(_bottomMovie);
    _bottomMovie->start();

    ui->btn_qrcode->setChecked(false);
    ui->btn_qrcode->setFocusPolicy(Qt::NoFocus);
    ui->btn_min->setFocusPolicy(Qt::NoFocus);
    ui->btn_close->setFocusPolicy(Qt::NoFocus);

    connect(ui->btn_qrcode, SIGNAL(clicked()), this, SLOT(slotOnClickQRCodeScan()));
}

void TNLoginWidget::InitUiDataIfAutoLogin()
{
    //if (_bIsEnableAutoLogin)
    {
        TableBaseVec tableBaseVec;
        TNDataControlServer::GetInstance()->GetLatestUserFromCommonDb(tableBaseVec);
        if (tableBaseVec.size() == 1)
        {
            st_LoginUserPtr loginUser = std::dynamic_pointer_cast<st_LoginUser>(tableBaseVec[0]);
            if ((loginUser->GetCheckState() == 1) || (loginUser->GetPwdState() == 1)) // 如果上次勾选了[自动登录]或[记住密码]
            {
                _userInfo = loginUser;

                QString teleCode;
                QString mobile;
                QString errorContent;
                if (TNLoginUtil::parseMobileFromLoginUser(loginUser, &teleCode, &mobile, &errorContent))
                {
                    loginFormUi->mobileLineEdit->setText(mobile);
                    loginFormUi->passwordLineEdit->setText("*************");
                    if (loginUser->GetCheckState() == 1)
                    {
                        if (_bIsEnableAutoLogin)
                            loginFormUi->autoLoginCheckBox->setChecked(true);
                        else
                            loginFormUi->rememberPsdCheckBox->setChecked(true);
                    }
                    else if(loginUser->GetPwdState() == 1)
                    {
                        loginFormUi->rememberPsdCheckBox->setChecked(true);
                    }
                }
                else
                {
                    ShowMessage(errorContent);
                }
                loginFormUi->loginPushButton->setFocus();
            }
        }
    }
}

void TNLoginWidget::InitRouterList()
{
    _pluginParam->strMacAddress  = TNLoginUtil::getHostMacAddress();
    _pluginParam->strTnUserAgent = TNLoginUtil::getUserAgent();
	_pluginParam->strHostInfo = QString("10.250.200.198:10012");

    _httpDomainRouterApi = std::make_shared<TNHttpDomainRouterApi>();
    _httpApi = std::make_shared<TNHttpApi>();
	_bInitNetRoute = true;
}

void TNLoginWidget::slotOnClickQRCodeScan()
{
    if (!this->_bInitNetRoute)
    {
        ShowMessage(("操作失败，请稍后重试"));
        InitRouterList();
        return;
    }

    if (ui->btn_qrcode->isChecked())
    {
        ui->stackedWidget->setCurrentIndex(4);
        _scanLogin->GetQRCodePic();
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(0);
        _scanLogin->CancelQRCodeLogin();
    }
}

void TNLoginWidget::slotOnClickLoginButton()
{
    loginFormUi->loginPushButton->setText(("登录中"));
    loginFormUi->loginPushButton->setEnabled(false);
    if (_userInfo && ((_userInfo->GetCheckState() == 1) || (_userInfo->GetPwdState() == 1))) // 如果上次勾选了[自动登录]或[记住密码]
    {
        exeAutoLogin(_userInfo);
    }
    else
    {
        if (!validateParameters_LoginForm())
        {
            loginFormUi->loginPushButton->setEnabled(true);
            loginFormUi->loginPushButton->setText(("登录"));
            return;
        }

        QString strEmail   = getMobileNumber_Login();
        QString strPassword = getPasswordAfterMD5_Login();
        LoginOKByPassword(strEmail, strPassword);
    }
    loginFormUi->loginPushButton->setEnabled(true);
    loginFormUi->loginPushButton->setText(("登录"));
}

void TNLoginWidget::LoginIMServer()
{
    TNIMCoreClient* client = TNIMCoreClient::GetIMClient();
    client->InitIM(_pluginParam);
}

void TNLoginWidget::LoginOKByPassword(const QString &strEmail, const QString &strPassword, bool isAuto, bool faceId)
{
	int nRet = 2;
    if (nRet == 1)
    {
        ShowMessage(("用户未注册"));
    }
    else if (nRet == 2)
    {
        QJsonObject object;
		int nWithPasswordRet = _httpApi->LoginWithPassword(strEmail, strPassword, object);
        if (nWithPasswordRet == 1)
        {
			QString strTnUserID = object.value("data").toObject().value("imid").toString();
			QString strTnUserToken = strPassword /*object.value("data").toObject().value("session").toString()*/;
			TNUtil::setPasswordLogin(true);
			SaveLoginUserToDB(strEmail, strTnUserToken);
			if (SetCurrentUserInfo(strTnUserID, strTnUserToken, strEmail))
            {
                LoginIMServer();
                LoadCardCaseDataToDB();
                emit SendPluginParamSignal(_pluginParam);
            }
        }
        else
        {
			ShowMessage(("用户名或密码错误"));
        }
    }
}

void TNLoginWidget::ShowMessage(const QString& errorContent)
{    
    switch(ui->stackedWidget->currentIndex())
    {
    case 0:
        loginFormUi->errorLabel->setText(errorContent);
        break;
    case 1:
        resetPsdForm01Ui->errorLabel->setText(errorContent);
        break;
    case 2:
        resetPsdForm02Ui->errorLabel->setText(errorContent);
        break;
    default:
        break;
    }
}

void TNLoginWidget::LoadCardCaseDataToDB()
{
    TNIMCoreClient::GetIMClient()->UpdateAddressBookFromServer();
}

void TNLoginWidget::SaveLoginUserToDB(const QString &strEmail, const QString &strPassword)
{
    st_LoginUserPtr loginUser = std::make_shared<st_LoginUser>();

    if (loginFormUi->rememberPsdCheckBox->isChecked())
    {
        loginUser->SetPwdState(1);
    }
    else
    {
        loginUser->SetPwdState(0);
    }
    if (loginFormUi->autoLoginCheckBox->isChecked())
    {
        loginUser->SetCheckState(1);
    }
    else
    {
        loginUser->SetCheckState(0);
    }

    loginUser->SetMobile(strEmail);

    QString logDate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    loginUser->SetLogDate(logDate);

    QString passwordDB;
    TNLoginUtil::TokenCode(strPassword, passwordDB, logDate, 0);
    loginUser->SetToken(passwordDB);

    TNDataControlServer::GetInstance()->InsertDatas(std::dynamic_pointer_cast<TableBase>(loginUser),DBTYPE_COMMON);
}

bool TNLoginWidget::SetCurrentUserInfo(const QString& userId, const QString& userToken,const QString& userEmail)
{
    _pluginParam->strTnUserID = userId;
    _pluginParam->strTnUserToken = userToken;
	_pluginParam->strEmailAddress = userEmail;

	qInfo() << "[Toon][TNLoginWidget] setcurrentuserInfo userid:" << userId << " usertoken:" << userToken << userEmail;
    TNPathUtil::SetCurrentUser(userId);
    TNUserDataUtil::GetInstance()->setUserPluginParam(_pluginParam);
    bool ok = TNDataControlServer::GetInstance()->ResetConnect();

    QString recFilePathFromDB = TNDbUtil::getRecFilePathFromDB();
    qInfo() << "[Toon][TNLoginWidget] setcurrentuserInfo recFilePathFromDB:" << recFilePathFromDB;
    if (!recFilePathFromDB.isEmpty())
        TNPathUtil::SetUserRecFile(recFilePathFromDB);

    return ok;
}

void TNLoginWidget::OnScanCodeReadySlot(const QString &path)
{
    QPixmap pixmap(path);
    qrCodeForm01Ui->qrPixmapLabel->setPixmap(pixmap);
    //获取二维码之后，轮训取状态
    _scanLogin->GetQRCodeStatus();
}

void TNLoginWidget::OnGetScanCodeStatusSlot(int status)
{
	if (status == OPERA_SCAN)
	{
		//更新图片，显示当前登录手机号
		QString mobile = _scanLogin->GetMobile();
		qrCodeForm02Ui->mobileLabel->setText(mobile);
		ui->stackedWidget->setCurrentIndex(5);
	}
	else if (status == OPERA_LOGIN)
	{
		//登陆成功
		QString token = _scanLogin->GetToken();
		QString userId = _scanLogin->GetUserId();
		QString mobile = _scanLogin->GetMobile();
		TNUtil::setPasswordLogin(false);
		if (SetCurrentUserInfo(userId, token, mobile))
		{
			LoginIMServer();
			LoadCardCaseDataToDB();
			emit SendPluginParamSignal(_pluginParam);
		}
	}
}

void TNLoginWidget::OnScanCodeInvaldSlot()
{
    //无效自动获取
    ui->stackedWidget->setCurrentIndex(5);
    _scanLogin->GetQRCodePic();
}

void TNLoginWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

bool TNLoginWidget::eventFilter(QObject *target, QEvent *event)
{
	/*
    if (target == loginFormUi->mobileLineEdit)
    {
        if (event->type() == QEvent::FocusIn)
        {
            ShowMessage(QString::null);
        }
    }
    if (target == loginFormUi->passwordLineEdit)
    {
        if (event->type() == QEvent::FocusIn)
        {
            QString strTeleCode = getTeleCode_Login();
            QString strEmail = loginFormUi->mobileLineEdit->text();
            if (strEmail.isEmpty())
            {
                QString errorMsg = (strTeleCode == "0000") ? ("运营号不能为空") : ("手机号不能为空");
                ShowMessage(errorMsg);
            }
            else if (strEmail.size() > 0 && strEmail.size() != 11)
            {
                QString errorMsg = (strTeleCode == "0000") ? ("运营号格式不正确") : ("手机号格式不正确");
                ShowMessage(errorMsg);
            }
            else
            {
                ShowMessage(QString::null);
            }
        }
    }

    if (target == resetPsdForm01Ui->mobileLineEdit)
    {
        if (event->type() == QEvent::FocusIn)
        {
            ShowMessage(QString::null);
        }
    }
    if (target == resetPsdForm01Ui->idCodeLineEdit)
    {
        if (event->type() == QEvent::FocusIn)
        {
            QString strEmail = resetPsdForm01Ui->mobileLineEdit->text();
            if (strEmail.isEmpty())
            {
                ShowMessage(("手机号不能为空"));
            }
            else if (strEmail.size() > 0 && strEmail.size() != 11)
            {
                ShowMessage(("手机号格式不正确"));
            }
            else
            {
                ShowMessage(QString::null);
            }
        }
    }

    if (target == resetPsdForm02Ui->passwordLineEdit_1)
    {
        if (event->type() == QEvent::FocusIn)
        {
            ShowMessage(QString::null);
        }
    }
    if (target == resetPsdForm02Ui->passwordLineEdit_2)
    {
        if (event->type() == QEvent::FocusIn)
        {
            QString password_1 = resetPsdForm02Ui->passwordLineEdit_1->text();
            if (!TNLoginUtil::checkPasswordValid(password_1))
            {
                ShowMessage(("8-16位 至少含数字/字母/符号2种组合"));
                resetPsdForm02Ui->resetPswFirst->setChecked(false);
            }
            else
            {
                ShowMessage(QString::null);
                resetPsdForm02Ui->resetPswFirst->setChecked(true);
            }
        }
    }
	*/
    return QWidget::eventFilter(target, event);
}

void TNLoginWidget::keyPressEvent(QKeyEvent *event)
{
    if (ui->stackedWidget->currentIndex() == 0)
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
            {
                slotOnClickLoginButton();
            }
        }
    }

    QWidget::keyPressEvent(event);
}

void TNLoginWidget::checkUpgrade()
{
    TNUpgradeMangement::instance()->checkNewVersion(_pluginParam, TNUpgradeMangement::ctBoot);
}

void TNLoginWidget::initLoginForm()
{
    QWidget *loginForm = new QWidget();
    loginFormUi->setupUi(loginForm);

    //setMobileLineEdit(loginFormUi->mobileLineEdit);
    setPasswordLineEdit(loginFormUi->passwordLineEdit);
    loginFormUi->passwordLineEdit->setMaxLength(20);

    loginFormUi->errorLabel->setText(QString::null);
    loginFormUi->autoLoginCheckBox->setObjectName("checkBox_AotoLogin");
    loginFormUi->autoLoginCheckBox->setFocusPolicy(Qt::NoFocus);
    loginFormUi->rememberPsdCheckBox->setFocusPolicy(Qt::NoFocus);
    loginFormUi->forgetPsdPushButton->setFocusPolicy(Qt::NoFocus);
	loginFormUi->mobileLineEdit->setText("wangzhiyong@huohua.cn");
    //初始化上次登录的手机号
    TableBaseVec tableBaseVec;
    TNDataControlServer::GetInstance()->GetLatestUserFromCommonDb(tableBaseVec);
    if (tableBaseVec.size() == 1)
    {
        st_LoginUserPtr loginUser = std::dynamic_pointer_cast<st_LoginUser>(tableBaseVec[0]);
        QString teleCode;
        QString mobile;
        QString errorContent;
        if (TNLoginUtil::parseMobileFromLoginUser(loginUser, &teleCode, &mobile, &errorContent))
        {
            loginFormUi->mobileLineEdit->setText(mobile);
        }
        else
        {
            ShowMessage(errorContent);
        }
    }

    ui->stackedWidget->addWidget(loginForm);

    connect(loginFormUi->rememberPsdCheckBox, SIGNAL(stateChanged(int)), this, SLOT(slotRememberPsdStateChanged(int)));
    connect(loginFormUi->autoLoginCheckBox, SIGNAL(stateChanged(int)), this, SLOT(slotAutoLoginStateChanged(int)));

    connect(loginFormUi->mobileLineEdit, SIGNAL(textEdited(const QString &)), this, SLOT(slotLoginMobileTextChanged(const QString &)));
    connect(loginFormUi->passwordLineEdit, SIGNAL(textEdited(const QString &)), this, SLOT(slotLoginPasswordTextChanged(const QString &)));

    connect(loginFormUi->forgetPsdPushButton, SIGNAL(clicked()), this, SLOT(slotForgetPassword()));
    connect(loginFormUi->loginPushButton, SIGNAL(clicked()), this, SLOT(slotOnClickLoginButton()));
}

void TNLoginWidget::initResetPasswordForm01()
{
    QWidget *resetPsdForm01 = new QWidget();
    resetPsdForm01Ui->setupUi(resetPsdForm01);

    resetPsdForm01Ui->errorLabel->setText(QString::null);
    //setMobileLineEdit(resetPsdForm01Ui->mobileLineEdit);
    setIdCodeLineEdit(resetPsdForm01Ui->idCodeLineEdit);
    resetPsdForm01Ui->resetPushButton->setEnabled(false);

    ui->stackedWidget->addWidget(resetPsdForm01);
    connect(resetPsdForm01Ui->mobileLineEdit, SIGNAL(textEdited(const QString &)), this, SLOT(slotButtonStateChanged_ResetPsd01(const QString &)));
    connect(resetPsdForm01Ui->idCodeLineEdit, SIGNAL(textEdited(const QString &)), this, SLOT(slotButtonStateChanged_ResetPsd01(const QString &)));
    connect(resetPsdForm01Ui->resetPushButton, SIGNAL(clicked()), this, SLOT(slotResetPassword01_ok()));
    connect(resetPsdForm01Ui->obtainIdCodeButton, SIGNAL(clicked()), this, SLOT(slotOnClickObtainIdCodeButton_ResetPsd()));
}

void TNLoginWidget::initResetPasswordForm02()
{
    QWidget *resetPsdForm02 = new QWidget();
    resetPsdForm02Ui->setupUi(resetPsdForm02);
    ui->stackedWidget->addWidget(resetPsdForm02);

    resetPsdForm02Ui->errorLabel->setText(QString::null);
    resetPsdForm02Ui->resetPswFirst->setFocusPolicy(Qt::NoFocus);
    resetPsdForm02Ui->resetPswSecond->setFocusPolicy(Qt::NoFocus);
    resetPsdForm02Ui->resetPswFirst->setEnabled(false);
    resetPsdForm02Ui->resetPswSecond->setEnabled(false);
    setPasswordLineEdit(resetPsdForm02Ui->passwordLineEdit_1);
    setPasswordLineEdit(resetPsdForm02Ui->passwordLineEdit_2);
    resetPsdForm02Ui->passwordLineEdit_1->setMaxLength(16);
    resetPsdForm02Ui->passwordLineEdit_2->setMaxLength(16);
    resetPsdForm02Ui->resetPushButton->setEnabled(false);

    connect(resetPsdForm02Ui->passwordLineEdit_1, SIGNAL(textEdited(const QString &)), this, SLOT(slotButtonStateChanged_ResetPsd02(const QString &)));
    connect(resetPsdForm02Ui->passwordLineEdit_2, SIGNAL(textEdited(const QString &)), this, SLOT(slotButtonStateChanged_ResetPsd02(const QString &)));
    connect(resetPsdForm02Ui->resetPushButton, SIGNAL(clicked()), this, SLOT(slotResetPassword02()));
}

void TNLoginWidget::initResetPasswordForm03()
{
    QWidget *resetPsdForm03 = new QWidget();
    resetPsdForm03Ui->setupUi(resetPsdForm03);
    ui->stackedWidget->addWidget(resetPsdForm03);

    connect(resetPsdForm03Ui->goLoginPushButton, SIGNAL(clicked()), this, SLOT(slotResetPassword03()));
}

void TNLoginWidget::initQRCodeScanForm01()
{
    QWidget *qrCodeForm01 = new QWidget();
    qrCodeForm01Ui->setupUi(qrCodeForm01);
    ui->stackedWidget->addWidget(qrCodeForm01);
	APP_TYPE  appType = ENUM_APPTYPE;
	if (appType != APP_TYPE_TOON)
	{
		QString scanInfo = QString("请使用%1手机版扫描二维码登录").arg(TOON_TITLE);
		qrCodeForm01Ui->label_scantip->setText(tr(scanInfo.toStdString().c_str()));
	}
	if (appType == APP_TYPE_BJTOON)
		loginFormUi->label_title->setGeometry(110, 40, 100, 29);
	else if (appType == APP_TYPE_QLTOON)
		loginFormUi->label_title->setGeometry(93, 39, 134, 32);
	else if(appType == APP_TYPE_MCTOON)
		loginFormUi->label_title->setGeometry(110, 40, 100, 29);
	else if (appType == APP_TYPE_ZQTOON)
		loginFormUi->label_title->setGeometry(108, 40, 100, 32);
	else if (appType == APP_TYPE_DAOTOON)
		loginFormUi->label_title->setGeometry(108, 40, 100, 32);
    _scanLogin = new TNQRCodeLogin(_pluginParam);
    connect(_scanLogin, SIGNAL(DownQRCodeSuccess(QString)), this, SLOT(OnScanCodeReadySlot(QString)));
    connect(_scanLogin, SIGNAL(GetScanCodeStatus(int)), this, SLOT(OnGetScanCodeStatusSlot(int)));
    connect(_scanLogin, SIGNAL(CurrentQRcodeInvalid()), this, SLOT(OnScanCodeInvaldSlot()));
}

void TNLoginWidget::initQRCodeScanForm02()
{
    QWidget *qrCodeForm02 = new QWidget();
    qrCodeForm02Ui->setupUi(qrCodeForm02);
    ui->stackedWidget->addWidget(qrCodeForm02);

    connect(qrCodeForm02Ui->backCodeScanButton, SIGNAL(clicked()), this, SLOT(slotBackCodeScanLogin()));
}

void TNLoginWidget::slotRememberPsdStateChanged(int state)
{
    if (Qt::CheckState(state) == Qt::Unchecked)
    {
        loginFormUi->autoLoginCheckBox->setCheckState(Qt::CheckState(state));
    }
}

void TNLoginWidget::slotAutoLoginStateChanged(int state)
{
    if (Qt::CheckState(state) == Qt::Checked)
    {
        loginFormUi->rememberPsdCheckBox->setCheckState(Qt::CheckState(state));
    }
}

void TNLoginWidget::slotLoginMobileTextChanged(const QString &text)
{
    Q_UNUSED(text);
    loginFormUi->passwordLineEdit->clear();
    loginFormUi->rememberPsdCheckBox->setChecked(false);
    _userInfo.reset();
}

void TNLoginWidget::slotLoginPasswordTextChanged(const QString &text)
{
    Q_UNUSED(text);
    _userInfo.reset();
}

void TNLoginWidget::slotForgetPassword()
{
    QString strTeleCode = getTeleCode_Login();
    if (strTeleCode == "0000")
    {
        TNOpForgetPsdTipDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted)
            return;
    }

    TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_ForgetPWD, _pluginParam);
    ui->btn_qrcode->setChecked(true);
    ui->stackedWidget->setCurrentIndex(1);

    QString mobile = loginFormUi->mobileLineEdit->text().trimmed();
    if (TNLoginUtil::checkMobileNumber(mobile))
    {
        resetPsdForm01Ui->mobileLineEdit->setText(mobile);
    }
    resetPsdForm01Ui->idCodeLineEdit->setText(QString::null);
    resetPsdForm01Ui->resetPushButton->setEnabled(false);

    resetPsdForm02Ui->passwordLineEdit_1->setText(QString::null);
    resetPsdForm02Ui->passwordLineEdit_2->setText(QString::null);
}

void TNLoginWidget::slotButtonStateChanged_ResetPsd01(const QString &text)
{
    Q_UNUSED(text);
    QString strEmail = resetPsdForm01Ui->mobileLineEdit->text().trimmed();
    QString strIdCode = resetPsdForm01Ui->idCodeLineEdit->text().trimmed();
    if (TNLoginUtil::checkMobileNumber(strEmail) && (strIdCode.trimmed().size()>=4))
    {
        resetPsdForm01Ui->resetPushButton->setEnabled(true);
    }
    else
    {
        resetPsdForm01Ui->resetPushButton->setEnabled(false);
    }
}

void TNLoginWidget::slotButtonStateChanged_ResetPsd02(const QString &text)
{
    Q_UNUSED(text);
    QString password_1 = resetPsdForm02Ui->passwordLineEdit_1->text();
    QString password_2 = resetPsdForm02Ui->passwordLineEdit_2->text();
    if (TNLoginUtil::checkPasswordValid(password_1))
    {
        if (password_1 == password_2)
        {
            ShowMessage(QString::null);
            resetPsdForm02Ui->resetPswSecond->setChecked(true);
            resetPsdForm02Ui->resetPushButton->setEnabled(true);
        }
        else
        {
            if (password_2.size() >= password_1.size())
            {
                if (password_1 != password_2)
                    ShowMessage(("密码输入不一致"));
            }
            else
            {
                ShowMessage(QString::null);
            }

            resetPsdForm02Ui->resetPswSecond->setChecked(false);
            resetPsdForm02Ui->resetPushButton->setEnabled(false);
        }
    }
}

void TNLoginWidget::slotResetPassword01_ok()
{
    qInfo()<<"[Toon][TNLoginWidget]slotResetPassword01_ok begin...";
	/*
    if (resetPsdForm01Ui->mobileLineEdit->text().trimmed().isEmpty())
    {
        ShowMessage(("手机号不能为空"));
        return;
    }
    if (!TNLoginUtil::checkMobileNumber(resetPsdForm01Ui->mobileLineEdit->text().trimmed()))
    {
        ShowMessage(("手机号格式不正确"));
        return;
    }

    if (resetPsdForm01Ui->idCodeLineEdit->text().trimmed().isEmpty())
    {
        ShowMessage(("验证码不能为空"));
        return;
    }

    const QString teleCode = getTeleCode_ResetPsd();
    const QString mobile = getMobileNumber_ResetPsd();
    const QString mobileVerfiyCode = getIdCode_ResetPsd();
    m_checkVCodeResetPsd.setParams(teleCode, mobile, mobileVerfiyCode);

    auto resetPasswordCheckVCodeFinished = [&](bool success, QJsonObject jsonObject)
    {
        qInfo()<<"[Toon][TNLoginWidget]resetPasswordCheckVCodeFinished-callback begin...";
        if (success)
        {
            QString debugText = QJsonDocument(jsonObject).toJson();
            qInfo()<<"[Toon][TNLoginWidget]resetPasswordCheckVCodeFinished-debugText="<<debugText;
            int retCode = jsonObject["meta"].toObject().value("code").toInt();
            if (retCode == 0)
            {
                QString strTnUserID    = QString("%1").arg(jsonObject.value("data").toObject().value("userId").toInt());
                QString strTnUserToken = jsonObject.value("data").toObject().value("token").toString();
                _pluginParam->strTnUserID    = strTnUserID;
                _pluginParam->strTnUserToken = strTnUserToken;
                ui->stackedWidget->setCurrentIndex(2);
            }
            else
            {
                QString content = jsonObject.value("meta").toObject().value("message").toString();
                qInfo() << "[Toon][TNLoginWidget]resetPasswordCheckVCodeFinished failed. retCode=" << retCode << " content=" << content;
                ShowMessage(content);
            }
        }
        else
        {
            ShowMessage(("操作失败，请检查您的网络状态"));
        }

        qInfo()<<"[Toon][TNLoginWidget]resetPasswordCheckVCodeFinished-callback end.";
    };

    m_checkVCodeResetPsd.GetJson(resetPasswordCheckVCodeFinished, _pluginParam);
	*/
    qInfo()<<"[Toon][TNLoginWidget]resetPasswordFinished end.";
}

void TNLoginWidget::slotResetPassword02()
{
    qInfo()<<"[Toon][TNLoginWidget]slotResetPassword02 begin...";

    QString password_1 = resetPsdForm02Ui->passwordLineEdit_1->text();
    QString password_2 = resetPsdForm02Ui->passwordLineEdit_2->text();
    if (password_1.isEmpty() || password_2.isEmpty())
    {
        ShowMessage(("密码不能为空"));
        return;
    }
    if (!TNLoginUtil::checkPasswordValid(password_1))
    {
        ShowMessage(("8-16位 至少含数字/字母/符号2种组合"));
        return;
    }
    if (!TNLoginUtil::checkPasswordValid(password_2))
    {
        ShowMessage(("8-16位 至少含数字/字母/符号2种组合"));
        return;
    }
    if (password_1 != password_2)
    {
        ShowMessage(("密码输入不一致"));
        return;
    }

    const QString password = getPasswordAfterMD5_ResetPsd();

    auto resetPasswordFinished = [&](bool success, QJsonObject jsonObject)
    {
        qInfo()<<"[Toon][TNLoginWidget]resetPasswordFinished-callback begin...";
        if (success)
        {
            QString debugText = QJsonDocument(jsonObject).toJson();
            qInfo()<<"[Toon][TNLoginWidget]resetPasswordFinished-debugText="<<debugText;
            int retCode = jsonObject["meta"].toObject().value("code").toInt();
            if (retCode == 0)
            {
                ui->stackedWidget->setCurrentIndex(3);
            }
            else
            {
                QString content = jsonObject.value("meta").toObject().value("message").toString();
                qInfo() << "[Toon][TNLoginWidget]resetPasswordFinished failed. retCode=" << retCode << " content=" << content;
                ShowMessage(content);
            }
        }
        else
        {
            ShowMessage(("操作失败，请检查您的网络状态"));
        }
        qInfo()<<"[Toon][TNLoginWidget]resetPasswordFinished-callback end.";
    };

    m_resetPassword.GetJson(resetPasswordFinished, _pluginParam, password);

    qInfo()<<"[Toon][TNLoginWidget]resetPasswordFinished end.";
}

void TNLoginWidget::slotResetPassword03()
{
    TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_BackLogin, _pluginParam);
    ui->btn_qrcode->setChecked(false);
    loginFormUi->mobileLineEdit->setText(getMobileNumber_ResetPsd());
    loginFormUi->passwordLineEdit->clear();
    loginFormUi->rememberPsdCheckBox->setChecked(false);
    loginFormUi->autoLoginCheckBox->setChecked(false);
    _userInfo.reset();
    ui->stackedWidget->setCurrentIndex(0);
}

void TNLoginWidget::slotBackCodeScanLogin()
{
    _scanLogin->CancelQRCodeLogin();
    ui->stackedWidget->setCurrentIndex(5);
    _scanLogin->GetQRCodePic();
}

void TNLoginWidget::setTeleComboBox(QComboBox *comboBox)
{
    comboBox->addItem("+86");
    comboBox->addItem("+00");
#ifdef Q_OS_MAC
    comboBox->setStyleSheet("QComboBox::item{min-height:20px;max-height:20px;padding:0 20px;}");
#endif
}

void TNLoginWidget::setMobileLineEdit(QLineEdit *lineEdit)
{
    lineEdit->setMaxLength(11);
    QRegExp regExp("^[1][0-9]{10}$"); //第二位允许为0-9，不再限制
    lineEdit->setValidator(new QRegExpValidator(regExp, this));
    lineEdit->setContextMenuPolicy(Qt::NoContextMenu);
    lineEdit->setAttribute(Qt::WA_MacShowFocusRect, false);
}

void TNLoginWidget::setPasswordLineEdit(QLineEdit *lineEdit)
{
    //QRegExp passwordRegExp("^[0-9a-zA-Z]*$");
    QRegExp passwordRegExp("^[\x21-\x7e]*$");
    lineEdit->setValidator(new QRegExpValidator(passwordRegExp, this));
    lineEdit->setEchoMode(QLineEdit::Password);
    lineEdit->setContextMenuPolicy(Qt::NoContextMenu);
    lineEdit->setAttribute(Qt::WA_MacShowFocusRect, false);
}

void TNLoginWidget::setIdCodeLineEdit(QLineEdit *lineEdit)
{
    lineEdit->setContextMenuPolicy(Qt::NoContextMenu);
    lineEdit->setAttribute(Qt::WA_MacShowFocusRect, false);
}

bool TNLoginWidget::validateParameters_LoginForm()
{
    if (loginFormUi->passwordLineEdit->text().trimmed().isEmpty())
    {
        ShowMessage(("密码不能为空"));
        return false;
    }

    return true;
}

QString TNLoginWidget::getTeleCode_Login()
{
	return "";
}

QString TNLoginWidget::getMobileNumber_Login()
{
    return loginFormUi->mobileLineEdit->text().trimmed();
}

QString TNLoginWidget::getPasswordAfterMD5_Login()
{
	return loginFormUi->passwordLineEdit->text().trimmed();
	/*
    const QString strPassword = loginFormUi->passwordLineEdit->text().trimmed();
    return TNLoginUtil::getPasswordAfterMD5(strPassword);
	*/
}

QString TNLoginWidget::getTeleCode_ResetPsd()
{
    return "0086";
}

QString TNLoginWidget::getMobileNumber_ResetPsd()
{
    return resetPsdForm01Ui->mobileLineEdit->text().trimmed();
}

QString TNLoginWidget::getIdCode_ResetPsd()
{
    return resetPsdForm01Ui->idCodeLineEdit->text().trimmed();
}

QString TNLoginWidget::getPasswordAfterMD5_ResetPsd()
{
    const QString strPassword = resetPsdForm02Ui->passwordLineEdit_2->text().trimmed();
    return TNLoginUtil::getPasswordAfterMD5(strPassword);
}
