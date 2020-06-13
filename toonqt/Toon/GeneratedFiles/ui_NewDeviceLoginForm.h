/********************************************************************************
** Form generated from reading UI file 'NewDeviceLoginForm.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWDEVICELOGINFORM_H
#define UI_NEWDEVICELOGINFORM_H

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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewDeviceLoginForm
{
public:
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_title;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *errorLabel;
    QLabel *deviceLabel;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *idCodeLineEdit;
    QPushButton *obtainIdCodeButton;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *loginPushButton;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *NewDeviceLoginForm)
    {
        if (NewDeviceLoginForm->objectName().isEmpty())
            NewDeviceLoginForm->setObjectName(QStringLiteral("NewDeviceLoginForm"));
        NewDeviceLoginForm->resize(241, 274);
        verticalLayout_4 = new QVBoxLayout(NewDeviceLoginForm);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(38, 0, 38, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 22, -1, 18);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_title = new QLabel(NewDeviceLoginForm);
        label_title->setObjectName(QStringLiteral("label_title"));
        label_title->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_title);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 10, -1, 20);
        errorLabel = new QLabel(NewDeviceLoginForm);
        errorLabel->setObjectName(QStringLiteral("errorLabel"));

        verticalLayout_2->addWidget(errorLabel);


        verticalLayout_3->addLayout(verticalLayout_2);

        deviceLabel = new QLabel(NewDeviceLoginForm);
        deviceLabel->setObjectName(QStringLiteral("deviceLabel"));
        deviceLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(deviceLabel);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 20, -1, 30);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        idCodeLineEdit = new QLineEdit(NewDeviceLoginForm);
        idCodeLineEdit->setObjectName(QStringLiteral("idCodeLineEdit"));
        idCodeLineEdit->setMaxLength(4);

        horizontalLayout->addWidget(idCodeLineEdit);

        obtainIdCodeButton = new QPushButton(NewDeviceLoginForm);
        obtainIdCodeButton->setObjectName(QStringLiteral("obtainIdCodeButton"));

        horizontalLayout->addWidget(obtainIdCodeButton);


        verticalLayout->addLayout(horizontalLayout);

        line_2 = new QFrame(NewDeviceLoginForm);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);


        verticalLayout_3->addLayout(verticalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        loginPushButton = new QPushButton(NewDeviceLoginForm);
        loginPushButton->setObjectName(QStringLiteral("loginPushButton"));
        loginPushButton->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_3->addWidget(loginPushButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        verticalLayout_4->addLayout(verticalLayout_3);


        retranslateUi(NewDeviceLoginForm);

        QMetaObject::connectSlotsByName(NewDeviceLoginForm);
    } // setupUi

    void retranslateUi(QWidget *NewDeviceLoginForm)
    {
        NewDeviceLoginForm->setWindowTitle(QApplication::translate("NewDeviceLoginForm", "Form", 0));
        label_title->setText(QString());
        errorLabel->setText(QApplication::translate("NewDeviceLoginForm", "\351\224\231\350\257\257\346\217\220\347\244\272", 0));
        deviceLabel->setText(QApplication::translate("NewDeviceLoginForm", "\344\270\272\344\277\235\350\257\201\346\202\250\347\232\204\350\264\246\345\217\267\345\256\211\345\205\250\357\274\214\350\257\267\350\276\223\345\205\245\351\252\214\350\257\201\347\240\201", 0));
        idCodeLineEdit->setPlaceholderText(QApplication::translate("NewDeviceLoginForm", "\347\237\255\344\277\241\351\252\214\350\257\201\347\240\201", 0));
        obtainIdCodeButton->setText(QApplication::translate("NewDeviceLoginForm", "\350\216\267\345\217\226\351\252\214\350\257\201\347\240\201", 0));
        loginPushButton->setText(QApplication::translate("NewDeviceLoginForm", "\347\231\273\345\275\225", 0));
    } // retranslateUi

};

namespace Ui {
    class NewDeviceLoginForm: public Ui_NewDeviceLoginForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWDEVICELOGINFORM_H
