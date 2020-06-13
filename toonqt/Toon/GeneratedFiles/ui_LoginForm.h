/********************************************************************************
** Form generated from reading UI file 'LoginForm.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINFORM_H
#define UI_LOGINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginForm
{
public:
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_title;
    QSpacerItem *horizontalSpacer_2;
    QLabel *errorLabel;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *mobileLineEdit;
    QFrame *line;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *passwordLineEdit;
    QFrame *line_2;
    QGridLayout *gridLayout;
    QCheckBox *autoLoginCheckBox;
    QPushButton *forgetPsdPushButton;
    QCheckBox *rememberPsdCheckBox;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *loginPushButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *LoginForm)
    {
        if (LoginForm->objectName().isEmpty())
            LoginForm->setObjectName(QStringLiteral("LoginForm"));
        LoginForm->resize(230, 314);
        verticalLayout_4 = new QVBoxLayout(LoginForm);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(38, 0, 38, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 22, -1, 18);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_title = new QLabel(LoginForm);
        label_title->setObjectName(QStringLiteral("label_title"));
        label_title->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_title);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        errorLabel = new QLabel(LoginForm);
        errorLabel->setObjectName(QStringLiteral("errorLabel"));

        verticalLayout_3->addWidget(errorLabel);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        mobileLineEdit = new QLineEdit(LoginForm);
        mobileLineEdit->setObjectName(QStringLiteral("mobileLineEdit"));

        horizontalLayout->addWidget(mobileLineEdit);

        horizontalLayout->setStretch(0, 1);

        verticalLayout->addLayout(horizontalLayout);

        line = new QFrame(LoginForm);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);


        verticalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        passwordLineEdit = new QLineEdit(LoginForm);
        passwordLineEdit->setObjectName(QStringLiteral("passwordLineEdit"));

        verticalLayout_2->addWidget(passwordLineEdit);

        line_2 = new QFrame(LoginForm);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);


        verticalLayout_3->addLayout(verticalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(0);
        gridLayout->setVerticalSpacing(8);
        gridLayout->setContentsMargins(-1, 10, 0, 24);
        autoLoginCheckBox = new QCheckBox(LoginForm);
        autoLoginCheckBox->setObjectName(QStringLiteral("autoLoginCheckBox"));

        gridLayout->addWidget(autoLoginCheckBox, 1, 0, 1, 1);

        forgetPsdPushButton = new QPushButton(LoginForm);
        forgetPsdPushButton->setObjectName(QStringLiteral("forgetPsdPushButton"));
        forgetPsdPushButton->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout->addWidget(forgetPsdPushButton, 0, 2, 1, 1);

        rememberPsdCheckBox = new QCheckBox(LoginForm);
        rememberPsdCheckBox->setObjectName(QStringLiteral("rememberPsdCheckBox"));

        gridLayout->addWidget(rememberPsdCheckBox, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout);

        loginPushButton = new QPushButton(LoginForm);
        loginPushButton->setObjectName(QStringLiteral("loginPushButton"));
        loginPushButton->setFocusPolicy(Qt::NoFocus);

        verticalLayout_3->addWidget(loginPushButton);


        verticalLayout_4->addLayout(verticalLayout_3);

        verticalSpacer = new QSpacerItem(20, 77, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);


        retranslateUi(LoginForm);

        QMetaObject::connectSlotsByName(LoginForm);
    } // setupUi

    void retranslateUi(QWidget *LoginForm)
    {
        LoginForm->setWindowTitle(QApplication::translate("LoginForm", "Form", 0));
        label_title->setText(QString());
        errorLabel->setText(QApplication::translate("LoginForm", "\351\224\231\350\257\257\346\217\220\347\244\272", 0));
        mobileLineEdit->setPlaceholderText(QApplication::translate("LoginForm", "\350\257\267\350\276\223\345\205\245\351\202\256\347\256\261", 0));
        passwordLineEdit->setPlaceholderText(QApplication::translate("LoginForm", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", 0));
        autoLoginCheckBox->setText(QApplication::translate("LoginForm", "\350\207\252\345\212\250\347\231\273\345\275\225", 0));
        forgetPsdPushButton->setText(QApplication::translate("LoginForm", "\345\277\230\350\256\260\345\257\206\347\240\201", 0));
        rememberPsdCheckBox->setText(QApplication::translate("LoginForm", "\350\256\260\344\275\217\345\257\206\347\240\201", 0));
        loginPushButton->setText(QApplication::translate("LoginForm", "\347\231\273\345\275\225", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginForm: public Ui_LoginForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINFORM_H
