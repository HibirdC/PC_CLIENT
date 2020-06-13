/********************************************************************************
** Form generated from reading UI file 'TNMessageBox.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNMESSAGEBOX_H
#define UI_TNMESSAGEBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TNMessageBox
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_MessageBox;
    QLabel *lineEdit_MessageBox;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *TNMessageBox)
    {
        if (TNMessageBox->objectName().isEmpty())
            TNMessageBox->setObjectName(QStringLiteral("TNMessageBox"));
        TNMessageBox->resize(190, 30);
        horizontalLayout_2 = new QHBoxLayout(TNMessageBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_MessageBox = new QPushButton(TNMessageBox);
        pushButton_MessageBox->setObjectName(QStringLiteral("pushButton_MessageBox"));

        horizontalLayout->addWidget(pushButton_MessageBox);

        lineEdit_MessageBox = new QLabel(TNMessageBox);
        lineEdit_MessageBox->setObjectName(QStringLiteral("lineEdit_MessageBox"));
        lineEdit_MessageBox->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lineEdit_MessageBox);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalLayout->setStretch(2, 1);

        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(TNMessageBox);

        QMetaObject::connectSlotsByName(TNMessageBox);
    } // setupUi

    void retranslateUi(QWidget *TNMessageBox)
    {
        TNMessageBox->setWindowTitle(QApplication::translate("TNMessageBox", "TNMessageBox", 0));
        pushButton_MessageBox->setText(QString());
        lineEdit_MessageBox->setText(QApplication::translate("TNMessageBox", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class TNMessageBox: public Ui_TNMessageBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNMESSAGEBOX_H
