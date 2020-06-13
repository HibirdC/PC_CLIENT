/********************************************************************************
** Form generated from reading UI file 'TNLocaleStorageSettingWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNLOCALESTORAGESETTINGWIDGET_H
#define UI_TNLOCALESTORAGESETTINGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TNLocaleStorageSettingWidget
{
public:
    QHBoxLayout *horizontalLayout_13;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_10;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_8;
    QLabel *localStorageSystemTitle;
    QCheckBox *bootUpCheckBox;
    QSpacerItem *horizontalSpacer_12;
    QCheckBox *noDisturbCheckBox;
    QSpacerItem *horizontalSpacer_13;
    QCheckBox *autoLoginCheckBox;
    QSpacerItem *horizontalSpacer_9;
    QWidget *safeLoginWidget;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_10;
    QLabel *localStorageSystemTitle_2;
    QHBoxLayout *horizontalLayout_9;
    QLabel *faceIdButton;
    QSpacerItem *horizontalSpacer_6;
    QLabel *facelabel;
    QVBoxLayout *verticalLayout_2;
    QLabel *localStorageSystemTitle_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *localStorageSystemTitle_4;
    QComboBox *languageComboBox;
    QSpacerItem *horizontalSpacer_8;
    QVBoxLayout *verticalLayout_3;
    QLabel *localStorageLabelTitle;
    QHBoxLayout *horizontalLayout;
    QLabel *labelFileMan;
    QLineEdit *localStorageFileLineEdit;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *localStorageLabel;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *changeDirButton;
    QPushButton *openDirButton;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout_4;
    QLabel *shortKeyLabel;
    QHBoxLayout *horizontalLayout_4;
    QLabel *sendMessageLable;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_7;
    QLabel *hotKeyScreenShot;
    QPushButton *screentShotShortCut;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_5;
    QLabel *checkHotKey;
    QCheckBox *hotKeyCheckBox;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *TNLocaleStorageSettingWidget)
    {
        if (TNLocaleStorageSettingWidget->objectName().isEmpty())
            TNLocaleStorageSettingWidget->setObjectName(QStringLiteral("TNLocaleStorageSettingWidget"));
        TNLocaleStorageSettingWidget->resize(791, 640);
        horizontalLayout_13 = new QHBoxLayout(TNLocaleStorageSettingWidget);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(-1, 38, -1, -1);
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_10);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(-1, -1, -1, 30);
        localStorageSystemTitle = new QLabel(TNLocaleStorageSettingWidget);
        localStorageSystemTitle->setObjectName(QStringLiteral("localStorageSystemTitle"));
        localStorageSystemTitle->setMinimumSize(QSize(78, 0));

        horizontalLayout_8->addWidget(localStorageSystemTitle);

        bootUpCheckBox = new QCheckBox(TNLocaleStorageSettingWidget);
        bootUpCheckBox->setObjectName(QStringLiteral("bootUpCheckBox"));

        horizontalLayout_8->addWidget(bootUpCheckBox);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_12);

        noDisturbCheckBox = new QCheckBox(TNLocaleStorageSettingWidget);
        noDisturbCheckBox->setObjectName(QStringLiteral("noDisturbCheckBox"));

        horizontalLayout_8->addWidget(noDisturbCheckBox);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_13);

        autoLoginCheckBox = new QCheckBox(TNLocaleStorageSettingWidget);
        autoLoginCheckBox->setObjectName(QStringLiteral("autoLoginCheckBox"));

        horizontalLayout_8->addWidget(autoLoginCheckBox);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_9);

        horizontalLayout_8->setStretch(6, 1);

        verticalLayout_5->addLayout(horizontalLayout_8);

        safeLoginWidget = new QWidget(TNLocaleStorageSettingWidget);
        safeLoginWidget->setObjectName(QStringLiteral("safeLoginWidget"));
        horizontalLayout_11 = new QHBoxLayout(safeLoginWidget);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 1, 1, 1);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 28);
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(-1, -1, -1, 2);
        localStorageSystemTitle_2 = new QLabel(safeLoginWidget);
        localStorageSystemTitle_2->setObjectName(QStringLiteral("localStorageSystemTitle_2"));
        localStorageSystemTitle_2->setMinimumSize(QSize(112, 0));

        horizontalLayout_10->addWidget(localStorageSystemTitle_2);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        faceIdButton = new QLabel(safeLoginWidget);
        faceIdButton->setObjectName(QStringLiteral("faceIdButton"));

        horizontalLayout_9->addWidget(faceIdButton);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_6);


        horizontalLayout_10->addLayout(horizontalLayout_9);


        verticalLayout->addLayout(horizontalLayout_10);

        facelabel = new QLabel(safeLoginWidget);
        facelabel->setObjectName(QStringLiteral("facelabel"));
        facelabel->setIndent(118);

        verticalLayout->addWidget(facelabel);


        horizontalLayout_11->addLayout(verticalLayout);


        verticalLayout_5->addWidget(safeLoginWidget);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        localStorageSystemTitle_3 = new QLabel(TNLocaleStorageSettingWidget);
        localStorageSystemTitle_3->setObjectName(QStringLiteral("localStorageSystemTitle_3"));

        verticalLayout_2->addWidget(localStorageSystemTitle_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, 8, -1, 30);
        localStorageSystemTitle_4 = new QLabel(TNLocaleStorageSettingWidget);
        localStorageSystemTitle_4->setObjectName(QStringLiteral("localStorageSystemTitle_4"));
        localStorageSystemTitle_4->setMinimumSize(QSize(112, 0));

        horizontalLayout_6->addWidget(localStorageSystemTitle_4);

        languageComboBox = new QComboBox(TNLocaleStorageSettingWidget);
        languageComboBox->setObjectName(QStringLiteral("languageComboBox"));

        horizontalLayout_6->addWidget(languageComboBox);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);


        verticalLayout_2->addLayout(horizontalLayout_6);


        verticalLayout_5->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        localStorageLabelTitle = new QLabel(TNLocaleStorageSettingWidget);
        localStorageLabelTitle->setObjectName(QStringLiteral("localStorageLabelTitle"));

        verticalLayout_3->addWidget(localStorageLabelTitle);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 8, -1, -1);
        labelFileMan = new QLabel(TNLocaleStorageSettingWidget);
        labelFileMan->setObjectName(QStringLiteral("labelFileMan"));
        labelFileMan->setMinimumSize(QSize(112, 0));

        horizontalLayout->addWidget(labelFileMan);

        localStorageFileLineEdit = new QLineEdit(TNLocaleStorageSettingWidget);
        localStorageFileLineEdit->setObjectName(QStringLiteral("localStorageFileLineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(localStorageFileLineEdit->sizePolicy().hasHeightForWidth());
        localStorageFileLineEdit->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(localStorageFileLineEdit);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        horizontalLayout->setStretch(1, 2);
        horizontalLayout->setStretch(2, 1);

        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(120, -1, -1, -1);
        localStorageLabel = new QLabel(TNLocaleStorageSettingWidget);
        localStorageLabel->setObjectName(QStringLiteral("localStorageLabel"));

        horizontalLayout_2->addWidget(localStorageLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(20);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(120, -1, -1, 30);
        changeDirButton = new QPushButton(TNLocaleStorageSettingWidget);
        changeDirButton->setObjectName(QStringLiteral("changeDirButton"));
        changeDirButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_3->addWidget(changeDirButton);

        openDirButton = new QPushButton(TNLocaleStorageSettingWidget);
        openDirButton->setObjectName(QStringLiteral("openDirButton"));
        openDirButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_3->addWidget(openDirButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);


        verticalLayout_3->addLayout(horizontalLayout_3);


        verticalLayout_5->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        shortKeyLabel = new QLabel(TNLocaleStorageSettingWidget);
        shortKeyLabel->setObjectName(QStringLiteral("shortKeyLabel"));

        verticalLayout_4->addWidget(shortKeyLabel);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 8, -1, -1);
        sendMessageLable = new QLabel(TNLocaleStorageSettingWidget);
        sendMessageLable->setObjectName(QStringLiteral("sendMessageLable"));
        sendMessageLable->setMinimumSize(QSize(112, 0));

        horizontalLayout_4->addWidget(sendMessageLable);

        comboBox = new QComboBox(TNLocaleStorageSettingWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_4->addWidget(comboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(-1, 8, -1, -1);
        hotKeyScreenShot = new QLabel(TNLocaleStorageSettingWidget);
        hotKeyScreenShot->setObjectName(QStringLiteral("hotKeyScreenShot"));
        hotKeyScreenShot->setMinimumSize(QSize(112, 0));

        horizontalLayout_7->addWidget(hotKeyScreenShot);

        screentShotShortCut = new QPushButton(TNLocaleStorageSettingWidget);
        screentShotShortCut->setObjectName(QStringLiteral("screentShotShortCut"));
        screentShotShortCut->setCursor(QCursor(Qt::PointingHandCursor));
        screentShotShortCut->setFlat(true);

        horizontalLayout_7->addWidget(screentShotShortCut);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 8, -1, -1);
        checkHotKey = new QLabel(TNLocaleStorageSettingWidget);
        checkHotKey->setObjectName(QStringLiteral("checkHotKey"));
        checkHotKey->setMinimumSize(QSize(112, 0));

        horizontalLayout_5->addWidget(checkHotKey);

        hotKeyCheckBox = new QCheckBox(TNLocaleStorageSettingWidget);
        hotKeyCheckBox->setObjectName(QStringLiteral("hotKeyCheckBox"));

        horizontalLayout_5->addWidget(hotKeyCheckBox);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout_4->addLayout(horizontalLayout_5);


        verticalLayout_5->addLayout(verticalLayout_4);


        horizontalLayout_12->addLayout(verticalLayout_5);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_11);


        verticalLayout_6->addLayout(horizontalLayout_12);

        verticalSpacer = new QSpacerItem(261, 144, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);


        horizontalLayout_13->addLayout(verticalLayout_6);

        QWidget::setTabOrder(localStorageFileLineEdit, changeDirButton);
        QWidget::setTabOrder(changeDirButton, openDirButton);
        QWidget::setTabOrder(openDirButton, hotKeyCheckBox);

        retranslateUi(TNLocaleStorageSettingWidget);
        QObject::connect(comboBox, SIGNAL(currentIndexChanged(QString)), TNLocaleStorageSettingWidget, SLOT(showFullScreen()));

        QMetaObject::connectSlotsByName(TNLocaleStorageSettingWidget);
    } // setupUi

    void retranslateUi(QWidget *TNLocaleStorageSettingWidget)
    {
        TNLocaleStorageSettingWidget->setWindowTitle(QApplication::translate("TNLocaleStorageSettingWidget", "TNLocaleStorageSettingWidget", 0));
        localStorageSystemTitle->setText(QApplication::translate("TNLocaleStorageSettingWidget", "\347\263\273\347\273\237\350\256\276\347\275\256", 0));
        bootUpCheckBox->setText(QApplication::translate("TNLocaleStorageSettingWidget", "\345\274\200\346\234\272\345\220\257\345\212\250", 0));
        noDisturbCheckBox->setText(QApplication::translate("TNLocaleStorageSettingWidget", "\345\205\215\346\211\223\346\211\260", 0));
        autoLoginCheckBox->setText(QApplication::translate("TNLocaleStorageSettingWidget", "\350\207\252\345\212\250\347\231\273\345\275\225", 0));
        localStorageSystemTitle_2->setText(QApplication::translate("TNLocaleStorageSettingWidget", "\345\256\211\345\205\250\347\231\273\345\275\225", 0));
        faceIdButton->setText(QApplication::translate("TNLocaleStorageSettingWidget", "\345\220\257\347\224\250\344\272\272\350\204\270\350\257\206\345\210\253", 0));
        facelabel->setText(QApplication::translate("TNLocaleStorageSettingWidget", "\345\257\206\347\240\201\347\231\273\345\275\225\345\220\216\345\217\257\344\275\277\347\224\250\344\272\272\350\204\270\350\257\206\345\210\253", 0));
        localStorageSystemTitle_3->setText(QApplication::translate("TNLocaleStorageSettingWidget", "\350\257\255\350\250\200\350\256\276\347\275\256", 0));
        localStorageSystemTitle_4->setText(QApplication::translate("TNLocaleStorageSettingWidget", "\350\257\255\350\250\200", 0));
        localStorageLabelTitle->setText(QApplication::translate("TNLocaleStorageSettingWidget", "\346\234\254\345\234\260\345\255\230\345\202\250\350\256\276\347\275\256", 0));
        labelFileMan->setText(QApplication::translate("TNLocaleStorageSettingWidget", "\346\226\207\344\273\266\347\256\241\347\220\206", 0));
        localStorageLabel->setText(QApplication::translate("TNLocaleStorageSettingWidget", "\351\273\230\350\256\244\346\212\212\346\216\245\346\224\266\345\210\260\347\232\204\346\226\207\344\273\266\344\277\235\345\255\230\345\210\260\346\255\244\346\226\207\344\273\266\345\244\271\344\270\255", 0));
        changeDirButton->setText(QApplication::translate("TNLocaleStorageSettingWidget", "\346\233\264\346\224\271\347\233\256\345\275\225", 0));
        openDirButton->setText(QApplication::translate("TNLocaleStorageSettingWidget", "\346\211\223\345\274\200\346\226\207\344\273\266\345\244\271", 0));
        shortKeyLabel->setText(QApplication::translate("TNLocaleStorageSettingWidget", "\345\277\253\346\215\267\346\214\211\351\224\256", 0));
        sendMessageLable->setText(QApplication::translate("TNLocaleStorageSettingWidget", "\345\217\221\351\200\201\346\266\210\346\201\257", 0));
        hotKeyScreenShot->setText(QApplication::translate("TNLocaleStorageSettingWidget", "\346\210\252\345\233\276\343\200\200\343\200\200", 0));
        screentShotShortCut->setText(QApplication::translate("TNLocaleStorageSettingWidget", "\350\256\276\347\275\256\345\277\253\346\215\267\351\224\256", 0));
        checkHotKey->setText(QApplication::translate("TNLocaleStorageSettingWidget", "\346\243\200\346\265\213\347\203\255\351\224\256", 0));
        hotKeyCheckBox->setText(QApplication::translate("TNLocaleStorageSettingWidget", "\347\203\255\351\224\256\344\270\216\345\205\266\344\273\226\350\275\257\344\273\266\345\206\262\347\252\201\346\227\266\346\217\220\351\206\222", 0));
    } // retranslateUi

};

namespace Ui {
    class TNLocaleStorageSettingWidget: public Ui_TNLocaleStorageSettingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNLOCALESTORAGESETTINGWIDGET_H
