#include "SetUpListArea.h"

#include <QDir>
#include <QLabel>
#include <QSettings>
#include <QToolButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCoreApplication>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>

#include "TNDataControlServer.h"
#include "TNSetUp.h"
#include "TNSettingData.h"
#include "TNNoticeUpdater.h"
#include "TNProgressLoadingWithPrompt.h"

#include "TNUtil.h"
#include "ListAreaBase.h"
#include "TNPromptSignLabel.h"
#include "tnnotifycenter.h"
#include "TNDataCache.h"
#include "TNExitLoginConfirmDialog.h"
#include "common_global.h"
#include "TNVersionInfo.h"
SetUpListArea::SetUpListArea(int id, TNPluginParamPtr pluginParam, QWidget *parent)
	: ListAreaBase(id, parent)
	, _pluginParam(pluginParam)
    , _promptSignLabel(nullptr)
    , _ProgressLoadingWidget(nullptr)
    , _noticeUpdator(nullptr)
	, _appearanceButton(nullptr)
{		
    //注：由原来的“本地存储设置”更改为通用设置，控件名字不再更改
	_localeStorageButton = new QPushButton(("通用设置"), this);
	_localeStorageButton->setObjectName("localeStorageButton");
	_localeStorageButton->setCheckable(true);
	_localeStorageButton->setFlat(true);
	_localeStorageButton->setContentsMargins(0, 0, 0, 0);

	if (TNVersionInfo::IsBaseToonVersion())
	{
		_appearanceButton = new QPushButton(("皮肤设置"), this);
		_appearanceButton->setObjectName("appearanceButton");
		_appearanceButton->setCheckable(true);
		_appearanceButton->setFlat(true);
		_appearanceButton->setContentsMargins(0, 0, 0, 0);
	}
	_userAgreementButton = new QPushButton(("用户使用协议"), this);
	_userAgreementButton->setObjectName("userAgreementButton");
	_userAgreementButton->setCheckable(true);
	_userAgreementButton->setFlat(true);
	_userAgreementButton->setContentsMargins(0, 0, 0, 0);
		
	_aboutUsButton = new QPushButton(("关于我们"), this);
	_aboutUsButton->setObjectName("aboutUsButton");
	_aboutUsButton->setCheckable(true);
	_aboutUsButton->setFlat(true);
	_aboutUsButton->setContentsMargins(0, 0, 0, 0);

	_exitLoginButton = new QPushButton(("退出登录"), this);
	_exitLoginButton->setObjectName("exitLoginButton");
	_exitLoginButton->setCheckable(true);
	_exitLoginButton->setFlat(true);
	_exitLoginButton->setContentsMargins(0, 0, 0, 0);
	
    _syncCatalog = new QPushButton(("同步通讯录"), this);
    _syncCatalog->setObjectName("syncCatalog");
	_syncCatalog->setCheckable(true);
    _syncCatalog->setFlat(true);
    _syncCatalog->setContentsMargins(0, 0, 0, 0);
	
	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->setSpacing(0);
	mainLayout->addWidget(_localeStorageButton);
	if (_appearanceButton)
		mainLayout->addWidget(_appearanceButton);
	mainLayout->addWidget(_userAgreementButton);
	mainLayout->addWidget(_aboutUsButton);
	mainLayout->addWidget(_exitLoginButton);
    mainLayout->addWidget(_syncCatalog);
    _syncCatalog->setVisible(false);
	mainLayout->setContentsMargins(0, 0, 0, 0);

	QWidget * mainWidget = new QWidget(this);
	mainWidget->setLayout(mainLayout);
	mainWidget->setObjectName("SetUpListArea");

	if (_appearanceButton)
		connect(_appearanceButton, SIGNAL(clicked()), this, SLOT(slotAppearanceButton()));
	connect(_localeStorageButton, SIGNAL(clicked()), this, SLOT(slotLocaleStorageButton()));
	connect(_userAgreementButton, SIGNAL(clicked()), this, SLOT(slotUserAgreementButton()));
	connect(_aboutUsButton, SIGNAL(clicked()), this, SLOT(slotAboutUsButton()));
	connect(_syncCatalog, SIGNAL(clicked()), this, SLOT(slotSyncCatalogButton()));
	connect(_exitLoginButton, SIGNAL(clicked()), this, SLOT(slotExitLoginButton()));

	InitSettings();

    TNNotifyCenter::instance()->connectNotifyCheckVersionFinished(this);
    if (!TNSettingData::instance()->isNewestVersion())
    {
        _promptSignLabel = new TNPromptSignLabel(_aboutUsButton, TNPromptSignLabel::CenterRight);
    }
}

SetUpListArea::~SetUpListArea()
{
    m_syncCatalogThread.quit();
    delete _noticeUpdator;
}

