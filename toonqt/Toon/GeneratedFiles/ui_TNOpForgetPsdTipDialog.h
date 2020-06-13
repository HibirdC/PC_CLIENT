/********************************************************************************
** Form generated from reading UI file 'TNOpForgetPsdTipDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNOPFORGETPSDTIPDIALOG_H
#define UI_TNOPFORGETPSDTIPDIALOG_H

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

class Ui_TNOpForgetPsdTipDialog
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
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *TNOpForgetPsdTipDialog)
    {
        if (TNOpForgetPsdTipDialog->objectName().isEmpty())
            TNOpForgetPsdTipDialog->setObjectName(QStringLiteral("TNOpForgetPsdTipDialog"));
        TNOpForgetPsdTipDialog->resize(350, 165);
        TNOpForgetPsdTipDialog->setMinimumSize(QSize(300, 100));
        TNOpForgetPsdTipDialog->setMaximumSize(QSize(418, 165));
        verticalLayout = new QVBoxLayout(TNOpForgetPsdTipDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 14, -1, 22);
        languageTipTitle = new QLabel(TNOpForgetPsdTipDialog);
        languageTipTitle->setObjectName(QStringLiteral("languageTipTitle"));
        languageTipTitle->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(languageTipTitle);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 4, -1, -1);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        languageTipLabel = new QLabel(TNOpForgetPsdTipDialog);
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

        okButton = new QPushButton(TNOpForgetPsdTipDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(okButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout->setStretch(1, 1);

        retranslateUi(TNOpForgetPsdTipDialog);

        QMetaObject::connectSlotsByName(TNOpForgetPsdTipDialog);
    } // setupUi

    void retranslateUi(QDialog *TNOpForgetPsdTipDialog)
    {
        TNOpForgetPsdTipDialog->setWindowTitle(QApplication::translate("TNOpForgetPsdTipDialog", "Dialog", 0));
        languageTipTitle->setText(QApplication::translate("TNOpForgetPsdTipDialog", "\346\217\220\347\244\272", 0));
        languageTipLabel->setText(QApplication::translate("TNOpForgetPsdTipDialog", "\350\277\220\350\220\245\350\264\246\345\217\267\346\232\202\344\270\215\346\224\257\346\214\201\346\211\276\345\233\236\345\257\206\347\240\201\357\274\214\n"
"\350\257\267\345\210\260\346\211\213\346\234\272\347\253\257\346\211\276\345\233\236\345\257\206\347\240\201", 0));
        okButton->setText(QApplication::translate("TNOpForgetPsdTipDialog", "\347\241\256\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class TNOpForgetPsdTipDialog: public Ui_TNOpForgetPsdTipDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNOPFORGETPSDTIPDIALOG_H
