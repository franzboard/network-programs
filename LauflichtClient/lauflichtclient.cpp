#include "lauflichtclient.h"

LauflichtClient::LauflichtClient(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    udpSocket = new QUdpSocket(this);
 }

void LauflichtClient::on_speed_valueChanged(int value)
{
    lcdNumber->display(value);
}

void LauflichtClient::on_sendButton_clicked()
{
    quint16 portnumber = port->text().toUShort();
    QString hostname = host->text();
    int speedval = speed->value();

    if ((portnumber > 0) && (!hostname.isEmpty())) {
       QByteArray data;
       data.setNum(speedval);
       udpSocket->writeDatagram(data, address, portnumber);
    }
}

void LauflichtClient::on_host_editingFinished()
{
    QHostInfo info = QHostInfo::fromName(host->text());
    if (!info.addresses().isEmpty())
        address = info.addresses().first();
}
