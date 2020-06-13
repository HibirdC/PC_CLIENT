/********************************************************************************
** Form generated from reading UI file 'TNDownloadProgressDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNDOWNLOADPROGRESSDIALOG_H
#define UI_TNDOWNLOADPROGRESSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TNDownloadProgressDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QWidget *exitConfirmTitleWidget;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *confirmTitleLabel;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *closeButton;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *unknownSizeLabel;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout;
    QLabel *speedLabel;
    QSpacerItem *horizontalSpacer;
    QLabel *downloadedLabel;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *reDownLoadButton;
    QPushButton *fromBrownserButton;
    QSpacerItem *horizontalSpacer_7;

    void setupUi(QDialog *TNDownloadProgressDialog)
    {
        if (TNDownloadProgressDialog->objectName().isEmpty())
            TNDownloadProgressDialog->setObjectName(QStringLiteral("TNDownloadProgressDialog"));
        TNDownloadProgressDialog->resize(350, 194);
        TNDownloadProgressDialog->setMinimumSize(QSize(350, 160));
        TNDownloadProgressDialog->setMaximumSize(QSize(450, 260));
        verticalLayout_3 = new QVBoxLayout(TNDownloadProgressDialog);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(9, -1, 9, -1);
        exitConfirmTitleWidget = new QWidget(TNDownloadProgressDialog);
        exitConfirmTitleWidget->setObjectName(QStringLiteral("exitConfirmTitleWidget"));
        exitConfirmTitleWidget->setMinimumSize(QSize(100, 25));
        horizontalLayout_3 = new QHBoxLayout(exitConfirmTitleWidget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(1, 1, 1, 1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        confirmTitleLabel = new QLabel(exitConfirmTitleWidget);
        confirmTitleLabel->setObjectName(QStringLiteral("confirmTitleLabel"));
        confirmTitleLabel->setMinimumSize(QSize(0, 22));
        confirmTitleLabel->setIndent(0);

        horizontalLayout_2->addWidget(confirmTitleLabel);

        horizontalSpacer_2 = new QSpacerItem(14, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        closeButton = new QPushButton(exitConfirmTitleWidget);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        closeButton->setMinimumSize(QSize(12, 12));
        closeButton->setMaximumSize(QSize(12, 12));
        closeButton->setFlat(true);

        horizontalLayout_2->addWidget(closeButton);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_3->addWidget(exitConfirmTitleWidget);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(20, 18, 20, 18);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        unknownSizeLabel = new QLabel(TNDownloadProgressDialog);
        unknownSizeLabel->setObjectName(QStringLiteral("unknownSizeLabel"));
        unknownSizeLabel->setMinimumSize(QSize(40, 22));

        verticalLayout->addWidget(unknownSizeLabel);

        progressBar = new QProgressBar(TNDownloadProgressDialog);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setMinimumSize(QSize(0, 8));
        progressBar->setMaximumSize(QSize(16777215, 8));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);

        verticalLayout->addWidget(progressBar);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, -1, 4, -1);
        speedLabel = new QLabel(TNDownloadProgressDialog);
        speedLabel->setObjectName(QStringLiteral("speedLabel"));
        speedLabel->setMinimumSize(QSize(60, 20));

        horizontalLayout->addWidget(speedLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        downloadedLabel = new QLabel(TNDownloadProgressDialog);
        downloadedLabel->setObjectName(QStringLiteral("downloadedLabel"));
        downloadedLabel->setMinimumSize(QSize(20, 20));
        downloadedLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(downloadedLabel);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(20);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, -1, 20, 9);
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);

        reDownLoadButton = new QPushButton(TNDownloadProgressDialog);
        reDownLoadButton->setObjectName(QStringLiteral("reDownLoadButton"));

        horizontalLayout_5->addWidget(reDownLoadButton);

        fromBrownserButton = new QPushButton(TNDownloadProgressDialog);
        fromBrownserButton->setObjectName(QStringLiteral("fromBrownserButton"));

        horizontalLayout_5->addWidget(fromBrownserButton);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);


        verticalLayout_3->addLayout(horizontalLayout_5);

        verticalLayout_3->setStretch(1, 1);

        retranslateUi(TNDownloadProgressDialog);

        QMetaObject::connectSlotsByName(TNDownloadProgressDialog);
    } // setupUi

    void retranslateUi(QDialog *TNDownloadProgressDialog)
    {
        TNDownloadProgressDialog->setWindowTitle(QApplication::translate("TNDownloadProgressDialog", "Dialog", 0));
        confirmTitleLabel->setText(QApplication::translate("TNDownloadProgressDialog", "\345\215\207\347\272\247\347\250\213\345\272\217\346\255\243\345\234\250\350\277\220\350\241\214......", 0));
        closeButton->setText(QApplication::translate("TNDownloadProgressDialog", "+", 0));
        unknownSizeLabel->setText(QApplication::translate("TNDownloadProgressDialog", "100%", 0));
        speedLabel->setText(QApplication::translate("TNDownloadProgressDialog", "0KB/S", 0));
        downloadedLabel->setText(QApplication::translate("TNDownloadProgressDialog", "0 M", 0));
        reDownLoadButton->setText(QApplication::translate("TNDownloadProgressDialog", "\351\207\215\346\226\260\344\270\213\350\275\275", 0));
        fromBrownserButton->setText(QApplication::translate("TNDownloadProgressDialog", "\345\256\230\347\275\221\344\270\213\350\275\275", 0));
    } // retranslateUi

};

namespace Ui {
    class TNDownloadProgressDialog: public Ui_TNDownloadProgressDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNDOWNLOADPROGRESSDIALOG_H
