/********************************************************************************
** Form generated from reading UI file 'tnaudiobrowser.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNAUDIOBROWSER_H
#define UI_TNAUDIOBROWSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "tnstatuslabel.h"

QT_BEGIN_NAMESPACE

class Ui_TNAudioBrowser
{
public:
    QHBoxLayout *horizontalLayout_4;
    QWidget *widget_audio_left;
    QHBoxLayout *horizontalLayout;
    QLabel *label_audio_movie_left;
    QSpacerItem *horizontalSpacer;
    QLabel *label_audio_time_left;
    QWidget *widget_audio_readed;
    QHBoxLayout *horizontalLayout_3;
    TNStatusLabel *label_is_readed;
    QWidget *widget_audio_right;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_audio_time_right;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_audio_movie_right;

    void setupUi(QWidget *TNAudioBrowser)
    {
        if (TNAudioBrowser->objectName().isEmpty())
            TNAudioBrowser->setObjectName(QStringLiteral("TNAudioBrowser"));
        TNAudioBrowser->resize(480, 34);
        TNAudioBrowser->setMinimumSize(QSize(244, 34));
        TNAudioBrowser->setMaximumSize(QSize(16777215, 34));
        horizontalLayout_4 = new QHBoxLayout(TNAudioBrowser);
        horizontalLayout_4->setSpacing(10);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        widget_audio_left = new QWidget(TNAudioBrowser);
        widget_audio_left->setObjectName(QStringLiteral("widget_audio_left"));
        widget_audio_left->setMinimumSize(QSize(200, 34));
        widget_audio_left->setMaximumSize(QSize(200, 34));
        horizontalLayout = new QHBoxLayout(widget_audio_left);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, 0, 10, 0);
        label_audio_movie_left = new QLabel(widget_audio_left);
        label_audio_movie_left->setObjectName(QStringLiteral("label_audio_movie_left"));
        label_audio_movie_left->setMinimumSize(QSize(12, 17));
        label_audio_movie_left->setMaximumSize(QSize(12, 17));

        horizontalLayout->addWidget(label_audio_movie_left);

        horizontalSpacer = new QSpacerItem(253, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_audio_time_left = new QLabel(widget_audio_left);
        label_audio_time_left->setObjectName(QStringLiteral("label_audio_time_left"));
        label_audio_time_left->setMaximumSize(QSize(100, 16777215));
        label_audio_time_left->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_audio_time_left);


        horizontalLayout_4->addWidget(widget_audio_left);

        widget_audio_readed = new QWidget(TNAudioBrowser);
        widget_audio_readed->setObjectName(QStringLiteral("widget_audio_readed"));
        widget_audio_readed->setMaximumSize(QSize(34, 16777215));
        horizontalLayout_3 = new QHBoxLayout(widget_audio_readed);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_is_readed = new TNStatusLabel(widget_audio_readed);
        label_is_readed->setObjectName(QStringLiteral("label_is_readed"));
        label_is_readed->setMinimumSize(QSize(34, 34));
        label_is_readed->setMaximumSize(QSize(34, 34));
        label_is_readed->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_is_readed);


        horizontalLayout_4->addWidget(widget_audio_readed);

        widget_audio_right = new QWidget(TNAudioBrowser);
        widget_audio_right->setObjectName(QStringLiteral("widget_audio_right"));
        widget_audio_right->setMinimumSize(QSize(200, 34));
        widget_audio_right->setMaximumSize(QSize(200, 34));
        horizontalLayout_2 = new QHBoxLayout(widget_audio_right);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(10, 0, 10, 0);
        label_audio_time_right = new QLabel(widget_audio_right);
        label_audio_time_right->setObjectName(QStringLiteral("label_audio_time_right"));
        label_audio_time_right->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(label_audio_time_right);

        horizontalSpacer_2 = new QSpacerItem(253, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label_audio_movie_right = new QLabel(widget_audio_right);
        label_audio_movie_right->setObjectName(QStringLiteral("label_audio_movie_right"));
        label_audio_movie_right->setMinimumSize(QSize(12, 17));
        label_audio_movie_right->setMaximumSize(QSize(12, 17));

        horizontalLayout_2->addWidget(label_audio_movie_right);


        horizontalLayout_4->addWidget(widget_audio_right);


        retranslateUi(TNAudioBrowser);

        QMetaObject::connectSlotsByName(TNAudioBrowser);
    } // setupUi

    void retranslateUi(QWidget *TNAudioBrowser)
    {
        TNAudioBrowser->setWindowTitle(QApplication::translate("TNAudioBrowser", "TNAudioBrowser", 0));
        label_audio_movie_left->setText(QApplication::translate("TNAudioBrowser", "TextLabel", 0));
        label_audio_time_left->setText(QApplication::translate("TNAudioBrowser", "60\"", 0));
        label_is_readed->setText(QString());
        label_audio_time_right->setText(QApplication::translate("TNAudioBrowser", "60\"", 0));
        label_audio_movie_right->setText(QApplication::translate("TNAudioBrowser", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class TNAudioBrowser: public Ui_TNAudioBrowser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNAUDIOBROWSER_H
