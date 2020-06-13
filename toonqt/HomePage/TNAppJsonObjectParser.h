#ifndef TNAPPJSONOBJECTPARSER_H
#define TNAPPJSONOBJECTPARSER_H

#include <QObject>
#include <QJsonObject>

class TNAppJsonObjectParser : public QObject
{
    Q_OBJECT

public:
	explicit TNAppJsonObjectParser(QObject *parent = Q_NULLPTR);
    explicit TNAppJsonObjectParser(const QString &feedId, const QJsonObject &json, QObject *parent = Q_NULLPTR);
	~TNAppJsonObjectParser();

    void setJsonObject(const QString &feedId, const QJsonObject &json);

	QString getAppId() const;
    QString getAppRegisterId() const;

	QString getFeedId() const;
	int getPubStatus() const;
	int getRegisterType() const;
	int getLinkType() const;	
	int getSubLinkType() const;

	QString getFrame() const;

	QString getAppName() const;
	QString getAppIconUrl() const;
	QString getAppLinkUrl() const;

	bool isMyself() const;
	bool isFriend() const;
	bool isGeneralLink() const;
	void reParser(QString &appLinkUrl) const;

    bool showInHomePage() const;

private:
	QJsonObject m_jsonObject;

	QString m_appId;
    QString m_appRegisterId;

    QString m_feedId; //应用拥有者的feedId
	int m_pubStatus; //公开状态 0:只自己可见  1:全公开 2:自己及好友可见
	int m_registerType; //注册类型 1:应用(code)  2:链接
	int m_linkType; // 链接类型 0：普通链接   1：群聊
	mutable int m_sublinkType; // 普通链接类型 0：超链接   1：名片

    void parser();
};

#endif // TNAPPJSONOBJECTPARSER_H

