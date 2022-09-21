#include "testxml.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestXml w;
    w.show();

    return a.exec();
}
