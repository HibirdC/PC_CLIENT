#include "TNWebViewDetailsArea.h"

#include "TNUtil.h"
#include "TNDbUtil.h"
#include "TNPathUtil.h"
#include "TNVersionInfo.h"
#include "TNNameSpace.h"
#include "TNNetAvatarDown.h"
#include "TNUserDataHelper.h"
#include "TNSimpleBrowser.h"
#include "TNWebEnginePage.h"
#include "TNZoomFactor.h"
#include "tnnotifycenter.h"
#include "NetWorkAPI_global.h"
#include "TNMessageBox.h"
#include "frames/TNBizActionResponder.h"
#include "frames/TNFrameViewer.h"
#include "TNDataControlServer.h"
#include "TNChooseCardDialog.h"
#include "TNPictureViewerDialog.h"
#include "TNDataStatistics.h"
#include "TNDataCache.h"
#include "TNConfig.h"
#include "frames/TNFrameId.h"

#include <QTime>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QWebEngineProfile>
#include <QVBoxLayout>
#include <QApplication>
#include <QLabel>
#include <QWebEngineSettings>
#include "TNWebEngineUrlRequestInterceptor.h"

TNWebViewDetailsArea::TNWebViewDetailsArea(int id, TNPluginParamPtr pluginParam, QWidget *parent)
    : DetailsAreaBase(id, parent)
    , m_pluginParam(pluginParam)
    , m_newFriendWebEngineView(0)
    , m_newFriendWebChannel(0)
    , m_newFriendContent(0)
    , m_webEngineView(0)
    , m_webChannel(0)
    , m_content(0)
{
    m_stackedWidget = new QStackedWidget(this);
    m_stackedWidget->setObjectName("stackedWidget");
    m_stackedWidget->setContentsMargins(0, 0, 0, 0);

    m_bizActionResponder = new TNBizActionResponder(this);

    initFirstPageWidget();
    initSecondPageWidget();
    initThirdPageWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_stackedWidget);
}

TNWebViewDetailsArea::~TNWebViewDetailsArea()
{

}

void TNWebViewDetailsArea::initFirstPageWidget()
{
    QWidget *firstPageWidget  = new QWidget;
    firstPageWidget->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *firstPageLayout = new QVBoxLayout(this);
    firstPageLayout->setSpacing(0);
    firstPageLayout->setContentsMargins(0, 8, 0, 0);
    QLabel *newFriendLabelTitle = new QLabel(("新学员"), this);
    newFriendLabelTitle->setObjectName("widget_CardCaseDetailTitle");
    newFriendLabelTitle->setContentsMargins(0, 0, 0, 8);
    newFriendLabelTitle->setAlignment(Qt::AlignCenter);
    firstPageLayout->addWidget(newFriendLabelTitle);
    m_newFriendWebEngineView = new QWebEngineView(this);
    m_newFriendWebEngineView->setObjectName("newFriendWebViewMineDetial");
#ifndef QT_DEBUG
    m_newFriendWebEngineView->setContextMenuPolicy(Qt::NoContextMenu);
#endif
    firstPageLayout->addWidget(m_newFriendWebEngineView);
    firstPageWidget->setLayout(firstPageLayout);

    m_stackedWidget->addWidget(firstPageWidget);

    m_newFriendWebChannel = new QWebChannel(this);
    m_newFriendContent    = new TNDocument(this);
    m_newFriendWebChannel->registerObject(QString("TNBrowserContent"), m_newFriendContent);
    m_newFriendWebEngineView->page()->setWebChannel(m_newFriendWebChannel);
    m_newFriendWebEngineView->page()->profile()->setHttpUserAgent(HttpUserAgent_H5);
    m_newFriendWebEngineView->page()->profile()->setRequestInterceptor(TNWebEngineUrlRequestInterceptor::getInstance());
    connect(m_newFriendWebEngineView, SIGNAL(loadFinished(bool)), this, SLOT(slotFriendWebLoadFinished(bool)));
    connect(m_newFriendContent, SIGNAL(sendReceiveText(const QString&)), this, SLOT(slotReceiveMessageFromNewFriendH5(const QString&)));
}

