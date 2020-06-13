#ifndef TNCONVERTAMR_H
#define TNCONVERTAMR_H

#include <QObject>

class TNConvertAmr : public QObject
{
	Q_OBJECT

public:
	TNConvertAmr(QObject *parent);
	~TNConvertAmr();

	static bool convertAmrToWav(const QString& srcFile, const QString& wavFile);
};

#endif // TNCONVERTAMR_H
