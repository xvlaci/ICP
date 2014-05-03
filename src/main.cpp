#include "mainwindow.h"
#include <QApplication>

#include "server.h"
#include "board.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Board *b = new Board(6,3, "123456789123456789");

    return a.exec();
}
