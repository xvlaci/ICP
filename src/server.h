#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "board.h"

using boost::asio::ip::tcp;

class session
{
public:
  session(boost::asio::io_service& io_service)
    : socket_(io_service)
  {
  }

  tcp::socket& socket()
  {
    return socket_;
  }

  void start();
  std::string GetData();

private:
  void handle_read(const boost::system::error_code& error,
      size_t bytes_transferred);

  void handle_write(const boost::system::error_code& error);

  tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];
};

class tcp_server
{
public:
  tcp_server(boost::asio::io_service& io_service, short port)
    : io_service_(io_service),
      acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
  {
    start_accept();
  }

private:
  void start_accept();

  void handle_accept(session* new_session,
      const boost::system::error_code& error);

  boost::asio::io_service& io_service_;
  tcp::acceptor acceptor_;
};
