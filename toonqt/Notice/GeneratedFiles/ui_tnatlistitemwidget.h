/********************************************************************************
** Form generated from reading UI file 'tnatlistitemwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNATLISTITEMWIDGET_H
#define UI_TNATLISTITEMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <TNElidedLabelV2.h>

QT_BEGIN_NAMESPACE

class Ui_TNATListItemWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *atbtnitem_icon;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    TNElidedLabelV2 *atlbitem_name;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *TNATListItemWidget)
    {
        if (TNATListItemWidget->objectName().isEmpty())
            TNATListItemWidget->setObjectName(QStringLiteral("TNATListItemWidget"));
        TNATListItemWidget->resize(431, 140);
        horizontalLayout_2 = new QHBoxLayout(TNATListItemWidget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(10, -1, 0, -1);
        verticalSpacer = new QSpacerItem(29, 34, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        atbtnitem_icon = new QPushButton(TNATListItemWidget);
        atbtnitem_icon->setObjectName(QStringLiteral("atbtnitem_icon"));
        atbtnitem_icon->setMinimumSize(QSize(20, 20));
        atbtnitem_icon->setMaximumSize(QSize(20, 20));

        verticalLayout_2->addWidget(atbtnitem_icon);

        verticalSpacer_2 = new QSpacerItem(29, 33, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, -1, -1, -1);
        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        atlbitem_name = new TNElidedLabelV2(TNATListItemWidget);
        atlbitem_name->setObjectName(QStringLiteral("atlbitem_name"));
        atlbitem_name->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(atlbitem_name);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        horizontalLayout_2->addLayout(verticalLayout);


        retranslateUi(TNATListItemWidget);

        QMetaObject::connectSlotsByName(TNATListItemWidget);
    } // setupUi

    void retranslateUi(QWidget *TNATListItemWidget)
    {
        TNATListItemWidget->setWindowTitle(QApplication::translate("TNATListItemWidget", "TNATListItemWidget", 0));
        atbtnitem_icon->setText(QString());
        atlbitem_name->setText(QApplication::translate("TNATListItemWidget", "name", 0));
    } // retranslateUi

};

namespace Ui {
    class TNATListItemWidget: public Ui_TNATListItemWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNATLISTITEMWIDGET_H
