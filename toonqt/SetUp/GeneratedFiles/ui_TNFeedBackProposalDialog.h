/********************************************************************************
** Form generated from reading UI file 'TNFeedBackProposalDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNFEEDBACKPROPOSALDIALOG_H
#define UI_TNFEEDBACKPROPOSALDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TNFeedBackProposalDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *feedBackProposalTitleWidget;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *feedBackTitleLabel;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *feedBackTextEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *dialogCloseButton;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *TNFeedBackProposalDialog)
    {
        if (TNFeedBackProposalDialog->objectName().isEmpty())
            TNFeedBackProposalDialog->setObjectName(QStringLiteral("TNFeedBackProposalDialog"));
        TNFeedBackProposalDialog->resize(450, 235);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TNFeedBackProposalDialog->sizePolicy().hasHeightForWidth());
        TNFeedBackProposalDialog->setSizePolicy(sizePolicy);
        TNFeedBackProposalDialog->setMinimumSize(QSize(450, 235));
        TNFeedBackProposalDialog->setMaximumSize(QSize(450, 235));
        verticalLayout_2 = new QVBoxLayout(TNFeedBackProposalDialog);
        verticalLayout_2->setSpacing(10);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 30);
        feedBackProposalTitleWidget = new QWidget(TNFeedBackProposalDialog);
        feedBackProposalTitleWidget->setObjectName(QStringLiteral("feedBackProposalTitleWidget"));
        horizontalLayout_3 = new QHBoxLayout(feedBackProposalTitleWidget);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, -1, -1, -1);
        feedBackTitleLabel = new QLabel(feedBackProposalTitleWidget);
        feedBackTitleLabel->setObjectName(QStringLiteral("feedBackTitleLabel"));
        sizePolicy.setHeightForWidth(feedBackTitleLabel->sizePolicy().hasHeightForWidth());
        feedBackTitleLabel->setSizePolicy(sizePolicy);
        feedBackTitleLabel->setAlignment(Qt::AlignCenter);
        feedBackTitleLabel->setIndent(0);

        horizontalLayout_2->addWidget(feedBackTitleLabel);

        horizontalLayout_2->setStretch(0, 1);

        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_2->addWidget(feedBackProposalTitleWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(30, -1, 30, -1);
        feedBackTextEdit = new QPlainTextEdit(TNFeedBackProposalDialog);
        feedBackTextEdit->setObjectName(QStringLiteral("feedBackTextEdit"));
        feedBackTextEdit->setEnabled(true);
        feedBackTextEdit->setContextMenuPolicy(Qt::NoContextMenu);

        verticalLayout->addWidget(feedBackTextEdit);

        verticalLayout->setStretch(0, 1);

        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 20, 0, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okButton = new QPushButton(TNFeedBackProposalDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(okButton);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        dialogCloseButton = new QPushButton(TNFeedBackProposalDialog);
        dialogCloseButton->setObjectName(QStringLiteral("dialogCloseButton"));
        dialogCloseButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(dialogCloseButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(4, 1);

        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(TNFeedBackProposalDialog);

        QMetaObject::connectSlotsByName(TNFeedBackProposalDialog);
    } // setupUi

    void retranslateUi(QDialog *TNFeedBackProposalDialog)
    {
        TNFeedBackProposalDialog->setWindowTitle(QApplication::translate("TNFeedBackProposalDialog", "Dialog", 0));
        feedBackTitleLabel->setText(QApplication::translate("TNFeedBackProposalDialog", "\351\227\256\351\242\230\345\222\214\345\273\272\350\256\256", 0));
        feedBackTextEdit->setPlaceholderText(QApplication::translate("TNFeedBackProposalDialog", "\350\257\267\347\256\200\350\246\201\346\217\217\350\277\260\346\202\250\347\232\204\351\227\256\351\242\230\345\222\214\345\273\272\350\256\256", 0));
        okButton->setText(QApplication::translate("TNFeedBackProposalDialog", " \347\241\256\345\256\232", 0));
        dialogCloseButton->setText(QApplication::translate("TNFeedBackProposalDialog", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class TNFeedBackProposalDialog: public Ui_TNFeedBackProposalDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNFEEDBACKPROPOSALDIALOG_H
