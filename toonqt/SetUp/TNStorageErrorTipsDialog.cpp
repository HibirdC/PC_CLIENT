#include "TNStorageErrorTipsDialog.h"
#include "ui_TNStorageErrorTipsDialog.h"

#include "TNVersionInfo.h"

TNStorageErrorTipsDialog::TNStorageErrorTipsDialog(QWidget *parent) :
    /*QDialog*/DropShadowWidget(parent),
    ui(new Ui::TNStorageErrorTipsDialog)
{
    ui->setupUi(this);

    ui->closeButton->hide();

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(close()));

    this->setWindowIcon(TOON_ICON);
    this->setWindowTitle(TOON_TITLE);
    this->setObjectName("TNOfflineNoticeDialog");
}

TNStorageErrorTipsDialog::~TNStorageErrorTipsDialog()
{
    delete ui;
}