void SetUpListArea::InitSettings()
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

	std::map<QString, QString>::const_iterator iter3 = records.find("LocalPath");
	QString strLocalPath = "";
	if (iter3 != records.end())
	{
		strLocalPath = iter3->second;
	}

	std::map<QString, QString>::const_iterator iter4 = records.find("SendHotKey");
	QString strSendHotKey = "";
	if (iter4 != records.end())
	{
		strSendHotKey = iter4->second;
	}
	std::map<QString, QString>::const_iterator iter5 = records.find("ScreenShotHotKey");
	QString strScreenShotHotKey = "";
	if (iter5 != records.end())
	{
        strScreenShotHotKey = iter5->second;
	}

	std::map<QString, QString>::const_iterator iter6 = records.find("IsHideAtScreenShot");
    bool isHideAtScreenShot = false;
    if (iter6 != records.end())
	{
        if (iter6->second == ("1"))
		{
            isHideAtScreenShot = true;
		}
	}

	TNSettingData::instance()->SetLocalPath(strLocalPath);
	TNSettingData::instance()->SetSendHotKey(strSendHotKey);
    TNSettingData::instance()->SetScreenShotKey(strScreenShotHotKey);
    TNSettingData::instance()->SetHideAtScreenShot(isHideAtScreenShot);
}

void SetUpListArea::slotAppearanceButton()
{
    setAllButtonUnchecked();
    _appearanceButton->setChecked(true);
	emit clickedButton(SetUpListArea::skinSet);
}

void SetUpListArea::slotLocaleStorageButton()
{
    setAllButtonUnchecked();
	_localeStorageButton->setChecked(true);
	emit clickedButton(SetUpListArea::localeStorage);
}

void SetUpListArea::slotUserAgreementButton()
{
    setAllButtonUnchecked();
	_userAgreementButton->setChecked(true);
	emit clickedButton(SetUpListArea::userAgreement);
}

void SetUpListArea::slotAboutUsButton()
{
    setAllButtonUnchecked();
	_aboutUsButton->setChecked(true);
	emit clickedButton(SetUpListArea::aboutUs);
}

void SetUpListArea::slotExitLoginButton()
{
    setAllButtonUnchecked();
	_exitLoginButton->setChecked(true);
	emit clickedButton(SetUpListArea::exitLogin);
}

void SetUpListArea::slotSyncCatalogButton()
{
    setAllButtonUnchecked();
    _syncCatalog->setChecked(true);
    emit clickedButton(SetUpListArea::backgroundWidget);
    //注意：此处用的“确认对话框”和“退出登录对话框样式”完全一样
    TNExitLoginConfirmDialog *confirmDialog = new TNExitLoginConfirmDialog(0);
    confirmDialog->setObjectName("exitConfirmDialog");
    confirmDialog->setContentsMargins(0, 0, 0, 0);
    confirmDialog->setAttribute(Qt::WA_DeleteOnClose);
    confirmDialog->setTitle(("同步提示"));
    confirmDialog->setText(("是否同步通讯录？"));
    if (confirmDialog->exec() == QDialog::Accepted)
    {
		TNDataCache::GetInstance()->ReSetCache();
        if (_ProgressLoadingWidget == nullptr)
        {
            _ProgressLoadingWidget = new TNProgressLoadingWithPrompt(this);
        }
        _ProgressLoadingWidget->setText(("正在同步..."));
        if (!m_syncCatalogThread.isRunning())
        {
            m_syncCatalogThread.start();
        }
        if (_noticeUpdator == nullptr)
        {
            _noticeUpdator = new TNNoticeUpdater(false);
            _noticeUpdator->moveToThread(&m_syncCatalogThread);
            connect(this, SIGNAL(syncCatalogStart()), _noticeUpdator, SLOT(StartUpdateThread()));
            connect(_noticeUpdator, SIGNAL(AllUpdateFinished()), this, SLOT(onSyncCatalogFinised()));
        }
        emit syncCatalogStart();

        _ProgressLoadingWidget->showLoding();
    }
    _syncCatalog->setChecked(false);
    //_syncCatalog->setStyleSheet("background-color: transparent;");
}

void SetUpListArea::setAllButtonUnchecked()
{
	_localeStorageButton->setChecked(false);
	_aboutUsButton->setChecked(false);
	_exitLoginButton->setChecked(false);
	_userAgreementButton->setChecked(false);
    _syncCatalog->setChecked(false);
	if (_appearanceButton)
		_appearanceButton->setChecked(false);
}

void SetUpListArea::on_notifyCheckVersionFinished(bool isNeedUpgrade,
                                                  bool isForceUpgrade,
                                                  QString downLoadURL,
                                                  int nCheckType,
                                                  QString versionDecs
                                                  )
{
    if (nullptr == _promptSignLabel)
    {
        if (isNeedUpgrade)
        {
            _promptSignLabel = new TNPromptSignLabel(_aboutUsButton, TNPromptSignLabel::CenterRight);
            _promptSignLabel->relocate();
        }
    }
}

void SetUpListArea::onSyncCatalogFinised()
{
    _ProgressLoadingWidget->setAttribute(Qt::WA_DeleteOnClose);
    _ProgressLoadingWidget->setText(("同步完成"));
    _ProgressLoadingWidget->showComplete(3000);
    _ProgressLoadingWidget = nullptr;
}

