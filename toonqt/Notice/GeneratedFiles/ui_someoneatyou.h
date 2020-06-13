/********************************************************************************
** Form generated from reading UI file 'someoneatyou.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOMEONEATYOU_H
#define UI_SOMEONEATYOU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <TNElidedLabelV2.h>

QT_BEGIN_NAMESPACE

class Ui_someoneatyou
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    TNElidedLabelV2 *lineEdit_AtYou_MessageBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *AtClosePushButton;

    void setupUi(QWidget *someoneatyou)
    {
        if (someoneatyou->objectName().isEmpty())
            someoneatyou->setObjectName(QStringLiteral("someoneatyou"));
        someoneatyou->resize(215, 35);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(someoneatyou->sizePolicy().hasHeightForWidth());
        someoneatyou->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(someoneatyou);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(10, 0, 15, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 5, -1, 5);
        lineEdit_AtYou_MessageBox = new TNElidedLabelV2(someoneatyou);
        lineEdit_AtYou_MessageBox->setObjectName(QStringLiteral("lineEdit_AtYou_MessageBox"));
        lineEdit_AtYou_MessageBox->setMinimumSize(QSize(165, 20));
        lineEdit_AtYou_MessageBox->setMaximumSize(QSize(16777215, 20));
        lineEdit_AtYou_MessageBox->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lineEdit_AtYou_MessageBox);


        horizontalLayout_2->addLayout(horizontalLayout);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        AtClosePushButton = new QPushButton(someoneatyou);
        AtClosePushButton->setObjectName(QStringLiteral("AtClosePushButton"));
        AtClosePushButton->setMinimumSize(QSize(10, 10));
        AtClosePushButton->setMaximumSize(QSize(10, 10));

        horizontalLayout_2->addWidget(AtClosePushButton);

        horizontalLayout_2->setStretch(1, 1);

        retranslateUi(someoneatyou);

        QMetaObject::connectSlotsByName(someoneatyou);
    } // setupUi

    void retranslateUi(QWidget *someoneatyou)
    {
        someoneatyou->setWindowTitle(QApplication::translate("someoneatyou", "someoneatyou", 0));
        lineEdit_AtYou_MessageBox->setText(QApplication::translate("someoneatyou", "TextLabel", 0));
        AtClosePushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class someoneatyou: public Ui_someoneatyou {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOMEONEATYOU_H
