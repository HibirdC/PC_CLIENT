/********************************************************************************
** Form generated from reading UI file 'QRCodeScanForm02.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QRCODESCANFORM02_H
#define UI_QRCODESCANFORM02_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QRCodeScanForm02
{
public:
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_title;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *mobileLabel;
    QVBoxLayout *verticalLayout;
    QLabel *confirmTextLabel;
    QVBoxLayout *verticalLayout_3;
    QPushButton *backCodeScanButton;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *QRCodeScanForm02)
    {
        if (QRCodeScanForm02->objectName().isEmpty())
            QRCodeScanForm02->setObjectName(QStringLiteral("QRCodeScanForm02"));
        QRCodeScanForm02->resize(223, 303);
        verticalLayout_5 = new QVBoxLayout(QRCodeScanForm02);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 22, -1, 90);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_title = new QLabel(QRCodeScanForm02);
        label_title->setObjectName(QStringLiteral("label_title"));

        horizontalLayout->addWidget(label_title);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_4->addLayout(horizontalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        mobileLabel = new QLabel(QRCodeScanForm02);
        mobileLabel->setObjectName(QStringLiteral("mobileLabel"));
        mobileLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(mobileLabel);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 20, -1, 40);
        confirmTextLabel = new QLabel(QRCodeScanForm02);
        confirmTextLabel->setObjectName(QStringLiteral("confirmTextLabel"));
        confirmTextLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(confirmTextLabel);


        verticalLayout_4->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        backCodeScanButton = new QPushButton(QRCodeScanForm02);
        backCodeScanButton->setObjectName(QStringLiteral("backCodeScanButton"));

        verticalLayout_3->addWidget(backCodeScanButton);


        verticalLayout_4->addLayout(verticalLayout_3);

        verticalSpacer_2 = new QSpacerItem(17, 68, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);


        verticalLayout_5->addLayout(verticalLayout_4);


        retranslateUi(QRCodeScanForm02);

        QMetaObject::connectSlotsByName(QRCodeScanForm02);
    } // setupUi

    void retranslateUi(QWidget *QRCodeScanForm02)
    {
        QRCodeScanForm02->setWindowTitle(QApplication::translate("QRCodeScanForm02", "Form", 0));
        label_title->setText(QString());
        mobileLabel->setText(QApplication::translate("QRCodeScanForm02", "13811487498", 0));
        confirmTextLabel->setText(QApplication::translate("QRCodeScanForm02", "\350\257\267\345\234\250\346\211\213\346\234\272\344\270\212\347\241\256\350\256\244\347\231\273\345\275\225", 0));
        backCodeScanButton->setText(QApplication::translate("QRCodeScanForm02", "\350\277\224\345\233\236\346\211\253\347\240\201\347\231\273\345\275\225", 0));
    } // retranslateUi

};

namespace Ui {
    class QRCodeScanForm02: public Ui_QRCodeScanForm02 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QRCODESCANFORM02_H
