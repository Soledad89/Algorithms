#include "qframe.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFrame w;
    w.show();

    return a.exec();
}
