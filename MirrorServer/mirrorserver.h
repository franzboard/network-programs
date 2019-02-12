#ifndef MIRRORSERVER_H
#define MIRRORSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>

class MirrorServer : public QObject
{
    Q_OBJECT
public:
    explicit MirrorServer(QObject *parent = 0);
    
signals:
    
public slots:
    void newConnection();
    void ServerRead();
    void ClientDisconnect();

private:
    QTcpServer *m_server;
    QTcpSocket *m_socket;
};

#endif // MIRRORSERVER_H
