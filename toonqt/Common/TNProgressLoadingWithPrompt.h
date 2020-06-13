#ifndef TNPROGRESSLOADINGWITHPROMPT_H
#define TNPROGRESSLOADINGWITHPROMPT_H

#include <QDialog>
#include <QTimer>

#include "common_global.h"
class QLabel;

class COMMON_EXPORT TNProgressLoadingWithPrompt : public QDialog
{
	Q_OBJECT

public:
	explicit TNProgressLoadingWithPrompt(QWidget *parent = 0);
	~TNProgressLoadingWithPrompt();

    void setText(const QString &strPrompt);
    void showLoding(int maxMillSec = -1);
    void showComplete(int maxMillSec = -1);

public slots:
	void stop();

private:
	QMovie*		m_loadMovie;
    QLabel     *m_textLabel;
	QTimer*     m_timer;
};

#endif //TNPROGRESSLOADING_H