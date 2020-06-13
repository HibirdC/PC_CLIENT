/********************************************************************************
** Form generated from reading UI file 'TNDefaultPage.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNDEFAULTPAGE_H
#define UI_TNDEFAULTPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TNDefaultPage
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_nullpage_pic;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_nullpage_text;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *TNDefaultPage)
    {
        if (TNDefaultPage->objectName().isEmpty())
            TNDefaultPage->setObjectName(QStringLiteral("TNDefaultPage"));
        TNDefaultPage->resize(250, 136);
        verticalLayout_3 = new QVBoxLayout(TNDefaultPage);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_nullpage_pic = new QLabel(TNDefaultPage);
        label_nullpage_pic->setObjectName(QStringLiteral("label_nullpage_pic"));
        label_nullpage_pic->setMinimumSize(QSize(51, 51));
        label_nullpage_pic->setMaximumSize(QSize(51, 51));

        horizontalLayout->addWidget(label_nullpage_pic);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_nullpage_text = new QLabel(TNDefaultPage);
        label_nullpage_text->setObjectName(QStringLiteral("label_nullpage_text"));
        label_nullpage_text->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_nullpage_text);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(TNDefaultPage);

        QMetaObject::connectSlotsByName(TNDefaultPage);
    } // setupUi

    void retranslateUi(QWidget *TNDefaultPage)
    {
        TNDefaultPage->setWindowTitle(QApplication::translate("TNDefaultPage", "TNDefaultPage", 0));
        label_nullpage_pic->setText(QString());
        label_nullpage_text->setText(QApplication::translate("TNDefaultPage", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class TNDefaultPage: public Ui_TNDefaultPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNDEFAULTPAGE_H
