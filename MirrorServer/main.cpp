#include <QCoreApplication>
#include "mirrorserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MirrorServer server;

    return a.exec();
}
