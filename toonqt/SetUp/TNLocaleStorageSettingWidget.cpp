#include <QFileDialog>
#include <qdesktopservices.h>
#include <QProgressDialog>
#include <QKeyEvent>
#include <QSettings>
#include <QProcess>
#ifdef Q_OS_WIN
#include <io.h>
#elif __linux__
#include <unistd.h>
#include <fcntl.h>
#elif __APPLE__
#include <unistd.h>
#endif

#include "TNMessageBox.h"
#include "TNStorageErrorTipsDialog.h"
#include "TNLocaleStorageSettingWidget.h"
#include "TNDataControlServer.h"
#include "TNPathUtil.h"
#include "TNSettingData.h"
#include "tnnotifycenter.h"
#include "TNGlobalShotCutManagement.h"
#include "ScreenShot.h"
#include "TNUtil.h"
#include "TNShortCutSettingDialog.h"
#include "TNShortCutKeyTextMap.h"
#include "TNLanguageChangeTipDialog.h"
#include "TNConfig.h"
#include "TNDbUtil.h"
#include "TNUserDataHelper.h"

TNLocaleStorageSettingWidget::TNLocaleStorageSettingWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    ui.safeLoginWidget->hide();

#if defined(DAOTOON)
    ui.bootUpCheckBox->hide();
    ui.autoLoginCheckBox->hide();
#endif

#ifdef Q_OS_MAC
    ui.bootUpCheckBox->hide();
    ui.safeLoginWidget->hide();
#endif

    ui.languageComboBox->addItem(("简体中文"));
    ui.languageComboBox->addItem(("繁體中文"));
    //ui.languageComboBox->addItem(("English"));

    ui.checkHotKey->hide();
    ui.hotKeyCheckBox->hide();

    ui.screentShotShortCut->setToolTip(("点击设置新的快捷键"));

#ifdef Q_OS_MAC
    ui.comboBox->addItem("Return");
    ui.comboBox->addItem("⌘+Return");
#else
    ui.comboBox->addItem("Enter");
    ui.comboBox->addItem("Ctrl+Enter");
    ui.localStorageSystemTitle->setFixedWidth(120);
#endif
    ui.localStorageFileLineEdit->setAttribute(Qt::WA_InputMethodEnabled, false);
    ui.localStorageFileLineEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);

    connect(ui.bootUpCheckBox, SIGNAL(stateChanged(int)), this, SLOT(slotBootUp(int)));
    connect(ui.noDisturbCheckBox, SIGNAL(stateChanged(int)), this, SLOT(slotNoDisturb(int)));
    connect(ui.autoLoginCheckBox, SIGNAL(stateChanged(int)), this, SLOT(slotAutoLogin(int)));

    connect(ui.changeDirButton, SIGNAL(clicked()), this, SLOT(slotChangePathDialog()));
    connect(ui.openDirButton, SIGNAL(clicked()), this, SLOT(slotOpenDirFileDialog()));
    connect(ui.comboBox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(onHotKeyChanged(const QString &)));
    connect(ui.screentShotShortCut, SIGNAL(clicked()), this, SLOT(slotShortCutSettingDialog()));
    connect(ui.hotKeyCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onCheckBoxStateChanged(int)));

    InitSettings();

    connect(ui.languageComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCurrentLanguageChanged(int)));
}

TNLocaleStorageSettingWidget::~TNLocaleStorageSettingWidget()
{
}

