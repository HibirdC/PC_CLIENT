/********************************************************************************
** Form generated from reading UI file 'TNBackgroudWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNBACKGROUDWIDGET_H
#define UI_TNBACKGROUDWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_backgroundWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_backpic;
    QLabel *label_default_backpic;
    QSpacerItem *horizontalSpacer_1;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_1;

    void setupUi(QWidget *backgroundWidget)
    {
        if (backgroundWidget->objectName().isEmpty())
            backgroundWidget->setObjectName(QStringLiteral("backgroundWidget"));
        backgroundWidget->resize(400, 300);
        verticalLayout = new QVBoxLayout(backgroundWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout_backpic = new QGridLayout();
        gridLayout_backpic->setObjectName(QStringLiteral("gridLayout_backpic"));
        label_default_backpic = new QLabel(backgroundWidget);
        label_default_backpic->setObjectName(QStringLiteral("label_default_backpic"));
        label_default_backpic->setMinimumSize(QSize(200, 125));
        label_default_backpic->setMaximumSize(QSize(200, 125));

        gridLayout_backpic->addWidget(label_default_backpic, 1, 1, 1, 1);

        horizontalSpacer_1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_backpic->addItem(horizontalSpacer_1, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_backpic->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_backpic->addItem(verticalSpacer_3, 0, 1, 1, 1);

        verticalSpacer_1 = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_backpic->addItem(verticalSpacer_1, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_backpic);


        retranslateUi(backgroundWidget);

        QMetaObject::connectSlotsByName(backgroundWidget);
    } // setupUi

    void retranslateUi(QWidget *backgroundWidget)
    {
        backgroundWidget->setWindowTitle(QApplication::translate("backgroundWidget", "Form", 0));
        label_default_backpic->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class backgroundWidget: public Ui_backgroundWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNBACKGROUDWIDGET_H
