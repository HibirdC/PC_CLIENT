#ifndef TNCOMPANYEXTFIELDPARSER_H
#define TNCOMPANYEXTFIELDPARSER_H

#include <QObject>

class TNCompanyExtFieldParser : public QObject
{
	Q_OBJECT

public:
	explicit TNCompanyExtFieldParser(QObject *parent = Q_NULLPTR);
	explicit TNCompanyExtFieldParser(const QString &companyExt, QObject *parent = Q_NULLPTR);
	~TNCompanyExtFieldParser();

	void setCompanyExtContent(const QString &companyExt);

	//QString(strComID + "," + comFeedId + "," + comName + "," + comIntroduction + "," + logo + "," + comAddr + "," + comTel + "," + comEmail)
	QString getCompanyId() const;
	QString getCompanyFeedId() const;
	QString getCompanyName() const;
	QString getCompanyIntroduction() const;

	QString getCompanyLogoUrl() const;
	QString getCompanycomAddr() const;
	QString getCompanycomTel() const;
	QString getCompanycomEmail() const;

private:
	enum FieldNo
	{
		InValid = -1,

		ComID = 0,
		ComFeedId,
		ComName,
		ComIntroduction,
		ComLogo,
		ComAddr,
		ComTel,
		ComEmail,

		FieldCount = 8
	};

	QString m_fields[FieldCount];

	void parser(const QString &companyExt);
};

#endif // TNCOMPANYEXTFIELDPARSER_H

