#ifndef CLIENT_H
#define CLIENT_H

#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
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
    }

    void client_connect();

    tcp::socket& socket()
    {
      return socket_;
    }

    void send(std::string s);

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
