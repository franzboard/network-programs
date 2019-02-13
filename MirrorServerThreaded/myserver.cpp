#include "myserver.h"
#include "mythread.h"

MyServer::MyServer(QObject *parent) :
    QTcpServer(parent)
{
}

void MyServer::startServer()
{
    int port = 5000;

    if(!this->listen(QHostAddress::Any,port))
        qDebug() << "Could not start server";
    else
        qDebug() << "Listening to port " << port << "...";
}

void MyServer::incomingConnection(qintptr m_socketDescriptor)
{
    qDebug() << m_socketDescriptor << " Connecting...";

    MyThread *thread = new MyThread(m_socketDescriptor, this);

    // connect signal/slot
    // once a thread is not needed, it will be deleted later
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}

