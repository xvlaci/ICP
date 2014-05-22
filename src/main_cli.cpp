/**
@author Martin Vlacil - xvlaci00@stud.fit.vutbr.cz
@author Jan Sedo      - xsedoj00@stud.fit.vutbr.cz
*/


#include "mainwindow.h"
#include "server.h"
#include "client.h"

#include <QApplication>

#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <pthread.h>
#include <time.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>

#include "controller.h"

using std::cout;
using std::endl;

Controller * cont;
Board * b;


void repaintBoard(std::string board_state)
{
    std::stringstream stream(board_state);
    std::string temp;

    int width;
    int height;

    try
    {
        std::getline(stream, temp);
        width = boost::lexical_cast<int>( temp );
        std::getline(stream, temp);
        height = boost::lexical_cast<int> ( temp );
    }
    catch( boost::bad_lexical_cast const& )
    {
        std::cout << "Error: input string was not valid" << std::endl;
    }

    char c;
    for (int y = 0; y < height*20; y+=20)
    {
        for (int x = 0; x < width*20; x+=20)
        {
            c = stream.get();
            if ( c == 10 )
            {
                c = stream.get();
            }

            switch (c)
            {

            }
        }
    }
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
    {
        std::cout << std::endl << "IP adress of server you want to connect to:" << std::endl;
        getline(std::cin, choice);
        std::string server(choice);

        std::cout << std::endl << "Port of server you want to connect to:" << std::endl;
        getline(std::cin, choice);
        std::string port(choice);

        boost::asio::io_service io_service;
        client *my_client;
        my_client = new client(io_service, server, port);

        if (my_client->is_connected == false)
        {
            std::cout << "Connection failed." << std::endl << std::endl;
            return 0;
        }
        else
        {
            std::cout << "Connected to server." << std::endl << std::endl;
        }

        my_client->send("load");

        std::cout << "Choose from offered maps: " << std::endl;
        std::string list_of_maps = my_client->getLoads();

        std::cout << list_of_maps << std::endl << std::endl;

        getline(std::cin,choice);
        std::string mapname(choice);

        std::cout << std::endl << "Choose time of one round: " << std::endl;
        getline(std::cin,choice);
        std::string roundtime(choice);

        std::string settings = "mapp ";
        settings += roundtime;
        settings += " ";
        settings += mapname;

        my_client->send(settings);

        while (getline(std::cin, choice))
        {
            my_client->send(choice);
            if (choice == "")
                repaintBoard(my_client->getState());
        }

    }



}


