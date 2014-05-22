/**
@author Martin Vlacil - xvlaci00@stud.fit.vutbr.cz
@author Jan Sedo      - xsedoj00@stud.fit.vutbr.cz
*/


#include "mainwindow.h"
#include "server.h"

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

    std::cout << "Welcome to bludiste 2014 cli version." << std::endl <<
                 "You have following options:" << std::endl <<
                 "Insert \"1\" to start bludiste2014 server" << std::endl <<
                 "Insert \"2\" to start bludiste2014 client" << std::endl << std::endl;

    std::string choice;

    getline(std::cin,choice);

    if (choice == "1")
    {
        std::cout << std::endl << "Insert port you want to start server on:" << std::endl;

        int port;

        try
        {
            getline(std::cin, choice);
            port = boost::lexical_cast<int>( choice );
        }
        catch( boost::bad_lexical_cast const& )
        {
            std::cout << "Error: input string was not valid" << std::endl;
        }

        std::cout << std::endl << "Trying to start server on port " << port << "..." << std::endl;

        try
        {
            boost::asio::io_service io_service;
            tcp::endpoint listen_endpoint(tcp::v4(), port);
            server::Instance(io_service, listen_endpoint);
            io_service.run();
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }


    }


    else if (choice == "2")
        std::cout << "You have selected client." << std::endl;



}


