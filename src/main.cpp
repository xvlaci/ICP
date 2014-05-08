#include "mainwindow.h"
#include <QApplication>

#include "controller.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Controller *cont = new Controller();

    maze_map maze = cont->load("zkusebni_mapa");


    Board * b = new Board(maze.width,maze.height, maze.maze);
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
    cont->save("bla.txt");



    /*b->player_start_pos[0] = cont->move(b->player_start_pos[0]);
    cont->turn(b->player_start_pos[0], LEFT);

    //std::cout << abs(-2 % 4);
    */
    return a.exec();
}
