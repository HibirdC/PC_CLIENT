
//#include "stdafx.h"

#include "httpserver.h"
#include "httprequest.h"
#include "httpresponse.h"
#include "httpconnection.h"
#include "common_global.h"

#include <QFile>
#include <QEventLoop>
#include <QApplication>
#include <QTimer>
#include <QTcpServer>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

QHash<int, QString> STATUS_CODES;

HttpServer::HttpServer(QObject *parent)
: QObject(parent)
, m_tcpServer(0)
, m_toonProtocolHandleFinished(false)
{
#define STATUS_CODE(num, reason) STATUS_CODES.insert(num, reason);
	// {{{
	STATUS_CODE(100, "Continue")
		STATUS_CODE(101, "Switching Protocols")
		STATUS_CODE(102, "Processing")                 // RFC 2518) obsoleted by RFC 4918
		STATUS_CODE(200, "OK")
		STATUS_CODE(201, "Created")
		STATUS_CODE(202, "Accepted")
		STATUS_CODE(203, "Non-Authoritative Information")
		STATUS_CODE(204, "No Content")
		STATUS_CODE(205, "Reset Content")
		STATUS_CODE(206, "Partial Content")
		STATUS_CODE(207, "Multi-Status")               // RFC 4918
		STATUS_CODE(300, "Multiple Choices")
		STATUS_CODE(301, "Moved Permanently")
		STATUS_CODE(302, "Moved Temporarily")
		STATUS_CODE(303, "See Other")
		STATUS_CODE(304, "Not Modified")
		STATUS_CODE(305, "Use Proxy")
		STATUS_CODE(307, "Temporary Redirect")
		STATUS_CODE(400, "Bad Request")
		STATUS_CODE(401, "Unauthorized")
		STATUS_CODE(402, "Payment Required")
		STATUS_CODE(403, "Forbidden")
		STATUS_CODE(404, "Not Found")
		STATUS_CODE(405, "Method Not Allowed")
		STATUS_CODE(406, "Not Acceptable")
		STATUS_CODE(407, "Proxy Authentication Required")
		STATUS_CODE(408, "Request Time-out")
		STATUS_CODE(409, "Conflict")
		STATUS_CODE(410, "Gone")
		STATUS_CODE(411, "Length Required")
		STATUS_CODE(412, "Precondition Failed")
		STATUS_CODE(413, "Request Entity Too Large")
		STATUS_CODE(414, "Request-URI Too Large")
		STATUS_CODE(415, "Unsupported Media Type")
		STATUS_CODE(416, "Requested Range Not Satisfiable")
		STATUS_CODE(417, "Expectation Failed")
		STATUS_CODE(418, "I\"m a teapot")              // RFC 2324
		STATUS_CODE(422, "Unprocessable Entity")       // RFC 4918
		STATUS_CODE(423, "Locked")                     // RFC 4918
		STATUS_CODE(424, "Failed Dependency")          // RFC 4918
		STATUS_CODE(425, "Unordered Collection")       // RFC 4918
		STATUS_CODE(426, "Upgrade Required")           // RFC 2817
		STATUS_CODE(500, "Internal Server Error")
		STATUS_CODE(501, "Not Implemented")
		STATUS_CODE(502, "Bad Gateway")
		STATUS_CODE(503, "Service Unavailable")
		STATUS_CODE(504, "Gateway Time-out")
		STATUS_CODE(505, "HTTP Version not supported")
		STATUS_CODE(506, "Variant Also Negotiates")    // RFC 2295
		STATUS_CODE(507, "Insufficient Storage")       // RFC 4918
		STATUS_CODE(509, "Bandwidth Limit Exceeded")
		STATUS_CODE(510, "Not Extended")                // RFC 2774
		// }}}
}

HttpServer::~HttpServer()
{
}

void HttpServer::newConnection()
{
	Q_ASSERT(m_tcpServer);
	while (m_tcpServer->hasPendingConnections()) {
		HttpConnection *connection = new HttpConnection(m_tcpServer->nextPendingConnection(), this);
		// connect(connection, SIGNAL(newRequest(HttpRequest*, HttpResponse*)),
		//   this, SIGNAL(newRequest(HttpRequest*, HttpResponse*)));
		connect(connection, SIGNAL(newRequest(HttpRequest*, HttpResponse*)),
			this, SLOT(onRequest(HttpRequest*, HttpResponse*)));
	}
}

bool HttpServer::listen(const QHostAddress &address, quint16 port)
{
	m_tcpServer = new QTcpServer;

	connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
	return m_tcpServer->listen(address, port);
}

bool HttpServer::listen(quint16 port)
{
	return listen(QHostAddress::Any, port);
}

void HttpServer::setJsonData(const QString &flagId, const QJsonObject &jsonData)
{
    if (jsonData.isEmpty())
        return;

	QString plainText = QJsonDocument(jsonData).toJson();
	Q_ASSERT(!m_flagIdToJsonData.contains(flagId));
	m_flagIdToJsonData[flagId] = jsonData;
}

