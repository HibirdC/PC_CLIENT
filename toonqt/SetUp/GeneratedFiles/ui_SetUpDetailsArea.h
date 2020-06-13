/********************************************************************************
** Form generated from reading UI file 'SetUpDetailsArea.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUPDETAILSAREA_H
#define UI_SETUPDETAILSAREA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetUpDetailsArea
{
public:

    void setupUi(QWidget *SetUpDetailsArea)
    {
        if (SetUpDetailsArea->objectName().isEmpty())
            SetUpDetailsArea->setObjectName(QStringLiteral("SetUpDetailsArea"));
        SetUpDetailsArea->resize(450, 544);
        SetUpDetailsArea->setStyleSheet(QStringLiteral(""));

        retranslateUi(SetUpDetailsArea);

        QMetaObject::connectSlotsByName(SetUpDetailsArea);
    } // setupUi

    void retranslateUi(QWidget *SetUpDetailsArea)
    {
        SetUpDetailsArea->setWindowTitle(QApplication::translate("SetUpDetailsArea", "toon", 0));
    } // retranslateUi

};

namespace Ui {
    class SetUpDetailsArea: public Ui_SetUpDetailsArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUPDETAILSAREA_H
