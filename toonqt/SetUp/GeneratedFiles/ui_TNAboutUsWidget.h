/********************************************************************************
** Form generated from reading UI file 'TNAboutUsWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNABOUTUSWIDGET_H
#define UI_TNABOUTUSWIDGET_H

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

class Ui_TNAboutUsWidget
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *aboutUsLogoLabel;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_9;
    QLabel *aboutUsSoftNameLabel;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_7;
    QVBoxLayout *verticalLayout;
    QLabel *aboutUsVersionLabel;
    QLabel *aboutUsCompanyLabel;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *aboutUsCheckUpdateButton;
    QPushButton *aboutUsFeedBackButton;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *TNAboutUsWidget)
    {
        if (TNAboutUsWidget->objectName().isEmpty())
            TNAboutUsWidget->setObjectName(QStringLiteral("TNAboutUsWidget"));
        TNAboutUsWidget->resize(566, 396);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TNAboutUsWidget->sizePolicy().hasHeightForWidth());
        TNAboutUsWidget->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(TNAboutUsWidget);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, 70, -1, -1);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_4 = new QSpacerItem(68, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, -1, 15);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        aboutUsLogoLabel = new QLabel(TNAboutUsWidget);
        aboutUsLogoLabel->setObjectName(QStringLiteral("aboutUsLogoLabel"));
        aboutUsLogoLabel->setMinimumSize(QSize(80, 80));
        aboutUsLogoLabel->setMaximumSize(QSize(80, 80));
        aboutUsLogoLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(aboutUsLogoLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);

        aboutUsSoftNameLabel = new QLabel(TNAboutUsWidget);
        aboutUsSoftNameLabel->setObjectName(QStringLiteral("aboutUsSoftNameLabel"));
        aboutUsSoftNameLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(aboutUsSoftNameLabel);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_10);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 20, -1, -1);
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        aboutUsVersionLabel = new QLabel(TNAboutUsWidget);
        aboutUsVersionLabel->setObjectName(QStringLiteral("aboutUsVersionLabel"));
        aboutUsVersionLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(aboutUsVersionLabel);

        aboutUsCompanyLabel = new QLabel(TNAboutUsWidget);
        aboutUsCompanyLabel->setObjectName(QStringLiteral("aboutUsCompanyLabel"));
        aboutUsCompanyLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(aboutUsCompanyLabel);


        horizontalLayout_3->addLayout(verticalLayout);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_8);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(20);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 30, -1, -1);
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        aboutUsCheckUpdateButton = new QPushButton(TNAboutUsWidget);
        aboutUsCheckUpdateButton->setObjectName(QStringLiteral("aboutUsCheckUpdateButton"));
        aboutUsCheckUpdateButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(aboutUsCheckUpdateButton);

        aboutUsFeedBackButton = new QPushButton(TNAboutUsWidget);
        aboutUsFeedBackButton->setObjectName(QStringLiteral("aboutUsFeedBackButton"));
        aboutUsFeedBackButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(aboutUsFeedBackButton);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_5->addLayout(verticalLayout_2);

        horizontalSpacer_3 = new QSpacerItem(58, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_5);


        retranslateUi(TNAboutUsWidget);

        QMetaObject::connectSlotsByName(TNAboutUsWidget);
    } // setupUi

    void retranslateUi(QWidget *TNAboutUsWidget)
    {
        TNAboutUsWidget->setWindowTitle(QApplication::translate("TNAboutUsWidget", "TNAboutUsWidget", 0));
        aboutUsLogoLabel->setText(QApplication::translate("TNAboutUsWidget", "toon", 0));
        aboutUsSoftNameLabel->setText(QApplication::translate("TNAboutUsWidget", "\345\214\227\344\272\254\351\200\232\345\256\242\346\210\267\347\253\257", 0));
        aboutUsVersionLabel->setText(QApplication::translate("TNAboutUsWidget", "toon1.0.0 Beta\347\211\210", 0));
        aboutUsCompanyLabel->setText(QApplication::translate("TNAboutUsWidget", "\345\214\227\344\272\254\346\200\235\346\272\220\344\272\222\350\201\224\347\247\221\346\212\200\346\234\211\351\231\220\345\205\254\345\217\270\347\211\210\346\235\203\346\211\200\346\234\211", 0));
        aboutUsCheckUpdateButton->setText(QApplication::translate("TNAboutUsWidget", "\346\243\200\346\237\245\346\233\264\346\226\260", 0));
        aboutUsFeedBackButton->setText(QApplication::translate("TNAboutUsWidget", "\345\217\215\351\246\210\345\273\272\350\256\256", 0));
    } // retranslateUi

};

namespace Ui {
    class TNAboutUsWidget: public Ui_TNAboutUsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNABOUTUSWIDGET_H
