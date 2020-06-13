#include "TNDefaultPage.h"
#include "ui_TNDefaultPage.h"

TNDefaultPage::TNDefaultPage(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::TNDefaultPage)
{
	ui->setupUi(this);
//    ui->label_nullpage_pic->setScaledContents(true);
	ui->label_nullpage_text->setAlignment(Qt::AlignCenter);
}

TNDefaultPage::~TNDefaultPage()
{

}
void TNDefaultPage::setTextTitle(const QString &text)
{
	ui->label_nullpage_text->setText(text);
}
void TNDefaultPage::setBackPic(const QString & objectname, QSize size)
{
    ui->label_nullpage_pic->setObjectName(objectname);
//	QPixmap pic = QPixmap(path);
//	pic = pic.scaled(60, 60, Qt::KeepAspectRatio);
//	ui->label_nullpage_pic->setPixmap(pic);
}
void TNDefaultPage::setBorderImage(const QString &path)
{
    ui->label_nullpage_pic->setStyleSheet(QString("border-image: url(%1);").arg(path));
}
