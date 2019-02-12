#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include "ui_mytcpclient.h"
#include <QTcpSocket>
#include <QAbstractSocket>

class MyTcpClient : public QWidget, private Ui::MyTcpClient
{
    Q_OBJECT
public:
    explicit MyTcpClient(QWidget *parent = 0);
    void doConnect(const QString &address, int port);

private slots:
    void connected();
    void readyRead();
    void on_sendButton_clicked();

    void on_enterText_returnPressed();

private:
     QTcpSocket *m_socket;
     QByteArray m_message;
};
#endif // MYTCPCLIENT_H
