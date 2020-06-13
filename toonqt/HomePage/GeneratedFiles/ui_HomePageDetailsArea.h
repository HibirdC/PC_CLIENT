/********************************************************************************
** Form generated from reading UI file 'HomePageDetailsArea.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMEPAGEDETAILSAREA_H
#define UI_HOMEPAGEDETAILSAREA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HomePageDetailsArea
{
public:

    void setupUi(QWidget *HomePageDetailsArea)
    {
        if (HomePageDetailsArea->objectName().isEmpty())
            HomePageDetailsArea->setObjectName(QStringLiteral("HomePageDetailsArea"));
        HomePageDetailsArea->resize(450, 544);
        HomePageDetailsArea->setStyleSheet(QStringLiteral(""));

        retranslateUi(HomePageDetailsArea);

        QMetaObject::connectSlotsByName(HomePageDetailsArea);
    } // setupUi

    void retranslateUi(QWidget *HomePageDetailsArea)
    {
        HomePageDetailsArea->setWindowTitle(QApplication::translate("HomePageDetailsArea", "toon", 0));
    } // retranslateUi

};

namespace Ui {
    class HomePageDetailsArea: public Ui_HomePageDetailsArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEPAGEDETAILSAREA_H
