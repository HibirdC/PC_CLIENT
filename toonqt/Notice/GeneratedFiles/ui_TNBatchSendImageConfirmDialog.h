/********************************************************************************
** Form generated from reading UI file 'TNBatchSendImageConfirmDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNBATCHSENDIMAGECONFIRMDIALOG_H
#define UI_TNBATCHSENDIMAGECONFIRMDIALOG_H

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

class Ui_TNBatchSendImageConfirmDialog
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

    void setupUi(QDialog *TNBatchSendImageConfirmDialog)
    {
        if (TNBatchSendImageConfirmDialog->objectName().isEmpty())
            TNBatchSendImageConfirmDialog->setObjectName(QStringLiteral("TNBatchSendImageConfirmDialog"));
        TNBatchSendImageConfirmDialog->resize(360, 434);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TNBatchSendImageConfirmDialog->sizePolicy().hasHeightForWidth());
        TNBatchSendImageConfirmDialog->setSizePolicy(sizePolicy);
        TNBatchSendImageConfirmDialog->setMinimumSize(QSize(360, 0));
        TNBatchSendImageConfirmDialog->setMaximumSize(QSize(360, 16777215));
        verticalLayout_2 = new QVBoxLayout(TNBatchSendImageConfirmDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(40, 14, 30, 30);
        chooseCardTitleLabel = new QLabel(TNBatchSendImageConfirmDialog);
        chooseCardTitleLabel->setObjectName(QStringLiteral("chooseCardTitleLabel"));
        chooseCardTitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(chooseCardTitleLabel);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 20, -1, -1);
        cardTableWidget = new QTableWidget(TNBatchSendImageConfirmDialog);
        cardTableWidget->setObjectName(QStringLiteral("cardTableWidget"));

        verticalLayout->addWidget(cardTableWidget);


        verticalLayout_2->addLayout(verticalLayout);

        warningTipLabel = new QLabel(TNBatchSendImageConfirmDialog);
        warningTipLabel->setObjectName(QStringLiteral("warningTipLabel"));
        warningTipLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(warningTipLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 10, -1, -1);
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okButton = new QPushButton(TNBatchSendImageConfirmDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(okButton);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        cancelButton = new QPushButton(TNBatchSendImageConfirmDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(cancelButton);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(4, 1);

        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(TNBatchSendImageConfirmDialog);

        QMetaObject::connectSlotsByName(TNBatchSendImageConfirmDialog);
    } // setupUi

    void retranslateUi(QDialog *TNBatchSendImageConfirmDialog)
    {
        TNBatchSendImageConfirmDialog->setWindowTitle(QString());
        chooseCardTitleLabel->setText(QApplication::translate("TNBatchSendImageConfirmDialog", "\345\217\221\351\200\201\345\233\276\347\211\207", 0));
        warningTipLabel->setText(QApplication::translate("TNBatchSendImageConfirmDialog", "\344\270\200\346\254\241\345\217\221\351\200\201\347\232\204\345\233\276\347\211\207\346\225\260\344\270\215\350\203\275\350\266\205\350\277\2079\344\270\252", 0));
        okButton->setText(QApplication::translate("TNBatchSendImageConfirmDialog", "\345\217\221\351\200\201", 0));
        cancelButton->setText(QApplication::translate("TNBatchSendImageConfirmDialog", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class TNBatchSendImageConfirmDialog: public Ui_TNBatchSendImageConfirmDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNBATCHSENDIMAGECONFIRMDIALOG_H
