/********************************************************************************
** Form generated from reading UI file 'TNNewFriendCard.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNNEWFRIENDCARD_H
#define UI_TNNEWFRIENDCARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <TNElidedLabel.h>
#include <tnavatorbutton.h>

QT_BEGIN_NAMESPACE

class Ui_TNNewFriendCard
{
public:
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_8;
    QLabel *finishedMarkLabel;
    QSpacerItem *horizontalSpacer_4;
    QWidget *mainWidget;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QLabel *timeLabel;
    QLabel *subCatalogLabel;
    QWidget *infoWidget;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QWidget *avatarWidget;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    TNAvatorButton *herAvatarButton;
    QVBoxLayout *verticalLayout;
    TNElidedLabel *herNickNameLabel;
    TNElidedLabel *herSubTitleLabel;
    QSpacerItem *horizontalSpacer_3;
    TNAvatorButton *mineAvatarButton;
    QWidget *textWidget;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *summeryLabel;
    QLabel *textLabel;
    TNElidedLabel *resourceLabel;
    QWidget *buttonWidget;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *acceptButton;
    QPushButton *rejectButton;
    QPushButton *buttonNameButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_5;

    void setupUi(QWidget *TNNewFriendCard)
    {
        if (TNNewFriendCard->objectName().isEmpty())
            TNNewFriendCard->setObjectName(QStringLiteral("TNNewFriendCard"));
        TNNewFriendCard->resize(700, 248);
        TNNewFriendCard->setMinimumSize(QSize(652, 180));
        TNNewFriendCard->setStyleSheet(QStringLiteral(""));
        verticalLayout_7 = new QVBoxLayout(TNNewFriendCard);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        finishedMarkLabel = new QLabel(TNNewFriendCard);
        finishedMarkLabel->setObjectName(QStringLiteral("finishedMarkLabel"));
        finishedMarkLabel->setMaximumSize(QSize(58, 64));

        horizontalLayout_8->addWidget(finishedMarkLabel);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_4);

        mainWidget = new QWidget(TNNewFriendCard);
        mainWidget->setObjectName(QStringLiteral("mainWidget"));
        mainWidget->setMinimumSize(QSize(600, 100));
        mainWidget->setMaximumSize(QSize(600, 16777215));
        horizontalLayout_7 = new QHBoxLayout(mainWidget);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(20);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        timeLabel = new QLabel(mainWidget);
        timeLabel->setObjectName(QStringLiteral("timeLabel"));
        timeLabel->setMinimumSize(QSize(0, 15));
        timeLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(timeLabel);

        subCatalogLabel = new QLabel(mainWidget);
        subCatalogLabel->setObjectName(QStringLiteral("subCatalogLabel"));
        subCatalogLabel->setMinimumSize(QSize(0, 15));
        subCatalogLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(subCatalogLabel);


        verticalLayout_6->addLayout(verticalLayout_4);

        infoWidget = new QWidget(mainWidget);
        infoWidget->setObjectName(QStringLiteral("infoWidget"));
        horizontalLayout_6 = new QHBoxLayout(infoWidget);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        avatarWidget = new QWidget(infoWidget);
        avatarWidget->setObjectName(QStringLiteral("avatarWidget"));
        avatarWidget->setMinimumSize(QSize(0, 0));
        horizontalLayout_4 = new QHBoxLayout(avatarWidget);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 1, -1, 1);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(10, 5, 10, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        herAvatarButton = new TNAvatorButton(avatarWidget);
        herAvatarButton->setObjectName(QStringLiteral("herAvatarButton"));
        herAvatarButton->setMinimumSize(QSize(40, 40));
        herAvatarButton->setMaximumSize(QSize(40, 40));
        herAvatarButton->setFlat(true);

        horizontalLayout_2->addWidget(herAvatarButton);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 4, -1, 4);
        herNickNameLabel = new TNElidedLabel(avatarWidget);
        herNickNameLabel->setObjectName(QStringLiteral("herNickNameLabel"));

        verticalLayout->addWidget(herNickNameLabel);

        herSubTitleLabel = new TNElidedLabel(avatarWidget);
        herSubTitleLabel->setObjectName(QStringLiteral("herSubTitleLabel"));

        verticalLayout->addWidget(herSubTitleLabel);


        horizontalLayout_2->addLayout(verticalLayout);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        mineAvatarButton = new TNAvatorButton(avatarWidget);
        mineAvatarButton->setObjectName(QStringLiteral("mineAvatarButton"));
        mineAvatarButton->setMinimumSize(QSize(40, 40));
        mineAvatarButton->setMaximumSize(QSize(40, 40));
        mineAvatarButton->setFlat(true);

        horizontalLayout_3->addWidget(mineAvatarButton);


        horizontalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout_5->addWidget(avatarWidget);

        textWidget = new QWidget(infoWidget);
        textWidget->setObjectName(QStringLiteral("textWidget"));
        textWidget->setMinimumSize(QSize(0, 60));
        verticalLayout_3 = new QVBoxLayout(textWidget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, 1, -1, 1);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(20, -1, -1, -1);
        summeryLabel = new QLabel(textWidget);
        summeryLabel->setObjectName(QStringLiteral("summeryLabel"));
        summeryLabel->setMinimumSize(QSize(0, 0));
        summeryLabel->setIndent(0);

        verticalLayout_2->addWidget(summeryLabel);

        textLabel = new QLabel(textWidget);
        textLabel->setObjectName(QStringLiteral("textLabel"));
        textLabel->setWordWrap(true);
        textLabel->setIndent(0);

        verticalLayout_2->addWidget(textLabel);

        resourceLabel = new TNElidedLabel(textWidget);
        resourceLabel->setObjectName(QStringLiteral("resourceLabel"));
        resourceLabel->setIndent(0);

        verticalLayout_2->addWidget(resourceLabel);


        verticalLayout_3->addLayout(verticalLayout_2);


        verticalLayout_5->addWidget(textWidget);

        buttonWidget = new QWidget(infoWidget);
        buttonWidget->setObjectName(QStringLiteral("buttonWidget"));
        horizontalLayout_5 = new QHBoxLayout(buttonWidget);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 0, -1, 3);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, -1, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        acceptButton = new QPushButton(buttonWidget);
        acceptButton->setObjectName(QStringLiteral("acceptButton"));

        horizontalLayout->addWidget(acceptButton);

        rejectButton = new QPushButton(buttonWidget);
        rejectButton->setObjectName(QStringLiteral("rejectButton"));

        horizontalLayout->addWidget(rejectButton);

        buttonNameButton = new QPushButton(buttonWidget);
        buttonNameButton->setObjectName(QStringLiteral("buttonNameButton"));

        horizontalLayout->addWidget(buttonNameButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        horizontalLayout_5->addLayout(horizontalLayout);


        verticalLayout_5->addWidget(buttonWidget);

        verticalLayout_5->setStretch(1, 1);

        horizontalLayout_6->addLayout(verticalLayout_5);


        verticalLayout_6->addWidget(infoWidget);

        verticalLayout_6->setStretch(1, 1);

        horizontalLayout_7->addLayout(verticalLayout_6);


        horizontalLayout_8->addWidget(mainWidget);

        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_5);


        verticalLayout_7->addLayout(horizontalLayout_8);


        retranslateUi(TNNewFriendCard);

        QMetaObject::connectSlotsByName(TNNewFriendCard);
    } // setupUi

    void retranslateUi(QWidget *TNNewFriendCard)
    {
        TNNewFriendCard->setWindowTitle(QApplication::translate("TNNewFriendCard", "Form", 0));
        finishedMarkLabel->setText(QApplication::translate("TNNewFriendCard", "\345\267\262\345\256\214\346\210\220", 0));
        timeLabel->setText(QApplication::translate("TNNewFriendCard", "\346\227\245\346\234\237\346\227\266\351\227\264", 0));
        subCatalogLabel->setText(QApplication::translate("TNNewFriendCard", "subCatalog", 0));
        herAvatarButton->setText(QApplication::translate("TNNewFriendCard", "\345\257\271\346\226\271", 0));
        herNickNameLabel->setText(QApplication::translate("TNNewFriendCard", "\346\210\221\347\232\204\345\260\217\351\261\274\344\275\240\351\206\222\344\272\206", 0));
        herSubTitleLabel->setText(QApplication::translate("TNNewFriendCard", "\345\277\253\344\271\220\347\224\237\346\264\273\357\274\214\345\277\253\344\271\220\345\255\246\344\271\240\343\200\202", 0));
        mineAvatarButton->setText(QApplication::translate("TNNewFriendCard", "\346\210\221\346\226\271", 0));
        summeryLabel->setText(QApplication::translate("TNNewFriendCard", "summery", 0));
        textLabel->setText(QApplication::translate("TNNewFriendCard", "text", 0));
        resourceLabel->setText(QApplication::translate("TNNewFriendCard", "resource", 0));
        acceptButton->setText(QApplication::translate("TNNewFriendCard", "\346\216\245\345\217\227", 0));
        rejectButton->setText(QApplication::translate("TNNewFriendCard", "\346\213\222\347\273\235", 0));
        buttonNameButton->setText(QApplication::translate("TNNewFriendCard", "buttonName", 0));
    } // retranslateUi

};

namespace Ui {
    class TNNewFriendCard: public Ui_TNNewFriendCard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNNEWFRIENDCARD_H