static QString getFlagIdFromUrl(const QUrl &url)
{
	QString urlString = url.toString(QUrl::DecodeReserved);
	int pos = urlString.lastIndexOf("params=");
	QString params = urlString.mid(pos + 7);

	//??? begin: 进行URL解码（decode）
	QByteArray text01 = QByteArray::fromPercentEncoding(params.toLatin1());
	QByteArray text02 = QByteArray::fromPercentEncoding(text01);
	params = QString(text02);
	// end

	QJsonParseError jsonError;
	QJsonDocument jsonDoucment = QJsonDocument::fromJson(params.toUtf8(), &jsonError);
	qDebug() << "getFlagIdFromUrl-jsonError=" << jsonError.errorString();
	if (jsonError.error == QJsonParseError::NoError)
	{
		if (jsonDoucment.isArray())
		{
			qDebug() << Q_FUNC_INFO << "error! json format error! json should object.";
		}
		if (jsonDoucment.isObject())
		{
			const QJsonObject jsonObject(jsonDoucment.object());
			QString debugText = QJsonDocument(jsonObject).toJson(); 

			return QString::number(jsonObject.value("flagId").toDouble(), 'f', 4);
		}
	}

    qDebug() << Q_FUNC_INFO << "urlString=" << urlString;
    //Q_ASSERT(!"http://127.0.0.1:6780/getResult参数错误");
	return QString::null;
}

void HttpServer::onRequest(HttpRequest* req, HttpResponse* resp)
{
    QString urlStr = req->url().toString();
    qDebug() << "HttpServer::onRequest-req->url=" << urlStr;
    // 屏蔽思源食堂和考勤打卡的数据请求
    if (urlStr.contains("http://syswincanteen.qitoon.com/app") || urlStr.contains("http://t100kaoqinapp.zhengtoon.com"))
    {
        return;
    }

#ifndef DAOTOON
    if ( (urlStr.contains("http://127.0.0.1:6780/pc/login") || urlStr.contains("http://localhost/pc/login"))
         || (urlStr.contains("127.0.0.1:6780/pc/logout") || urlStr.contains("localhost/pc/logout")) )
    {
        return;
    }
#endif

#ifdef DAOTOON
    // 为冬奥通增加的登录代码（接收到登录信息帮助用户登录通客户端）
    if (urlStr.startsWith("http://127.0.0.1:6780/pc/login") || urlStr.startsWith("http://localhost/pc/login"))
    {
        resp->setHeader("Content-Type", "text/plain");
        resp->setHeader("Access-Control-Allow-Origin", "*");
        resp->setStatus(200);

        QByteArray receivedText = QByteArray::fromPercentEncoding(urlStr.toLatin1());
        qDebug()<<"receivedText="<<receivedText;
        int pos = receivedText.indexOf("HTTP/");
        qDebug()<<"HTTP/-position="<<pos;
        QString loginParas = receivedText.left(pos).trimmed();
        qDebug()<<"loginParas="<<loginParas;

        QString str = QString("success");
        resp->end(str);
        static bool bInitLogin = false;
        if (!bInitLogin)
        {
			bInitLogin = true;
            emit receivedLoginParasFromWeb(loginParas);
        }
        return;
    }


    // 为冬奥通增加的退出代码（通过浏览器关闭冬奥通客户端）
    if (urlStr.contains("127.0.0.1:6780/pc/logout") || urlStr.contains("localhost/pc/logout"))
    {
        resp->setHeader("Content-Type", "text/plain");
        resp->setHeader("Access-Control-Allow-Origin", "*");
        resp->setStatus(200);

        QString str = QString("success");
        resp->end(str);
        qApp->quit();
        return;
    }
#endif

    const QString flagId = getFlagIdFromUrl(req->url());
    //Q_ASSERT(!flagId.isEmpty());
    if (!m_flagIdToJsonData.contains(flagId))
    {
        // 阻塞等待 acceptNavigationRequest-handleToonProtocolFinished 执行完
        qDebug() << "I'm wait handleToonProtocolFinished";
        /*
        QEventLoop eventLoop;
        QObject::connect(this, SIGNAL(handleToonProtocolFinished()), &eventLoop, SLOT(quit()));
        QTimer::singleShot(3000, &eventLoop, SLOT(quit()));
        eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
        */

        QObject::connect(this, SIGNAL(handleToonProtocolFinished()), this, SLOT(slotHandleToonProtocolFinished()));
        QTimer::singleShot(3000, this, SLOT(slotHandleToonProtocolFinished())); // 这个超时设置似乎没有起到什么作用?
        while (!m_toonProtocolHandleFinished)
        {
            QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
            qDebug()<<"while while while while while while while while while ......";
        }
        m_toonProtocolHandleFinished =  false;
    }

    //实现响应代码
    resp->setHeader("Content-Type", "application/json");
    resp->setHeader("Access-Control-Allow-Origin", "*");
    resp->setStatus(200);

    if (m_flagIdToJsonData.contains(flagId))
    {
        QJsonObject jsonData(m_flagIdToJsonData.take(flagId));
        QString str = QString(QJsonDocument(jsonData).toJson(QJsonDocument::Compact));
        resp->end(str);
    }
    else
    {
        QJsonObject jsonData;
        jsonData.insert("code", -999);
        QString str = QString(QJsonDocument(jsonData).toJson(QJsonDocument::Compact));
        resp->end(str);
    }
}

void HttpServer::slotHandleToonProtocolFinished()
{
    m_toonProtocolHandleFinished = true;
}
