/********************************************************************************
** Form generated from reading UI file 'TNGroupChatMembersWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNGROUPCHATMEMBERSWIDGET_H
#define UI_TNGROUPCHATMEMBERSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TNGroupChatMembersWidget
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *groupChatNameLabel;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QTableView *leftTableView;
    QVBoxLayout *verticalLayout_5;
    QPushButton *exitButton;

    void setupUi(QWidget *TNGroupChatMembersWidget)
    {
        if (TNGroupChatMembersWidget->objectName().isEmpty())
            TNGroupChatMembersWidget->setObjectName(QStringLiteral("TNGroupChatMembersWidget"));
        TNGroupChatMembersWidget->resize(250, 482);
        TNGroupChatMembersWidget->setFocusPolicy(Qt::StrongFocus);
        verticalLayout_3 = new QVBoxLayout(TNGroupChatMembersWidget);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(15, 10, 15, 8);
        groupChatNameLabel = new QLabel(TNGroupChatMembersWidget);
        groupChatNameLabel->setObjectName(QStringLiteral("groupChatNameLabel"));

        verticalLayout->addWidget(groupChatNameLabel);


        verticalLayout_3->addLayout(verticalLayout);

        widget = new QWidget(TNGroupChatMembersWidget);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(widget);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(15, -1, 1, -1);
        leftTableView = new QTableView(TNGroupChatMembersWidget);
        leftTableView->setObjectName(QStringLiteral("leftTableView"));

        verticalLayout_2->addWidget(leftTableView);


        verticalLayout_3->addLayout(verticalLayout_2);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        exitButton = new QPushButton(TNGroupChatMembersWidget);
        exitButton->setObjectName(QStringLiteral("exitButton"));

        verticalLayout_5->addWidget(exitButton);


        verticalLayout_3->addLayout(verticalLayout_5);


        retranslateUi(TNGroupChatMembersWidget);

        QMetaObject::connectSlotsByName(TNGroupChatMembersWidget);
    } // setupUi

    void retranslateUi(QWidget *TNGroupChatMembersWidget)
    {
        TNGroupChatMembersWidget->setWindowTitle(QApplication::translate("TNGroupChatMembersWidget", "\351\200\211\346\213\251\350\201\224\347\263\273\344\272\272", 0));
        groupChatNameLabel->setText(QApplication::translate("TNGroupChatMembersWidget", "\347\276\244\350\201\212\345\220\215\345\255\227", 0));
        exitButton->setText(QApplication::translate("TNGroupChatMembersWidget", "\351\200\200\345\207\272\347\276\244\350\201\212", 0));
    } // retranslateUi

};

namespace Ui {
    class TNGroupChatMembersWidget: public Ui_TNGroupChatMembersWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNGROUPCHATMEMBERSWIDGET_H
