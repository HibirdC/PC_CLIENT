/********************************************************************************
** Form generated from reading UI file 'LoginBody.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINBODY_H
#define UI_LOGINBODY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "PasswordLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_LoginBody
{
public:
    QLabel *label_title;
    QPushButton *checkBox_tabPage;
    QStackedWidget *loginStackedWidget;
    QWidget *page_login;
    QPushButton *pushButton_login;
    QFrame *line_2;
    QFrame *line_3;
    QCheckBox *checkBox_AotoLogin;
    QStackedWidget *stackedWidget_2;
    QWidget *page_password;
    PasswordLineEdit *lineEdit_Password;
    QWidget *page_idecode;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEdit_IdentifyCode;
    QPushButton *pushButton_SendIdentifyCode;
    QLabel *label_info;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *checkBox_pwdLogin;
    QPushButton *checkBox_IdeCodeLogin;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *comboBox_mobilePre;
    QLineEdit *lineEdit_mobile;
    QWidget *page_scan;
    QLabel *label_scanpic;
    QLabel *label_scantip;
    QWidget *page_scanConfirm;
    QLabel *label_mobile;
    QLabel *label_2;
    QLabel *labelCancelScan;
    QWidget *page_faceid;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_11;
    QVBoxLayout *verticalLayout_10;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_4;
    QComboBox *comboBox_mobilePre_code;
    QLineEdit *lineEdit_phone_num;
    QFrame *line;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_13;
    QLabel *label_login_error;
    QSpacerItem *horizontalSpacer_14;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btn_face_login;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btn_faceid_other;
    QSpacerItem *horizontalSpacer;
    QWidget *page_faceid_login_failed;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_faceid_failed_icon;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label_faceid_failed_error;
    QSpacerItem *horizontalSpacer_12;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btn_faceid_failed_tryagain;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *btn_faceid_failed_other_login;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *btn_min;
    QPushButton *btn_close;
    QLabel *label_bottom;
    QLabel *deviceLabel;
    QPushButton *btn_faceid;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_11;
    QWidget *layoutWidget6;
    QVBoxLayout *verticalLayout_5;
    QWidget *layoutWidget7;
    QVBoxLayout *verticalLayout_6;
    QWidget *layoutWidget8;
    QVBoxLayout *verticalLayout_7;
    QWidget *layoutWidget9;
    QVBoxLayout *verticalLayout_9;

    void setupUi(QWidget *LoginBody)
    {
        if (LoginBody->objectName().isEmpty())
            LoginBody->setObjectName(QStringLiteral("LoginBody"));
        LoginBody->resize(320, 432);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LoginBody->sizePolicy().hasHeightForWidth());
        LoginBody->setSizePolicy(sizePolicy);
        LoginBody->setAutoFillBackground(true);
        LoginBody->setStyleSheet(QStringLiteral(""));
        label_title = new QLabel(LoginBody);
        label_title->setObjectName(QStringLiteral("label_title"));
        label_title->setGeometry(QRect(125, 40, 70, 27));
        label_title->setAlignment(Qt::AlignCenter);
        checkBox_tabPage = new QPushButton(LoginBody);
        checkBox_tabPage->setObjectName(QStringLiteral("checkBox_tabPage"));
        checkBox_tabPage->setGeometry(QRect(18, 10, 16, 16));
        checkBox_tabPage->setCursor(QCursor(Qt::PointingHandCursor));
        checkBox_tabPage->setIconSize(QSize(30, 26));
        checkBox_tabPage->setCheckable(true);
        loginStackedWidget = new QStackedWidget(LoginBody);
        loginStackedWidget->setObjectName(QStringLiteral("loginStackedWidget"));
        loginStackedWidget->setGeometry(QRect(10, 106, 300, 250));
        page_login = new QWidget();
        page_login->setObjectName(QStringLiteral("page_login"));
        pushButton_login = new QPushButton(page_login);
        pushButton_login->setObjectName(QStringLiteral("pushButton_login"));
        pushButton_login->setGeometry(QRect(35, 180, 230, 70));
        pushButton_login->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_login->setStyleSheet(QStringLiteral(""));
        line_2 = new QFrame(page_login);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(40, 82, 214, 1));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(page_login);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(40, 133, 214, 1));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        checkBox_AotoLogin = new QCheckBox(page_login);
        checkBox_AotoLogin->setObjectName(QStringLiteral("checkBox_AotoLogin"));
        checkBox_AotoLogin->setGeometry(QRect(190, 143, 101, 21));
        checkBox_AotoLogin->setCursor(QCursor(Qt::PointingHandCursor));
        stackedWidget_2 = new QStackedWidget(page_login);
        stackedWidget_2->setObjectName(QStringLiteral("stackedWidget_2"));
        stackedWidget_2->setGeometry(QRect(0, 88, 300, 41));
        page_password = new QWidget();
        page_password->setObjectName(QStringLiteral("page_password"));
        lineEdit_Password = new PasswordLineEdit(page_password);
        lineEdit_Password->setObjectName(QStringLiteral("lineEdit_Password"));
        lineEdit_Password->setGeometry(QRect(40, 9, 131, 31));
        stackedWidget_2->addWidget(page_password);
        page_idecode = new QWidget();
        page_idecode->setObjectName(QStringLiteral("page_idecode"));
        layoutWidget = new QWidget(page_idecode);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 10, 227, 33));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        lineEdit_IdentifyCode = new QLineEdit(layoutWidget);
        lineEdit_IdentifyCode->setObjectName(QStringLiteral("lineEdit_IdentifyCode"));
        sizePolicy.setHeightForWidth(lineEdit_IdentifyCode->sizePolicy().hasHeightForWidth());
        lineEdit_IdentifyCode->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(lineEdit_IdentifyCode);

        pushButton_SendIdentifyCode = new QPushButton(layoutWidget);
        pushButton_SendIdentifyCode->setObjectName(QStringLiteral("pushButton_SendIdentifyCode"));
        sizePolicy.setHeightForWidth(pushButton_SendIdentifyCode->sizePolicy().hasHeightForWidth());
        pushButton_SendIdentifyCode->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(pushButton_SendIdentifyCode);

        stackedWidget_2->addWidget(page_idecode);
        label_info = new QLabel(page_login);
        label_info->setObjectName(QStringLiteral("label_info"));
        label_info->setGeometry(QRect(24, 143, 168, 16));
        label_info->setLayoutDirection(Qt::LeftToRight);
        layoutWidget1 = new QWidget(page_login);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 0, 320, 33));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(30);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(78, 0, 78, 0);
        checkBox_pwdLogin = new QPushButton(layoutWidget1);
        checkBox_pwdLogin->setObjectName(QStringLiteral("checkBox_pwdLogin"));
        checkBox_pwdLogin->setMinimumSize(QSize(56, 0));
        checkBox_pwdLogin->setMaximumSize(QSize(56, 16777215));
        checkBox_pwdLogin->setCursor(QCursor(Qt::PointingHandCursor));
        checkBox_pwdLogin->setLayoutDirection(Qt::LeftToRight);
        checkBox_pwdLogin->setCheckable(true);

        horizontalLayout->addWidget(checkBox_pwdLogin);

        checkBox_IdeCodeLogin = new QPushButton(layoutWidget1);
        checkBox_IdeCodeLogin->setObjectName(QStringLiteral("checkBox_IdeCodeLogin"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(checkBox_IdeCodeLogin->sizePolicy().hasHeightForWidth());
        checkBox_IdeCodeLogin->setSizePolicy(sizePolicy1);
        checkBox_IdeCodeLogin->setMinimumSize(QSize(70, 0));
        checkBox_IdeCodeLogin->setMaximumSize(QSize(70, 16777215));
        checkBox_IdeCodeLogin->setCursor(QCursor(Qt::PointingHandCursor));
        checkBox_IdeCodeLogin->setCheckable(true);

        horizontalLayout->addWidget(checkBox_IdeCodeLogin);

        layoutWidget2 = new QWidget(page_login);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(40, 50, 279, 27));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        comboBox_mobilePre = new QComboBox(layoutWidget2);
        comboBox_mobilePre->setObjectName(QStringLiteral("comboBox_mobilePre"));
        sizePolicy.setHeightForWidth(comboBox_mobilePre->sizePolicy().hasHeightForWidth());
        comboBox_mobilePre->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(comboBox_mobilePre);

        lineEdit_mobile = new QLineEdit(layoutWidget2);
        lineEdit_mobile->setObjectName(QStringLiteral("lineEdit_mobile"));
        sizePolicy.setHeightForWidth(lineEdit_mobile->sizePolicy().hasHeightForWidth());
        lineEdit_mobile->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(lineEdit_mobile);

        loginStackedWidget->addWidget(page_login);
        page_scan = new QWidget();
        page_scan->setObjectName(QStringLiteral("page_scan"));
        label_scanpic = new QLabel(page_scan);
        label_scanpic->setObjectName(QStringLiteral("label_scanpic"));
        label_scanpic->setGeometry(QRect(75, 10, 150, 150));
        label_scanpic->setMinimumSize(QSize(150, 150));
        label_scanpic->setMaximumSize(QSize(150, 150));
        label_scantip = new QLabel(page_scan);
        label_scantip->setObjectName(QStringLiteral("label_scantip"));
        label_scantip->setGeometry(QRect(0, 180, 300, 16));
        label_scantip->setAlignment(Qt::AlignCenter);
        loginStackedWidget->addWidget(page_scan);
        page_scanConfirm = new QWidget();
        page_scanConfirm->setObjectName(QStringLiteral("page_scanConfirm"));
        label_mobile = new QLabel(page_scanConfirm);
        label_mobile->setObjectName(QStringLiteral("label_mobile"));
        label_mobile->setGeometry(QRect(0, 50, 300, 20));
        label_mobile->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(page_scanConfirm);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 88, 300, 20));
        label_2->setAlignment(Qt::AlignCenter);
        labelCancelScan = new QLabel(page_scanConfirm);
        labelCancelScan->setObjectName(QStringLiteral("labelCancelScan"));
        labelCancelScan->setGeometry(QRect(0, 132, 300, 15));
        labelCancelScan->setAlignment(Qt::AlignCenter);
        labelCancelScan->setOpenExternalLinks(false);
        loginStackedWidget->addWidget(page_scanConfirm);
        page_faceid = new QWidget();
        page_faceid->setObjectName(QStringLiteral("page_faceid"));
        layoutWidget3 = new QWidget(page_faceid);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 10, 281, 241));
        verticalLayout_11 = new QVBoxLayout(layoutWidget3);
        verticalLayout_11->setSpacing(35);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(10);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(39, -1, 40, -1);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        comboBox_mobilePre_code = new QComboBox(layoutWidget3);
        comboBox_mobilePre_code->setObjectName(QStringLiteral("comboBox_mobilePre_code"));
        sizePolicy.setHeightForWidth(comboBox_mobilePre_code->sizePolicy().hasHeightForWidth());
        comboBox_mobilePre_code->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(comboBox_mobilePre_code);

        lineEdit_phone_num = new QLineEdit(layoutWidget3);
        lineEdit_phone_num->setObjectName(QStringLiteral("lineEdit_phone_num"));
        lineEdit_phone_num->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout_4->addWidget(lineEdit_phone_num);


        verticalLayout_8->addLayout(horizontalLayout_4);

        line = new QFrame(layoutWidget3);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_8->addWidget(line);


        verticalLayout_10->addLayout(verticalLayout_8);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(0);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_13);

        label_login_error = new QLabel(layoutWidget3);
        label_login_error->setObjectName(QStringLiteral("label_login_error"));
        label_login_error->setMaximumSize(QSize(16777215, 16));
        label_login_error->setAlignment(Qt::AlignCenter);

        horizontalLayout_12->addWidget(label_login_error);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_14);


        verticalLayout_10->addLayout(horizontalLayout_12);


        verticalLayout_11->addLayout(verticalLayout_10);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        btn_face_login = new QPushButton(layoutWidget3);
        btn_face_login->setObjectName(QStringLiteral("btn_face_login"));
        btn_face_login->setMinimumSize(QSize(230, 72));
        btn_face_login->setMaximumSize(QSize(230, 72));
        btn_face_login->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_6->addWidget(btn_face_login);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        btn_faceid_other = new QPushButton(layoutWidget3);
        btn_faceid_other->setObjectName(QStringLiteral("btn_faceid_other"));
        btn_faceid_other->setMinimumSize(QSize(84, 15));
        btn_faceid_other->setMaximumSize(QSize(16777215, 20));
        btn_faceid_other->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_5->addWidget(btn_faceid_other);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_5);


        verticalLayout_11->addLayout(verticalLayout);

        loginStackedWidget->addWidget(page_faceid);
        page_faceid_login_failed = new QWidget();
        page_faceid_login_failed->setObjectName(QStringLiteral("page_faceid_login_failed"));
        layoutWidget4 = new QWidget(page_faceid_login_failed);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(1, 20, 301, 231));
        verticalLayout_4 = new QVBoxLayout(layoutWidget4);
        verticalLayout_4->setSpacing(10);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(10);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(0);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_9);

        label_faceid_failed_icon = new QLabel(layoutWidget4);
        label_faceid_failed_icon->setObjectName(QStringLiteral("label_faceid_failed_icon"));
        label_faceid_failed_icon->setMinimumSize(QSize(50, 50));
        label_faceid_failed_icon->setMaximumSize(QSize(50, 50));

        horizontalLayout_9->addWidget(label_faceid_failed_icon);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_10);


        verticalLayout_3->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(0);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_11);

        label_faceid_failed_error = new QLabel(layoutWidget4);
        label_faceid_failed_error->setObjectName(QStringLiteral("label_faceid_failed_error"));
        label_faceid_failed_error->setMaximumSize(QSize(16777215, 15));

        horizontalLayout_10->addWidget(label_faceid_failed_error);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_12);


        verticalLayout_3->addLayout(horizontalLayout_10);


        verticalLayout_4->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(10);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);

        btn_faceid_failed_tryagain = new QPushButton(layoutWidget4);
        btn_faceid_failed_tryagain->setObjectName(QStringLiteral("btn_faceid_failed_tryagain"));
        btn_faceid_failed_tryagain->setMinimumSize(QSize(230, 72));
        btn_faceid_failed_tryagain->setMaximumSize(QSize(230, 72));
        btn_faceid_failed_tryagain->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_7->addWidget(btn_faceid_failed_tryagain);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_6);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_7);

        btn_faceid_failed_other_login = new QPushButton(layoutWidget4);
        btn_faceid_failed_other_login->setObjectName(QStringLiteral("btn_faceid_failed_other_login"));
        btn_faceid_failed_other_login->setMinimumSize(QSize(84, 20));
        btn_faceid_failed_other_login->setMaximumSize(QSize(84, 20));
        btn_faceid_failed_other_login->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_8->addWidget(btn_faceid_failed_other_login);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_8);


        verticalLayout_2->addLayout(horizontalLayout_8);


        verticalLayout_4->addLayout(verticalLayout_2);

        loginStackedWidget->addWidget(page_faceid_login_failed);
        btn_min = new QPushButton(LoginBody);
        btn_min->setObjectName(QStringLiteral("btn_min"));
        btn_min->setGeometry(QRect(268, 0, 18, 18));
        btn_min->setMaximumSize(QSize(18, 18));
        btn_close = new QPushButton(LoginBody);
        btn_close->setObjectName(QStringLiteral("btn_close"));
        btn_close->setGeometry(QRect(286, 0, 18, 18));
        sizePolicy.setHeightForWidth(btn_close->sizePolicy().hasHeightForWidth());
        btn_close->setSizePolicy(sizePolicy);
        btn_close->setMaximumSize(QSize(18, 18));
        label_bottom = new QLabel(LoginBody);
        label_bottom->setObjectName(QStringLiteral("label_bottom"));
        label_bottom->setGeometry(QRect(11, 365, 298, 46));
        deviceLabel = new QLabel(LoginBody);
        deviceLabel->setObjectName(QStringLiteral("deviceLabel"));
        deviceLabel->setGeometry(QRect(0, 164, 320, 19));
        sizePolicy.setHeightForWidth(deviceLabel->sizePolicy().hasHeightForWidth());
        deviceLabel->setSizePolicy(sizePolicy);
        deviceLabel->setAlignment(Qt::AlignCenter);
        btn_faceid = new QPushButton(LoginBody);
        btn_faceid->setObjectName(QStringLiteral("btn_faceid"));
        btn_faceid->setGeometry(QRect(49, 10, 16, 16));
        btn_faceid->setCursor(QCursor(Qt::PointingHandCursor));
        layoutWidget5 = new QWidget(LoginBody);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(0, 0, 2, 2));
        horizontalLayout_11 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        layoutWidget6 = new QWidget(LoginBody);
        layoutWidget6->setObjectName(QStringLiteral("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout_5 = new QVBoxLayout(layoutWidget6);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        layoutWidget7 = new QWidget(LoginBody);
        layoutWidget7->setObjectName(QStringLiteral("layoutWidget7"));
        layoutWidget7->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout_6 = new QVBoxLayout(layoutWidget7);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        layoutWidget8 = new QWidget(LoginBody);
        layoutWidget8->setObjectName(QStringLiteral("layoutWidget8"));
        layoutWidget8->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout_7 = new QVBoxLayout(layoutWidget8);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        layoutWidget9 = new QWidget(LoginBody);
        layoutWidget9->setObjectName(QStringLiteral("layoutWidget9"));
        layoutWidget9->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout_9 = new QVBoxLayout(layoutWidget9);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        label_bottom->raise();
        label_title->raise();
        checkBox_tabPage->raise();
        loginStackedWidget->raise();
        btn_min->raise();
        btn_close->raise();
        deviceLabel->raise();
        btn_faceid->raise();
        layoutWidget->raise();
        QWidget::setTabOrder(checkBox_pwdLogin, checkBox_IdeCodeLogin);
        QWidget::setTabOrder(checkBox_IdeCodeLogin, comboBox_mobilePre);
        QWidget::setTabOrder(comboBox_mobilePre, lineEdit_mobile);
        QWidget::setTabOrder(lineEdit_mobile, lineEdit_Password);
        QWidget::setTabOrder(lineEdit_Password, checkBox_AotoLogin);
        QWidget::setTabOrder(checkBox_AotoLogin, pushButton_login);
        QWidget::setTabOrder(pushButton_login, checkBox_tabPage);
        QWidget::setTabOrder(checkBox_tabPage, lineEdit_IdentifyCode);
        QWidget::setTabOrder(lineEdit_IdentifyCode, pushButton_SendIdentifyCode);

        retranslateUi(LoginBody);

        loginStackedWidget->setCurrentIndex(3);
        stackedWidget_2->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(LoginBody);
    } // setupUi

    void retranslateUi(QWidget *LoginBody)
    {
        LoginBody->setWindowTitle(QApplication::translate("LoginBody", "LoginBody", 0));
        label_title->setText(QString());
        checkBox_tabPage->setText(QString());
        pushButton_login->setText(QApplication::translate("LoginBody", "\347\231\273 \345\275\225", 0));
        checkBox_AotoLogin->setText(QApplication::translate("LoginBody", "\350\207\252\345\212\250\347\231\273\345\275\225", 0));
        lineEdit_Password->setPlaceholderText(QApplication::translate("LoginBody", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", 0));
        lineEdit_IdentifyCode->setPlaceholderText(QApplication::translate("LoginBody", "\350\257\267\350\276\223\345\205\245\351\252\214\350\257\201\347\240\201", 0));
        pushButton_SendIdentifyCode->setText(QApplication::translate("LoginBody", "\350\216\267\345\217\226\351\252\214\350\257\201\347\240\201", 0));
        label_info->setText(QApplication::translate("LoginBody", "TextLabel", 0));
        checkBox_pwdLogin->setText(QApplication::translate("LoginBody", "\345\257\206\347\240\201\347\231\273\345\275\225", 0));
        checkBox_IdeCodeLogin->setText(QApplication::translate("LoginBody", "\351\252\214\350\257\201\347\240\201\347\231\273\345\275\225", 0));
        comboBox_mobilePre->setCurrentText(QString());
        lineEdit_mobile->setPlaceholderText(QApplication::translate("LoginBody", "\350\257\267\350\276\223\345\205\245\346\211\213\346\234\272\345\217\267", 0));
        label_scanpic->setText(QString());
        label_scantip->setText(QApplication::translate("LoginBody", "\350\257\267\344\275\277\347\224\250\351\200\232toon\346\211\213\346\234\272\347\211\210\346\211\253\346\217\217\344\272\214\347\273\264\347\240\201\347\231\273\345\275\225", 0));
        label_mobile->setText(QApplication::translate("LoginBody", "138****8888", 0));
        label_2->setText(QApplication::translate("LoginBody", "\350\257\267\345\234\250\346\211\213\346\234\272\344\270\212\347\241\256\350\256\244\347\231\273\345\275\225", 0));
        labelCancelScan->setText(QApplication::translate("LoginBody", "<style> a {text-decoration: none} </style><a style='color: #3395FF;' href =\"www.toon.com\"> \350\277\224\345\233\236\346\211\253\347\240\201\347\231\273\345\275\225</a>", 0));
        comboBox_mobilePre_code->setCurrentText(QString());
        label_login_error->setText(QApplication::translate("LoginBody", "face error", 0));
        btn_face_login->setText(QApplication::translate("LoginBody", "\344\272\272\350\204\270\350\257\206\345\210\253\347\231\273\345\275\225", 0));
        btn_faceid_other->setText(QApplication::translate("LoginBody", "\345\205\266\345\256\203\347\231\273\345\275\225\346\226\271\345\274\217", 0));
        label_faceid_failed_icon->setText(QString());
        label_faceid_failed_error->setText(QApplication::translate("LoginBody", "\344\272\272\350\204\270\350\257\206\345\210\253\345\244\261\350\264\245", 0));
        btn_faceid_failed_tryagain->setText(QApplication::translate("LoginBody", "\345\206\215\350\257\225\344\270\200\346\254\241", 0));
        btn_faceid_failed_other_login->setText(QApplication::translate("LoginBody", "\345\205\266\345\256\203\347\231\273\345\275\225\346\226\271\345\274\217", 0));
        btn_min->setText(QString());
        btn_close->setText(QString());
        label_bottom->setText(QApplication::translate("LoginBody", "TextLabel", 0));
        deviceLabel->setText(QApplication::translate("LoginBody", "\346\215\242\350\256\276\345\244\207\344\272\206", 0));
        btn_faceid->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoginBody: public Ui_LoginBody {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINBODY_H
