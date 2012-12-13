#include <QApplication>
#include "QtBoats.h"

#include <cstdio>
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtBoats w;
    w.show();
    
    srand(time(NULL));

    return a.exec();
}
