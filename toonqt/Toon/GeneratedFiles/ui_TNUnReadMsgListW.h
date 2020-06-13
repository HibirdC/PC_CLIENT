/********************************************************************************
** Form generated from reading UI file 'TNUnReadMsgListW.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNUNREADMSGLISTW_H
#define UI_TNUNREADMSGLISTW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TNUnReadMsgListW
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *unMsgLine;
    QHBoxLayout *horizontalLayout_3;
    QLabel *unMsgListLabelTitle;
    QListView *unReadListView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *unMsgListButton;

    void setupUi(QWidget *TNUnReadMsgListW)
    {
        if (TNUnReadMsgListW->objectName().isEmpty())
            TNUnReadMsgListW->setObjectName(QStringLiteral("TNUnReadMsgListW"));
        TNUnReadMsgListW->resize(230, 336);
        TNUnReadMsgListW->setMinimumSize(QSize(230, 0));
        TNUnReadMsgListW->setMaximumSize(QSize(230, 16777215));
        verticalLayout = new QVBoxLayout(TNUnReadMsgListW);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        unMsgLine = new QLabel(TNUnReadMsgListW);
        unMsgLine->setObjectName(QStringLiteral("unMsgLine"));
        unMsgLine->setMinimumSize(QSize(0, 4));
        unMsgLine->setMaximumSize(QSize(16777215, 4));

        horizontalLayout_2->addWidget(unMsgLine);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        unMsgListLabelTitle = new QLabel(TNUnReadMsgListW);
        unMsgListLabelTitle->setObjectName(QStringLiteral("unMsgListLabelTitle"));
        unMsgListLabelTitle->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        unMsgListLabelTitle->setIndent(15);

        horizontalLayout_3->addWidget(unMsgListLabelTitle);


        verticalLayout->addLayout(horizontalLayout_3);

        unReadListView = new QListView(TNUnReadMsgListW);
        unReadListView->setObjectName(QStringLiteral("unReadListView"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(unReadListView->sizePolicy().hasHeightForWidth());
        unReadListView->setSizePolicy(sizePolicy);
        unReadListView->setMinimumSize(QSize(230, 0));
        unReadListView->setLineWidth(0);

        verticalLayout->addWidget(unReadListView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 6, 10, 6);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        unMsgListButton = new QPushButton(TNUnReadMsgListW);
        unMsgListButton->setObjectName(QStringLiteral("unMsgListButton"));

        horizontalLayout->addWidget(unMsgListButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(TNUnReadMsgListW);

        QMetaObject::connectSlotsByName(TNUnReadMsgListW);
    } // setupUi

    void retranslateUi(QWidget *TNUnReadMsgListW)
    {
        TNUnReadMsgListW->setWindowTitle(QApplication::translate("TNUnReadMsgListW", "TNUnReadMsgListW", 0));
        unMsgLine->setText(QString());
        unMsgListLabelTitle->setText(QApplication::translate("TNUnReadMsgListW", "TextLabel", 0));
        unMsgListButton->setText(QApplication::translate("TNUnReadMsgListW", "\345\277\275\347\225\245\345\205\250\351\203\250", 0));
    } // retranslateUi

};

namespace Ui {
    class TNUnReadMsgListW: public Ui_TNUnReadMsgListW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNUNREADMSGLISTW_H
