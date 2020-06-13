#include "TNLanguageChangeTipDialog.h"
#include "ui_TNLanguageChangeTipDialog.h"
#include "TNVersionInfo.h"
TNLanguageChangeTipDialog::TNLanguageChangeTipDialog(QWidget *parent) :
    /*QDialog*/DropShadowWidget(parent),
    ui(new Ui::TNLanguageChangeTipDialog)
{
    ui->setupUi(this);

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));

    this->setWindowIcon(TOON_ICON);
    this->setWindowTitle(TOON_TITLE);
    this->setObjectName("TNLanguageChangeTipDialog");
}

TNLanguageChangeTipDialog::~TNLanguageChangeTipDialog()
{
    delete ui;
}
