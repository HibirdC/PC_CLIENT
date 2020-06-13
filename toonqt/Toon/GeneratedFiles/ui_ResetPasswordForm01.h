/********************************************************************************
** Form generated from reading UI file 'ResetPasswordForm01.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESETPASSWORDFORM01_H
#define UI_RESETPASSWORDFORM01_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ResetPasswordForm01
{
public:
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *resetPsdLabel;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QToolButton *resetNum1;
    QLabel *resetLabel1;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *resetArrow;
    QSpacerItem *horizontalSpacer_4;
    QToolButton *resetNum2;
    QLabel *resetLabel2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *errorLabel;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *mobileLineEdit;
    QFrame *line;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *idCodeLineEdit;
    QPushButton *obtainIdCodeButton;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *resetPushButton;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *ResetPasswordForm01)
    {
        if (ResetPasswordForm01->objectName().isEmpty())
            ResetPasswordForm01->setObjectName(QStringLiteral("ResetPasswordForm01"));
        ResetPasswordForm01->resize(488, 358);
        verticalLayout_4 = new QVBoxLayout(ResetPasswordForm01);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(28, 0, 28, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 26, -1, 26);
        resetPsdLabel = new QLabel(ResetPasswordForm01);
        resetPsdLabel->setObjectName(QStringLiteral("resetPsdLabel"));
        resetPsdLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(resetPsdLabel);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(4);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, -1, -1, 20);
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        resetNum1 = new QToolButton(ResetPasswordForm01);
        resetNum1->setObjectName(QStringLiteral("resetNum1"));

        horizontalLayout_3->addWidget(resetNum1);

        resetLabel1 = new QLabel(ResetPasswordForm01);
        resetLabel1->setObjectName(QStringLiteral("resetLabel1"));

        horizontalLayout_3->addWidget(resetLabel1);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        resetArrow = new QPushButton(ResetPasswordForm01);
        resetArrow->setObjectName(QStringLiteral("resetArrow"));

        horizontalLayout_3->addWidget(resetArrow);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        resetNum2 = new QToolButton(ResetPasswordForm01);
        resetNum2->setObjectName(QStringLiteral("resetNum2"));

        horizontalLayout_3->addWidget(resetNum2);

        resetLabel2 = new QLabel(ResetPasswordForm01);
        resetLabel2->setObjectName(QStringLiteral("resetLabel2"));

        horizontalLayout_3->addWidget(resetLabel2);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_3);

        errorLabel = new QLabel(ResetPasswordForm01);
        errorLabel->setObjectName(QStringLiteral("errorLabel"));

        verticalLayout_3->addWidget(errorLabel);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        mobileLineEdit = new QLineEdit(ResetPasswordForm01);
        mobileLineEdit->setObjectName(QStringLiteral("mobileLineEdit"));

        horizontalLayout->addWidget(mobileLineEdit);

        horizontalLayout->setStretch(0, 1);

        verticalLayout->addLayout(horizontalLayout);

        line = new QFrame(ResetPasswordForm01);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);


        verticalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, -1, -1, 32);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        idCodeLineEdit = new QLineEdit(ResetPasswordForm01);
        idCodeLineEdit->setObjectName(QStringLiteral("idCodeLineEdit"));

        horizontalLayout_2->addWidget(idCodeLineEdit);

        obtainIdCodeButton = new QPushButton(ResetPasswordForm01);
        obtainIdCodeButton->setObjectName(QStringLiteral("obtainIdCodeButton"));

        horizontalLayout_2->addWidget(obtainIdCodeButton);


        verticalLayout_2->addLayout(horizontalLayout_2);

        line_2 = new QFrame(ResetPasswordForm01);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);


        verticalLayout_3->addLayout(verticalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        resetPushButton = new QPushButton(ResetPasswordForm01);
        resetPushButton->setObjectName(QStringLiteral("resetPushButton"));

        horizontalLayout_5->addWidget(resetPushButton);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);


        verticalLayout_3->addLayout(horizontalLayout_5);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        verticalLayout_4->addLayout(verticalLayout_3);


        retranslateUi(ResetPasswordForm01);

        QMetaObject::connectSlotsByName(ResetPasswordForm01);
    } // setupUi

    void retranslateUi(QWidget *ResetPasswordForm01)
    {
        ResetPasswordForm01->setWindowTitle(QApplication::translate("ResetPasswordForm01", "Form", 0));
        resetPsdLabel->setText(QApplication::translate("ResetPasswordForm01", "\351\207\215\347\275\256\345\257\206\347\240\201", 0));
        resetNum1->setText(QString());
        resetLabel1->setText(QApplication::translate("ResetPasswordForm01", "\351\252\214\350\257\201\350\272\253\344\273\275", 0));
        resetArrow->setText(QString());
        resetNum2->setText(QString());
        resetLabel2->setText(QApplication::translate("ResetPasswordForm01", "\350\256\276\347\275\256\346\226\260\345\257\206\347\240\201", 0));
        errorLabel->setText(QApplication::translate("ResetPasswordForm01", "\351\224\231\350\257\257\346\217\220\347\244\272", 0));
        mobileLineEdit->setPlaceholderText(QApplication::translate("ResetPasswordForm01", "\350\257\267\345\241\253\345\206\231\346\263\250\345\206\214\346\211\213\346\234\272\345\217\267", 0));
        idCodeLineEdit->setPlaceholderText(QApplication::translate("ResetPasswordForm01", "\347\237\255\344\277\241\351\252\214\350\257\201\347\240\201", 0));
        obtainIdCodeButton->setText(QApplication::translate("ResetPasswordForm01", "\350\216\267\345\217\226\351\252\214\350\257\201\347\240\201", 0));
        resetPushButton->setText(QApplication::translate("ResetPasswordForm01", "\347\241\256\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class ResetPasswordForm01: public Ui_ResetPasswordForm01 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESETPASSWORDFORM01_H
