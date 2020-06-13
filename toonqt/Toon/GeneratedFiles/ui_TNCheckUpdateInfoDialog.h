/********************************************************************************
** Form generated from reading UI file 'TNCheckUpdateInfoDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNCHECKUPDATEINFODIALOG_H
#define UI_TNCHECKUPDATEINFODIALOG_H

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
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TNCheckUpdateInfoDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *updateInfoTitleWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *updateInfoTitleLabel;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QTextEdit *textEdit;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *nowButton;
    QPushButton *quitButton;
    QPushButton *afterButton;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *TNCheckUpdateInfoDialog)
    {
        if (TNCheckUpdateInfoDialog->objectName().isEmpty())
            TNCheckUpdateInfoDialog->setObjectName(QStringLiteral("TNCheckUpdateInfoDialog"));
        TNCheckUpdateInfoDialog->resize(450, 242);
        verticalLayout_2 = new QVBoxLayout(TNCheckUpdateInfoDialog);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 6, 0, 30);
        updateInfoTitleWidget = new QWidget(TNCheckUpdateInfoDialog);
        updateInfoTitleWidget->setObjectName(QStringLiteral("updateInfoTitleWidget"));
        updateInfoTitleWidget->setMinimumSize(QSize(100, 25));
        horizontalLayout_2 = new QHBoxLayout(updateInfoTitleWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 5, -1, 5);
        updateInfoTitleLabel = new QLabel(updateInfoTitleWidget);
        updateInfoTitleLabel->setObjectName(QStringLiteral("updateInfoTitleLabel"));
        updateInfoTitleLabel->setMinimumSize(QSize(200, 15));
        updateInfoTitleLabel->setAlignment(Qt::AlignCenter);
        updateInfoTitleLabel->setIndent(0);

        horizontalLayout_2->addWidget(updateInfoTitleLabel);


        verticalLayout_2->addWidget(updateInfoTitleWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(40, -1, 40, -1);
        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        textEdit = new QTextEdit(TNCheckUpdateInfoDialog);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setMinimumSize(QSize(320, 110));
        textEdit->setMaximumSize(QSize(16777215, 110));
        textEdit->setReadOnly(true);

        verticalLayout->addWidget(textEdit);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(24);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, 0, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        nowButton = new QPushButton(TNCheckUpdateInfoDialog);
        nowButton->setObjectName(QStringLiteral("nowButton"));
        nowButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(nowButton);

        quitButton = new QPushButton(TNCheckUpdateInfoDialog);
        quitButton->setObjectName(QStringLiteral("quitButton"));
        quitButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(quitButton);

        afterButton = new QPushButton(TNCheckUpdateInfoDialog);
        afterButton->setObjectName(QStringLiteral("afterButton"));
        afterButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(afterButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(4, 1);

        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout_2->setStretch(1, 1);

        retranslateUi(TNCheckUpdateInfoDialog);

        QMetaObject::connectSlotsByName(TNCheckUpdateInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *TNCheckUpdateInfoDialog)
    {
        TNCheckUpdateInfoDialog->setWindowTitle(QApplication::translate("TNCheckUpdateInfoDialog", "Dialog", 0));
        updateInfoTitleLabel->setText(QApplication::translate("TNCheckUpdateInfoDialog", "\345\217\221\347\216\260\346\226\260\347\211\210\346\234\254", 0));
        textEdit->setHtml(QApplication::translate("TNCheckUpdateInfoDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\346\233\264\346\226\260\345\206\205\345\256\271\357\274\232</p></body></html>", 0));
        nowButton->setText(QApplication::translate("TNCheckUpdateInfoDialog", "\347\253\213\345\215\263\346\233\264\346\226\260", 0));
        quitButton->setText(QApplication::translate("TNCheckUpdateInfoDialog", "\345\205\263\351\227\255", 0));
        afterButton->setText(QApplication::translate("TNCheckUpdateInfoDialog", "\347\250\215\345\220\216\346\217\220\351\206\222\346\210\221", 0));
    } // retranslateUi

};

namespace Ui {
    class TNCheckUpdateInfoDialog: public Ui_TNCheckUpdateInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNCHECKUPDATEINFODIALOG_H
