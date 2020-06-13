#include "login.h"

Login::Login(QWidget *parent)
    : DropShadowWidget(parent)
	, m_loginWidget(NULL), m_bQuitApp(true)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog | Qt::WindowMinimizeButtonHint);
    setFixedWidth(320);
    setFixedHeight(432);

    this->installEventFilter(this);
}

Login::~Login()
{

}

void Login::Init(bool enableAutoLogin)
{
    m_loginWidget = new TNLoginWidget(enableAutoLogin, this);
    m_loginWidget->setGeometry(QRect(0, 0, 320, 432));
    m_loginWidget->setContentsMargins(10, 0, 10, 20);
    this->setObjectName("Login");

	connect(this, SIGNAL(autoLoginFromErr()), this, SLOT(autoLoginFromErrSlot()));
	connect(this, SIGNAL(autoLoginFromErrByCode()), m_loginWidget, SLOT(slotOnClickLoginButton_NewDevice()));
	connect(this, SIGNAL(autoLoginFromErrByPwd()), m_loginWidget, SLOT(slotOnClickLoginButton()));
    connect(m_loginWidget->GetMinBtn(), SIGNAL(clicked()), this, SLOT(showLoginMin()));
    connect(m_loginWidget->GetCloseBtn(), SIGNAL(clicked()), this, SLOT(destroyLoginWidget()));
    connect(m_loginWidget, SIGNAL(SendPluginParamSignal(TNPluginParamPtr)), this, SLOT(OnPluginParamSlot(TNPluginParamPtr)));
}

void Login::showWidget()
{
    this->showNormal();
    this->raise();
    this->activateWindow();
}

void Login::showLoginMin()
{
    showMinimized();
}

void Login::destroyLoginWidget()
{
    reject();
    qApp->quit();
}

void Login::closeEvent(QCloseEvent *event)
{
    qInfo()<<"[Toon][Login]closeEvent";
	if (m_bQuitApp)
		destroyLoginWidget();
}

bool Login::eventFilter(QObject *o, QEvent *e)
{
    if (o == this)
    {
        switch (e->type())
        {
        case QEvent::KeyPress:
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(e);
            if (keyEvent->key() == Qt::Key_Escape)
            {
                return true;
            }
        }
        default:
            break;
        }
    }

    return DropShadowWidget::eventFilter(o, e);
}

void Login::OnPluginParamSlot(TNPluginParamPtr param)
{
    qInfo()<<"[Toon][Login]OnPluginParamSlot";
	m_bQuitApp = false;
    emit SendPluginParamSignal(param);
}
void Login::autoLoginFromErrSlot()
{
	if (m_loginWidget != nullptr)
	{
		switch (m_loginWidget->getCurrentPage())
		{
		case 0:
			emit autoLoginFromErrByPwd();
			break;
		case 4:
			emit autoLoginFromErrByCode();
			break;
		default:
			break;
		}
	}
}
