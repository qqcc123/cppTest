#include "QtEventLoop.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtEventLoop w;
    w.show();
    return a.exec();
}
