#ifndef TNWEBENGINEPAGE_H
#define TNWEBENGINEPAGE_H

#include "ToonProtocol_global.h"
#include <QWebEnginePage>

class TOONPROTOCOL_EXPORT TNWebEnginePage : public QWebEnginePage
{
	Q_OBJECT

public:
	explicit TNWebEnginePage(QObject *parent = nullptr);
	~TNWebEnginePage();

protected:
	virtual bool acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame);

public:
    static void handleToonProtocol(const QString &url, const QMap<QString, QString> &extraArgs = QMap<QString, QString>());
};

#endif // TNWEBENGINEPAGE_H

