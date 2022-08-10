#include "generatpr.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    generatpr w;
    w.show();
    return a.exec();
}
