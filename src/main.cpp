#include "mainwindow.h"
#include <QApplication>

#include "server.h"
#include "board.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Board *b = new Board(4,4, "1111105113411121");

    b->printMap();

    std::cout << b->generateMsg();

    return a.exec();
}
