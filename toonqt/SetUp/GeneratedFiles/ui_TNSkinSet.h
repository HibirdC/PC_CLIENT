/********************************************************************************
** Form generated from reading UI file 'TNSkinSet.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNSKINSET_H
#define UI_TNSKINSET_H

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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TNSkinSet
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *skinBlueBtn;
    QLabel *skinLabel_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *skinPinkBtn;
    QLabel *skinLabel_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *skinPurpleBtn;
    QLabel *skinLabel_4;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *skinBudBtn;
    QLabel *skinLabel_5;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *skinTeaBtn;
    QLabel *skinLabel_6;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *skinGreenBtn;
    QLabel *skinLabel_7;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *skinOrchidBtn;
    QLabel *skinLabel_8;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *skinOrangeBtn;
    QLabel *skinLabel_9;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *TNSkinSet)
    {
        if (TNSkinSet->objectName().isEmpty())
            TNSkinSet->setObjectName(QStringLiteral("TNSkinSet"));
        TNSkinSet->resize(757, 443);
        verticalLayout_2 = new QVBoxLayout(TNSkinSet);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 30, -1, -1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(88);
        gridLayout->setVerticalSpacing(30);
        gridLayout->setContentsMargins(60, 20, 60, 50);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        skinBlueBtn = new QPushButton(TNSkinSet);
        skinBlueBtn->setObjectName(QStringLiteral("skinBlueBtn"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(skinBlueBtn->sizePolicy().hasHeightForWidth());
        skinBlueBtn->setSizePolicy(sizePolicy);
        skinBlueBtn->setMinimumSize(QSize(50, 50));
        skinBlueBtn->setCheckable(true);
        skinBlueBtn->setChecked(false);

        horizontalLayout_2->addWidget(skinBlueBtn);

        skinLabel_2 = new QLabel(TNSkinSet);
        skinLabel_2->setObjectName(QStringLiteral("skinLabel_2"));

        horizontalLayout_2->addWidget(skinLabel_2);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        skinPinkBtn = new QPushButton(TNSkinSet);
        skinPinkBtn->setObjectName(QStringLiteral("skinPinkBtn"));
        sizePolicy.setHeightForWidth(skinPinkBtn->sizePolicy().hasHeightForWidth());
        skinPinkBtn->setSizePolicy(sizePolicy);
        skinPinkBtn->setMinimumSize(QSize(50, 50));
        skinPinkBtn->setCheckable(true);
        skinPinkBtn->setChecked(false);

        horizontalLayout_3->addWidget(skinPinkBtn);

        skinLabel_3 = new QLabel(TNSkinSet);
        skinLabel_3->setObjectName(QStringLiteral("skinLabel_3"));

        horizontalLayout_3->addWidget(skinLabel_3);


        gridLayout->addLayout(horizontalLayout_3, 0, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(10);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        skinPurpleBtn = new QPushButton(TNSkinSet);
        skinPurpleBtn->setObjectName(QStringLiteral("skinPurpleBtn"));
        sizePolicy.setHeightForWidth(skinPurpleBtn->sizePolicy().hasHeightForWidth());
        skinPurpleBtn->setSizePolicy(sizePolicy);
        skinPurpleBtn->setMinimumSize(QSize(50, 50));
        skinPurpleBtn->setCheckable(true);
        skinPurpleBtn->setChecked(false);

        horizontalLayout_4->addWidget(skinPurpleBtn);

        skinLabel_4 = new QLabel(TNSkinSet);
        skinLabel_4->setObjectName(QStringLiteral("skinLabel_4"));

        horizontalLayout_4->addWidget(skinLabel_4);


        gridLayout->addLayout(horizontalLayout_4, 0, 2, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(10);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        skinBudBtn = new QPushButton(TNSkinSet);
        skinBudBtn->setObjectName(QStringLiteral("skinBudBtn"));
        sizePolicy.setHeightForWidth(skinBudBtn->sizePolicy().hasHeightForWidth());
        skinBudBtn->setSizePolicy(sizePolicy);
        skinBudBtn->setMinimumSize(QSize(50, 50));
        skinBudBtn->setCheckable(true);
        skinBudBtn->setChecked(false);

        horizontalLayout_5->addWidget(skinBudBtn);

        skinLabel_5 = new QLabel(TNSkinSet);
        skinLabel_5->setObjectName(QStringLiteral("skinLabel_5"));

        horizontalLayout_5->addWidget(skinLabel_5);


        gridLayout->addLayout(horizontalLayout_5, 1, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(10);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        skinTeaBtn = new QPushButton(TNSkinSet);
        skinTeaBtn->setObjectName(QStringLiteral("skinTeaBtn"));
        sizePolicy.setHeightForWidth(skinTeaBtn->sizePolicy().hasHeightForWidth());
        skinTeaBtn->setSizePolicy(sizePolicy);
        skinTeaBtn->setMinimumSize(QSize(50, 50));
        skinTeaBtn->setCheckable(true);
        skinTeaBtn->setChecked(false);

        horizontalLayout_6->addWidget(skinTeaBtn);

        skinLabel_6 = new QLabel(TNSkinSet);
        skinLabel_6->setObjectName(QStringLiteral("skinLabel_6"));

        horizontalLayout_6->addWidget(skinLabel_6);


        gridLayout->addLayout(horizontalLayout_6, 1, 1, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(10);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        skinGreenBtn = new QPushButton(TNSkinSet);
        skinGreenBtn->setObjectName(QStringLiteral("skinGreenBtn"));
        sizePolicy.setHeightForWidth(skinGreenBtn->sizePolicy().hasHeightForWidth());
        skinGreenBtn->setSizePolicy(sizePolicy);
        skinGreenBtn->setMinimumSize(QSize(50, 50));
        skinGreenBtn->setCheckable(true);
        skinGreenBtn->setChecked(false);

        horizontalLayout_7->addWidget(skinGreenBtn);

        skinLabel_7 = new QLabel(TNSkinSet);
        skinLabel_7->setObjectName(QStringLiteral("skinLabel_7"));

        horizontalLayout_7->addWidget(skinLabel_7);


        gridLayout->addLayout(horizontalLayout_7, 1, 2, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(10);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        skinOrchidBtn = new QPushButton(TNSkinSet);
        skinOrchidBtn->setObjectName(QStringLiteral("skinOrchidBtn"));
        sizePolicy.setHeightForWidth(skinOrchidBtn->sizePolicy().hasHeightForWidth());
        skinOrchidBtn->setSizePolicy(sizePolicy);
        skinOrchidBtn->setMinimumSize(QSize(50, 50));
        skinOrchidBtn->setCheckable(true);
        skinOrchidBtn->setChecked(false);

        horizontalLayout_8->addWidget(skinOrchidBtn);

        skinLabel_8 = new QLabel(TNSkinSet);
        skinLabel_8->setObjectName(QStringLiteral("skinLabel_8"));

        horizontalLayout_8->addWidget(skinLabel_8);


        gridLayout->addLayout(horizontalLayout_8, 2, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(10);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        skinOrangeBtn = new QPushButton(TNSkinSet);
        skinOrangeBtn->setObjectName(QStringLiteral("skinOrangeBtn"));
        sizePolicy.setHeightForWidth(skinOrangeBtn->sizePolicy().hasHeightForWidth());
        skinOrangeBtn->setSizePolicy(sizePolicy);
        skinOrangeBtn->setMinimumSize(QSize(50, 50));
        skinOrangeBtn->setCheckable(true);
        skinOrangeBtn->setChecked(false);

        horizontalLayout_9->addWidget(skinOrangeBtn);

        skinLabel_9 = new QLabel(TNSkinSet);
        skinLabel_9->setObjectName(QStringLiteral("skinLabel_9"));

        horizontalLayout_9->addWidget(skinLabel_9);


        gridLayout->addLayout(horizontalLayout_9, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(TNSkinSet);

        QMetaObject::connectSlotsByName(TNSkinSet);
    } // setupUi

    void retranslateUi(QWidget *TNSkinSet)
    {
        TNSkinSet->setWindowTitle(QApplication::translate("TNSkinSet", "Form", 0));
        skinBlueBtn->setText(QString());
        skinLabel_2->setText(QApplication::translate("TNSkinSet", "\345\214\227\346\254\247\350\223\235", 0));
        skinPinkBtn->setText(QString());
        skinLabel_3->setText(QApplication::translate("TNSkinSet", "\345\277\203\350\267\263\345\233\236\345\277\206", 0));
        skinPurpleBtn->setText(QString());
        skinLabel_4->setText(QApplication::translate("TNSkinSet", "\346\242\246\345\271\273\344\275\263\344\272\272", 0));
        skinBudBtn->setText(QString());
        skinLabel_5->setText(QApplication::translate("TNSkinSet", "\346\263\225\345\233\275\350\225\276\344\270\235", 0));
        skinTeaBtn->setText(QString());
        skinLabel_6->setText(QApplication::translate("TNSkinSet", "\347\231\276\351\246\231\350\214\227", 0));
        skinGreenBtn->setText(QString());
        skinLabel_7->setText(QApplication::translate("TNSkinSet", "\350\212\263\350\215\211\347\273\277", 0));
        skinOrchidBtn->setText(QString());
        skinLabel_8->setText(QApplication::translate("TNSkinSet", "\351\276\231\350\210\214\345\205\260", 0));
        skinOrangeBtn->setText(QString());
        skinLabel_9->setText(QApplication::translate("TNSkinSet", "\351\246\231\346\251\231", 0));
    } // retranslateUi

};

namespace Ui {
    class TNSkinSet: public Ui_TNSkinSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNSKINSET_H
