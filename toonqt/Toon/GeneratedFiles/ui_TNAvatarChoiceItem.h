/********************************************************************************
** Form generated from reading UI file 'TNAvatarChoiceItem.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNAVATARCHOICEITEM_H
#define UI_TNAVATARCHOICEITEM_H

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
#include <TNElidedLabelV2.h>

QT_BEGIN_NAMESPACE

class Ui_TNAvatarChoiceItem
{
public:
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *avatarChoiceBtnItem;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    TNElidedLabelV2 *avatorlbitem_name;
    QSpacerItem *horizontalSpacer;
    QLabel *avatorlbitem_status;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *TNAvatarChoiceItem)
    {
        if (TNAvatarChoiceItem->objectName().isEmpty())
            TNAvatarChoiceItem->setObjectName(QStringLiteral("TNAvatarChoiceItem"));
        TNAvatarChoiceItem->resize(148, 78);
        horizontalLayout_3 = new QHBoxLayout(TNAvatarChoiceItem);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 12, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(6, -1, 0, -1);
        verticalSpacer = new QSpacerItem(10, 34, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        avatarChoiceBtnItem = new QPushButton(TNAvatarChoiceItem);
        avatarChoiceBtnItem->setObjectName(QStringLiteral("avatarChoiceBtnItem"));
        avatarChoiceBtnItem->setMinimumSize(QSize(0, 0));
        avatarChoiceBtnItem->setMaximumSize(QSize(0, 0));

        verticalLayout_2->addWidget(avatarChoiceBtnItem);

        verticalSpacer_2 = new QSpacerItem(10, 33, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, 4, -1);
        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        avatorlbitem_name = new TNElidedLabelV2(TNAvatarChoiceItem);
        avatorlbitem_name->setObjectName(QStringLiteral("avatorlbitem_name"));
        avatorlbitem_name->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(avatorlbitem_name);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        avatorlbitem_status = new QLabel(TNAvatarChoiceItem);
        avatorlbitem_status->setObjectName(QStringLiteral("avatorlbitem_status"));

        horizontalLayout->addWidget(avatorlbitem_status);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        horizontalLayout_2->addLayout(verticalLayout);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        retranslateUi(TNAvatarChoiceItem);

        QMetaObject::connectSlotsByName(TNAvatarChoiceItem);
    } // setupUi

    void retranslateUi(QWidget *TNAvatarChoiceItem)
    {
        TNAvatarChoiceItem->setWindowTitle(QApplication::translate("TNAvatarChoiceItem", "TNAvatarChoiceItem", 0));
        avatarChoiceBtnItem->setText(QString());
        avatorlbitem_name->setText(QApplication::translate("TNAvatarChoiceItem", "name", 0));
        avatorlbitem_status->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TNAvatarChoiceItem: public Ui_TNAvatarChoiceItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNAVATARCHOICEITEM_H
