#include "tnsearchbottom.h"
#include "ui_tnsearchbottom.h"

tnsearchbottom::tnsearchbottom(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::tnsearchbottom)
{
	ui->setupUi(this);
}

tnsearchbottom::~tnsearchbottom()
{
	delete ui;
}
void tnsearchbottom::setButtomFixedHeight(int y)
{
	setFixedHeight(y);
	ui->tableView->setFixedHeight(y);
}
void tnsearchbottom::setButtomFixedWidth(int x)
{
	setFixedWidth(x);
	ui->tableView->setFixedWidth(x);
}
