#ifndef LAUFLICHTCLIENT_H
#define LAUFLICHTCLIENT_H

#include "ui_lauflichtclient.h"
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>
#include <QDebug>
#include <QHostInfo>

class LauflichtClient : public QWidget, private Ui::LauflichtClient
{
    Q_OBJECT

public:
    explicit LauflichtClient(QWidget *parent = nullptr);
private slots:
    void on_speed_valueChanged(int value);
    void on_sendButton_clicked();
    void on_host_editingFinished();

private:
    QUdpSocket* udpSocket;
    QHostAddress address;
    void sendValue();
};

#endif // LAUFLICHTCLIENT_H
