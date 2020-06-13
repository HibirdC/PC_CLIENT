/********************************************************************************
** Form generated from reading UI file 'TNOfflineNoticeDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNOFFLINENOTICEDIALOG_H
#define UI_TNOFFLINENOTICEDIALOG_H

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

class Ui_TNOfflineNoticeDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *offlineIcon;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QLabel *offlineTitleLabel;
    QLabel *offlineContentLabel;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *OfflineFixButton;
    QLabel *spaceLabel;
    QPushButton *offlineButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *TNOfflineNoticeDialog)
    {
        if (TNOfflineNoticeDialog->objectName().isEmpty())
            TNOfflineNoticeDialog->setObjectName(QStringLiteral("TNOfflineNoticeDialog"));
        TNOfflineNoticeDialog->resize(418, 165);
        TNOfflineNoticeDialog->setMinimumSize(QSize(418, 165));
        TNOfflineNoticeDialog->setMaximumSize(QSize(418, 165));
        verticalLayout = new QVBoxLayout(TNOfflineNoticeDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, -1);
        offlineIcon = new QPushButton(TNOfflineNoticeDialog);
        offlineIcon->setObjectName(QStringLiteral("offlineIcon"));
        offlineIcon->setMinimumSize(QSize(66, 66));
        offlineIcon->setMaximumSize(QSize(66, 66));

        horizontalLayout->addWidget(offlineIcon);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(12, -1, -1, -1);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        offlineTitleLabel = new QLabel(TNOfflineNoticeDialog);
        offlineTitleLabel->setObjectName(QStringLiteral("offlineTitleLabel"));
        offlineTitleLabel->setMinimumSize(QSize(0, 24));
        offlineTitleLabel->setMaximumSize(QSize(16777215, 24));
        offlineTitleLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_2->addWidget(offlineTitleLabel);

        offlineContentLabel = new QLabel(TNOfflineNoticeDialog);
        offlineContentLabel->setObjectName(QStringLiteral("offlineContentLabel"));
        offlineContentLabel->setMinimumSize(QSize(0, 24));
        offlineContentLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_2->addWidget(offlineContentLabel);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        OfflineFixButton = new QPushButton(TNOfflineNoticeDialog);
        OfflineFixButton->setObjectName(QStringLiteral("OfflineFixButton"));

        horizontalLayout_2->addWidget(OfflineFixButton);

        spaceLabel = new QLabel(TNOfflineNoticeDialog);
        spaceLabel->setObjectName(QStringLiteral("spaceLabel"));

        horizontalLayout_2->addWidget(spaceLabel);

        offlineButton = new QPushButton(TNOfflineNoticeDialog);
        offlineButton->setObjectName(QStringLiteral("offlineButton"));
        offlineButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(offlineButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(TNOfflineNoticeDialog);

        QMetaObject::connectSlotsByName(TNOfflineNoticeDialog);
    } // setupUi

    void retranslateUi(QDialog *TNOfflineNoticeDialog)
    {
        TNOfflineNoticeDialog->setWindowTitle(QApplication::translate("TNOfflineNoticeDialog", "Dialog", 0));
        offlineIcon->setText(QString());
        offlineTitleLabel->setText(QApplication::translate("TNOfflineNoticeDialog", "\344\270\213\347\272\277\351\200\232\347\237\245", 0));
        offlineContentLabel->setText(QApplication::translate("TNOfflineNoticeDialog", "\346\202\250\347\232\204\345\270\220\345\217\267\345\274\202\345\270\270\357\274\214\345\267\262\350\242\253\350\277\253\344\270\213\347\272\277\343\200\202", 0));
        OfflineFixButton->setText(QApplication::translate("TNOfflineNoticeDialog", "\344\277\256\345\244\215", 0));
        spaceLabel->setText(QString());
        offlineButton->setText(QApplication::translate("TNOfflineNoticeDialog", "\345\205\263\351\227\255", 0));
    } // retranslateUi

};

namespace Ui {
    class TNOfflineNoticeDialog: public Ui_TNOfflineNoticeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNOFFLINENOTICEDIALOG_H
