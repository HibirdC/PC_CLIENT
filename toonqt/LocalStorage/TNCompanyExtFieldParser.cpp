#include "TNCompanyExtFieldParser.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>

TNCompanyExtFieldParser::TNCompanyExtFieldParser(QObject *parent) : QObject(parent)
{

}

TNCompanyExtFieldParser::TNCompanyExtFieldParser(const QString &companyExt, QObject *parent) : QObject(parent)
{
	setCompanyExtContent(companyExt);
}

void TNCompanyExtFieldParser::setCompanyExtContent(const QString &companyExt)
{
	parser(companyExt);
}

TNCompanyExtFieldParser::~TNCompanyExtFieldParser()
{

}

void TNCompanyExtFieldParser::parser(const QString &companyExt)
{
	QStringList extFields = companyExt.split(QChar(','));

	Q_ASSERT(extFields.size() <= FieldCount);
	if (extFields.size() > FieldCount)
		qWarning() << "error! companyExt=" << companyExt;

	for (QStringList::size_type i = 0; i < extFields.size(); ++i)
	{
		m_fields[i] = extFields.at(i);
	}
}

QString TNCompanyExtFieldParser::getCompanyId() const
{
	return m_fields[ComID];
}

QString TNCompanyExtFieldParser::getCompanyFeedId() const
{
	return m_fields[ComFeedId];
}

QString TNCompanyExtFieldParser::getCompanyName() const
{
	return m_fields[ComName];
}

QString TNCompanyExtFieldParser::getCompanyIntroduction() const
{
	return m_fields[ComIntroduction];
}

QString TNCompanyExtFieldParser::getCompanyLogoUrl() const
{
	return m_fields[ComLogo];
}

QString TNCompanyExtFieldParser::getCompanycomAddr() const
{
	return m_fields[ComAddr];
}

QString TNCompanyExtFieldParser::getCompanycomTel() const
{
	return m_fields[ComTel];
}

QString TNCompanyExtFieldParser::getCompanycomEmail() const
{
	return m_fields[ComEmail];
}
