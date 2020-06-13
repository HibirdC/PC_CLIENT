/********************************************************************************
** Form generated from reading UI file 'TNStorageErrorTipsDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNSTORAGEERRORTIPSDIALOG_H
#define UI_TNSTORAGEERRORTIPSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TNStorageErrorTipsDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *confirmTitleLabel;
    QHBoxLayout *horizontalLayout;
    QPushButton *offlineIcon;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *offlineContentLabel;
    QLabel *offlineContentLabel2;
    QLabel *offlineContentLabel3;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *okButton;
    QLabel *spaceLabel;
    QPushButton *closeButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *TNStorageErrorTipsDialog)
    {
        if (TNStorageErrorTipsDialog->objectName().isEmpty())
            TNStorageErrorTipsDialog->setObjectName(QStringLiteral("TNStorageErrorTipsDialog"));
        TNStorageErrorTipsDialog->resize(418, 180);
        TNStorageErrorTipsDialog->setMinimumSize(QSize(418, 180));
        TNStorageErrorTipsDialog->setMaximumSize(QSize(418, 186));
        verticalLayout_3 = new QVBoxLayout(TNStorageErrorTipsDialog);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(20, 0, 20, 20);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 10, -1, -1);
        confirmTitleLabel = new QLabel(TNStorageErrorTipsDialog);
        confirmTitleLabel->setObjectName(QStringLiteral("confirmTitleLabel"));
        confirmTitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(confirmTitleLabel);


        verticalLayout_3->addLayout(verticalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 12, -1, 12);
        offlineIcon = new QPushButton(TNStorageErrorTipsDialog);
        offlineIcon->setObjectName(QStringLiteral("offlineIcon"));
        offlineIcon->setMinimumSize(QSize(66, 66));
        offlineIcon->setMaximumSize(QSize(66, 66));

        horizontalLayout->addWidget(offlineIcon);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(12, -1, -1, -1);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        offlineContentLabel = new QLabel(TNStorageErrorTipsDialog);
        offlineContentLabel->setObjectName(QStringLiteral("offlineContentLabel"));
        offlineContentLabel->setMinimumSize(QSize(0, 24));
        offlineContentLabel->setMaximumSize(QSize(16777215, 24));
        offlineContentLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(offlineContentLabel);

        offlineContentLabel2 = new QLabel(TNStorageErrorTipsDialog);
        offlineContentLabel2->setObjectName(QStringLiteral("offlineContentLabel2"));
        offlineContentLabel2->setMinimumSize(QSize(0, 24));
        offlineContentLabel2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(offlineContentLabel2);

        offlineContentLabel3 = new QLabel(TNStorageErrorTipsDialog);
        offlineContentLabel3->setObjectName(QStringLiteral("offlineContentLabel3"));

        verticalLayout->addWidget(offlineContentLabel3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, -1);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        okButton = new QPushButton(TNStorageErrorTipsDialog);
        okButton->setObjectName(QStringLiteral("okButton"));

        horizontalLayout_2->addWidget(okButton);

        spaceLabel = new QLabel(TNStorageErrorTipsDialog);
        spaceLabel->setObjectName(QStringLiteral("spaceLabel"));

        horizontalLayout_2->addWidget(spaceLabel);

        closeButton = new QPushButton(TNStorageErrorTipsDialog);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        closeButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(closeButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_2);


        retranslateUi(TNStorageErrorTipsDialog);

        QMetaObject::connectSlotsByName(TNStorageErrorTipsDialog);
    } // setupUi

    void retranslateUi(QDialog *TNStorageErrorTipsDialog)
    {
        TNStorageErrorTipsDialog->setWindowTitle(QApplication::translate("TNStorageErrorTipsDialog", "Dialog", 0));
        confirmTitleLabel->setText(QApplication::translate("TNStorageErrorTipsDialog", "\346\217\220\347\244\272", 0));
        offlineIcon->setText(QString());
        offlineContentLabel->setText(QApplication::translate("TNStorageErrorTipsDialog", "\346\226\207\344\273\266\345\255\230\345\202\250\344\275\215\347\275\256\346\235\203\351\231\220\345\255\230\345\234\250\351\227\256\351\242\230\357\274\214\345\217\257\350\203\275\344\274\232\345\257\274\350\207\264\346\202\250\347\232\204\351\203\250", 0));
        offlineContentLabel2->setText(QApplication::translate("TNStorageErrorTipsDialog", "\345\210\206\345\212\237\350\203\275\344\270\215\345\217\257\347\224\250\357\274\214\350\257\267\345\211\215\345\216\273\342\200\234\350\256\276\347\275\256-\351\200\232\347\224\250\350\256\276\347\275\256-\346\234\254\345\234\260\345\255\230", 0));
        offlineContentLabel3->setText(QApplication::translate("TNStorageErrorTipsDialog", "\345\202\250\350\256\276\347\275\256\342\200\235\344\270\255\346\233\264\346\224\271", 0));
        okButton->setText(QApplication::translate("TNStorageErrorTipsDialog", "\347\241\256\345\256\232", 0));
        spaceLabel->setText(QString());
        closeButton->setText(QApplication::translate("TNStorageErrorTipsDialog", "\345\205\263\351\227\255", 0));
    } // retranslateUi

};

namespace Ui {
    class TNStorageErrorTipsDialog: public Ui_TNStorageErrorTipsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNSTORAGEERRORTIPSDIALOG_H
