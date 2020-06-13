/********************************************************************************
** Form generated from reading UI file 'TNCheckUpdateDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNCHECKUPDATEDIALOG_H
#define UI_TNCHECKUPDATEDIALOG_H

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

class Ui_TNCheckUpdateDialog
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

    void setupUi(QDialog *TNCheckUpdateDialog)
    {
        if (TNCheckUpdateDialog->objectName().isEmpty())
            TNCheckUpdateDialog->setObjectName(QStringLiteral("TNCheckUpdateDialog"));
        TNCheckUpdateDialog->resize(350, 161);
        TNCheckUpdateDialog->setMinimumSize(QSize(350, 160));
        TNCheckUpdateDialog->setMaximumSize(QSize(350, 161));
        verticalLayout_2 = new QVBoxLayout(TNCheckUpdateDialog);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 20);
        exitConfirmTitleWidget = new QWidget(TNCheckUpdateDialog);
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

        tipsLabel = new QLabel(TNCheckUpdateDialog);
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

        okButton = new QPushButton(TNCheckUpdateDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(okButton);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        dialogCloseButton = new QPushButton(TNCheckUpdateDialog);
        dialogCloseButton->setObjectName(QStringLiteral("dialogCloseButton"));
        dialogCloseButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(dialogCloseButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(4, 1);

        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(TNCheckUpdateDialog);

        QMetaObject::connectSlotsByName(TNCheckUpdateDialog);
    } // setupUi

    void retranslateUi(QDialog *TNCheckUpdateDialog)
    {
        TNCheckUpdateDialog->setWindowTitle(QApplication::translate("TNCheckUpdateDialog", "Dialog", 0));
        confirmTitleLabel->setText(QApplication::translate("TNCheckUpdateDialog", "\346\217\220\347\244\272", 0));
        tipsLabel->setText(QApplication::translate("TNCheckUpdateDialog", "\345\275\223\345\211\215\347\211\210\346\234\254\345\267\262\347\273\217\346\230\257\346\234\200\346\226\260\347\211\210\346\234\254", 0));
        okButton->setText(QApplication::translate("TNCheckUpdateDialog", "\347\241\256\345\256\232", 0));
        dialogCloseButton->setText(QApplication::translate("TNCheckUpdateDialog", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class TNCheckUpdateDialog: public Ui_TNCheckUpdateDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNCHECKUPDATEDIALOG_H
