/********************************************************************************
** Form generated from reading UI file 'TNExitGroupChatConfirmDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNEXITGROUPCHATCONFIRMDIALOG_H
#define UI_TNEXITGROUPCHATCONFIRMDIALOG_H

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

class Ui_TNExitGroupChatConfirmDialog
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
    QSpacerItem *horizontalSpacer_3;
    QPushButton *dialogCloseButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *TNExitGroupChatConfirmDialog)
    {
        if (TNExitGroupChatConfirmDialog->objectName().isEmpty())
            TNExitGroupChatConfirmDialog->setObjectName(QStringLiteral("TNExitGroupChatConfirmDialog"));
        TNExitGroupChatConfirmDialog->resize(350, 161);
        TNExitGroupChatConfirmDialog->setMinimumSize(QSize(350, 160));
        TNExitGroupChatConfirmDialog->setMaximumSize(QSize(350, 161));
        verticalLayout_2 = new QVBoxLayout(TNExitGroupChatConfirmDialog);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 20);
        exitConfirmTitleWidget = new QWidget(TNExitGroupChatConfirmDialog);
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

        tipsLabel = new QLabel(TNExitGroupChatConfirmDialog);
        tipsLabel->setObjectName(QStringLiteral("tipsLabel"));
        tipsLabel->setAlignment(Qt::AlignCenter);
        tipsLabel->setIndent(40);

        verticalLayout->addWidget(tipsLabel);

        verticalSpacer_2 = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, 0, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okButton = new QPushButton(TNExitGroupChatConfirmDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(okButton);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        dialogCloseButton = new QPushButton(TNExitGroupChatConfirmDialog);
        dialogCloseButton->setObjectName(QStringLiteral("dialogCloseButton"));
        dialogCloseButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(dialogCloseButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(4, 1);

        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(TNExitGroupChatConfirmDialog);

        QMetaObject::connectSlotsByName(TNExitGroupChatConfirmDialog);
    } // setupUi

    void retranslateUi(QDialog *TNExitGroupChatConfirmDialog)
    {
        TNExitGroupChatConfirmDialog->setWindowTitle(QApplication::translate("TNExitGroupChatConfirmDialog", "Dialog", 0));
        confirmTitleLabel->setText(QApplication::translate("TNExitGroupChatConfirmDialog", "\346\217\220\347\244\272", 0));
        tipsLabel->setText(QApplication::translate("TNExitGroupChatConfirmDialog", "\347\241\256\345\256\232\345\210\240\351\231\244\345\271\266\351\200\200\345\207\272\347\276\244\350\201\212\357\274\237", 0));
        okButton->setText(QApplication::translate("TNExitGroupChatConfirmDialog", "\347\241\256\345\256\232", 0));
        dialogCloseButton->setText(QApplication::translate("TNExitGroupChatConfirmDialog", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class TNExitGroupChatConfirmDialog: public Ui_TNExitGroupChatConfirmDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNEXITGROUPCHATCONFIRMDIALOG_H
