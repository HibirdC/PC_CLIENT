/********************************************************************************
** Form generated from reading UI file 'TNLoginWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNLOGINWIDGET_H
#define UI_TNLOGINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TNLoginWidget
{
public:
    QStackedWidget *stackedWidget;
    QLabel *label_bottom;
    QPushButton *btn_close;
    QPushButton *btn_min;
    QPushButton *btn_qrcode;

    void setupUi(QWidget *TNLoginWidget)
    {
        if (TNLoginWidget->objectName().isEmpty())
            TNLoginWidget->setObjectName(QStringLiteral("TNLoginWidget"));
        TNLoginWidget->resize(320, 432);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TNLoginWidget->sizePolicy().hasHeightForWidth());
        TNLoginWidget->setSizePolicy(sizePolicy);
        TNLoginWidget->setMinimumSize(QSize(320, 432));
        TNLoginWidget->setMaximumSize(QSize(320, 432));
        TNLoginWidget->setAutoFillBackground(true);
        TNLoginWidget->setStyleSheet(QStringLiteral(""));
        stackedWidget = new QStackedWidget(TNLoginWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(11, 30, 298, 332));
        stackedWidget->setMinimumSize(QSize(100, 100));
        label_bottom = new QLabel(TNLoginWidget);
        label_bottom->setObjectName(QStringLiteral("label_bottom"));
        label_bottom->setGeometry(QRect(42, 291, 100, 30));
        label_bottom->setAlignment(Qt::AlignCenter);
        btn_close = new QPushButton(TNLoginWidget);
        btn_close->setObjectName(QStringLiteral("btn_close"));
        btn_close->setGeometry(QRect(290, 0, 32, 23));
        sizePolicy.setHeightForWidth(btn_close->sizePolicy().hasHeightForWidth());
        btn_close->setSizePolicy(sizePolicy);
        btn_close->setMaximumSize(QSize(16777215, 16777215));
        btn_min = new QPushButton(TNLoginWidget);
        btn_min->setObjectName(QStringLiteral("btn_min"));
        btn_min->setGeometry(QRect(250, 0, 32, 23));
        btn_min->setMaximumSize(QSize(16777215, 16777215));
        btn_qrcode = new QPushButton(TNLoginWidget);
        btn_qrcode->setObjectName(QStringLiteral("btn_qrcode"));
        btn_qrcode->setGeometry(QRect(18, 10, 16, 16));
        btn_qrcode->setCursor(QCursor(Qt::PointingHandCursor));
        btn_qrcode->setIconSize(QSize(30, 26));
        btn_qrcode->setCheckable(true);

        retranslateUi(TNLoginWidget);

        QMetaObject::connectSlotsByName(TNLoginWidget);
    } // setupUi

    void retranslateUi(QWidget *TNLoginWidget)
    {
        TNLoginWidget->setWindowTitle(QApplication::translate("TNLoginWidget", "LoginBody", 0));
        label_bottom->setText(QApplication::translate("TNLoginWidget", "\345\212\250\347\224\273\346\225\210\346\236\234", 0));
        btn_close->setText(QString());
        btn_min->setText(QString());
        btn_qrcode->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TNLoginWidget: public Ui_TNLoginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNLOGINWIDGET_H