void TNLocaleStorageSettingWidget::InitSettings()
{
    // 从本地存储读取相关设置初始化对应的控件状态
    TableBaseVec tableBaseVec;
    TNDataControlServer::GetInstance()->GetAllFieldsByTableName("SetUp", tableBaseVec, DBTYPE_USER);
    std::map<QString, QString> records;
    for (TableBaseVec::iterator iter = tableBaseVec.begin(); iter != tableBaseVec.end(); iter++)
    {
        st_SetUpPtr record = std::dynamic_pointer_cast<st_SetUp>(*iter);
        records.insert(std::make_pair(record->GetKey(), record->GetValue()));
    }

    bool isBootUp = false;
    std::map<QString, QString>::const_iterator iter = records.find("BootUp");
    if (iter != records.end())
    {
        if (iter->second == ("1"))
        {
            isBootUp = true;
        }
    }
    ui.bootUpCheckBox->setChecked(isBootUp);

    bool isNoDisturbButton = false;
    std::map<QString, QString>::const_iterator iter2 = records.find("NoDisturbing");
    if (iter2 != records.end())
    {
        if (iter2->second == ("1"))
        {
            isNoDisturbButton = true;
        }
    }
    ui.noDisturbCheckBox->setChecked(isNoDisturbButton);

    bool isAutoLogin = false;
    TableBaseVec userTableBaseVec;
    TNDataControlServer::GetInstance()->GetLatestUserFromCommonDb(userTableBaseVec);
    if (userTableBaseVec.size() == 1)
    {
        st_LoginUserPtr loginState = std::dynamic_pointer_cast<st_LoginUser>(userTableBaseVec[0]);
        if (loginState->GetCheckState() == 1)
        {
            isAutoLogin = true;
        }
    }
    ui.autoLoginCheckBox->setChecked(isAutoLogin);
    if (!TNUtil::getPasswordLogin())
    {
        ui.autoLoginCheckBox->setChecked(false);
        ui.autoLoginCheckBox->setEnabled(false);
    }

    QString strMobile = TNUserDataHelper::GetInstance()->_pluginParam->strMobile;
    qDebug()<<"TNLocaleStorageSettingWidget-strMobile="<<strMobile;
    if (strMobile.isEmpty())
        qInfo()<<"error! strMobile is null";
    bool oncePassWordLogin = TNDbUtil::onceUsedPassWordLogin(strMobile);
    ui.faceIdButton->setText(oncePassWordLogin ? ("已启用人脸识别") : ("未启用人脸识别"));

    int languageIndex = int(TNConfig::instance()->GetCurrentLangueSet());
    if (languageIndex>=0 && languageIndex<ui.languageComboBox->count())
        ui.languageComboBox->setCurrentIndex(languageIndex);

    QString localPath = TNSettingData::instance()->LocalPath();
    if (localPath.isEmpty())
    {
        QFileInfo info(TNPathUtil::getUserRecFile());
        localPath = info.absolutePath();
        TNSettingData::instance()->SetLocalPath(localPath);
        if (!localPath.endsWith("/"))
        {
            localPath += "/";
        }
    }
    checkDirIsWritable(localPath);
    TNPathUtil::SetUserRecFile(localPath);
    ui.localStorageFileLineEdit->setText(localPath);
    ui.localStorageFileLineEdit->installEventFilter(this);
    ui.localStorageFileLineEdit->setContextMenuPolicy(Qt::NoContextMenu);

    //发送热键
    QString sendHotKey = TNSettingData::instance()->sendHotKey();
    if (sendHotKey.isEmpty())
    {
#ifdef Q_OS_MAC
        sendHotKey = "Return";
#else
        sendHotKey = "Enter";
#endif // Q_OS_MAC
        TNSettingData::instance()->SetSendHotKey(sendHotKey);
        saveSendHotKeySettingToDB();
    }
    TNNotifyCenter::instance()->postNotifySendHotKeyChanged(sendHotKey);
    ui.comboBox->setCurrentText(sendHotKey);

    //截屏热键
    QString screenShotHotKey = TNSettingData::instance()->ScreenShotKey();
    qDebug()<<"TNLocaleStorageSettingWidget-screenShotHotKey="<<screenShotHotKey;
    if (screenShotHotKey.isEmpty())
    {
#ifdef Q_OS_MAC
        screenShotHotKey = "Meta+A";
#else
        screenShotHotKey = "Alt+A";
#endif
        TNSettingData::instance()->SetScreenShotKey(screenShotHotKey);
        saveScreenShotHotKeySettingToDB(screenShotHotKey);
    }
    registerScreenHotKey(screenShotHotKey);
    connect(TNGlobalShotCutManagement::instance(), SIGNAL(screenShotKeyActived(QxtGlobalShortcut*)), this, SLOT(onScreenShotKey(QxtGlobalShortcut*)));
    QString uiTextByText = TNShortCutKeyTextMap::getUiTextByText(screenShotHotKey);
    if (uiTextByText.isEmpty())
        uiTextByText = ("设置快捷键");
    ui.screentShotShortCut->setText(uiTextByText);
}

