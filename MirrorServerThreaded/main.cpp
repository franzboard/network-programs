// Multi threaded text mirroring server
// adapted from
// https://www.bogotobogo.com/Qt/Qt5_QTcpServer_Multithreaded_Client_Server.php

#include <QCoreApplication>
#include "myserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyServer server;
    server.startServer();

    return a.exec();
}

