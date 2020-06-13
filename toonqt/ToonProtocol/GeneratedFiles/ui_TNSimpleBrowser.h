/********************************************************************************
** Form generated from reading UI file 'TNSimpleBrowser.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNSIMPLEBROWSER_H
#define UI_TNSIMPLEBROWSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_TNSimpleBrowser
{
public:

    void setupUi(QDialog *TNSimpleBrowser)
    {
        if (TNSimpleBrowser->objectName().isEmpty())
            TNSimpleBrowser->setObjectName(QStringLiteral("TNSimpleBrowser"));
        TNSimpleBrowser->resize(400, 300);

        retranslateUi(TNSimpleBrowser);

        QMetaObject::connectSlotsByName(TNSimpleBrowser);
    } // setupUi

    void retranslateUi(QDialog *TNSimpleBrowser)
    {
        TNSimpleBrowser->setWindowTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class TNSimpleBrowser: public Ui_TNSimpleBrowser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNSIMPLEBROWSER_H
