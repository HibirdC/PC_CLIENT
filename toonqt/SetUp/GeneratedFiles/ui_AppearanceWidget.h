/********************************************************************************
** Form generated from reading UI file 'AppearanceWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPEARANCEWIDGET_H
#define UI_APPEARANCEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AppearanceWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QToolButton *toolButton_4;
    QToolButton *toolButton_5;
    QToolButton *toolButton_6;
    QToolButton *toolButton_8;
    QToolButton *toolButton_9;
    QToolButton *toolButton_7;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *AppearanceWidget)
    {
        if (AppearanceWidget->objectName().isEmpty())
            AppearanceWidget->setObjectName(QStringLiteral("AppearanceWidget"));
        AppearanceWidget->resize(419, 361);
        verticalLayout = new QVBoxLayout(AppearanceWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        toolButton = new QToolButton(AppearanceWidget);
        toolButton->setObjectName(QStringLiteral("toolButton"));

        gridLayout->addWidget(toolButton, 0, 0, 1, 1);

        toolButton_2 = new QToolButton(AppearanceWidget);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));

        gridLayout->addWidget(toolButton_2, 0, 1, 1, 1);

        toolButton_3 = new QToolButton(AppearanceWidget);
        toolButton_3->setObjectName(QStringLiteral("toolButton_3"));

        gridLayout->addWidget(toolButton_3, 0, 2, 1, 1);

        toolButton_4 = new QToolButton(AppearanceWidget);
        toolButton_4->setObjectName(QStringLiteral("toolButton_4"));

        gridLayout->addWidget(toolButton_4, 1, 0, 1, 1);

        toolButton_5 = new QToolButton(AppearanceWidget);
        toolButton_5->setObjectName(QStringLiteral("toolButton_5"));

        gridLayout->addWidget(toolButton_5, 1, 1, 1, 1);

        toolButton_6 = new QToolButton(AppearanceWidget);
        toolButton_6->setObjectName(QStringLiteral("toolButton_6"));

        gridLayout->addWidget(toolButton_6, 1, 2, 1, 1);

        toolButton_8 = new QToolButton(AppearanceWidget);
        toolButton_8->setObjectName(QStringLiteral("toolButton_8"));

        gridLayout->addWidget(toolButton_8, 2, 0, 1, 1);

        toolButton_9 = new QToolButton(AppearanceWidget);
        toolButton_9->setObjectName(QStringLiteral("toolButton_9"));

        gridLayout->addWidget(toolButton_9, 2, 1, 1, 1);

        toolButton_7 = new QToolButton(AppearanceWidget);
        toolButton_7->setObjectName(QStringLiteral("toolButton_7"));

        gridLayout->addWidget(toolButton_7, 2, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 266, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(AppearanceWidget);

        QMetaObject::connectSlotsByName(AppearanceWidget);
    } // setupUi

    void retranslateUi(QWidget *AppearanceWidget)
    {
        AppearanceWidget->setWindowTitle(QApplication::translate("AppearanceWidget", "AppearanceWidget", 0));
        toolButton->setText(QApplication::translate("AppearanceWidget", "...", 0));
        toolButton_2->setText(QApplication::translate("AppearanceWidget", "...", 0));
        toolButton_3->setText(QApplication::translate("AppearanceWidget", "...", 0));
        toolButton_4->setText(QApplication::translate("AppearanceWidget", "...", 0));
        toolButton_5->setText(QApplication::translate("AppearanceWidget", "...", 0));
        toolButton_6->setText(QApplication::translate("AppearanceWidget", "...", 0));
        toolButton_8->setText(QApplication::translate("AppearanceWidget", "...", 0));
        toolButton_9->setText(QApplication::translate("AppearanceWidget", "...", 0));
        toolButton_7->setText(QApplication::translate("AppearanceWidget", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class AppearanceWidget: public Ui_AppearanceWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPEARANCEWIDGET_H
