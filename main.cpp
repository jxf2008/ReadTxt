#include <QApplication>
#include "ReadTxt.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ReadTxt w;
    w.show();

    return a.exec();
}
