/********************************************************************************
** Form generated from reading UI file 'tnnoticeatarea.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNNOTICEATAREA_H
#define UI_TNNOTICEATAREA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tnnoticeatarea
{
public:

    void setupUi(QWidget *tnnoticeatarea)
    {
        if (tnnoticeatarea->objectName().isEmpty())
            tnnoticeatarea->setObjectName(QStringLiteral("tnnoticeatarea"));
        tnnoticeatarea->resize(400, 300);

        retranslateUi(tnnoticeatarea);

        QMetaObject::connectSlotsByName(tnnoticeatarea);
    } // setupUi

    void retranslateUi(QWidget *tnnoticeatarea)
    {
        tnnoticeatarea->setWindowTitle(QApplication::translate("tnnoticeatarea", "tnnoticeatarea", 0));
    } // retranslateUi

};

namespace Ui {
    class tnnoticeatarea: public Ui_tnnoticeatarea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNNOTICEATAREA_H
