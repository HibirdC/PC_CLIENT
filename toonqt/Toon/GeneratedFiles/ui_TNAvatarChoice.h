/********************************************************************************
** Form generated from reading UI file 'TNAvatarChoice.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNAVATARCHOICE_H
#define UI_TNAVATARCHOICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TNAvatarChoice
{
public:

    void setupUi(QWidget *TNAvatarChoice)
    {
        if (TNAvatarChoice->objectName().isEmpty())
            TNAvatarChoice->setObjectName(QStringLiteral("TNAvatarChoice"));
        TNAvatarChoice->resize(336, 205);

        retranslateUi(TNAvatarChoice);

        QMetaObject::connectSlotsByName(TNAvatarChoice);
    } // setupUi

    void retranslateUi(QWidget *TNAvatarChoice)
    {
        TNAvatarChoice->setWindowTitle(QApplication::translate("TNAvatarChoice", "TNAvatarChoice", 0));
    } // retranslateUi

};

namespace Ui {
    class TNAvatarChoice: public Ui_TNAvatarChoice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNAVATARCHOICE_H
