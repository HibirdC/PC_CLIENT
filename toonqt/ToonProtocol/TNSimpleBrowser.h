#ifndef TNSIMPLEBROWSER_H
#define TNSIMPLEBROWSER_H

#include "ToonProtocol_global.h"

#include <QDialog>
#include <QHash>
#include <QJsonDocument>

namespace Ui {
class TNSimpleBrowser;
}

#include <QWebEngineProfile>
#include <QWebEngineView>
#include <QWebChannel>
#include "TNDocument.h"
#include "DropShadowWidget.h"

class TOONPROTOCOL_EXPORT TNSimpleBrowser : public /*QDialog*/DropShadowWidget
{
    Q_OBJECT

public:
    static TNSimpleBrowser *getInstance();
    static void freeInstance();
	explicit TNSimpleBrowser(QWidget *parent = 0);
    ~TNSimpleBrowser();

    void setPluginParam(const TNPluginParamPtr &pluginParam);
    void setUrl(const QString &url);
	void showOnTop();

signals:
    void sendReceivedTextFromH5(const QString &text);

public slots:
	void slotClose();

private slots:
	void slotBack();
	void slotForward();
	void slotFresh();
	void slotMinimum();
	void slotMaximum(bool checked);
	
    void slotSendDataToH5(bool ok);
protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::TNSimpleBrowser *ui;

	QPushButton *m_backButton;
	QPushButton *m_forwardButton;
	QPushButton *m_freshButton;
	QPushButton *m_minButton;
	QPushButton *m_maxButton;
	QPushButton *m_closeButton;

    QWebEngineView *m_webEngineView;
    QWebChannel *m_webChannel;
    TNDocument m_content;

    TNPluginParamPtr m_pluginParam;

	static TNSimpleBrowser *m_instance;

    QTime m_time;
};

#endif // TNSIMPLEBROWSER_H
