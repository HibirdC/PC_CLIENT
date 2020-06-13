#include "TNOpForgetPsdTipDialog.h"
#include "ui_TNOpForgetPsdTipDialog.h"

#include "TNVersionInfo.h"

TNOpForgetPsdTipDialog::TNOpForgetPsdTipDialog(QWidget *parent) :
    /*QDialog*/DropShadowWidget(parent),
    ui(new Ui::TNOpForgetPsdTipDialog)
{
    ui->setupUi(this);

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));

    this->setWindowIcon(TOON_ICON);
    this->setWindowTitle(TOON_TITLE);
    this->setObjectName("TNOpForgetPsdTipDialog");
}

TNOpForgetPsdTipDialog::~TNOpForgetPsdTipDialog()
{
    delete ui;
}
