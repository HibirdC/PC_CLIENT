/********************************************************************************
** Form generated from reading UI file 'tnfilebrowser.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNFILEBROWSER_H
#define UI_TNFILEBROWSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "TNElidedLabel.h"

QT_BEGIN_NAMESPACE

class Ui_TNFileBrowser
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_file_content;
    QHBoxLayout *horizontalLayout_4;
    QWidget *widget_file_pic;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_file_pic;
    QVBoxLayout *verticalLayout_2;
    TNElidedLabel *label_file_name;
    QLabel *label_file_size;
    QHBoxLayout *horizontalLayout_3;
    QProgressBar *progressBar_file;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *button_cancel_upload;
    QWidget *widget_file_operation;
    QHBoxLayout *horizontalLayout;
    QLabel *label_file_isdownload;
    QSpacerItem *horizontalSpacer;
    QPushButton *button_file_open;
    QPushButton *button_file_opendir;
    QPushButton *button_file_sendForward;

    void setupUi(QWidget *TNFileBrowser)
    {
        if (TNFileBrowser->objectName().isEmpty())
            TNFileBrowser->setObjectName(QStringLiteral("TNFileBrowser"));
        TNFileBrowser->resize(250, 100);
        TNFileBrowser->setMinimumSize(QSize(250, 100));
        TNFileBrowser->setMaximumSize(QSize(250, 100));
        verticalLayout = new QVBoxLayout(TNFileBrowser);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_file_content = new QWidget(TNFileBrowser);
        widget_file_content->setObjectName(QStringLiteral("widget_file_content"));
        widget_file_content->setMinimumSize(QSize(250, 70));
        widget_file_content->setMaximumSize(QSize(250, 70));
        horizontalLayout_4 = new QHBoxLayout(widget_file_content);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(10, 0, 11, 0);
        widget_file_pic = new QWidget(widget_file_content);
        widget_file_pic->setObjectName(QStringLiteral("widget_file_pic"));
        widget_file_pic->setMinimumSize(QSize(50, 50));
        widget_file_pic->setMaximumSize(QSize(50, 50));
        horizontalLayout_2 = new QHBoxLayout(widget_file_pic);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_file_pic = new QLabel(widget_file_pic);
        label_file_pic->setObjectName(QStringLiteral("label_file_pic"));
        label_file_pic->setMinimumSize(QSize(50, 50));
        label_file_pic->setMaximumSize(QSize(50, 50));

        horizontalLayout_2->addWidget(label_file_pic);


        horizontalLayout_4->addWidget(widget_file_pic);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 7, -1, 8);
        label_file_name = new TNElidedLabel(widget_file_content);
        label_file_name->setObjectName(QStringLiteral("label_file_name"));
        label_file_name->setMinimumSize(QSize(0, 18));
        label_file_name->setMaximumSize(QSize(16777215, 18));

        verticalLayout_2->addWidget(label_file_name);

        label_file_size = new QLabel(widget_file_content);
        label_file_size->setObjectName(QStringLiteral("label_file_size"));
        label_file_size->setMinimumSize(QSize(0, 16));

        verticalLayout_2->addWidget(label_file_size);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, -1, -1, 4);
        progressBar_file = new QProgressBar(widget_file_content);
        progressBar_file->setObjectName(QStringLiteral("progressBar_file"));
        progressBar_file->setMinimumSize(QSize(0, 4));
        progressBar_file->setMaximumSize(QSize(148, 4));
        progressBar_file->setValue(24);

        horizontalLayout_3->addWidget(progressBar_file);

        horizontalSpacer_2 = new QSpacerItem(20, 4, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        button_cancel_upload = new QPushButton(widget_file_content);
        button_cancel_upload->setObjectName(QStringLiteral("button_cancel_upload"));
        button_cancel_upload->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(button_cancel_upload->sizePolicy().hasHeightForWidth());
        button_cancel_upload->setSizePolicy(sizePolicy);
        button_cancel_upload->setMinimumSize(QSize(14, 14));
        button_cancel_upload->setMaximumSize(QSize(14, 14));

        horizontalLayout_3->addWidget(button_cancel_upload);


        verticalLayout_2->addLayout(horizontalLayout_3);


        horizontalLayout_4->addLayout(verticalLayout_2);


        verticalLayout->addWidget(widget_file_content);

        widget_file_operation = new QWidget(TNFileBrowser);
        widget_file_operation->setObjectName(QStringLiteral("widget_file_operation"));
        widget_file_operation->setMinimumSize(QSize(250, 30));
        widget_file_operation->setMaximumSize(QSize(270, 30));
        horizontalLayout = new QHBoxLayout(widget_file_operation);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, 0, 11, 0);
        label_file_isdownload = new QLabel(widget_file_operation);
        label_file_isdownload->setObjectName(QStringLiteral("label_file_isdownload"));
        label_file_isdownload->setMinimumSize(QSize(0, 12));
        label_file_isdownload->setMaximumSize(QSize(16777215, 24));

        horizontalLayout->addWidget(label_file_isdownload);

        horizontalSpacer = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        button_file_open = new QPushButton(widget_file_operation);
        button_file_open->setObjectName(QStringLiteral("button_file_open"));
        button_file_open->setMaximumSize(QSize(16777215, 24));
        button_file_open->setStyleSheet(QStringLiteral(""));
        button_file_open->setIconSize(QSize(0, 0));

        horizontalLayout->addWidget(button_file_open);

        button_file_opendir = new QPushButton(widget_file_operation);
        button_file_opendir->setObjectName(QStringLiteral("button_file_opendir"));
        button_file_opendir->setMinimumSize(QSize(0, 12));
        button_file_opendir->setMaximumSize(QSize(16777215, 24));
        button_file_opendir->setIconSize(QSize(0, 0));

        horizontalLayout->addWidget(button_file_opendir);

        button_file_sendForward = new QPushButton(widget_file_operation);
        button_file_sendForward->setObjectName(QStringLiteral("button_file_sendForward"));
        button_file_sendForward->setMinimumSize(QSize(0, 12));
        button_file_sendForward->setMaximumSize(QSize(16777215, 24));

        horizontalLayout->addWidget(button_file_sendForward);


        verticalLayout->addWidget(widget_file_operation);


        retranslateUi(TNFileBrowser);

        QMetaObject::connectSlotsByName(TNFileBrowser);
    } // setupUi

    void retranslateUi(QWidget *TNFileBrowser)
    {
        TNFileBrowser->setWindowTitle(QApplication::translate("TNFileBrowser", "TNFileBrowser", 0));
        label_file_pic->setText(QString());
        label_file_name->setText(QApplication::translate("TNFileBrowser", "TextLabel", 0));
        label_file_size->setText(QApplication::translate("TNFileBrowser", "TextLabel", 0));
        button_cancel_upload->setText(QString());
        label_file_isdownload->setText(QApplication::translate("TNFileBrowser", "TextLabel", 0));
        button_file_open->setText(QApplication::translate("TNFileBrowser", "\346\211\223\345\274\200", 0));
        button_file_opendir->setText(QApplication::translate("TNFileBrowser", "\346\211\223\345\274\200\346\226\207\344\273\266\345\244\271", 0));
        button_file_sendForward->setText(QApplication::translate("TNFileBrowser", "\350\275\254\345\217\221", 0));
    } // retranslateUi

};

namespace Ui {
    class TNFileBrowser: public Ui_TNFileBrowser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNFILEBROWSER_H
