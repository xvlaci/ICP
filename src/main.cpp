#include "mainwindow.h"
#include <QApplication>

#include <boost/asio.hpp>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>

#include "controller.h"

boost::asio::io_service io;


void move(Controller *cont, Board * b){
    cont->moveGuard();
    b->printMap();
}

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

    boost::asio::io_service io;

    boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));

    t.async_wait(boost::bind(move, cont, b));
    io.run();
    /*
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



    b->player_start_pos[0] = cont->move(b->player_start_pos[0]);
    cont->turn(b->player_start_pos[0], LEFT);

    //std::cout << abs(-2 % 4);
    */
    return a.exec();
}


