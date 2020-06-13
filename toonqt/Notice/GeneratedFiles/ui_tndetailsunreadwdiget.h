/********************************************************************************
** Form generated from reading UI file 'tndetailsunreadwdiget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNDETAILSUNREADWDIGET_H
#define UI_TNDETAILSUNREADWDIGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TNDetailsUnreadWdiget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *details_unread_button_up;
    QPushButton *details_unread_button_down;
    QPushButton *details_unread_button_close;

    void setupUi(QWidget *TNDetailsUnreadWdiget)
    {
        if (TNDetailsUnreadWdiget->objectName().isEmpty())
            TNDetailsUnreadWdiget->setObjectName(QStringLiteral("TNDetailsUnreadWdiget"));
        TNDetailsUnreadWdiget->resize(206, 25);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TNDetailsUnreadWdiget->sizePolicy().hasHeightForWidth());
        TNDetailsUnreadWdiget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(TNDetailsUnreadWdiget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(10, 0, 8, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, -1, 0, -1);
        details_unread_button_up = new QPushButton(TNDetailsUnreadWdiget);
        details_unread_button_up->setObjectName(QStringLiteral("details_unread_button_up"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(details_unread_button_up->sizePolicy().hasHeightForWidth());
        details_unread_button_up->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(details_unread_button_up);

        details_unread_button_down = new QPushButton(TNDetailsUnreadWdiget);
        details_unread_button_down->setObjectName(QStringLiteral("details_unread_button_down"));
        sizePolicy1.setHeightForWidth(details_unread_button_down->sizePolicy().hasHeightForWidth());
        details_unread_button_down->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(details_unread_button_down);

        details_unread_button_close = new QPushButton(TNDetailsUnreadWdiget);
        details_unread_button_close->setObjectName(QStringLiteral("details_unread_button_close"));
        details_unread_button_close->setMinimumSize(QSize(10, 10));
        details_unread_button_close->setMaximumSize(QSize(10, 10));
        details_unread_button_close->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(details_unread_button_close);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(TNDetailsUnreadWdiget);

        QMetaObject::connectSlotsByName(TNDetailsUnreadWdiget);
    } // setupUi

    void retranslateUi(QWidget *TNDetailsUnreadWdiget)
    {
        TNDetailsUnreadWdiget->setWindowTitle(QApplication::translate("TNDetailsUnreadWdiget", "Form", 0));
        details_unread_button_up->setText(QApplication::translate("TNDetailsUnreadWdiget", "up", 0));
        details_unread_button_down->setText(QApplication::translate("TNDetailsUnreadWdiget", "down", 0));
        details_unread_button_close->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TNDetailsUnreadWdiget: public Ui_TNDetailsUnreadWdiget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNDETAILSUNREADWDIGET_H
