/********************************************************************************
** Form generated from reading UI file 'TNExitLoginConfirmDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNEXITLOGINCONFIRMDIALOG_H
#define UI_TNEXITLOGINCONFIRMDIALOG_H

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

class Ui_TNExitLoginConfirmDialog
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
    QSpacerItem *horizontalSpacer_2;
    QPushButton *dialogCloseButton;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *TNExitLoginConfirmDialog)
    {
        if (TNExitLoginConfirmDialog->objectName().isEmpty())
            TNExitLoginConfirmDialog->setObjectName(QStringLiteral("TNExitLoginConfirmDialog"));
        TNExitLoginConfirmDialog->resize(350, 160);
        TNExitLoginConfirmDialog->setMinimumSize(QSize(350, 160));
        TNExitLoginConfirmDialog->setMaximumSize(QSize(350, 181));
        verticalLayout_2 = new QVBoxLayout(TNExitLoginConfirmDialog);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 20);
        exitConfirmTitleWidget = new QWidget(TNExitLoginConfirmDialog);
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
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        tipsLabel = new QLabel(TNExitLoginConfirmDialog);
        tipsLabel->setObjectName(QStringLiteral("tipsLabel"));
        tipsLabel->setIndent(40);

        verticalLayout->addWidget(tipsLabel);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, 0, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okButton = new QPushButton(TNExitLoginConfirmDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(okButton);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        dialogCloseButton = new QPushButton(TNExitLoginConfirmDialog);
        dialogCloseButton->setObjectName(QStringLiteral("dialogCloseButton"));
        dialogCloseButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(dialogCloseButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(4, 1);

        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(TNExitLoginConfirmDialog);

        QMetaObject::connectSlotsByName(TNExitLoginConfirmDialog);
    } // setupUi

    void retranslateUi(QDialog *TNExitLoginConfirmDialog)
    {
        TNExitLoginConfirmDialog->setWindowTitle(QApplication::translate("TNExitLoginConfirmDialog", "Dialog", 0));
        confirmTitleLabel->setText(QApplication::translate("TNExitLoginConfirmDialog", "\351\200\200\345\207\272\347\231\273\345\275\225", 0));
        tipsLabel->setText(QApplication::translate("TNExitLoginConfirmDialog", "\351\200\200\345\207\272\347\231\273\345\275\225\345\220\216\345\260\206\346\227\240\346\263\225\346\224\266\345\210\260\346\226\260\346\266\210\346\201\257\357\274\214\347\241\256\345\256\232\351\200\200\345\207\272\347\231\273\345\275\225\357\274\237", 0));
        okButton->setText(QApplication::translate("TNExitLoginConfirmDialog", "\347\241\256\345\256\232", 0));
        dialogCloseButton->setText(QApplication::translate("TNExitLoginConfirmDialog", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class TNExitLoginConfirmDialog: public Ui_TNExitLoginConfirmDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNEXITLOGINCONFIRMDIALOG_H
