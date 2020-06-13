/********************************************************************************
** Form generated from reading UI file 'ResetPasswordForm03.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESETPASSWORDFORM03_H
#define UI_RESETPASSWORDFORM03_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ResetPasswordForm03
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *resetSuccess;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *resetOkTextLabel;
    QHBoxLayout *horizontalLayout;
    QPushButton *goLoginPushButton;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *ResetPasswordForm03)
    {
        if (ResetPasswordForm03->objectName().isEmpty())
            ResetPasswordForm03->setObjectName(QStringLiteral("ResetPasswordForm03"));
        ResetPasswordForm03->resize(367, 343);
        verticalLayout_3 = new QVBoxLayout(ResetPasswordForm03);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(38, -1, 38, -1);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(17, 68, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        resetSuccess = new QLabel(ResetPasswordForm03);
        resetSuccess->setObjectName(QStringLiteral("resetSuccess"));
        resetSuccess->setMinimumSize(QSize(50, 50));
        resetSuccess->setMaximumSize(QSize(50, 50));
        resetSuccess->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(resetSuccess);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 20, -1, 58);
        resetOkTextLabel = new QLabel(ResetPasswordForm03);
        resetOkTextLabel->setObjectName(QStringLiteral("resetOkTextLabel"));
        resetOkTextLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(resetOkTextLabel);


        verticalLayout->addLayout(verticalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        goLoginPushButton = new QPushButton(ResetPasswordForm03);
        goLoginPushButton->setObjectName(QStringLiteral("goLoginPushButton"));

        horizontalLayout->addWidget(goLoginPushButton);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(17, 68, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        verticalLayout_3->addLayout(verticalLayout);


        retranslateUi(ResetPasswordForm03);

        QMetaObject::connectSlotsByName(ResetPasswordForm03);
    } // setupUi

    void retranslateUi(QWidget *ResetPasswordForm03)
    {
        ResetPasswordForm03->setWindowTitle(QApplication::translate("ResetPasswordForm03", "Form", 0));
        resetSuccess->setText(QString());
        resetOkTextLabel->setText(QApplication::translate("ResetPasswordForm03", "\346\226\260\345\257\206\347\240\201\350\256\276\347\275\256\346\210\220\345\212\237", 0));
        goLoginPushButton->setText(QApplication::translate("ResetPasswordForm03", "\345\216\273\347\231\273\345\275\225", 0));
    } // retranslateUi

};

namespace Ui {
    class ResetPasswordForm03: public Ui_ResetPasswordForm03 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESETPASSWORDFORM03_H
