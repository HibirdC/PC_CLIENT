#ifndef TNStartloadingpage_H
#define TNStartloadingpage_H

#include <QDialog>
#include <QTimer>

#include "common_global.h"

class COMMON_EXPORT TNStartloadingpage : public QDialog
{
	Q_OBJECT

public:
	TNStartloadingpage(QWidget *parent = 0);
	~TNStartloadingpage();

	void start();
	void stop();

private slots:
	void slotTimerOut();

private:
	QMovie*		m_loadMovie;
	
signals:
	void TimeOutSignal();
};

#endif // TNStartloadingpage_H
