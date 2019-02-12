#include "mytcpclient.h"
#include <QMessageBox>

MyTcpClient::MyTcpClient(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
}

void MyTcpClient::on_sendButton_clicked()
{
    QString hostaddr = enterHost->text();
    int port = enterPort->text().toInt();
    m_message = enterText->text().toUtf8();
    doConnect(hostaddr, port);

}

void MyTcpClient::doConnect(const QString &address, int port)
{
    m_socket = new QTcpSocket(this);
    connect(m_socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(m_socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

    m_socket->connectToHost(address, port);
    if(!m_socket->waitForConnected(5000))
        QMessageBox::critical(nullptr, "Error", "Connect failed");
}

void MyTcpClient::connected()
{
    m_socket->write(m_message);
}

void MyTcpClient::readyRead()
{
    answerLabel->setText(m_socket->readAll());
    // m_socket->disconnect();
}

void MyTcpClient::on_enterText_returnPressed()
{
    on_sendButton_clicked();
}
