/********************************************************************************
** Form generated from reading UI file 'tnwarndlag.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNWARNDLAG_H
#define UI_TNWARNDLAG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TNWarnDlag
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_warn_head;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_notify_static;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_notify_close;
    QWidget *widget_warn_bottom;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_notify;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *TNWarnDlag)
    {
        if (TNWarnDlag->objectName().isEmpty())
            TNWarnDlag->setObjectName(QStringLiteral("TNWarnDlag"));
        TNWarnDlag->resize(400, 160);
        TNWarnDlag->setMaximumSize(QSize(400, 160));
        verticalLayout_2 = new QVBoxLayout(TNWarnDlag);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget_warn_head = new QWidget(TNWarnDlag);
        widget_warn_head->setObjectName(QStringLiteral("widget_warn_head"));
        widget_warn_head->setMinimumSize(QSize(0, 34));
        widget_warn_head->setMaximumSize(QSize(16777215, 34));
        horizontalLayout_3 = new QHBoxLayout(widget_warn_head);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(20, 0, 20, 0);
        label_notify_static = new QLabel(widget_warn_head);
        label_notify_static->setObjectName(QStringLiteral("label_notify_static"));

        horizontalLayout_3->addWidget(label_notify_static);

        horizontalSpacer_3 = new QSpacerItem(293, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        pushButton_notify_close = new QPushButton(widget_warn_head);
        pushButton_notify_close->setObjectName(QStringLiteral("pushButton_notify_close"));
        pushButton_notify_close->setMaximumSize(QSize(34, 34));

        horizontalLayout_3->addWidget(pushButton_notify_close);


        verticalLayout_2->addWidget(widget_warn_head);

        widget_warn_bottom = new QWidget(TNWarnDlag);
        widget_warn_bottom->setObjectName(QStringLiteral("widget_warn_bottom"));
        verticalLayout = new QVBoxLayout(widget_warn_bottom);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 54, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_notify = new QLabel(widget_warn_bottom);
        label_notify->setObjectName(QStringLiteral("label_notify"));

        horizontalLayout->addWidget(label_notify);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 54, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        verticalLayout_2->addWidget(widget_warn_bottom);


        retranslateUi(TNWarnDlag);

        QMetaObject::connectSlotsByName(TNWarnDlag);
    } // setupUi

    void retranslateUi(QWidget *TNWarnDlag)
    {
        TNWarnDlag->setWindowTitle(QApplication::translate("TNWarnDlag", "TNWarnDlag", 0));
        label_notify_static->setText(QApplication::translate("TNWarnDlag", "\346\217\220\347\244\272", 0));
        pushButton_notify_close->setText(QString());
        label_notify->setText(QApplication::translate("TNWarnDlag", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class TNWarnDlag: public Ui_TNWarnDlag {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNWARNDLAG_H
