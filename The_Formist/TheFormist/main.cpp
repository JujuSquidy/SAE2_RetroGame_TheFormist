#include "gui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game * g = new Game;
    GUI w(g);
    return a.exec();
}
