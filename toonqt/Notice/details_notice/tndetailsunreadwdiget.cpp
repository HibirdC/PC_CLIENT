#include "tndetailsunreadwdiget.h"
#include "ui_tndetailsunreadwdiget.h"
#include "TNConfig.h"

TNDetailsUnreadWdiget::TNDetailsUnreadWdiget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TNDetailsUnreadWdiget)
  , _upUnreadNum(0)
  , _downUnreadNum(0)
  , _upOrDown(false)
{
    ui->setupUi(this);
    this->setFixedWidth(ui->details_unread_button_up->width() + 30);
    LANGUE_TYPE languageIndex = TNConfig::instance()->GetCurrentLangueSet();
    if (languageIndex == TYPE_LANGUE_EN){
        this->setObjectName("TNDetailsUnreadWdiget_EN");
    }
    connect(ui->details_unread_button_down,SIGNAL(clicked()),
            this,SIGNAL(downClicked()));
    connect(ui->details_unread_button_up,SIGNAL(clicked()),
            this,SIGNAL(upClicked()));
    ui->details_unread_button_close->setCursor(Qt::PointingHandCursor);
    ui->details_unread_button_down->setCursor(Qt::PointingHandCursor);
    ui->details_unread_button_up->setCursor(Qt::PointingHandCursor);
}

TNDetailsUnreadWdiget::~TNDetailsUnreadWdiget()
{
    delete ui;
}

void TNDetailsUnreadWdiget::on_details_unread_button_close_clicked()
{
    hide();
}

void TNDetailsUnreadWdiget::setUpAndDown(bool up)
{
    if(up){
        ui->details_unread_button_up->show();
        ui->details_unread_button_down->hide();
    }else{
        ui->details_unread_button_up->hide();
        ui->details_unread_button_down->show();
    }
    _upOrDown = up;
}

void TNDetailsUnreadWdiget::setUpUnReadNum(int number)
{
    _upUnreadNum = number;
    if(_upUnreadNum > 0){
        QString strNum = QString(tr(QStringLiteral("%1条新消息").toUtf8().data()).arg(_upUnreadNum));
        ui->details_unread_button_up->setText(strNum);
    }
}

void TNDetailsUnreadWdiget::setDownUnReadNum(int number)
{
    _downUnreadNum = number;
}

void TNDetailsUnreadWdiget::addUpUnreadNum()
{
    _upUnreadNum++;
	QString strNum = QString(tr(QStringLiteral("%1条新消息").toUtf8().data()).arg(_upUnreadNum));
    ui->details_unread_button_up->setText(strNum);
}

void TNDetailsUnreadWdiget::addDownUnreadNum()
{
    _downUnreadNum++;
	QString strNum = QString(tr(QStringLiteral("%1条新消息").toUtf8().data()).arg(_downUnreadNum));
    ui->details_unread_button_down->setText(strNum);
}

void TNDetailsUnreadWdiget::paintEvent(QPaintEvent * event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