void TNWebViewDetailsArea::initSecondPageWidget()
{
    QWidget *secondPageWidget = new QWidget;
    secondPageWidget->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *secondPageLayout = new QVBoxLayout(this);
    secondPageLayout->setSpacing(0);
    secondPageLayout->setContentsMargins(0, 8, 0, 0);
    m_pLabelTitle = new QLabel(this);
    m_pLabelTitle->setObjectName("widget_CardCaseDetailTitle");
    m_pLabelTitle->setContentsMargins(0,0,0,8);
    m_pLabelTitle->setAlignment(Qt::AlignCenter);
    m_pLabelTitle->setTextFormat(Qt::PlainText);
    secondPageLayout->addWidget(m_pLabelTitle);
    m_webEngineView = new QWebEngineView(this);
    m_webEngineView->setObjectName("webViewMineDetial");
#ifndef QT_DEBUG
    m_webEngineView->setContextMenuPolicy(Qt::NoContextMenu);
#endif
    secondPageLayout->addWidget(m_webEngineView);
    secondPageWidget->setLayout(secondPageLayout);

    m_stackedWidget->addWidget(secondPageWidget);

    m_webChannel = new QWebChannel(this);
    m_content    = new TNDocument(this);
    m_webChannel->registerObject(QString("TNBrowserContent"), m_content);
    m_webEngineView->page()->setWebChannel(m_webChannel);
    m_webEngineView->page()->profile()->setHttpUserAgent(HttpUserAgent_H5);
    m_webEngineView->page()->profile()->setRequestInterceptor(TNWebEngineUrlRequestInterceptor::getInstance());
    connect(m_webEngineView, SIGNAL(loadFinished(bool)), this, SLOT(slotFrameWebLoadFinished(bool)));
    connect(m_content, SIGNAL(sendReceiveText(const QString&)), m_bizActionResponder, SLOT(slotReceiveMessageFromH5(const QString&)));
}

void TNWebViewDetailsArea::initThirdPageWidget()
{
    QWidget *thirdPageWidget = new QWidget;
    thirdPageWidget->setContentsMargins(0, 0, 0, 0);

    QGridLayout *thirdPageLayout = new QGridLayout(this);
    QLabel *label_default_backpic = new QLabel(this);
    label_default_backpic->setFixedSize(200, 124);
    label_default_backpic->setObjectName("label_default_backpic");
    thirdPageLayout->addWidget(new QLabel(this), 0, 0);
    thirdPageLayout->addWidget(new QLabel(this), 0, 1);
    thirdPageLayout->addWidget(new QLabel(this), 0, 2);
    thirdPageLayout->addWidget(new QLabel(this), 1, 0);
    thirdPageLayout->addWidget(label_default_backpic, 1, 1);
    thirdPageLayout->addWidget(new QLabel(this), 1, 2);
    thirdPageLayout->addWidget(new QLabel(this), 2, 0);
    thirdPageLayout->addWidget(new QLabel(this), 2, 1);
    thirdPageLayout->addWidget(new QLabel(this), 2, 2);
    thirdPageWidget->setLayout(thirdPageLayout);

    m_stackedWidget->addWidget(thirdPageWidget);
}

void TNWebViewDetailsArea::setCurrentPage(int pageIndex)
{
    m_stackedWidget->setCurrentIndex(pageIndex);
}

int TNWebViewDetailsArea::getCurrentPage() const
{
    return m_stackedWidget->currentIndex();
}

bool TNWebViewDetailsArea::isRunning() const
{
    // 如果当前有子窗口弹出，认为程序正在运行，未休眠
    if (QApplication::activeWindow()&& (QApplication::activeWindow()->objectName() == ("TNMessageBox")))
        return true;

    if (QApplication::activeWindow() && (QApplication::activeWindow()->objectName() == ("browserWidget")))
        return true;

    return m_stackedWidget->currentWidget()->isActiveWindow();
}

void TNWebViewDetailsArea::setTitleNameLabel(const QString &title)
{
    QString elidedText = m_pLabelTitle->fontMetrics().elidedText(title, Qt::ElideMiddle, 350, Qt::TextShowMnemonic);
    m_pLabelTitle->setText(elidedText);
}

void TNWebViewDetailsArea::slotReceiveMessageFromNewFriendH5(const QString &text)
{
    qInfo()<<"[TNMVD][TNWebViewDetailsArea]TNWebViewDetailsArea::slotReceiveMessageFromNewFriendH5="<<text;
    QJsonParseError jsonError;
    QJsonDocument jsonDoucment = QJsonDocument::fromJson(text.toUtf8(), &jsonError);
    if (jsonError.error == QJsonParseError::NoError)
    {
        if (jsonDoucment.isArray())
        {
            qInfo() << "[TNMVD][TNWebViewDetailsArea]error! json format error! jason should object.";
        }
        if (jsonDoucment.isObject())
        {
            handleNewFriendBiz(jsonDoucment.object());
        }
    }
}