void TNLocaleStorageSettingWidget::slotBootUp(int state)
{
    st_SetUpPtr bootUpSetting = std::make_shared<st_SetUp>();
    bootUpSetting->SetKey("BootUp");
    bootUpSetting->SetValue((state == Qt::Checked) ? ("1") : ("0"));
    TNDataControlServer::GetInstance()->InsertDatas(std::dynamic_pointer_cast<TableBase>(bootUpSetting), DBTYPE_USER);

    //开机启动
    QSettings reg("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    QString strAppName("toonPC");
    if (state == Qt::Checked)
    {
        QString strAppPath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
        reg.setValue(strAppName, strAppPath);
        if (reg.value(strAppName).toString().isEmpty())
        {
            //如果注册失败，则恢复按钮选中状态
            state = Qt::Unchecked;
            ui.bootUpCheckBox->setCheckState(Qt::CheckState(state));
        }
    }
    else
    {
        reg.setValue(strAppName, "");
    }
    ui.bootUpCheckBox->setCheckState(Qt::CheckState(state));
}

void TNLocaleStorageSettingWidget::slotNoDisturb(int state)
{
    st_SetUpPtr noDisturbingSetting = std::make_shared<st_SetUp>();
    noDisturbingSetting->SetKey("NoDisturbing");
    noDisturbingSetting->SetValue((state == Qt::Checked) ? ("1") : ("0"));
	emit updateSettingStatus("NoDisturbing", (state == Qt::Checked) ? 1 : 0);
    TNDataControlServer::GetInstance()->InsertDatas(std::dynamic_pointer_cast<TableBase>(noDisturbingSetting), DBTYPE_USER);
    ui.noDisturbCheckBox->setCheckState(Qt::CheckState(state));
}

void TNLocaleStorageSettingWidget::slotAutoLogin(int state)
{
    TableBaseVec userTableBaseVec;
    TNDataControlServer::GetInstance()->GetLatestUserFromCommonDb(userTableBaseVec);
    if (userTableBaseVec.size() == 1)
    {
        st_LoginUserPtr loginState = std::dynamic_pointer_cast<st_LoginUser>(userTableBaseVec[0]);
        int checkState = (state == Qt::Checked)  ? 1 : 0;
        loginState->SetCheckState(checkState);
        TNDataControlServer::GetInstance()->InsertDatas(std::dynamic_pointer_cast<TableBase>(loginState), DBTYPE_COMMON);
    }
}

void TNLocaleStorageSettingWidget::slotCurrentLanguageChanged(int index)
{    
    TNLanguageChangeTipDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        TNConfig::instance()->SetCurrentLangueSet(LANGUE_TYPE(index));
        qApp->quit();
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
    }
    else
    {
        disconnect(ui.languageComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCurrentLanguageChanged(int)));
        LANGUE_TYPE index = TNConfig::instance()->GetCurrentLangueSet();
        ui.languageComboBox->setCurrentIndex(int(index));
        connect(ui.languageComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCurrentLanguageChanged(int)));
    }
}

void TNLocaleStorageSettingWidget::slotChangePathDialog()
{
    const QString source = ui.localStorageFileLineEdit->text();
    QString destination = QFileDialog::getExistingDirectory(this,
                                                            ("选择目录"),
                                                            source,
                                                            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!destination.isEmpty())
    {
        if (!destination.endsWith("/"))
        {
            destination += "/";
        }
        if (source != destination)
        {
            checkDirIsWritable(destination);
            ui.localStorageFileLineEdit->setText(destination);
            TNPathUtil::SetUserRecFile(destination);
            saveLocalPathSettingToDB();
        }
    }
}

void TNLocaleStorageSettingWidget::slotOpenDirFileDialog()
{
    QString userRecFile = ui.localStorageFileLineEdit->text();
    //创建文件目录，有则不创建，没有则创建
    TNPathUtil::CreateFilePath(userRecFile);
    QDesktopServices::openUrl(QUrl::fromLocalFile(userRecFile));
}

void TNLocaleStorageSettingWidget::saveSendHotKeySettingToDB()
{
    st_SetUpPtr localPathSetting = std::make_shared<st_SetUp>();
    localPathSetting->SetKey("SendHotKey");
    localPathSetting->SetValue(ui.comboBox->currentText());
    TNDataControlServer::GetInstance()->InsertDatas(std::dynamic_pointer_cast<TableBase>(localPathSetting), DBTYPE_USER);
}

void TNLocaleStorageSettingWidget::saveScreenShotHotKeySettingToDB(const QString &key)
{
    st_SetUpPtr localPathSetting = std::make_shared<st_SetUp>();
    localPathSetting->SetKey("ScreenShotHotKey");
    localPathSetting->SetValue(key);
    TNDataControlServer::GetInstance()->InsertDatas(std::dynamic_pointer_cast<TableBase>(localPathSetting), DBTYPE_USER);
}

void TNLocaleStorageSettingWidget::saveLocalPathSettingToDB()
{
    st_SetUpPtr localPathSetting = std::make_shared<st_SetUp>();
    localPathSetting->SetKey("LocalPath");
    localPathSetting->SetValue(ui.localStorageFileLineEdit->text());
    TNDataControlServer::GetInstance()->InsertDatas(std::dynamic_pointer_cast<TableBase>(localPathSetting), DBTYPE_USER);
}

void TNLocaleStorageSettingWidget::checkDirIsWritable(const QString &path)
{
    qInfo()<<"[SetUp][TNLocaleStorageSettingWidget]checkDirIsWritable-path="<<path;
#ifdef Q_OS_WIN
    int retValue = _access(path.toStdString().c_str(), 06);
#else
    int retValue = access(path.toStdString().c_str(), 6);
#endif
    if (retValue == -1)
    {
        TNStorageErrorTipsDialog messageBox(this);
        if (messageBox.exec() == QDialog::Accepted)
        {

        }
    }
}

