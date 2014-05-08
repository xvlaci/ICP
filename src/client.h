#ifndef CLIENT_H
#define CLIENT_H

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class client
{
public:
    client(boost::asio::io_service& io_service)
        : io_service_(io_service),
          resolver_(io_service),
          query_(tcp::v4(), "127.0.0.1", "2345"),
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
    boost::asio::io_service& io_service_;
    tcp::resolver resolver_;
    tcp::resolver::query query_;
    tcp::resolver::iterator iterator_;
    tcp::socket socket_;
    char client_id;
    void client_init();
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
