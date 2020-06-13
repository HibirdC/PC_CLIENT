/********************************************************************************
** Form generated from reading UI file 'QRCodeScanForm01.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QRCODESCANFORM01_H
#define UI_QRCODESCANFORM01_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QRCodeScanForm01
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_title;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *qrPixmapLabel;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_scantip;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *QRCodeScanForm01)
    {
        if (QRCodeScanForm01->objectName().isEmpty())
            QRCodeScanForm01->setObjectName(QStringLiteral("QRCodeScanForm01"));
        QRCodeScanForm01->resize(288, 303);
        verticalLayout_2 = new QVBoxLayout(QRCodeScanForm01);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(20, 0, 20, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 22, -1, 18);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_title = new QLabel(QRCodeScanForm01);
        label_title->setObjectName(QStringLiteral("label_title"));
        label_title->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_title);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 30, -1, 30);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        qrPixmapLabel = new QLabel(QRCodeScanForm01);
        qrPixmapLabel->setObjectName(QStringLiteral("qrPixmapLabel"));
        qrPixmapLabel->setMinimumSize(QSize(100, 100));
        qrPixmapLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(qrPixmapLabel);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);

        label_scantip = new QLabel(QRCodeScanForm01);
        label_scantip->setObjectName(QStringLiteral("label_scantip"));
        label_scantip->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_scantip);

        verticalSpacer_2 = new QSpacerItem(20, 71, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(QRCodeScanForm01);

        QMetaObject::connectSlotsByName(QRCodeScanForm01);
    } // setupUi

    void retranslateUi(QWidget *QRCodeScanForm01)
    {
        QRCodeScanForm01->setWindowTitle(QApplication::translate("QRCodeScanForm01", "Form", 0));
        label_title->setText(QString());
        qrPixmapLabel->setText(QApplication::translate("QRCodeScanForm01", "\344\272\214\347\273\264\347\240\201\345\233\276", 0));
        label_scantip->setText(QApplication::translate("QRCodeScanForm01", "\350\257\267\344\275\277\347\224\250\347\201\253\350\212\261IM\346\211\213\346\234\272\347\211\210\346\211\253\346\217\217\344\272\214\347\273\264\347\240\201\347\231\273\345\275\225", 0));
    } // retranslateUi

};

namespace Ui {
    class QRCodeScanForm01: public Ui_QRCodeScanForm01 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QRCODESCANFORM01_H
