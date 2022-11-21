#include "include/UI/WatchUpApp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WatchUpApp w;
    w.show();
    return a.exec();
}
