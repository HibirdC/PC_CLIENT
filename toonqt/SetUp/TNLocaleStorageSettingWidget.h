#ifndef TNLOCALESTORAGESETTINGWIDGET_H
#define TNLOCALESTORAGESETTINGWIDGET_H

#include <QWidget>
#include "ui_TNLocaleStorageSettingWidget.h"

class QxtGlobalShortcut;
class TNLocaleStorageSettingWidget : public QWidget
{
	Q_OBJECT

public:
	TNLocaleStorageSettingWidget(QWidget *parent = 0);
	~TNLocaleStorageSettingWidget();

protected:
	bool eventFilter(QObject *target, QEvent *event);

private slots:
    void slotBootUp(int state);
    void slotNoDisturb(int state);
    void slotAutoLogin(int state);

    void slotCurrentLanguageChanged(int index);
	void slotChangePathDialog();
	void slotOpenDirFileDialog();
    void onHotKeyChanged(const QString &key);
    void slotShortCutSettingDialog();
    void onCheckBoxStateChanged(int state);
    void onScreenShotKey(QxtGlobalShortcut* self);

private:
	Ui::TNLocaleStorageSettingWidget ui;

    void registerScreenHotKey(const QString &key);
	void InitSettings();
	void saveLocalPathSettingToDB();
	void saveSendHotKeySettingToDB();
    void saveScreenShotHotKeySettingToDB(const QString &key);
    void checkDirIsWritable(const QString &path);

Q_SIGNALS:
	void updateSettingStatus(QString, int);
};

#endif // TNLOCALESTORAGESETTINGWIDGET_H
