/********************************************************************************
** Form generated from reading UI file 'TNBatchSendFileConfirmDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNBATCHSENDFILECONFIRMDIALOG_H
#define UI_TNBATCHSENDFILECONFIRMDIALOG_H

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
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TNBatchSendFileConfirmDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *chooseCardTitleLabel;
    QVBoxLayout *verticalLayout;
    QTableWidget *cardTableWidget;
    QLabel *warningTipLabel;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *TNBatchSendFileConfirmDialog)
    {
        if (TNBatchSendFileConfirmDialog->objectName().isEmpty())
            TNBatchSendFileConfirmDialog->setObjectName(QStringLiteral("TNBatchSendFileConfirmDialog"));
        TNBatchSendFileConfirmDialog->resize(360, 402);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TNBatchSendFileConfirmDialog->sizePolicy().hasHeightForWidth());
        TNBatchSendFileConfirmDialog->setSizePolicy(sizePolicy);
        TNBatchSendFileConfirmDialog->setMinimumSize(QSize(360, 402));
        TNBatchSendFileConfirmDialog->setMaximumSize(QSize(360, 422));
        verticalLayout_2 = new QVBoxLayout(TNBatchSendFileConfirmDialog);
        verticalLayout_2->setSpacing(10);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(30, 14, 2, 30);
        chooseCardTitleLabel = new QLabel(TNBatchSendFileConfirmDialog);
        chooseCardTitleLabel->setObjectName(QStringLiteral("chooseCardTitleLabel"));
        chooseCardTitleLabel->setAlignment(Qt::AlignCenter);
        chooseCardTitleLabel->setIndent(-30);

        verticalLayout_2->addWidget(chooseCardTitleLabel);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 20, -1, -1);
        cardTableWidget = new QTableWidget(TNBatchSendFileConfirmDialog);
        cardTableWidget->setObjectName(QStringLiteral("cardTableWidget"));

        verticalLayout->addWidget(cardTableWidget);


        verticalLayout_2->addLayout(verticalLayout);

        warningTipLabel = new QLabel(TNBatchSendFileConfirmDialog);
        warningTipLabel->setObjectName(QStringLiteral("warningTipLabel"));
        warningTipLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(warningTipLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, 30, -1);
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okButton = new QPushButton(TNBatchSendFileConfirmDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(okButton);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        cancelButton = new QPushButton(TNBatchSendFileConfirmDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(cancelButton);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(4, 1);

        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(TNBatchSendFileConfirmDialog);

        QMetaObject::connectSlotsByName(TNBatchSendFileConfirmDialog);
    } // setupUi

    void retranslateUi(QDialog *TNBatchSendFileConfirmDialog)
    {
        TNBatchSendFileConfirmDialog->setWindowTitle(QString());
        chooseCardTitleLabel->setText(QApplication::translate("TNBatchSendFileConfirmDialog", "\345\217\221\351\200\201\351\231\204\344\273\266", 0));
        warningTipLabel->setText(QApplication::translate("TNBatchSendFileConfirmDialog", "\344\270\200\346\254\241\345\217\221\351\200\201\347\232\204\351\231\204\344\273\266\346\225\260\344\270\215\350\203\275\350\266\205\350\277\2079\344\270\252", 0));
        okButton->setText(QApplication::translate("TNBatchSendFileConfirmDialog", "\345\217\221\351\200\201", 0));
        cancelButton->setText(QApplication::translate("TNBatchSendFileConfirmDialog", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class TNBatchSendFileConfirmDialog: public Ui_TNBatchSendFileConfirmDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNBATCHSENDFILECONFIRMDIALOG_H
