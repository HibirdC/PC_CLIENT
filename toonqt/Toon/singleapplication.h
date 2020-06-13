#ifndef SINGLEAPPLICATION_H
#define SINGLEAPPLICATION_H
#include <QApplication>
#include <QObject>
class QLocalServer;


class SingleApplication : public QApplication
{
    Q_OBJECT
public:
    explicit SingleApplication(int &argc, char** argv);
    bool isRunning();
Q_SIGNALS:
    void newLocalConnection();
protected:
    void initLocalConnect();
    //创建服务端
    void newLocalServer();
    bool m_bRunning;                  // 是否已经有实例在运行
    QLocalServer *m_pLocalServer;      // 本地socket Server
    QString m_serverName;             // 服务名称
};

#endif // SINGLEAPPLICATION_H
