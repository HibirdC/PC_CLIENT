#include "TNWarningMessageBox.h"
#include <QHBoxLayout>
#include <QLabel>

TNWarningMessageBox::TNWarningMessageBox(QWidget *parent)
: QDialog(parent)
{
    setObjectName("TNWarningMessageBox");
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::FramelessWindowHint);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    setLayout(mainLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    _msgLabel = new QLabel();
    _msgLabel->setObjectName("TNWarningMessageText");
    _msgLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(_msgLabel);
}

TNWarningMessageBox::~TNWarningMessageBox()
{
}

void TNWarningMessageBox::setMsg(const QString msg)
{
    _msgLabel->setText(msg);
}
