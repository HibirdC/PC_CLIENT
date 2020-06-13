/********************************************************************************
** Form generated from reading UI file 'TNInputGroupChatNameDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNINPUTGROUPCHATNAMEDIALOG_H
#define UI_TNINPUTGROUPCHATNAMEDIALOG_H

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
#include <emotion/TNEmotionLineEdit.h>

QT_BEGIN_NAMESPACE

class Ui_TNInputGroupChatNameDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *confirmTitleLabel;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    TNEmotionLineEdit *groupChatLineEdit;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *groupNameOkButton;
    QPushButton *dialogCloseButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *TNInputGroupChatNameDialog)
    {
        if (TNInputGroupChatNameDialog->objectName().isEmpty())
            TNInputGroupChatNameDialog->setObjectName(QStringLiteral("TNInputGroupChatNameDialog"));
        TNInputGroupChatNameDialog->resize(350, 160);
        TNInputGroupChatNameDialog->setMinimumSize(QSize(350, 160));
        TNInputGroupChatNameDialog->setMaximumSize(QSize(350, 160));
        verticalLayout_2 = new QVBoxLayout(TNInputGroupChatNameDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 10, 0, -1);
        confirmTitleLabel = new QLabel(TNInputGroupChatNameDialog);
        confirmTitleLabel->setObjectName(QStringLiteral("confirmTitleLabel"));
        confirmTitleLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(confirmTitleLabel);

        horizontalLayout->setStretch(0, 1);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 12, -1, 12);
        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        groupChatLineEdit = new TNEmotionLineEdit(TNInputGroupChatNameDialog);
        groupChatLineEdit->setObjectName(QStringLiteral("groupChatLineEdit"));
        groupChatLineEdit->setMaxLength(30);

        horizontalLayout_3->addWidget(groupChatLineEdit);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(25);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        groupNameOkButton = new QPushButton(TNInputGroupChatNameDialog);
        groupNameOkButton->setObjectName(QStringLiteral("groupNameOkButton"));
        groupNameOkButton->setCursor(QCursor(Qt::PointingHandCursor));
        groupNameOkButton->setFlat(true);

        horizontalLayout_2->addWidget(groupNameOkButton);

        dialogCloseButton = new QPushButton(TNInputGroupChatNameDialog);
        dialogCloseButton->setObjectName(QStringLiteral("dialogCloseButton"));
        dialogCloseButton->setCursor(QCursor(Qt::PointingHandCursor));
        dialogCloseButton->setFlat(true);

        horizontalLayout_2->addWidget(dialogCloseButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(TNInputGroupChatNameDialog);

        QMetaObject::connectSlotsByName(TNInputGroupChatNameDialog);
    } // setupUi

    void retranslateUi(QDialog *TNInputGroupChatNameDialog)
    {
        TNInputGroupChatNameDialog->setWindowTitle(QApplication::translate("TNInputGroupChatNameDialog", "Dialog", 0));
        confirmTitleLabel->setText(QApplication::translate("TNInputGroupChatNameDialog", "\344\277\256\346\224\271\347\276\244\350\201\212\345\220\215\347\247\260", 0));
        groupNameOkButton->setText(QApplication::translate("TNInputGroupChatNameDialog", "\347\241\256\345\256\232", 0));
        dialogCloseButton->setText(QApplication::translate("TNInputGroupChatNameDialog", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class TNInputGroupChatNameDialog: public Ui_TNInputGroupChatNameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNINPUTGROUPCHATNAMEDIALOG_H
