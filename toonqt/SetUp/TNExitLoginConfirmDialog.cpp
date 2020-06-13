#include "TNExitLoginConfirmDialog.h"
#include "ui_TNExitLoginConfirmDialog.h"
#include "TNVersionInfo.h"
TNExitLoginConfirmDialog::TNExitLoginConfirmDialog(QWidget *parent) :
/*QDialog*/DropShadowWidget(parent),
    ui(new Ui::TNExitLoginConfirmDialog)
{
    ui->setupUi(this);

	//connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(ui->dialogCloseButton, SIGNAL(clicked()), this, SLOT(reject()));

	//ui->closeButton->setText(QString::null);
//#ifndef Q_OS_WIN
//    ui->horizontalLayout_2->removeWidget(ui->closeButton);
//    ui->horizontalLayout_2->insertWidget(0, ui->closeButton);
//    ui->horizontalLayout_2->setContentsMargins(10,0,16,0);
//    ui->closeButton->setObjectName("macClose");
//    ui->confirmTitleLabel->setAlignment(Qt::AlignCenter);
//#endif
	this->setWindowFlags(Qt::FramelessWindowHint);

    this->setWindowIcon(TOON_ICON);
    this->setWindowTitle(TOON_TITLE);
}

TNExitLoginConfirmDialog::~TNExitLoginConfirmDialog()
{
    delete ui;
}

void TNExitLoginConfirmDialog::setTitle(const QString &strTitle)
{
    ui->confirmTitleLabel->setText(strTitle);
}

void TNExitLoginConfirmDialog::setText(const QString &strText)
{
    ui->tipsLabel->setText(strText);
}
