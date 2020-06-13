/********************************************************************************
** Form generated from reading UI file 'TNJoinGroupChatConfirmDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNJOINGROUPCHATCONFIRMDIALOG_H
#define UI_TNJOINGROUPCHATCONFIRMDIALOG_H

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
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TNJoinGroupChatConfirmDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *chooseCardTitleLabel;
    QVBoxLayout *verticalLayout;
    QLabel *chooseCardLabel;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *meToolButton;
    QLabel *chooseCardArrow;
    QToolButton *groupChatToolButton;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *TNJoinGroupChatConfirmDialog)
    {
        if (TNJoinGroupChatConfirmDialog->objectName().isEmpty())
            TNJoinGroupChatConfirmDialog->setObjectName(QStringLiteral("TNJoinGroupChatConfirmDialog"));
        TNJoinGroupChatConfirmDialog->resize(344, 247);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TNJoinGroupChatConfirmDialog->sizePolicy().hasHeightForWidth());
        TNJoinGroupChatConfirmDialog->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(TNJoinGroupChatConfirmDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(50, 0, 50, 30);
        chooseCardTitleLabel = new QLabel(TNJoinGroupChatConfirmDialog);
        chooseCardTitleLabel->setObjectName(QStringLiteral("chooseCardTitleLabel"));
        chooseCardTitleLabel->setMinimumSize(QSize(0, 40));
        chooseCardTitleLabel->setMaximumSize(QSize(16777215, 40));
        chooseCardTitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(chooseCardTitleLabel);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        chooseCardLabel = new QLabel(TNJoinGroupChatConfirmDialog);
        chooseCardLabel->setObjectName(QStringLiteral("chooseCardLabel"));
        chooseCardLabel->setMinimumSize(QSize(0, 24));
        chooseCardLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout->addWidget(chooseCardLabel);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        meToolButton = new QToolButton(TNJoinGroupChatConfirmDialog);
        meToolButton->setObjectName(QStringLiteral("meToolButton"));
        meToolButton->setMinimumSize(QSize(80, 80));

        horizontalLayout_2->addWidget(meToolButton);

        chooseCardArrow = new QLabel(TNJoinGroupChatConfirmDialog);
        chooseCardArrow->setObjectName(QStringLiteral("chooseCardArrow"));
        chooseCardArrow->setMinimumSize(QSize(30, 26));
        chooseCardArrow->setMaximumSize(QSize(30, 26));
        chooseCardArrow->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(chooseCardArrow);

        groupChatToolButton = new QToolButton(TNJoinGroupChatConfirmDialog);
        groupChatToolButton->setObjectName(QStringLiteral("groupChatToolButton"));
        groupChatToolButton->setMinimumSize(QSize(80, 80));

        horizontalLayout_2->addWidget(groupChatToolButton);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 30, -1, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okButton = new QPushButton(TNJoinGroupChatConfirmDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(okButton);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        cancelButton = new QPushButton(TNJoinGroupChatConfirmDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(cancelButton);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(4, 1);

        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(TNJoinGroupChatConfirmDialog);

        QMetaObject::connectSlotsByName(TNJoinGroupChatConfirmDialog);
    } // setupUi

    void retranslateUi(QDialog *TNJoinGroupChatConfirmDialog)
    {
        TNJoinGroupChatConfirmDialog->setWindowTitle(QApplication::translate("TNJoinGroupChatConfirmDialog", "\351\200\211\346\213\251\345\220\215\347\211\207", 0));
        chooseCardTitleLabel->setText(QApplication::translate("TNJoinGroupChatConfirmDialog", "\347\276\244\350\201\212", 0));
        chooseCardLabel->setText(QApplication::translate("TNJoinGroupChatConfirmDialog", "\347\241\256\345\256\232\344\275\277\347\224\250\350\257\245\345\220\215\347\211\207\345\212\240\345\205\245\347\276\244\350\201\212", 0));
        meToolButton->setText(QApplication::translate("TNJoinGroupChatConfirmDialog", "\346\210\221", 0));
        chooseCardArrow->setText(QString());
        groupChatToolButton->setText(QApplication::translate("TNJoinGroupChatConfirmDialog", "\347\276\244\350\201\212", 0));
        okButton->setText(QApplication::translate("TNJoinGroupChatConfirmDialog", "\347\241\256\345\256\232", 0));
        cancelButton->setText(QApplication::translate("TNJoinGroupChatConfirmDialog", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class TNJoinGroupChatConfirmDialog: public Ui_TNJoinGroupChatConfirmDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNJOINGROUPCHATCONFIRMDIALOG_H
