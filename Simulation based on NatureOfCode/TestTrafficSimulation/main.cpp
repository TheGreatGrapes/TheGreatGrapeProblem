#include "dialog.h"
#include <QApplication>

int windowSize = 250;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();

    return a.exec();
}
