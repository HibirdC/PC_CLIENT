/********************************************************************************
** Form generated from reading UI file 'ResetPasswordForm02.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESETPASSWORDFORM02_H
#define UI_RESETPASSWORDFORM02_H

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

class Ui_ResetPasswordForm02
{
public:
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *resetPsdLabel;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QToolButton *resetNum1;
    QLabel *resetLabel1;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *resetArrowH;
    QSpacerItem *horizontalSpacer_4;
    QToolButton *resetNum2H;
    QLabel *resetLabel2H;
    QSpacerItem *horizontalSpacer_2;
    QLabel *errorLabel;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *passwordLineEdit_1;
    QPushButton *resetPswFirst;
    QFrame *line;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *passwordLineEdit_2;
    QPushButton *resetPswSecond;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *resetPushButton;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *ResetPasswordForm02)
    {
        if (ResetPasswordForm02->objectName().isEmpty())
            ResetPasswordForm02->setObjectName(QStringLiteral("ResetPasswordForm02"));
        ResetPasswordForm02->resize(409, 403);
        verticalLayout_5 = new QVBoxLayout(ResetPasswordForm02);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(28, 0, 28, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, 26, -1, 26);
        resetPsdLabel = new QLabel(ResetPasswordForm02);
        resetPsdLabel->setObjectName(QStringLiteral("resetPsdLabel"));
        resetPsdLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(resetPsdLabel);


        verticalLayout_4->addLayout(verticalLayout_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(4);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, -1, -1, 20);
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        resetNum1 = new QToolButton(ResetPasswordForm02);
        resetNum1->setObjectName(QStringLiteral("resetNum1"));

        horizontalLayout_3->addWidget(resetNum1);

        resetLabel1 = new QLabel(ResetPasswordForm02);
        resetLabel1->setObjectName(QStringLiteral("resetLabel1"));

        horizontalLayout_3->addWidget(resetLabel1);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        resetArrowH = new QPushButton(ResetPasswordForm02);
        resetArrowH->setObjectName(QStringLiteral("resetArrowH"));

        horizontalLayout_3->addWidget(resetArrowH);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        resetNum2H = new QToolButton(ResetPasswordForm02);
        resetNum2H->setObjectName(QStringLiteral("resetNum2H"));

        horizontalLayout_3->addWidget(resetNum2H);

        resetLabel2H = new QLabel(ResetPasswordForm02);
        resetLabel2H->setObjectName(QStringLiteral("resetLabel2H"));

        horizontalLayout_3->addWidget(resetLabel2H);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_4->addLayout(horizontalLayout_3);

        errorLabel = new QLabel(ResetPasswordForm02);
        errorLabel->setObjectName(QStringLiteral("errorLabel"));

        verticalLayout_4->addWidget(errorLabel);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        passwordLineEdit_1 = new QLineEdit(ResetPasswordForm02);
        passwordLineEdit_1->setObjectName(QStringLiteral("passwordLineEdit_1"));

        horizontalLayout->addWidget(passwordLineEdit_1);

        resetPswFirst = new QPushButton(ResetPasswordForm02);
        resetPswFirst->setObjectName(QStringLiteral("resetPswFirst"));
        resetPswFirst->setCheckable(true);

        horizontalLayout->addWidget(resetPswFirst);


        verticalLayout->addLayout(horizontalLayout);

        line = new QFrame(ResetPasswordForm02);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);


        verticalLayout_4->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, -1, -1, 32);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        passwordLineEdit_2 = new QLineEdit(ResetPasswordForm02);
        passwordLineEdit_2->setObjectName(QStringLiteral("passwordLineEdit_2"));

        horizontalLayout_2->addWidget(passwordLineEdit_2);

        resetPswSecond = new QPushButton(ResetPasswordForm02);
        resetPswSecond->setObjectName(QStringLiteral("resetPswSecond"));
        resetPswSecond->setCheckable(true);

        horizontalLayout_2->addWidget(resetPswSecond);


        verticalLayout_2->addLayout(horizontalLayout_2);

        line_2 = new QFrame(ResetPasswordForm02);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);


        verticalLayout_4->addLayout(verticalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        resetPushButton = new QPushButton(ResetPasswordForm02);
        resetPushButton->setObjectName(QStringLiteral("resetPushButton"));

        horizontalLayout_4->addWidget(resetPushButton);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);


        verticalLayout_4->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);


        verticalLayout_5->addLayout(verticalLayout_4);


        retranslateUi(ResetPasswordForm02);

        QMetaObject::connectSlotsByName(ResetPasswordForm02);
    } // setupUi

    void retranslateUi(QWidget *ResetPasswordForm02)
    {
        ResetPasswordForm02->setWindowTitle(QApplication::translate("ResetPasswordForm02", "Form", 0));
        resetPsdLabel->setText(QApplication::translate("ResetPasswordForm02", "\351\207\215\347\275\256\345\257\206\347\240\201", 0));
        resetNum1->setText(QString());
        resetLabel1->setText(QApplication::translate("ResetPasswordForm02", "\351\252\214\350\257\201\350\272\253\344\273\275", 0));
        resetArrowH->setText(QString());
        resetNum2H->setText(QString());
        resetLabel2H->setText(QApplication::translate("ResetPasswordForm02", "\350\256\276\347\275\256\346\226\260\345\257\206\347\240\201", 0));
        errorLabel->setText(QApplication::translate("ResetPasswordForm02", "\351\224\231\350\257\257\346\217\220\347\244\272", 0));
        passwordLineEdit_1->setPlaceholderText(QApplication::translate("ResetPasswordForm02", "8-16\344\275\215 \350\207\263\345\260\221\345\220\253\346\225\260\345\255\227/\345\255\227\346\257\215/\347\254\246\345\217\2672\347\247\215\347\273\204\345\220\210", 0));
        resetPswFirst->setText(QString());
        passwordLineEdit_2->setPlaceholderText(QApplication::translate("ResetPasswordForm02", "\347\241\256\350\256\244\345\257\206\347\240\201", 0));
        resetPswSecond->setText(QString());
        resetPushButton->setText(QApplication::translate("ResetPasswordForm02", "\347\241\256\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class ResetPasswordForm02: public Ui_ResetPasswordForm02 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESETPASSWORDFORM02_H
