#include "TNCheckUpdateDialog.h"
#include "ui_TNCheckUpdateDialog.h"
#include "TNVersionInfo.h"
TNCheckUpdateDialog::TNCheckUpdateDialog(QWidget *parent) :
/*QDialog*/DropShadowWidget(parent),
ui(new Ui::TNCheckUpdateDialog)
{
    ui->setupUi(this);

	connect(ui->dialogCloseButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
	
    this->setWindowIcon(TOON_ICON);
    this->setWindowTitle(TOON_TITLE);
}

TNCheckUpdateDialog::~TNCheckUpdateDialog()
{
    delete ui;
}
