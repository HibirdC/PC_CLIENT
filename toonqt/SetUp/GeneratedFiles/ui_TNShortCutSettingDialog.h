/********************************************************************************
** Form generated from reading UI file 'TNShortCutSettingDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNSHORTCUTSETTINGDIALOG_H
#define UI_TNSHORTCUTSETTINGDIALOG_H

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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TNShortCutSettingDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *exitConfirmTitleWidget;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *confirmTitleLabel;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *tipsLabel;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *TNShortCutSettingDialog)
    {
        if (TNShortCutSettingDialog->objectName().isEmpty())
            TNShortCutSettingDialog->setObjectName(QStringLiteral("TNShortCutSettingDialog"));
        TNShortCutSettingDialog->resize(350, 161);
        TNShortCutSettingDialog->setMinimumSize(QSize(350, 160));
        TNShortCutSettingDialog->setMaximumSize(QSize(350, 161));
        verticalLayout_2 = new QVBoxLayout(TNShortCutSettingDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 30);
        exitConfirmTitleWidget = new QWidget(TNShortCutSettingDialog);
        exitConfirmTitleWidget->setObjectName(QStringLiteral("exitConfirmTitleWidget"));
        exitConfirmTitleWidget->setMinimumSize(QSize(100, 20));
        horizontalLayout_3 = new QHBoxLayout(exitConfirmTitleWidget);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(1, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        confirmTitleLabel = new QLabel(exitConfirmTitleWidget);
        confirmTitleLabel->setObjectName(QStringLiteral("confirmTitleLabel"));
        confirmTitleLabel->setAlignment(Qt::AlignCenter);
        confirmTitleLabel->setIndent(0);

        horizontalLayout_2->addWidget(confirmTitleLabel);

        horizontalLayout_2->setStretch(0, 1);

        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_2->addWidget(exitConfirmTitleWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        tipsLabel = new QLabel(TNShortCutSettingDialog);
        tipsLabel->setObjectName(QStringLiteral("tipsLabel"));
        tipsLabel->setAlignment(Qt::AlignCenter);
        tipsLabel->setIndent(40);

        verticalLayout->addWidget(tipsLabel);

        verticalSpacer_2 = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(30);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, 0, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okButton = new QPushButton(TNShortCutSettingDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(TNShortCutSettingDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(cancelButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(TNShortCutSettingDialog);

        QMetaObject::connectSlotsByName(TNShortCutSettingDialog);
    } // setupUi

    void retranslateUi(QDialog *TNShortCutSettingDialog)
    {
        TNShortCutSettingDialog->setWindowTitle(QApplication::translate("TNShortCutSettingDialog", "Dialog", 0));
        confirmTitleLabel->setText(QApplication::translate("TNShortCutSettingDialog", "\350\256\276\347\275\256\346\210\252\345\233\276\345\277\253\346\215\267\351\224\256", 0));
        tipsLabel->setText(QApplication::translate("TNShortCutSettingDialog", "Alt+A", 0));
        okButton->setText(QApplication::translate("TNShortCutSettingDialog", "\347\241\256\345\256\232", 0));
        cancelButton->setText(QApplication::translate("TNShortCutSettingDialog", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class TNShortCutSettingDialog: public Ui_TNShortCutSettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNSHORTCUTSETTINGDIALOG_H
