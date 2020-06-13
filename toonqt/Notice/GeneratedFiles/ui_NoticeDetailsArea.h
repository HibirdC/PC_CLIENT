/********************************************************************************
** Form generated from reading UI file 'NoticeDetailsArea.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTICEDETAILSAREA_H
#define UI_NOTICEDETAILSAREA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "TNDropDownPushButton.h"
#include "TNNoticeDetailTableWidget.h"
#include "mytableview.h"
#include "tncustomtextedit.h"

QT_BEGIN_NAMESPACE

class Ui_NoticeDetailsArea
{
public:
    QHBoxLayout *horizontalLayout_8;
    QStackedWidget *stackedWidget;
    QWidget *page_1;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_top_add;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_top_name;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_top_arrow;
    QSplitter *splitter;
    QWidget *widget_details;
    QHBoxLayout *horizontalLayout_7;
    MyTableView *tableView_details;
    QWidget *widget_emoji_file_pic;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_Expression;
    QPushButton *pushButton_file;
    TNDropDownPushButton *pushButton_screenShot;
    QSpacerItem *horizontalSpacer_7;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    TNCustomTextEdit *textEdit_Send;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButton_Send;
    QWidget *page_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_5;
    QWidget *widget_top_add_notice;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QLabel *noticeTitleLabel;
    QSpacerItem *horizontalSpacer_4;
    TNNoticeDetailTableWidget *tableWidget;
    QWidget *page_3;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_backpic;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_default_backpic;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *NoticeDetailsArea)
    {
        if (NoticeDetailsArea->objectName().isEmpty())
            NoticeDetailsArea->setObjectName(QStringLiteral("NoticeDetailsArea"));
        NoticeDetailsArea->resize(1102, 935);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NoticeDetailsArea->sizePolicy().hasHeightForWidth());
        NoticeDetailsArea->setSizePolicy(sizePolicy);
        horizontalLayout_8 = new QHBoxLayout(NoticeDetailsArea);
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(NoticeDetailsArea);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setMinimumSize(QSize(0, 300));
        stackedWidget->setBaseSize(QSize(0, 0));
        stackedWidget->setFocusPolicy(Qt::StrongFocus);
        stackedWidget->setLineWidth(0);
        page_1 = new QWidget();
        page_1->setObjectName(QStringLiteral("page_1"));
        layoutWidget = new QWidget(page_1);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(180, 50, 731, 861));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_top_add = new QWidget(layoutWidget);
        widget_top_add->setObjectName(QStringLiteral("widget_top_add"));
        widget_top_add->setMinimumSize(QSize(690, 0));
        widget_top_add->setMaximumSize(QSize(16777215, 16777215));
        widget_top_add->setFocusPolicy(Qt::ClickFocus);
        verticalLayout_3 = new QVBoxLayout(widget_top_add);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(16, 24, 10, 6);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pushButton_top_name = new QPushButton(widget_top_add);
        pushButton_top_name->setObjectName(QStringLiteral("pushButton_top_name"));
        pushButton_top_name->setLayoutDirection(Qt::LeftToRight);
        pushButton_top_name->setCheckable(true);

        horizontalLayout_4->addWidget(pushButton_top_name);

        horizontalSpacer = new QSpacerItem(40, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushButton_top_arrow = new QPushButton(widget_top_add);
        pushButton_top_arrow->setObjectName(QStringLiteral("pushButton_top_arrow"));
        pushButton_top_arrow->setCheckable(true);

        horizontalLayout_4->addWidget(pushButton_top_arrow);


        verticalLayout_3->addLayout(horizontalLayout_4);


        verticalLayout->addWidget(widget_top_add);

        splitter = new QSplitter(layoutWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        widget_details = new QWidget(splitter);
        widget_details->setObjectName(QStringLiteral("widget_details"));
        widget_details->setMinimumSize(QSize(0, 200));
        widget_details->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout_7 = new QHBoxLayout(widget_details);
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        tableView_details = new MyTableView(widget_details);
        tableView_details->setObjectName(QStringLiteral("tableView_details"));

        horizontalLayout_7->addWidget(tableView_details);

        splitter->addWidget(widget_details);
        widget_emoji_file_pic = new QWidget(splitter);
        widget_emoji_file_pic->setObjectName(QStringLiteral("widget_emoji_file_pic"));
        widget_emoji_file_pic->setMinimumSize(QSize(0, 120));
        widget_emoji_file_pic->setMaximumSize(QSize(16777215, 16777215));
        widget_emoji_file_pic->setBaseSize(QSize(0, 0));
        widget_emoji_file_pic->setFocusPolicy(Qt::ClickFocus);
        widget_emoji_file_pic->setStyleSheet(QStringLiteral(""));
        horizontalLayout_3 = new QHBoxLayout(widget_emoji_file_pic);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(20);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(15, 14, -1, -1);
        pushButton_Expression = new QPushButton(widget_emoji_file_pic);
        pushButton_Expression->setObjectName(QStringLiteral("pushButton_Expression"));
        pushButton_Expression->setMinimumSize(QSize(20, 20));
        pushButton_Expression->setMaximumSize(QSize(20, 20));
        pushButton_Expression->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(pushButton_Expression);

        pushButton_file = new QPushButton(widget_emoji_file_pic);
        pushButton_file->setObjectName(QStringLiteral("pushButton_file"));
        pushButton_file->setMinimumSize(QSize(20, 20));
        pushButton_file->setMaximumSize(QSize(20, 20));

        horizontalLayout->addWidget(pushButton_file);

        pushButton_screenShot = new TNDropDownPushButton(widget_emoji_file_pic);
        pushButton_screenShot->setObjectName(QStringLiteral("pushButton_screenShot"));
        pushButton_screenShot->setMinimumSize(QSize(37, 20));
        pushButton_screenShot->setMaximumSize(QSize(37, 20));

        horizontalLayout->addWidget(pushButton_screenShot);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);


        verticalLayout_4->addLayout(horizontalLayout);

        widget = new QWidget(widget_emoji_file_pic);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(12, 6, 12, 6);
        textEdit_Send = new TNCustomTextEdit(widget);
        textEdit_Send->setObjectName(QStringLiteral("textEdit_Send"));
        textEdit_Send->setMinimumSize(QSize(0, 0));
        textEdit_Send->setMaximumSize(QSize(16777215, 16777215));
        textEdit_Send->setStyleSheet(QStringLiteral(""));
        textEdit_Send->setFrameShadow(QFrame::Plain);
        textEdit_Send->setLineWidth(0);

        horizontalLayout_2->addWidget(textEdit_Send);


        verticalLayout_4->addWidget(widget);


        horizontalLayout_3->addLayout(verticalLayout_4);

        splitter->addWidget(widget_emoji_file_pic);

        verticalLayout->addWidget(splitter);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(10);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, -1, 18, 10);
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_8);

        pushButton_Send = new QPushButton(layoutWidget);
        pushButton_Send->setObjectName(QStringLiteral("pushButton_Send"));
        pushButton_Send->setMinimumSize(QSize(80, 25));
        pushButton_Send->setMaximumSize(QSize(16777215, 16777215));
        pushButton_Send->setStyleSheet(QStringLiteral(""));

        horizontalLayout_10->addWidget(pushButton_Send);


        verticalLayout->addLayout(horizontalLayout_10);

        stackedWidget->addWidget(page_1);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        layoutWidget1 = new QWidget(page_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(86, 140, 690, 530));
        verticalLayout_5 = new QVBoxLayout(layoutWidget1);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        widget_top_add_notice = new QWidget(layoutWidget1);
        widget_top_add_notice->setObjectName(QStringLiteral("widget_top_add_notice"));
        horizontalLayout_6 = new QHBoxLayout(widget_top_add_notice);
        horizontalLayout_6->setSpacing(10);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 8, -1, 6);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        noticeTitleLabel = new QLabel(widget_top_add_notice);
        noticeTitleLabel->setObjectName(QStringLiteral("noticeTitleLabel"));
        noticeTitleLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout_5->addWidget(noticeTitleLabel);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        horizontalLayout_6->addLayout(horizontalLayout_5);


        verticalLayout_5->addWidget(widget_top_add_notice);

        tableWidget = new TNNoticeDetailTableWidget(layoutWidget1);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setMinimumSize(QSize(668, 488));
        tableWidget->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_5->addWidget(tableWidget);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        layoutWidget2 = new QWidget(page_3);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(231, 201, 451, 351));
        gridLayout_backpic = new QGridLayout(layoutWidget2);
        gridLayout_backpic->setSpacing(6);
        gridLayout_backpic->setContentsMargins(11, 11, 11, 11);
        gridLayout_backpic->setObjectName(QStringLiteral("gridLayout_backpic"));
        gridLayout_backpic->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_backpic->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_backpic->addItem(horizontalSpacer_5, 1, 0, 1, 1);

        label_default_backpic = new QLabel(layoutWidget2);
        label_default_backpic->setObjectName(QStringLiteral("label_default_backpic"));
        label_default_backpic->setMinimumSize(QSize(200, 125));
        label_default_backpic->setMaximumSize(QSize(200, 125));

        gridLayout_backpic->addWidget(label_default_backpic, 1, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_backpic->addItem(horizontalSpacer_6, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_backpic->addItem(verticalSpacer_2, 2, 1, 1, 1);

        stackedWidget->addWidget(page_3);

        horizontalLayout_8->addWidget(stackedWidget);


        retranslateUi(NoticeDetailsArea);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(NoticeDetailsArea);
    } // setupUi

    void retranslateUi(QWidget *NoticeDetailsArea)
    {
        NoticeDetailsArea->setWindowTitle(QApplication::translate("NoticeDetailsArea", "NoticeDetailsArea", 0));
        pushButton_top_name->setText(QString());
        pushButton_top_arrow->setText(QString());
        pushButton_Expression->setText(QString());
        pushButton_file->setText(QString());
        pushButton_screenShot->setText(QString());
        pushButton_Send->setText(QApplication::translate("NoticeDetailsArea", "\345\217\221\351\200\201", 0));
        noticeTitleLabel->setText(QApplication::translate("NoticeDetailsArea", "\346\226\260\347\232\204\346\234\213\345\217\213", 0));
        label_default_backpic->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class NoticeDetailsArea: public Ui_NoticeDetailsArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTICEDETAILSAREA_H
