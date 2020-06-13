#ifndef TNWEBVIEWDETAILS_H
#define TNWEBVIEWDETAILS_H

#include <QLabel>
#include <QWebChannel>
#include <QWebEngineView>
#include <QStackedWidget>

#include "TNMVD_global.h"
#include "DetailsAreaBase.h"
#include "TNNameSpace.h"
#include "TNDocument.h"

class MenuAreaBase;
class TNBizActionResponder;

class TNMVD_EXPORT TNWebViewDetailsArea : public DetailsAreaBase
{
    Q_OBJECT

public:
    TNWebViewDetailsArea(int id, TNPluginParamPtr pluginParam, QWidget *parent = 0);
    ~TNWebViewDetailsArea();

    void setCurrentPage(int pageIndex);
    int getCurrentPage() const;
    bool isRunning() const;
    void setTitleNameLabel(const QString &title);

    void showNewFriendH5(const QJsonObject &json);
    void showFrameH5(const QString &feedId, const QString &belongId);

public slots:
    void slotReceiveMessageFromNewFriendH5(const QString &text);
    void slotToChat(const QJsonObject &json);
	void CloseDetailPage(const QString &feedId, const QString&belongId);
    void slotFriendWebLoadFinished(bool ok);
    void slotFrameWebLoadFinished(bool ok);

private:
    void initFirstPageWidget();
    void initSecondPageWidget();
    void initThirdPageWidget();
    void handleNewFriendBiz(const QJsonObject &jsonObject);
    void handleChat(const QJsonObject &jsonObject);
    void chatToFriend(const QJsonObject &jsonObject);
    void chatToColleague(const QJsonObject &jsonObject);
    void chatToGroupChat(const QJsonObject &jsonObject);

    void clickAvatarInNewFriendToFrame_Self(const QJsonObject &jsonObject);
    void clickAvatarInNewFriendToFrame(const QJsonObject &jsonObject);

private:
	QString m_belongId;
	QString m_feedId;
    TNPluginParamPtr m_pluginParam;

    QStackedWidget *m_stackedWidget;

    QWebEngineView *m_newFriendWebEngineView;
    QWebChannel    *m_newFriendWebChannel;
    TNDocument     *m_newFriendContent;

    QWebEngineView *m_webEngineView;
    QWebChannel    *m_webChannel;
    TNDocument     *m_content;
    QLabel         *m_pLabelTitle;

    TNBizActionResponder *m_bizActionResponder;

    QTime m_friendWebTime;
    QJsonObject m_friendJsonData;

    QTime m_frameTime;
};

#endif // TNWEBVIEWDETAILS_H
