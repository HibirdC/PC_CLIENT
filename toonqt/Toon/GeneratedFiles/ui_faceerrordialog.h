/********************************************************************************
** Form generated from reading UI file 'faceerrordialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACEERRORDIALOG_H
#define UI_FACEERRORDIALOG_H

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

class Ui_FaceErrorDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *DialogTitleLabel;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *label_camera_status;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_redetect_device;
    QPushButton *btn_close;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *FaceErrorDialog)
    {
        if (FaceErrorDialog->objectName().isEmpty())
            FaceErrorDialog->setObjectName(QStringLiteral("FaceErrorDialog"));
        FaceErrorDialog->resize(350, 160);
        FaceErrorDialog->setMinimumSize(QSize(350, 160));
        FaceErrorDialog->setMaximumSize(QSize(350, 214));
        verticalLayout_3 = new QVBoxLayout(FaceErrorDialog);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 14, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        DialogTitleLabel = new QLabel(FaceErrorDialog);
        DialogTitleLabel->setObjectName(QStringLiteral("DialogTitleLabel"));
        DialogTitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(DialogTitleLabel);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_camera_status = new QLabel(FaceErrorDialog);
        label_camera_status->setObjectName(QStringLiteral("label_camera_status"));
        label_camera_status->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_camera_status);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(20);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, -1, 0, 30);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_redetect_device = new QPushButton(FaceErrorDialog);
        btn_redetect_device->setObjectName(QStringLiteral("btn_redetect_device"));
        btn_redetect_device->setMaximumSize(QSize(80, 25));
        btn_redetect_device->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(btn_redetect_device);

        btn_close = new QPushButton(FaceErrorDialog);
        btn_close->setObjectName(QStringLiteral("btn_close"));
        btn_close->setMaximumSize(QSize(80, 25));
        btn_close->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(btn_close);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout);


        retranslateUi(FaceErrorDialog);

        QMetaObject::connectSlotsByName(FaceErrorDialog);
    } // setupUi

    void retranslateUi(QDialog *FaceErrorDialog)
    {
        FaceErrorDialog->setWindowTitle(QApplication::translate("FaceErrorDialog", "Dialog", 0));
        DialogTitleLabel->setText(QApplication::translate("FaceErrorDialog", "\346\217\220\347\244\272", 0));
        label_camera_status->setText(QApplication::translate("FaceErrorDialog", "\346\221\204\345\203\217\345\244\264\344\270\215\345\217\257\347\224\250\357\274\214\350\257\267\346\243\200\346\237\245\350\256\276\345\244\207", 0));
        btn_redetect_device->setText(QApplication::translate("FaceErrorDialog", "\351\207\215\346\226\260\346\243\200\346\265\213", 0));
        btn_close->setText(QApplication::translate("FaceErrorDialog", "\345\205\263\351\227\255", 0));
    } // retranslateUi

};

namespace Ui {
    class FaceErrorDialog: public Ui_FaceErrorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACEERRORDIALOG_H
