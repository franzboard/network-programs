#include "lauflichtclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LauflichtClient w;
    w.show();

    return a.exec();
}
