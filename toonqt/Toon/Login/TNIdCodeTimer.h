#ifndef TNIdCodeTimer_H
#define TNIdCodeTimer_H

#include <QObject>
#include <QString>
#include <QTimer>

#include "LocalStorageCommon.h"

class TNIdCodeTimer : public QObject
{
    Q_OBJECT

public:
    explicit TNIdCodeTimer(QObject *parent=Q_NULLPTR);
    ~TNIdCodeTimer();

    void start(int msec = 1000);
    void resetTimer();
    bool isInitialState() const;

Q_SIGNALS:
    void remainingTimeChanged(const QString &timeText);

private slots:
    void slotOnTimer();

private:
    int m_nCountSec;
    QTimer *m_pTimer;
};

#endif // TNIdCodeTimer_H
