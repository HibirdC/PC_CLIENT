#ifndef TOONAPPLICATION_H
#define TOONAPPLICATION_H

#include <QObject>
#include <QException>
#include <QDebug>
#include "TNUtil.h"
#include "singleapplication.h"

class ToonApplication : public SingleApplication
{
    Q_OBJECT
public:
    ToonApplication(int &argc, char **argv) : SingleApplication(argc, argv) {
        connect(this,SIGNAL(newLocalConnection()),this,SLOT(showMainWidget()));
    }

    virtual bool notify(QObject *receiver, QEvent *event) {
        bool rc = true;
        try {
            rc = QApplication::notify(receiver, event);
        }
                catch (std::exception& e) {
                        qInfo() << "[Toon][ToonApplication]ToonApplication-notify(). errorInfo=" << e.what();
        }
        return rc;
    }
public slots:
    void showMainWidget(){
        if(TNUtil::getMainWidget()){
            QWidget* mainWidget = TNUtil::getMainWidget();
            if (!mainWidget->isMaximized())
                mainWidget->showNormal();
            else
                mainWidget->showMaximized();
            mainWidget->raise();
            mainWidget->activateWindow();
        }
    }
};

#endif // TOONAPPLICATION_H
