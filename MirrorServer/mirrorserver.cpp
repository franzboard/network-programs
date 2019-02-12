#include <QByteArray>
#include "mirrorserver.h"

MirrorServer::MirrorServer(QObject *parent) :
    QObject(parent)
{
    m_server = new QTcpServer(this);
    connect(m_server, &QTcpServer::newConnection, this, &MirrorServer::newConnection);

    if(!m_server->listen(QHostAddress::Any, 5000))
        qDebug() << "Server could not start";
    else
        qDebug() << "Server started!";
}

void MirrorServer::newConnection()
{
    m_socket = m_server->nextPendingConnection();
    connect(m_socket, &QTcpSocket::readyRead, this, &MirrorServer::ServerRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &MirrorServer::ClientDisconnect);
}

void MirrorServer::ServerRead()
{
    QByteArray answer;
    while(m_socket->bytesAvailable() > 0) {
        QByteArray msg = m_socket->readAll();
        for (int n = qstrlen(msg)-1; n >= 0; n--)
            answer += msg.at(n);
        m_socket->write(answer);
    }
}

void MirrorServer::ClientDisconnect()
{
    m_socket->close();
}
