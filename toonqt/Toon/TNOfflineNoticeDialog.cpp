#include "TNOfflineNoticeDialog.h"
#include "ui_TNOfflineNoticeDialog.h"
#include "TNVersionInfo.h"
TNOfflineNoticeDialog::TNOfflineNoticeDialog(int mode, QWidget *parent) :
/*QDialog*/DropShadowWidget(parent),
ui(new Ui::TNOfflineNoticeDialog)
{
	ui->setupUi(this);
	if (mode == warning)
	{
		ui->OfflineFixButton->setVisible(false);
		ui->spaceLabel->setVisible(false);
	}
	else if (mode == errorAndFixed)
	{
		ui->OfflineFixButton->setObjectName("offlineButton");
		ui->OfflineFixButton->setVisible(true);
		ui->spaceLabel->setFixedWidth(20);
		ui->spaceLabel->setVisible(true);
		connect(ui->OfflineFixButton, SIGNAL(clicked()), this, SLOT(accept()));
	}
    connect(ui->offlineButton, SIGNAL(clicked()), this, SLOT(close()));
    this->setWindowIcon(TOON_ICON);
    this->setWindowTitle(TOON_TITLE);
    this->setObjectName("TNOfflineNoticeDialog");
}

TNOfflineNoticeDialog::~TNOfflineNoticeDialog()
{
    delete ui;
}
void TNOfflineNoticeDialog::setText(const QString title, const QString contect)
{
	ui->offlineTitleLabel->setText(title);
	ui->offlineContentLabel->setText(contect);
}