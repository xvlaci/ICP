#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <pthread.h>
#include <time.h>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "controller.h"

using std::cout;
using std::endl;

Controller * cont;
Board * b;


void move(){
    cont->moveGuard();
    b->printMap();

}

void *PrintHello(void *threadid)
{
    while(true){
        sleep(1);
        move();

    }
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    using namespace boost;

    srand(time(NULL));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    cont = new Controller();

    maze_map maze = cont->load("zkusebni_mapa");


    b = new Board(maze.width,maze.height, maze.maze);
    cont->setBoard(b);

    pthread_t thread;
    int i;
    int rc = pthread_create(&thread, NULL, PrintHello, (void*) i);

    if (rc){
        cout << "Error:unable to create thread," << rc << endl;
        exit(-1);
    }

    //pthread_exit(NULL);





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


