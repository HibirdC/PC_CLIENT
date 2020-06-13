/********************************************************************************
** Form generated from reading UI file 'tnothermessagebrowser.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNOTHERMESSAGEBROWSER_H
#define UI_TNOTHERMESSAGEBROWSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TNOtherMessageBrowser
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_othermessage_notify;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *TNOtherMessageBrowser)
    {
        if (TNOtherMessageBrowser->objectName().isEmpty())
            TNOtherMessageBrowser->setObjectName(QStringLiteral("TNOtherMessageBrowser"));
        TNOtherMessageBrowser->resize(630, 151);
        TNOtherMessageBrowser->setMinimumSize(QSize(0, 0));
        TNOtherMessageBrowser->setMaximumSize(QSize(630, 16777215));
        verticalLayout = new QVBoxLayout(TNOtherMessageBrowser);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_2 = new QSpacerItem(20, 64, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(15, -1, 15, -1);
        horizontalSpacer = new QSpacerItem(142, 15, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_othermessage_notify = new QLabel(TNOtherMessageBrowser);
        label_othermessage_notify->setObjectName(QStringLiteral("label_othermessage_notify"));
        label_othermessage_notify->setMinimumSize(QSize(0, 0));
        label_othermessage_notify->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_othermessage_notify);

        horizontalSpacer_2 = new QSpacerItem(142, 15, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 64, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(TNOtherMessageBrowser);

        QMetaObject::connectSlotsByName(TNOtherMessageBrowser);
    } // setupUi

    void retranslateUi(QWidget *TNOtherMessageBrowser)
    {
        TNOtherMessageBrowser->setWindowTitle(QApplication::translate("TNOtherMessageBrowser", "TNOtherMessageBrowser", 0));
        label_othermessage_notify->setText(QApplication::translate("TNOtherMessageBrowser", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class TNOtherMessageBrowser: public Ui_TNOtherMessageBrowser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNOTHERMESSAGEBROWSER_H
