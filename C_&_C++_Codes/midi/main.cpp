#include "midi.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    midi w;
    w.show();

    return a.exec();
}
