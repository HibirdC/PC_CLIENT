/********************************************************************************
** Form generated from reading UI file 'TNLanguageChangeTipDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNLANGUAGECHANGETIPDIALOG_H
#define UI_TNLANGUAGECHANGETIPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TNLanguageChangeTipDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *languageTipTitle;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QLabel *languageTipLabel;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *TNLanguageChangeTipDialog)
    {
        if (TNLanguageChangeTipDialog->objectName().isEmpty())
            TNLanguageChangeTipDialog->setObjectName(QStringLiteral("TNLanguageChangeTipDialog"));
        TNLanguageChangeTipDialog->resize(350, 165);
        TNLanguageChangeTipDialog->setMinimumSize(QSize(300, 100));
        TNLanguageChangeTipDialog->setMaximumSize(QSize(418, 165));
        verticalLayout = new QVBoxLayout(TNLanguageChangeTipDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 14, -1, 22);
        languageTipTitle = new QLabel(TNLanguageChangeTipDialog);
        languageTipTitle->setObjectName(QStringLiteral("languageTipTitle"));
        languageTipTitle->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(languageTipTitle);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 4, -1, -1);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        languageTipLabel = new QLabel(TNLanguageChangeTipDialog);
        languageTipLabel->setObjectName(QStringLiteral("languageTipLabel"));
        languageTipLabel->setMinimumSize(QSize(0, 0));
        languageTipLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout_2->addWidget(languageTipLabel);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        verticalLayout->addLayout(verticalLayout_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(20);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        okButton = new QPushButton(TNLanguageChangeTipDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(okButton);

        cancelButton = new QPushButton(TNLanguageChangeTipDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(cancelButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout->setStretch(1, 1);

        retranslateUi(TNLanguageChangeTipDialog);

        QMetaObject::connectSlotsByName(TNLanguageChangeTipDialog);
    } // setupUi

    void retranslateUi(QDialog *TNLanguageChangeTipDialog)
    {
        TNLanguageChangeTipDialog->setWindowTitle(QApplication::translate("TNLanguageChangeTipDialog", "Dialog", 0));
        languageTipTitle->setText(QApplication::translate("TNLanguageChangeTipDialog", "\346\217\220\347\244\272", 0));
        languageTipLabel->setText(QApplication::translate("TNLanguageChangeTipDialog", "\346\233\264\346\224\271\350\257\255\350\250\200\351\234\200\351\207\215\346\226\260\345\220\257\345\212\250\346\211\215\350\203\275\347\224\237\346\225\210\357\274\214\n"
"\346\230\257\345\220\246\347\241\256\345\256\232\346\233\264\346\224\271\357\274\237", 0));
        okButton->setText(QApplication::translate("TNLanguageChangeTipDialog", "\347\241\256\345\256\232", 0));
        cancelButton->setText(QApplication::translate("TNLanguageChangeTipDialog", "\345\205\263\351\227\255", 0));
    } // retranslateUi

};

namespace Ui {
    class TNLanguageChangeTipDialog: public Ui_TNLanguageChangeTipDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNLANGUAGECHANGETIPDIALOG_H
