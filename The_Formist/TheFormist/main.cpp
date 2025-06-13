#include "gui.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/Pictures/icon.png"));

    GUI w(nullptr);
    w.show();

    return a.exec();
}
