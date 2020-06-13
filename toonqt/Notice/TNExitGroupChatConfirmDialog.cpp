#include "TNExitGroupChatConfirmDialog.h"
#include "ui_TNExitGroupChatConfirmDialog.h"
#include "TNVersionInfo.h"
TNExitGroupChatConfirmDialog::TNExitGroupChatConfirmDialog(QWidget *parent) :
/*QDialog*/DropShadowWidget(parent),
ui(new Ui::TNExitGroupChatConfirmDialog)
{
    ui->setupUi(this);

	connect(ui->dialogCloseButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
	
    this->setWindowIcon(TOON_ICON);
    this->setWindowTitle(TOON_TITLE);
}

TNExitGroupChatConfirmDialog::~TNExitGroupChatConfirmDialog()
{
    delete ui;
}
