/**
@author Martin Vlacil - xvlaci00@stud.fit.vutbr.cz
@author Jan Sedo      - xsedoj00@stud.fit.vutbr.cz
*/


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
    //b->printMap();

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

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
      return a.exec();
}


