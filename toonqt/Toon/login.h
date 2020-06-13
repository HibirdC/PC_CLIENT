#ifndef LOGIN_H
#define LOGIN_H

#include "Login/TNLoginWidget.h"
#include "DropShadowWidget.h"

class Login : public DropShadowWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

    void showWidget();

    void Init(bool enableAutoLogin);
	
private Q_SLOTS:
    void destroyLoginWidget();
    void showLoginMin();
    void OnPluginParamSlot(TNPluginParamPtr param);
	void autoLoginFromErrSlot();

signals:
    void SendPluginParamSignal(TNPluginParamPtr param);
	void autoLoginFromErrByPwd();
	void autoLoginFromErrByCode();
	void autoLoginFromErr();

protected:
    virtual void closeEvent(QCloseEvent *event);
    virtual bool eventFilter(QObject *o, QEvent *e);

private:
    TNLoginWidget  *m_loginWidget;
	bool		    m_bQuitApp;
};

#endif // LOGIN_H