bool TNLocaleStorageSettingWidget::eventFilter(QObject *target, QEvent *event)
{
    if (target == ui.localStorageFileLineEdit)
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(event);
            if (keyEvent)
            {
                do
                {
                    if (keyEvent->key() == Qt::Key_Left || keyEvent->key() == Qt::Key_Right)
                    {
                        break;
                    }
                    if (keyEvent->key() == Qt::Key_C && QApplication::keyboardModifiers() == Qt::ControlModifier)
                    {
                        break;
                    }
                    //其他输入性质的键盘事件禁止
                    return true;
                } while (false);
            }
        }
    }
    return QWidget::eventFilter(target, event);
}

void TNLocaleStorageSettingWidget::onHotKeyChanged(const QString &key)
{
    TNNotifyCenter::instance()->postNotifySendHotKeyChanged(key);
    TNSettingData::instance()->SetSendHotKey(key);
    saveSendHotKeySettingToDB();
}

void TNLocaleStorageSettingWidget::slotShortCutSettingDialog()
{    
    TNShortCutSettingDialog shortCutSettingDialog(ui.screentShotShortCut->text());
    TNUtil::moveCenterInMainWidget(&shortCutSettingDialog);
    if (shortCutSettingDialog.exec() == QDialog::Accepted)
    {
        QString screenShotHotKey = shortCutSettingDialog.getShortCutText();
        if (screenShotHotKey.isEmpty())
        {
            screenShotHotKey = QString("NULL");
            ui.screentShotShortCut->setText(("设置快捷键"));
        }
        else
        {
            QString uiTextByText = TNShortCutKeyTextMap::getUiTextByText(screenShotHotKey);
            ui.screentShotShortCut->setText(uiTextByText);
        }
        TNSettingData::instance()->SetScreenShotKey(screenShotHotKey);
        saveScreenShotHotKeySettingToDB(screenShotHotKey);
        registerScreenHotKey(screenShotHotKey);
    }
}

void TNLocaleStorageSettingWidget::onCheckBoxStateChanged(int state)
{
}

void TNLocaleStorageSettingWidget::registerScreenHotKey(const QString &key)
{
    //TNGlobalShotCutManagement::instance()->setScreenShotKey(key);
}

void TNLocaleStorageSettingWidget::onScreenShotKey(QxtGlobalShortcut* self)
{
    qInfo()<<"[SetUp][TNLocaleStorageSettingWidget]onScreenShotKey begin...";
    if (TNScreenShot::getCurrentScreenShot())
        return;

    QWidget *pCurrent = TNUtil::getMainWidget();
    bool currentIsActive = pCurrent->isActiveWindow();
    qInfo()<<"[SetUp][TNLocaleStorageSettingWidget]onScreenShotKey currentIsActive="<<currentIsActive;
    bool hasToastBlackWidget = false;
    QWidget *modalWidget = qApp->activeModalWidget();
    if (modalWidget && (modalWidget->objectName() == QString("TNMessageBox")))
        hasToastBlackWidget = true;
    qInfo()<<"[SetUp][TNLocaleStorageSettingWidget]onScreenShotKey hasToastBlackWidget="<<hasToastBlackWidget;
#ifdef Q_OS_WIN
    if (TNSettingData::instance()->IsHideAtScreenShot() && pCurrent)
    {
        qInfo()<<"[SetUp][TNLocaleStorageSettingWidget]onScreenShotKey showMinimized";
        pCurrent->showMinimized();
    }
#endif
    // 为解决Bug29注释掉（快捷键截图时不应该主动激活toon主窗口）
    /*
    if (pCurrent)
    {
        // 解决Bug503: QQ聊天图片打开时，使用toon截图快捷键无法截图
        pCurrent->activateWindow();
    }*/
    TN::ScreenShotExitFlag exitFlag = TNScreenShot::screenShot();
    if (pCurrent)
    {
        if (currentIsActive || hasToastBlackWidget)
        {
            pCurrent->showNormal();
            pCurrent->activateWindow();

            qInfo()<<"[SetUp][TNLocaleStorageSettingWidget]onScreenShotKey. exitFlag="<<exitFlag;
            if (exitFlag == TN::FinishedExit)
            {
                TNNotifyCenter::instance()->postNotifyFinishedScreenShotByShortCut();
            }
        }
        else
        {
            // 为解决Bug792注释掉（添加成员、创建群聊等弹框截图后就自动关闭了）
            /*
            QWidget *pCurrent = qApp->activeModalWidget();
            if (pCurrent)
                pCurrent->hide();
            */
        }
    }
    qInfo()<<"[SetUp][TNLocaleStorageSettingWidget]onScreenShotKey end.";
}
