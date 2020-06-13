/********************************************************************************
** Form generated from reading UI file 'tnloadinghository.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNLOADINGHOSITORY_H
#define UI_TNLOADINGHOSITORY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tnLoadingHository
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_loading_gif;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *tnLoadingHository)
    {
        if (tnLoadingHository->objectName().isEmpty())
            tnLoadingHository->setObjectName(QStringLiteral("tnLoadingHository"));
        tnLoadingHository->resize(690, 20);
        tnLoadingHository->setMinimumSize(QSize(690, 20));
        tnLoadingHository->setMaximumSize(QSize(690, 20));
        horizontalLayout = new QHBoxLayout(tnLoadingHository);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(258, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_loading_gif = new QLabel(tnLoadingHository);
        label_loading_gif->setObjectName(QStringLiteral("label_loading_gif"));
        label_loading_gif->setMinimumSize(QSize(20, 20));
        label_loading_gif->setMaximumSize(QSize(40, 20));

        horizontalLayout->addWidget(label_loading_gif);

        horizontalSpacer_2 = new QSpacerItem(258, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        retranslateUi(tnLoadingHository);

        QMetaObject::connectSlotsByName(tnLoadingHository);
    } // setupUi

    void retranslateUi(QWidget *tnLoadingHository)
    {
        tnLoadingHository->setWindowTitle(QApplication::translate("tnLoadingHository", "tnLoadingHository", 0));
        label_loading_gif->setText(QApplication::translate("tnLoadingHository", "gif", 0));
    } // retranslateUi

};

namespace Ui {
    class tnLoadingHository: public Ui_tnLoadingHository {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNLOADINGHOSITORY_H
