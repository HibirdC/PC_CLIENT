#ifndef TNABOUTUSWIDGET_H
#define TNABOUTUSWIDGET_H

#include <QWidget>
#include "ui_TNAboutUsWidget.h"
#include "common_global.h"

class TNPromptSignLabel;
class TNAboutUsWidget : public QWidget
{
	Q_OBJECT

public:
	TNAboutUsWidget(TNPluginParamPtr pluginParam, QWidget *parent = 0);
	~TNAboutUsWidget();

public slots:
	void slotCheckUpdateButtonDialog();
	void slotFeedBackProposalDialog();
    void on_notifyCheckVersionFinished(
        bool isNeedUpgrade, 
        bool isForceUpgrade, 
        QString downLoadURL,
        int nCheckType,
        QString versionDesc
        );

signals:
    void checkVersionFinished();

private:
	Ui::TNAboutUsWidget ui;
	TNPluginParamPtr _pluginParam;
    TNPromptSignLabel *_upgradePromptLabel;
};

#endif // TNABOUTUSWIDGET_H
