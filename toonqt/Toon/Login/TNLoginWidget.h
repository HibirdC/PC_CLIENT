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
class ResetPasswordForm01;
class ResetPasswordForm02;
class ResetPasswordForm03;
class QRCodeScanForm01;
class QRCodeScanForm02;
}

class QComboBox;
class QLineEdit;
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
    void slotExeAutoLogin();

    //二维码下载完
    void OnScanCodeReadySlot(const QString &path);
    //返回扫码状态
    void OnGetScanCodeStatusSlot(int status);
    //二维码过期
    void OnScanCodeInvaldSlot();
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

    void LoginIMServer();
    void SaveLoginUserToDB(const QString &strMobile, const QString &strPassword);
	bool SetCurrentUserInfo(const QString& userId, const QString& userToken, const QString& userEmail);

    void LoginThreadStart();
    void exeAutoLogin(st_LoginUserPtr loginUser);
    void checkUpgrade();
private:
    Ui::TNLoginWidget *ui;
    Ui::LoginForm *loginFormUi;
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

    bool _bInitNetRoute;
    bool _bIsFirstLogin;

    QMutex _mutex;
private slots:    
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
