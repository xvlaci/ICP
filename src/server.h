/* http://www.bogotobogo.com/cplusplus/Boost/boost_AsynchIO_asio_tcpip_socket_server_client_timer_bind_handler_multithreading_synchronizing_network_D.php */

#ifndef SERVER_H
#define SERVER_H

#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string make_daytime_string();

class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
{

public:
  typedef boost::shared_ptr<tcp_connection> pointer;
  static pointer create(boost::asio::io_service& io_service)
  {
    return pointer(new tcp_connection(io_service));
  }
  tcp::socket& socket()
  {
    return socket_;
  }

  void start();

private:
  tcp_connection(boost::asio::io_service& io_service)
    : socket_(io_service)
  {
  }

  void handle_write(const boost::system::error_code& /*error*/,size_t /*bytes_transferred*/);

  tcp::socket socket_;
  std::string m_message;

};

class tcp_server
{
public:
  tcp_server(boost::asio::io_service& io_service)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), 2345))
  {
    // start_accept() creates a socket and
    // initiates an asynchronous accept operation
    // to wait for a new connection.
    start_accept();
  }

private:

  void start_accept();
  void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error);

  tcp::acceptor acceptor_;
};


#endif // SERVER_H
