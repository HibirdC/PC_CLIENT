#include "TNWebEnginePage.h"

#include <QMessageBox>
#include <QApplication>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#include "TNToonCommandManager.h"

TNWebEnginePage::TNWebEnginePage(QObject *parent) : QWebEnginePage(parent)
{

}

TNWebEnginePage::~TNWebEnginePage()
{

}

// If the function returns true, the navigation request is accepted and url is loaded.
bool TNWebEnginePage::acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame)
{
	if (isMainFrame)
	{
		QString resUrl = url.toString(QUrl::DecodeReserved);
        qDebug()<<"[ToonProtocol][TNWebEnginePage]resUrl="<<resUrl;
		if (resUrl.startsWith(QStringLiteral("toon://"), Qt::CaseInsensitive))
		{
			handleToonProtocol(resUrl);
			emit TNToonCommandManager::instance()->server()->handleToonProtocolFinished();
			return false;
		}
	}

    return QWebEnginePage::acceptNavigationRequest(url, type, isMainFrame);
}

void TNWebEnginePage::handleToonProtocol(const QString &url, const QMap<QString, QString> &extraArgs)
{
	if (url.isEmpty())
	{
        qInfo() << "[ToonProtocol][TNWebEnginePage]handleToonProtocol-url is null";
		return;
	}

	int pos1 = 6;
	int pos2 = url.indexOf('?');
	int pos3 = url.indexOf('=');

	QString modulePath = url.mid(pos1 + 1, pos2 - pos1 - 1);
	QString params = url.mid(pos3 + 1);

	QJsonParseError jsonError;
	QJsonDocument jsonDoucment = QJsonDocument::fromJson(params.toUtf8(), &jsonError);
    qInfo() << "handleToonProtocol-jsonError=" << jsonError.errorString();
	if (jsonError.error == QJsonParseError::NoError)
	{
		if (jsonDoucment.isArray())
		{
            qInfo() << "[ToonProtocol][TNWebEnginePage]error! json format error! json should object.";
		}
		if (jsonDoucment.isObject())
		{
            QJsonObject jsonObject(jsonDoucment.object());
            if (!extraArgs.isEmpty())
            {
                foreach (const QString &key, extraArgs.keys())
                {
                    jsonObject.insert(key, extraArgs.value(key));
                }
            }
			QString debugText = QJsonDocument(jsonObject).toJson();
            qDebug() << "[ToonProtocol][TNWebEnginePage]-debugText=" << debugText;
			TNToonCommandManager::instance()->executeToonCommand(modulePath, jsonObject);
		}
	}
}