void TNWebViewDetailsArea::handleNewFriendBiz(const QJsonObject &jsonObject)
{
    QString debugText = QJsonDocument(jsonObject).toJson();
    qInfo() << "[TNMVD][TNWebViewDetailsArea]handleNewFriendBiz-debugText=" << debugText;
    TN::H5BizType bizType = TN::H5BizType(jsonObject["bizType"].toInt());

    if (bizType == TN::ClickAvatarInApp)
    {
        clickAvatarInNewFriendToFrame_Self(jsonObject);
    }
    if (bizType == TN::ClickAvatarInNewFriend)
    {
        clickAvatarInNewFriendToFrame(jsonObject);
    }
}

void TNWebViewDetailsArea::slotToChat(const QJsonObject &json)
{
    qInfo()<<"[TNMVD][TNWebViewDetailsArea]TNWebViewDetailsArea::slotToChat begin...";
    TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_Address_Talk, m_pluginParam);
    handleChat(json);
    qInfo()<<"[TNMVD][TNWebViewDetailsArea]TNWebViewDetailsArea::slotToChat end.";
}

void TNWebViewDetailsArea::showNewFriendH5(const QJsonObject &json)
{
    m_friendWebTime.restart();

    QString curNewFriendH5Url = NetWorkAPI::s_newFriendH5Url + ("?buildNo=") + TNVersionInfo::buildNo();
    qInfo()<<"[TNMVD][TNWebViewDetailsArea]showNewFriendH5-Url="<<curNewFriendH5Url;
    m_newFriendWebEngineView->page()->setUrl(QUrl(curNewFriendH5Url));
    m_friendJsonData = json;
}

void TNWebViewDetailsArea::showFrameH5(const QString &feedId, const QString &belongId)
{
    m_feedId = feedId;
    m_belongId  = belongId;

    QString frame = TNFrameId::getFrameId(feedId, belongId);

    m_frameTime.restart();

    const QString curLocalH5Url = QString("%1/%2/%3/%4/0").arg(NetWorkAPI::s_urlLocalH5Url).arg(m_feedId).arg(frame).arg(m_belongId);
    qInfo()<<"[TNMVD][TNWebViewDetailsArea]showFrameH5-Url="<<curLocalH5Url;
    m_webEngineView->page()->setUrl(QUrl(curLocalH5Url));
}

void TNWebViewDetailsArea::handleChat(const QJsonObject &jsonObject)
{
    TNSimpleBrowser::getInstance()->hide();
    TN::H5BizType bizType = TN::H5BizType(jsonObject["bizType"].toInt());
    qInfo()<<"[TNMVD][TNWebViewDetailsArea]handleChat begin..bizType="<<bizType;
    switch (bizType)
    {
    case TN::Friend:
        chatToFriend(jsonObject);
        break;
    case TN::Colleague:
        chatToColleague(jsonObject);
        break;
    case TN::GroupChat:
        chatToGroupChat(jsonObject);
        break;
    default:
        break;
    }
}

void TNWebViewDetailsArea::chatToFriend(const QJsonObject &jsonObject)
{
    qInfo()<<"[TNMVD][TNWebViewDetailsArea]chatToFriend begin...";
    emit MessageSignal(MENU_NOTICE_ID);

    qInfo()<<"[TNMVD][TNWebViewDetailsArea]chatToFriend begin...001";
    QString userId = jsonObject["userId"].toString();
    QString from = jsonObject["belongFeedId"].toString();
    QString to   = jsonObject["feedId"].toString();
    QString nickName = jsonObject["username"].toString();
    QString avatarUrl = jsonObject["avatar"].toString();

    QString sessionId = TNIMCoreClient::GetSessionId(from, to, MSG_BIZ_SINGLECHAT);
    TNMessageListAdapter tempMessageListAdapter(sessionId, MSG_BIZ_SINGLECHAT);
    tempMessageListAdapter.setName(nickName);
    tempMessageListAdapter.setMyFeedId(from);
    tempMessageListAdapter.setUserId(userId);
    tempMessageListAdapter.setToFeed(to);
    tempMessageListAdapter.setAvatarPhotoUrl(avatarUrl);
    QDateTime curTime = QDateTime::currentDateTime();
    tempMessageListAdapter.setTime(curTime.toTime_t());

    qInfo()<<"[TNMVD][TNWebViewDetailsArea]chatToFriend begin...002";
    emit MessageSignal(tempMessageListAdapter, true);
    qInfo()<<"[TNMVD][TNWebViewDetailsArea]chatToFriend end.";
}

