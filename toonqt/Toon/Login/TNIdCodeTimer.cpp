#include "TNIdCodeTimer.h"

#include <QDebug>

const int MaxCountSecond = 60;

TNIdCodeTimer::TNIdCodeTimer(QObject *parent) : QObject(parent), m_nCountSec(MaxCountSecond)
{
    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(slotOnTimer()));
}

TNIdCodeTimer::~TNIdCodeTimer()
{
}

void TNIdCodeTimer::start(int msec)
{
    m_pTimer->start(msec);
}

bool TNIdCodeTimer::isInitialState() const
{
    return m_nCountSec == MaxCountSecond;
}

void TNIdCodeTimer::resetTimer()
{
    if (m_pTimer->isActive())
    {
        m_pTimer->stop();
        m_nCountSec = MaxCountSecond;
    }
}

void TNIdCodeTimer::slotOnTimer()
{
    QString idCodeButtomText;
    if (m_nCountSec == 0)
    {
        idCodeButtomText = tr(QStringLiteral("重新发送").toUtf8().data());
        if (m_pTimer->isActive())
        {
            m_pTimer->stop();
            m_nCountSec = MaxCountSecond;
        }
    }
    else
    {
        idCodeButtomText = QString("%1s").arg(--m_nCountSec);
    }

    emit remainingTimeChanged(idCodeButtomText);
}
