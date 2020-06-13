#include "SetUpDetailsArea.h"
#include "ui_SetUpDetailsArea.h"
#include "ui_TNBackgroudWidget.h"

#include <QStackedWidget>
#include <QTextEdit>

#include "AppearanceWidget.h"
#include "TNLocaleStorageSettingWidget.h"
#include "TNAboutUsWidget.h"
#include "TNExitLoginWidget.h"
#include "TNSkinSet.h"
#include "TNVersionInfo.h"
SetUpDetailsArea::SetUpDetailsArea(int id, TNPluginParamPtr pluginParam, QWidget *parent)
: DetailsAreaBase(id, parent)
, _pluginParam(pluginParam)
{
	ui = new Ui::SetUpDetailsArea();
	ui->setupUi(this);

	_stackedWidget = new QStackedWidget(this);
	_stackedWidget->setObjectName("stackedWidget");

	TNLocaleStorageSettingWidget *storageWidget = new TNLocaleStorageSettingWidget(this);
	connect(storageWidget, SIGNAL(updateSettingStatus(QString, int)), this, SIGNAL(updateSettingStatus(QString, int)));
	_stackedWidget->addWidget(storageWidget);

	TNSkinSet* skinSet = new TNSkinSet(this);
	_stackedWidget->addWidget(skinSet);

	QTextEdit *userAgreeWidget = new QTextEdit(this);
	userAgreeWidget->setObjectName("userAgreeWidget");
    userAgreeWidget->setReadOnly(true);
    _stackedWidget->addWidget(userAgreeWidget);
	
    //加载用户协议文件内容

    QFile agreementFile(TNVersionInfo::GetUserProtocolHtml());

	if (agreementFile.open(QFile::ReadOnly | QFile::Text))
	{
		userAgreeWidget->setHtml(QString::fromUtf8(agreementFile.readAll()));
		agreementFile.close();
	}

	TNAboutUsWidget *aboutUsWidget = new TNAboutUsWidget(_pluginParam, this);
	_stackedWidget->addWidget(aboutUsWidget); 

	TNExitLoginWidget *exitLoginWidget = new TNExitLoginWidget(_pluginParam, this);
	connect(exitLoginWidget, SIGNAL(SendQuitSignal()), this, SIGNAL(SendQuitSignal()));
	_stackedWidget->addWidget(exitLoginWidget);

    QWidget *backgroundWidget = new QWidget(this);
    backgroudUi = new Ui::backgroundWidget();
    backgroudUi->setupUi(backgroundWidget);
    _stackedWidget->addWidget(backgroundWidget);
    _stackedWidget->setCurrentIndex(_stackedWidget->count() - 1);

	QVBoxLayout * mainLayout = new QVBoxLayout(this);
	mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 24, 0, 0);
	mainLayout->addWidget(_stackedWidget);
	this->setLayout(mainLayout); 
}

SetUpDetailsArea::~SetUpDetailsArea()
{
    delete backgroudUi;
	delete ui;
}

void SetUpDetailsArea::setCurrentWidgetIndex(int index)
{
	_stackedWidget->setCurrentIndex(index);
}