void TNWebViewDetailsArea::chatToColleague(const QJsonObject &jsonObject)
{
    qInfo()<<"[TNMVD][TNWebViewDetailsArea]chatToColleague begin...";
    emit MessageSignal(MENU_NOTICE_ID);

    qInfo()<<"[TNMVD][TNWebViewDetailsArea]chatToColleague begin...001";
    QString userId = jsonObject["userId"].toString();
    QString from = jsonObject["belongFeedId"].toString();
    QString to   = jsonObject["feedId"].toString();
    QString staffName = jsonObject["username"].toString();
    QString avatarUrl = jsonObject["avatar"].toString();

    QString sessionId = TNIMCoreClient::GetSessionId(from, to, MSG_BIZ_SINGLECHAT);
    TNMessageListAdapter tempMessageListAdapter(sessionId, MSG_BIZ_SINGLECHAT);
    tempMessageListAdapter.setName(staffName);
    tempMessageListAdapter.setMyFeedId(from);
    tempMessageListAdapter.setUserId(userId);
    tempMessageListAdapter.setToFeed(to);
    tempMessageListAdapter.setAvatarPhotoUrl(avatarUrl);
    QDateTime curTime = QDateTime::currentDateTime();
    tempMessageListAdapter.setTime(curTime.toTime_t());

    qInfo()<<"[TNMVD][TNWebViewDetailsArea]chatToColleague begin...002";
    emit MessageSignal(tempMessageListAdapter,true);
    qInfo()<<"[TNMVD][TNWebViewDetailsArea]chatToColleague end.";
}

void TNWebViewDetailsArea::chatToGroupChat(const QJsonObject &jsonObject)
{
    qInfo()<<"[TNMVD][TNWebViewDetailsArea]chatToGroupChat begin...";
    emit MessageSignal(MENU_NOTICE_ID);

    qInfo()<<"[TNMVD][TNWebViewDetailsArea]chatToGroupChat begin...001";
    QString userId = jsonObject["userId"].toString();
    QString from = jsonObject["belongFeedId"].toString();
    QString to   = jsonObject["feedId"].toString();
    QString staffName = jsonObject["username"].toString();
    QString avatarUrl = jsonObject["avatar"].toString();

    QString sessionId = TNIMCoreClient::GetSessionId(from, to, MSG_BIZ_GROUPCHAT);
    TNMessageListAdapter tempMessageListAdapter(sessionId, MSG_BIZ_GROUPCHAT);
    tempMessageListAdapter.setName(staffName);
    tempMessageListAdapter.setMyFeedId(from);
    tempMessageListAdapter.setUserId(userId);
    tempMessageListAdapter.setToFeed(to);
    tempMessageListAdapter.setAvatarPhotoUrl(avatarUrl);
    QDateTime curTime = QDateTime::currentDateTime();
    tempMessageListAdapter.setTime(curTime.toTime_t());

    qInfo()<<"[TNMVD][TNWebViewDetailsArea]chatToGroupChat begin...002";
    emit MessageSignal(tempMessageListAdapter, true);
    qInfo()<<"[TNMVD][TNWebViewDetailsArea]chatToGroupChat end.";
}

void TNWebViewDetailsArea::clickAvatarInNewFriendToFrame_Self(const QJsonObject &jsonObject)
{
    const QString frameFeedId = jsonObject.value("feedId").toString();
    const QString belongFeedId = jsonObject.value("belongId").toString();

    qInfo() << "[TNMVD][TNWebViewDetailsArea]clickAvatarInNewFriendToFrame_Self-frameFeedId=" << frameFeedId;
    qInfo() << "[TNMVD][TNWebViewDetailsArea]clickAvatarInNewFriendToFrame_Self-belongFeedId=" << belongFeedId;
    // 如果新学员已经通过同意成为好友了，在新学员页面点击对方头像也是走的该分支
    //Q_ASSERT(frameFeedId == belongFeedId);
    TNFrameViewer::instance()->showFrame(frameFeedId, belongFeedId);
}

