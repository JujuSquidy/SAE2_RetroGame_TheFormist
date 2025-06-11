#include "gui.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/Pictures/icon.png"));
    Game * g = new Game;
    GUI w(g);
    w.show();
    return a.exec();
}
