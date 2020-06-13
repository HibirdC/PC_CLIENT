#ifndef TNPROGRESSLOADING_H
#define TNPROGRESSLOADING_H

#include <QDialog>
#include <QTimer>

#include "common_global.h"

class COMMON_EXPORT TNProgressLoading : public QDialog
{
	Q_OBJECT

public:
	explicit TNProgressLoading(QWidget *parent = 0);
	~TNProgressLoading();

	void start(int maxMillSec = 3000);
	void stop();

private slots:
	void slotTimerOut();

private:
	QMovie*		m_loadMovie;
	QTimer*     m_timer;
};

#endif //TNPROGRESSLOADING_H