void TNWebViewDetailsArea::clickAvatarInNewFriendToFrame(const QJsonObject &jsonObject)
{
    const QString frameFeedId = jsonObject.value("feedId").toString();
    const QString belongFeedId = jsonObject.value("belongId").toString();

    qInfo() << "[TNMVD][TNWebViewDetailsArea]clickAvatarInNewFriendToFrame-frameFeedId=" << frameFeedId;
    qInfo() << "[TNMVD][TNWebViewDetailsArea]clickAvatarInNewFriendToFrame-belongFeedId=" << belongFeedId;
    Q_ASSERT(frameFeedId != belongFeedId);
    TNFrameViewer::instance()->showFrame(frameFeedId, belongFeedId, true);
}

void TNWebViewDetailsArea::CloseDetailPage(const QString &feedId,const QString&belongId)
{
    qInfo() << "[TNMVD][TNWebViewDetailsArea]Expect feed: " << m_feedId << ",Infact feed:" << feedId;
    qInfo() << "[TNMVD][TNWebViewDetailsArea]Expect belongfeed: " << m_belongId << ",Infact belongId:" << belongId;
    if ((feedId == m_feedId && belongId == m_belongId) || (feedId == AVATAR_ALL_FEED &&belongId == AVATAR_ALL_FEED))
    {
        setCurrentPage(2);
    }
}

void TNWebViewDetailsArea::slotFriendWebLoadFinished(bool ok)
{
    qInfo() << "[TNMVD][TNWebViewDetailsArea]friendloadtime=" << m_friendWebTime.elapsed();
    if (ok)
    {
        QString debugText = QJsonDocument(m_friendJsonData).toJson();
        qInfo() << "[TNMVD][TNWebViewDetailsArea]slotFriendWebLoadFinished-debugText=" << debugText;

        int languageIndex = int(TNConfig::instance()->GetCurrentLangueSet());
        m_friendJsonData.insert("language", languageIndex);
        m_friendJsonData.insert("toonType", APPTYPE);
        m_friendJsonData.insert("userId", m_pluginParam->strTnUserID);
        m_friendJsonData.insert("userToken", m_pluginParam->strTnUserToken);
        m_friendJsonData.insert("userAgent", m_pluginParam->strTnUserAgent);

        QJsonArray cardArray;
        QList<st_FeedPtr> myAllStuff;
        TNDataCache::GetInstance()->getMyStuff(myAllStuff);
        for (st_FeedPtr card : myAllStuff)
        {
            QJsonObject aCardJson;
            aCardJson.insert("feedId", card->GetFeedID());
            aCardJson.insert("feedName", card->GetTitle());
            aCardJson.insert("feedAvatar", card->GetAvatarID());
            cardArray.append(aCardJson);
        }
        m_friendJsonData.insert("feedList", cardArray);

        m_newFriendContent->setSendTextText(m_friendJsonData);
        qInfo() << "[TNMVD][TNWebViewDetailsArea]ToWeb-user data json to web.";
    }
    else
    {
        qInfo() << "TNWebViewDetailsArea::slotFriendWebLoadFinished-ok=" << ok;
    }
    qInfo() << "[TNMVD][TNWebViewDetailsArea]friendwebtime=" << m_friendWebTime.elapsed();
}

void TNWebViewDetailsArea::slotFrameWebLoadFinished(bool ok)
{
    qInfo() << "[TNMVD][TNWebViewDetailsArea]frameloadtime=" << m_frameTime.elapsed();
    if (ok)
    {
        QString url = m_webEngineView->page()->url().toString();
        qDebug() << "slotFrameWebLoadFinished-url=" << url;

        QJsonObject text;
        int languageIndex = int(TNConfig::instance()->GetCurrentLangueSet());
        text.insert("language", languageIndex);
        text.insert("toonType", APPTYPE);
        text.insert("userId", m_pluginParam->strTnUserID);
        text.insert("userToken", m_pluginParam->strTnUserToken);
        text.insert("userAgent", m_pluginParam->strTnUserAgent);

        QJsonArray cardArray;
        QList<st_FeedPtr> myAllStuff;
        TNDataCache::GetInstance()->getMyStuff(myAllStuff);
        for (st_FeedPtr card : myAllStuff)
        {
            QJsonObject aCardJson;
            aCardJson.insert("feedId", card->GetFeedID());
            aCardJson.insert("feedName", card->GetTitle());
            aCardJson.insert("feedAvatar", card->GetAvatarID());
            cardArray.append(aCardJson);
        }
        text.insert("feedList", cardArray);

        m_content->setSendTextText(text);
    }
    else
    {
        qInfo() << "TNWebViewDetailsArea::slotFrameWebLoadFinished-ok=" << ok;
    }
    qInfo() << "[TNMVD][TNWebViewDetailsArea]framewebtime=" << m_frameTime.elapsed();
}
