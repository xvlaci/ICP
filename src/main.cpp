#include "mainwindow.h"
#include <QApplication>

#include "server.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Controller *cont = new Controller();

    Board * b = new Board(9,23, "111111111111111111111111000000000000000003000110000000000000000000002100000001111110000000011000400011111100000000110000000111111000050001100000000000000000000011000000000000000000000111111111111111111111111");
    cont->setBoard(b);

    b->printMap();

    cont->move(b->player_start_pos[0]);
    //std::cout << b->generateMsg();
    b->printMap();
    return a.exec();
}
