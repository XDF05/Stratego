#include <QApplication>

#include "game.h"
#include "widget.h"

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);

    Widget w = Widget();
    w.show();
    return a.exec();
}
