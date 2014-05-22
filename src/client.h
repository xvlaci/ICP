/**
@author Martin Vlacil - xvlaci00@stud.fit.vutbr.cz
@author Jan Sedo      - xsedoj00@stud.fit.vutbr.cz
*/


#ifndef CLIENT_H
#define CLIENT_H

#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <deque>
#include <boost/thread/thread.hpp>


//#include "client_ask.h"
#include <boost/thread.hpp>
#include <pthread.h>
#include <time.h>
#include <boost/date_time/posix_time/posix_time.hpp>

using boost::asio::ip::tcp;

class client
{
public:
    client(boost::asio::io_service& io_service, std::string ip, std::string port)
        : io_service_(io_service),
          resolver_(io_service),
          query_(tcp::v4(), ip, port),
          socket_(io_service)
    {
        iterator_ = resolver_.resolve(query_);
        client_init();
        state_[0] = 'q';

        boost::asio::async_connect(socket_, iterator_,
            boost::bind(&client::handle_connect, this,
              boost::asio::placeholders::error));

    }

    void handle_connect(const boost::system::error_code& error)
    {
      if (!error)
      {
          std::cout << "blaaaaaa" << std::endl;

          boost::asio::async_read(socket_,
            boost::asio::buffer(msg_t, 2550),
            boost::bind(&client::handle_read_header, this,
              boost::asio::placeholders::error));
      }
    }

    void handle_read_header(const boost::system::error_code& error)
    {
      if (!error)
      {
          std::cout << "bleeeeee" << std::endl;

        boost::asio::async_read(socket_,
            boost::asio::buffer(msg_t, 2550),
            boost::bind(&client::handle_read_header, this,
              boost::asio::placeholders::error));
      }
    }

    void client_connect();

    tcp::socket& socket()
    {
      return socket_;
    }

    std::string getState(){
        return this->state_;
    }

    void send(std::string s);
    char msg_t[2550];
    char state_[2550];
    char tmp_state[2550];
private:

    void client_init();

    boost::asio::io_service& io_service_;
    tcp::resolver resolver_;
    tcp::resolver::query query_;
    tcp::resolver::iterator iterator_;
    tcp::socket socket_;
    char client_id;

};

#endif // CLIENT_H
