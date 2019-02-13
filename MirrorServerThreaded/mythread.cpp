#include "mythread.h"

MyThread::MyThread(qintptr ID, QObject *parent) :
    QThread(parent)
{
    this->m_socketDescriptor = ID;
}

void MyThread::run()
{
    qDebug() << " Thread started";
    m_socket = new QTcpSocket();

    // set the ID
    if(!m_socket->setSocketDescriptor(this->m_socketDescriptor))
    {
        // something's wrong, we just emit a signal
        emit error(m_socket->error());
        return;
    }

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    // We'll have multiple clients, we want to know which is which
    qDebug() << m_socketDescriptor << " Client connected";

    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies

    exec();
}

void MyThread::readyRead()
{   
    QByteArray msg = m_socket->readAll();
    qDebug() << m_socketDescriptor << " Data in: " << msg;

    // Mirror received string
    QByteArray answer;
    for (int n = qstrlen(msg)-1; n >= 0; n--)
        answer += msg.at(n);

    m_socket->write(answer);
}

void MyThread::disconnected()
{
    qDebug() << m_socketDescriptor << " Disconnected";
    m_socket->deleteLater();
    exit(0);
}

