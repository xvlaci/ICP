#include "mainwindow.h"
#include <QApplication>

#include "server.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Controller *cont = new Controller();
    std::string maze =
            "111111111111111111111111000000000c00000003000110000000000000000000002100000001111110000000011000a0001111110000000e1100000001111110000f000110000000b000000000000011000000000000000000000111111111111111111111111";
    Board * b = new Board(23,9, maze);
    cont->setBoard(b);
    b->printMap();
    cont->moveGuard();
    b->printMap();
    cont->moveGuard();
    b->printMap();
    cont->moveGuard();
    b->printMap();
    cont->moveGuard();
    b->printMap();
    cont->moveGuard();
    b->printMap();
    cont->setBoard(b);
    b->printMap();
    cont->moveGuard();
    b->printMap();
    cont->moveGuard();
    b->printMap();
    cont->moveGuard();
    b->printMap();
    cont->moveGuard();
    b->printMap();
    cont->moveGuard();
    b->printMap();


    /*b->player_start_pos[0] = cont->move(b->player_start_pos[0]);
    cont->turn(b->player_start_pos[0], LEFT);

    //std::cout << abs(-2 % 4);
    */
    return a.exec();
}
