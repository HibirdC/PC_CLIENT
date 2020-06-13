#ifndef TNLOGINWIDGET_H
#define TNLOGINWIDGET_H

#include <QWidget>
#include <QMutex>
#include <QPushButton>
#include <QMovie>

#include "TNHttpBasicRouterApi.h"
#include "TNHttpDomainRouterApi.h"
#include "LocalStorageCommon.h"
#include "TNHttpApi.h"
#include "common_global.h"
#include "TNQRCodeLogin.h"
#include "TNHttpResetPassword.h"
#include "TNHttpCheckVCodeBeforeLogin.h"

namespace Ui {
class TNLoginWidget;
class LoginForm;
class NewDeviceLoginForm;
class ResetPasswordForm01;
class ResetPasswordForm02;
class ResetPasswordForm03;
class QRCodeScanForm01;
class QRCodeScanForm02;
}

class QComboBox;
class QLineEdit;
class TNIdCodeTimer;
class TNLoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TNLoginWidget(bool isEnableAutoLogin, QWidget *parent = 0);
    ~TNLoginWidget();

public:
    QPushButton* GetMinBtn();
    QPushButton* GetCloseBtn();
	int getCurrentPage();

private Q_SLOTS:
    void slotOnClickQRCodeScan();

    void slotOnClickLoginButton();

    void slotOnClickObtainIdCodeButton_NewDevice();
    void slotOnClickLoginButton_NewDevice();

    void slotOnLoginIdCodeTimer(const QString &timeText);

    void slotExeAutoLogin();

    //二维码下载完
    void OnScanCodeReadySlot(const QString &path);
    //返回扫码状态
    void OnGetScanCodeStatusSlot(int status);
    //二维码过期
    void OnScanCodeInvaldSlot();

    void OnLoginDAOSlot(QString strParam);

    void slotOnClickObtainIdCodeButton_ResetPsd();
    void slotOnResetPsdIdCodeTimer(const QString &timeText);

signals:
    void SendPluginParamSignal(TNPluginParamPtr param);
    void LoginSignal();

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual bool eventFilter(QObject *target, QEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);

private:
    void ShowMessage(const QString &errorContent);

    void InitUiDataIfAutoLogin();
    void InitRouterList();

    void LoadCardCaseDataToDB();

    void LoginOKByPassword(const QString &strMobile, const QString &strPassword, bool isAuto = false, bool faceId = false);
    //第一次登陆需要验证码校验
    void OnCheckCodeForFirstLogin();
    void LoginOKByIdenfy(const QString &strTeleCode, const QString &strMobile, const QString &strIdentify);

    void LoginIMServer();
    void SaveLoginUserToDB(const QString &strTeleCode, const QString &strMobile, const QString &strPassword);
    bool SetCurrentUserInfo(const QString& userId, const QString& userToken, const QString& userMobile);

    void LoginThreadStart();
    void exeAutoLogin(st_LoginUserPtr loginUser);
    void checkUpgrade();
    void resetNewDeviceIdCodeTimer();
    void resetResetPsdIdCodeTimer();

    //冬奥通免登接口
    bool LoginByAutoIdenfy(const QString& strParam);

private:
    Ui::TNLoginWidget *ui;
    Ui::LoginForm *loginFormUi;
    Ui::NewDeviceLoginForm  *newDeviceFormUi;
    Ui::ResetPasswordForm01 *resetPsdForm01Ui;
    Ui::ResetPasswordForm02 *resetPsdForm02Ui;
    Ui::ResetPasswordForm03 *resetPsdForm03Ui;
    Ui::QRCodeScanForm01    *qrCodeForm01Ui;
    Ui::QRCodeScanForm02    *qrCodeForm02Ui;

    TNPluginParamPtr _pluginParam;
    bool _bIsEnableAutoLogin;
    QMovie*							_bottomMovie;

    TNHttpDomainRouterApiPtr		_httpDomainRouterApi;
    TNQRCodeLogin*					_scanLogin;
    st_LoginUserPtr                 _userInfo; //仅仅自动登录和记住密码时有用
    TNHttpApiPtr					_httpApi;

    TNHttpCheckVCodeBeforeLogin m_checkVCodeResetPsd;
    TNHttpResetPassword m_resetPassword;

    TNIdCodeTimer *m_newDeviceIdCodeTimer;
    TNIdCodeTimer *m_resetPsdIdCodeTimer;

    bool _bInitNetRoute;
    bool _bIsFirstLogin;

    QMutex _mutex;

private slots:    
    void slotTeleCodeChanged(int index);
    void slotRememberPsdStateChanged(int state);
    void slotAutoLoginStateChanged(int state);
    void slotLoginMobileTextChanged(const QString &text);
    void slotLoginPasswordTextChanged(const QString &text);

    void slotButtonStateChanged_ResetPsd01(const QString &text);
    void slotButtonStateChanged_ResetPsd02(const QString &text);

    void slotForgetPassword();
    void slotResetPassword01_ok();
    void slotResetPassword02();
    void slotResetPassword03();
    void slotBackCodeScanLogin();

private:
    void initMainForm();
    void initLoginForm();
    void initNewDeviceLoginForm();
    void initResetPasswordForm01();
    void initResetPasswordForm02();
    void initResetPasswordForm03();
    void initQRCodeScanForm01();
    void initQRCodeScanForm02();

    void setTeleComboBox(QComboBox *comboBox);
    void setMobileLineEdit(QLineEdit *lineEdit);
    void setPasswordLineEdit(QLineEdit *lineEdit);
    void setIdCodeLineEdit(QLineEdit *lineEdit);

    // 密码登录
    bool validateParameters_LoginForm();
    QString getTeleCode_Login();
    QString getMobileNumber_Login();
    QString getPasswordAfterMD5_Login();
    QString getIdCode_Login();

    // 重置密码
    QString getTeleCode_ResetPsd();
    QString getMobileNumber_ResetPsd();
    QString getIdCode_ResetPsd();
    QString getPasswordAfterMD5_ResetPsd();
};

#endif // TNLOGINDIALOG_H
