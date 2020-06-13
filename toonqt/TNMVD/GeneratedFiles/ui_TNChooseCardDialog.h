/********************************************************************************
** Form generated from reading UI file 'TNChooseCardDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNCHOOSECARDDIALOG_H
#define UI_TNCHOOSECARDDIALOG_H

#include <CommentTextEdit.h>
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

class Ui_TNChooseCardDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QLabel *chooseCardTitleLabel;
    QVBoxLayout *verticalLayout_2;
    QLabel *commentLabel;
    CommentTextEdit *commentTextEdit;
    QVBoxLayout *verticalLayout;
    QLabel *chooseCardLabel;
    QTableWidget *cardTableWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *TNChooseCardDialog)
    {
        if (TNChooseCardDialog->objectName().isEmpty())
            TNChooseCardDialog->setObjectName(QStringLiteral("TNChooseCardDialog"));
        TNChooseCardDialog->resize(360, 497);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TNChooseCardDialog->sizePolicy().hasHeightForWidth());
        TNChooseCardDialog->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(TNChooseCardDialog);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(32, 0, 32, 30);
        chooseCardTitleLabel = new QLabel(TNChooseCardDialog);
        chooseCardTitleLabel->setObjectName(QStringLiteral("chooseCardTitleLabel"));
        chooseCardTitleLabel->setMinimumSize(QSize(0, 40));
        chooseCardTitleLabel->setMaximumSize(QSize(16777215, 40));
        chooseCardTitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(chooseCardTitleLabel);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        commentLabel = new QLabel(TNChooseCardDialog);
        commentLabel->setObjectName(QStringLiteral("commentLabel"));

        verticalLayout_2->addWidget(commentLabel);

        commentTextEdit = new CommentTextEdit(TNChooseCardDialog);
        commentTextEdit->setObjectName(QStringLiteral("commentTextEdit"));

        verticalLayout_2->addWidget(commentTextEdit);


        verticalLayout_3->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        chooseCardLabel = new QLabel(TNChooseCardDialog);
        chooseCardLabel->setObjectName(QStringLiteral("chooseCardLabel"));

        verticalLayout->addWidget(chooseCardLabel);

        cardTableWidget = new QTableWidget(TNChooseCardDialog);
        cardTableWidget->setObjectName(QStringLiteral("cardTableWidget"));

        verticalLayout->addWidget(cardTableWidget);


        verticalLayout_3->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okButton = new QPushButton(TNChooseCardDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(okButton);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        cancelButton = new QPushButton(TNChooseCardDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(cancelButton);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(4, 1);

        verticalLayout_3->addLayout(horizontalLayout);


        retranslateUi(TNChooseCardDialog);

        QMetaObject::connectSlotsByName(TNChooseCardDialog);
    } // setupUi

    void retranslateUi(QDialog *TNChooseCardDialog)
    {
        TNChooseCardDialog->setWindowTitle(QApplication::translate("TNChooseCardDialog", "\351\200\211\346\213\251\345\220\215\347\211\207", 0));
        chooseCardTitleLabel->setText(QApplication::translate("TNChooseCardDialog", "Title", 0));
        commentLabel->setText(QApplication::translate("TNChooseCardDialog", "\350\257\264\347\202\271\345\225\245", 0));
        chooseCardLabel->setText(QApplication::translate("TNChooseCardDialog", "\350\257\267\351\200\211\346\213\251\345\220\215\347\211\207\357\274\232", 0));
        okButton->setText(QApplication::translate("TNChooseCardDialog", "\347\241\256\345\256\232", 0));
        cancelButton->setText(QApplication::translate("TNChooseCardDialog", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class TNChooseCardDialog: public Ui_TNChooseCardDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNCHOOSECARDDIALOG_H
