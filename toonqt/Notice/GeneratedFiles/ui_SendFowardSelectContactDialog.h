/********************************************************************************
** Form generated from reading UI file 'SendFowardSelectContactDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENDFOWARDSELECTCONTACTDIALOG_H
#define UI_SENDFOWARDSELECTCONTACTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SendFowardSelectContactDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *DialogTitleWidget;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *DialogTitleLabel;
    QGridLayout *gridLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *haveSelectedLabel;
    QLabel *clickRemoveLabel;
    QSpacerItem *horizontalSpacer_3;
    QLabel *clickAddLabel;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QPushButton *dialogCloseButton;
    QTableView *leftTableView;
    QTableView *rightTableView;

    void setupUi(QDialog *SendFowardSelectContactDialog)
    {
        if (SendFowardSelectContactDialog->objectName().isEmpty())
            SendFowardSelectContactDialog->setObjectName(QStringLiteral("SendFowardSelectContactDialog"));
        SendFowardSelectContactDialog->resize(580, 482);
        SendFowardSelectContactDialog->setMinimumSize(QSize(580, 482));
        SendFowardSelectContactDialog->setMaximumSize(QSize(580, 482));
        SendFowardSelectContactDialog->setFocusPolicy(Qt::StrongFocus);
        verticalLayout = new QVBoxLayout(SendFowardSelectContactDialog);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 20);
        DialogTitleWidget = new QWidget(SendFowardSelectContactDialog);
        DialogTitleWidget->setObjectName(QStringLiteral("DialogTitleWidget"));
        horizontalLayout_3 = new QHBoxLayout(DialogTitleWidget);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(2, -1, -1, -1);
        DialogTitleLabel = new QLabel(DialogTitleWidget);
        DialogTitleLabel->setObjectName(QStringLiteral("DialogTitleLabel"));
        DialogTitleLabel->setAlignment(Qt::AlignCenter);
        DialogTitleLabel->setIndent(0);

        horizontalLayout_2->addWidget(DialogTitleLabel);

        horizontalLayout_2->setStretch(0, 1);

        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(DialogTitleWidget);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(18);
        gridLayout->setVerticalSpacing(6);
        gridLayout->setContentsMargins(30, -1, 30, -1);
        widget = new QWidget(SendFowardSelectContactDialog);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(250, 0));
        widget->setMaximumSize(QSize(250, 16777215));

        gridLayout->addWidget(widget, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        haveSelectedLabel = new QLabel(SendFowardSelectContactDialog);
        haveSelectedLabel->setObjectName(QStringLiteral("haveSelectedLabel"));

        horizontalLayout->addWidget(haveSelectedLabel);

        clickRemoveLabel = new QLabel(SendFowardSelectContactDialog);
        clickRemoveLabel->setObjectName(QStringLiteral("clickRemoveLabel"));

        horizontalLayout->addWidget(clickRemoveLabel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 1);

        clickAddLabel = new QLabel(SendFowardSelectContactDialog);
        clickAddLabel->setObjectName(QStringLiteral("clickAddLabel"));

        gridLayout->addWidget(clickAddLabel, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(20);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 20, 0, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        okButton = new QPushButton(SendFowardSelectContactDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_4->addWidget(okButton);

        dialogCloseButton = new QPushButton(SendFowardSelectContactDialog);
        dialogCloseButton->setObjectName(QStringLiteral("dialogCloseButton"));
        dialogCloseButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_4->addWidget(dialogCloseButton);


        gridLayout->addLayout(horizontalLayout_4, 2, 1, 1, 1);

        leftTableView = new QTableView(SendFowardSelectContactDialog);
        leftTableView->setObjectName(QStringLiteral("leftTableView"));

        gridLayout->addWidget(leftTableView, 1, 0, 1, 1);

        rightTableView = new QTableView(SendFowardSelectContactDialog);
        rightTableView->setObjectName(QStringLiteral("rightTableView"));

        gridLayout->addWidget(rightTableView, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(SendFowardSelectContactDialog);

        QMetaObject::connectSlotsByName(SendFowardSelectContactDialog);
    } // setupUi

    void retranslateUi(QDialog *SendFowardSelectContactDialog)
    {
        SendFowardSelectContactDialog->setWindowTitle(QApplication::translate("SendFowardSelectContactDialog", "\351\200\211\346\213\251\350\201\224\347\263\273\344\272\272", 0));
        DialogTitleLabel->setText(QApplication::translate("SendFowardSelectContactDialog", "\351\200\211\346\213\251\350\201\224\347\263\273\344\272\272", 0));
        haveSelectedLabel->setText(QApplication::translate("SendFowardSelectContactDialog", "\345\267\262\351\200\211\346\213\251\347\232\204\350\201\224\347\263\273\344\272\272", 0));
        clickRemoveLabel->setText(QApplication::translate("SendFowardSelectContactDialog", "\357\274\210\347\202\271\345\207\273\345\210\240\351\231\244\357\274\211", 0));
        clickAddLabel->setText(QApplication::translate("SendFowardSelectContactDialog", "\347\202\271\345\207\273\346\267\273\345\212\240\350\201\224\347\263\273\344\272\272", 0));
        okButton->setText(QApplication::translate("SendFowardSelectContactDialog", "\347\241\256\345\256\232", 0));
        dialogCloseButton->setText(QApplication::translate("SendFowardSelectContactDialog", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class SendFowardSelectContactDialog: public Ui_SendFowardSelectContactDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENDFOWARDSELECTCONTACTDIALOG_H
