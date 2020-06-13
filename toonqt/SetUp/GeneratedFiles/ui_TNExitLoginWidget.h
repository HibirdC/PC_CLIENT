/********************************************************************************
** Form generated from reading UI file 'TNExitLoginWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNEXITLOGINWIDGET_H
#define UI_TNEXITLOGINWIDGET_H

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

QT_BEGIN_NAMESPACE

class Ui_TNExitLoginWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_7;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *exitAvatarLabel;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QLabel *exitUserNameLabel;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *exitPushButton;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_8;

    void setupUi(QWidget *TNExitLoginWidget)
    {
        if (TNExitLoginWidget->objectName().isEmpty())
            TNExitLoginWidget->setObjectName(QStringLiteral("TNExitLoginWidget"));
        TNExitLoginWidget->resize(600, 300);
        verticalLayout_2 = new QVBoxLayout(TNExitLoginWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(18, 70, -1, -1);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, -1, 20);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        exitAvatarLabel = new QLabel(TNExitLoginWidget);
        exitAvatarLabel->setObjectName(QStringLiteral("exitAvatarLabel"));
        exitAvatarLabel->setMinimumSize(QSize(80, 80));
        exitAvatarLabel->setMaximumSize(QSize(80, 80));
        exitAvatarLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(exitAvatarLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, -1, -1, 35);
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        exitUserNameLabel = new QLabel(TNExitLoginWidget);
        exitUserNameLabel->setObjectName(QStringLiteral("exitUserNameLabel"));
        exitUserNameLabel->setMinimumSize(QSize(0, 0));
        exitUserNameLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(exitUserNameLabel);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, -1, 0);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        exitPushButton = new QPushButton(TNExitLoginWidget);
        exitPushButton->setObjectName(QStringLiteral("exitPushButton"));
        exitPushButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(exitPushButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_4->addLayout(verticalLayout);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);


        verticalLayout_2->addLayout(horizontalLayout_4);

        exitUserNameLabel->raise();

        retranslateUi(TNExitLoginWidget);

        QMetaObject::connectSlotsByName(TNExitLoginWidget);
    } // setupUi

    void retranslateUi(QWidget *TNExitLoginWidget)
    {
        TNExitLoginWidget->setWindowTitle(QApplication::translate("TNExitLoginWidget", "TNExitLoginWidget", 0));
        exitAvatarLabel->setText(QApplication::translate("TNExitLoginWidget", "\345\244\264\345\203\217", 0));
        exitUserNameLabel->setText(QString());
        exitPushButton->setText(QApplication::translate("TNExitLoginWidget", "\351\200\200\345\207\272\347\231\273\345\275\225", 0));
    } // retranslateUi

};

namespace Ui {
    class TNExitLoginWidget: public Ui_TNExitLoginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNEXITLOGINWIDGET_H
