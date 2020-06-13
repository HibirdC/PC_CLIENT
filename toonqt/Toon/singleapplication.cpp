#include <QLocalServer>
#include <QLocalSocket>
#include "singleapplication.h"

SingleApplication::SingleApplication(int &argc,char** argv) : QApplication(argc,argv)
  ,m_bRunning(false)
  ,m_pLocalServer(NULL)
  ,m_serverName("toon_pc_local")
{
    initLocalConnect();
}

void SingleApplication::initLocalConnect()
{
    m_bRunning = false;
    QLocalSocket socket;
    socket.connectToServer(m_serverName);
    if(socket.waitForConnected(1000))
    {
        m_bRunning = true;
        return;
    }
    //连接不上服务器，就创建一个
    newLocalServer();
}

bool SingleApplication::isRunning()
{
    return m_bRunning;
}

void SingleApplication::newLocalServer()
{
    m_pLocalServer = new QLocalServer(this);
    connect(m_pLocalServer, SIGNAL(newConnection()), this, SIGNAL(newLocalConnection()));
    if(!m_pLocalServer->listen(m_serverName)){
        // 此时监听失败，可能是程序崩溃时,残留进程服务导致的,移除之
        if(m_pLocalServer->serverError() == QAbstractSocket::AddressInUseError){
            QLocalServer::removeServer(m_serverName);
            m_pLocalServer->listen(m_serverName);
        }else{
            qInfo() <<"[Toon] [SignleApplication] newLocalServer error code:" << m_pLocalServer->serverError()
                    << " errorString:" << m_pLocalServer->errorString();
        }
    }
}
