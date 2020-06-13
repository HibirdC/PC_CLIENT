#ifndef SETUPLISTAREA_H
#define SETUPLISTAREA_H

#include <QWidget>
#include <QLabel>
#include <QThread>

#include "ListAreaBase.h"

class QPushButton;
class TNPromptSignLabel;
class TNProgressLoadingWithPrompt;
class TNNoticeUpdater;
class SetUpListArea : public ListAreaBase
{
	Q_OBJECT

public:
	SetUpListArea(int id, TNPluginParamPtr pluginParam, QWidget *parent = 0);
	~SetUpListArea();

signals:
	void clickedButton(int index);
    void syncCatalogFinished();
    void syncCatalogStart();

public slots:
	void slotAppearanceButton();
	void slotLocaleStorageButton();
	void slotUserAgreementButton();
	void slotAboutUsButton();
	void slotExitLoginButton();
	void slotSyncCatalogButton();
    void onSyncCatalogFinised();
    void on_notifyCheckVersionFinished(
            bool isNeedUpgrade,
            bool isForceUpgrade,
            QString downLoadURL,
            int nCheckType,
            QString versionDesc
            );

private:
    void setAllButtonUnchecked();

private:
	enum ButtonIndex
	{
		//appearance,
		localeStorage,
		skinSet,
		userAgreement,
		aboutUs, 
		exitLogin,
		backgroundWidget	
	};
	TNPluginParamPtr _pluginParam;

	QPushButton * _appearanceButton;
	QPushButton * _localeStorageButton;
	QPushButton * _userAgreementButton;
	QPushButton * _aboutUsButton;
    QPushButton * _syncCatalog;
    QThread       m_syncCatalogThread;
	QPushButton * _exitLoginButton;
    TNPromptSignLabel * _promptSignLabel;

    TNNoticeUpdater * _noticeUpdator;
    TNProgressLoadingWithPrompt *_ProgressLoadingWidget;
	
	void InitSettings();
};

#endif // SETUPLISTAREA_H
