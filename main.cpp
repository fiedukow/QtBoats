#include <QApplication>
#include "QtBoats.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtBoats w;
    w.show();
    
    return a.exec();
}
