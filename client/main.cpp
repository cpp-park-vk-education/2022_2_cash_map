#include "include/UI/WatchUpApp.h"

#include <QApplication>

#include "include/UI/Base.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Base w;
    w.show();
    return a.exec();
}
