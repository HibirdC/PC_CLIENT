/********************************************************************************
** Form generated from reading UI file 'TNRemoveGroupChatMemberDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNREMOVEGROUPCHATMEMBERDIALOG_H
#define UI_TNREMOVEGROUPCHATMEMBERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TNRemoveGroupChatMemberDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QWidget *groupchatTitleWidget;
    QVBoxLayout *verticalLayout_4;
    QLabel *DialogTitleLabel;
    QGridLayout *gridLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *haveSelectedLabel;
    QSpacerItem *horizontalSpacer_3;
    QTableView *leftTableView;
    QVBoxLayout *verticalLayout;
    QTableView *rightTableView;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *TNRemoveGroupChatMemberDialog)
    {
        if (TNRemoveGroupChatMemberDialog->objectName().isEmpty())
            TNRemoveGroupChatMemberDialog->setObjectName(QStringLiteral("TNRemoveGroupChatMemberDialog"));
        TNRemoveGroupChatMemberDialog->resize(580, 482);
        TNRemoveGroupChatMemberDialog->setMinimumSize(QSize(580, 482));
        TNRemoveGroupChatMemberDialog->setMaximumSize(QSize(580, 482));
        TNRemoveGroupChatMemberDialog->setFocusPolicy(Qt::StrongFocus);
        verticalLayout_3 = new QVBoxLayout(TNRemoveGroupChatMemberDialog);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(30, 10, 30, 30);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupchatTitleWidget = new QWidget(TNRemoveGroupChatMemberDialog);
        groupchatTitleWidget->setObjectName(QStringLiteral("groupchatTitleWidget"));
        verticalLayout_4 = new QVBoxLayout(groupchatTitleWidget);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 18);
        DialogTitleLabel = new QLabel(groupchatTitleWidget);
        DialogTitleLabel->setObjectName(QStringLiteral("DialogTitleLabel"));
        DialogTitleLabel->setAlignment(Qt::AlignCenter);
        DialogTitleLabel->setIndent(0);

        verticalLayout_4->addWidget(DialogTitleLabel);


        verticalLayout_2->addWidget(groupchatTitleWidget);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(20);
        gridLayout->setVerticalSpacing(10);
        widget = new QWidget(TNRemoveGroupChatMemberDialog);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(250, 0));
        widget->setMaximumSize(QSize(250, 16777215));

        gridLayout->addWidget(widget, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        haveSelectedLabel = new QLabel(TNRemoveGroupChatMemberDialog);
        haveSelectedLabel->setObjectName(QStringLiteral("haveSelectedLabel"));

        horizontalLayout->addWidget(haveSelectedLabel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 1);

        leftTableView = new QTableView(TNRemoveGroupChatMemberDialog);
        leftTableView->setObjectName(QStringLiteral("leftTableView"));
        leftTableView->setMinimumSize(QSize(250, 0));
        leftTableView->setMaximumSize(QSize(250, 16777215));

        gridLayout->addWidget(leftTableView, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        rightTableView = new QTableView(TNRemoveGroupChatMemberDialog);
        rightTableView->setObjectName(QStringLiteral("rightTableView"));
        rightTableView->setMinimumSize(QSize(250, 0));
        rightTableView->setMaximumSize(QSize(250, 16777215));

        verticalLayout->addWidget(rightTableView);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 20, 0, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        okButton = new QPushButton(TNRemoveGroupChatMemberDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_4->addWidget(okButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        cancelButton = new QPushButton(TNRemoveGroupChatMemberDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_4->addWidget(cancelButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_4);


        gridLayout->addLayout(verticalLayout, 1, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


        verticalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(TNRemoveGroupChatMemberDialog);

        QMetaObject::connectSlotsByName(TNRemoveGroupChatMemberDialog);
    } // setupUi

    void retranslateUi(QDialog *TNRemoveGroupChatMemberDialog)
    {
        TNRemoveGroupChatMemberDialog->setWindowTitle(QApplication::translate("TNRemoveGroupChatMemberDialog", "\351\200\211\346\213\251\350\201\224\347\263\273\344\272\272", 0));
        DialogTitleLabel->setText(QApplication::translate("TNRemoveGroupChatMemberDialog", "\345\210\240\351\231\244\346\210\220\345\221\230", 0));
        haveSelectedLabel->setText(QApplication::translate("TNRemoveGroupChatMemberDialog", "\345\267\262\351\200\211\346\213\251\347\232\204\350\201\224\347\263\273\344\272\272", 0));
        okButton->setText(QApplication::translate("TNRemoveGroupChatMemberDialog", "\347\241\256\345\256\232", 0));
        cancelButton->setText(QApplication::translate("TNRemoveGroupChatMemberDialog", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class TNRemoveGroupChatMemberDialog: public Ui_TNRemoveGroupChatMemberDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNREMOVEGROUPCHATMEMBERDIALOG_H
