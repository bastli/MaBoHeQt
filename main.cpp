#include "MaBoHeMain.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MaBoHeMain w;
    w.show();

    return a.exec();
}
