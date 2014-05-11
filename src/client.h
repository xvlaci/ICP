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

    void newFuckingThread(){
        void * i;
        int rc = pthread_create(&this->thread, NULL, client::JHWrapper, static_cast<void *>(i));

        if (rc){
            std::cout << "Error:unable to create thread," << rc << std::endl;
            exit(-1);
        }
        //pthread_exit(NULL);


    }

    void client_connect();

    tcp::socket& socket()
    {
      return socket_;
    }

    void send(std::string s);

private:
    static void * JHWrapper(void *self){
       client *that = static_cast<client*>(self);
       return that->newMapState(self);
    }


    boost::asio::io_service& io_service_;
    tcp::resolver resolver_;
    tcp::resolver::query query_;
    tcp::resolver::iterator iterator_;
    tcp::socket socket_;
    char client_id;
    pthread_t thread;
    void client_init();
    void * newMapState(void *threadid);
};

/*class tcp_server
{
public:
  tcp_server(boost::asio::io_service& io_service, short port)
    : io_service_(io_service),
      acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
  {
    init_counter();
    start_accept();
  }

private:
  void init_counter();
  void start_accept();

  void handle_accept(session* new_session,
      const boost::system::error_code& error);

  boost::asio::io_service& io_service_;
  tcp::acceptor acceptor_;
  int connection_counter;
};

#endif // CLIENT_H

tcp::resolver::query query(tcp::v4(), "127.0.0.1", "2345");
tcp::resolver::iterator iterator = resolver.resolve(query);

tcp::socket s(io_service);
boost::asio::connect(s, iterator);*/

#endif // CLIENT_H
