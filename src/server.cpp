#include "server.h"

void tcp_connection::start()
{

    m_message = make_daytime_string();
    boost::asio::async_write(socket_, boost::asio::buffer(m_message),
        boost::bind(&tcp_connection::handle_write, shared_from_this(),
          boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

void tcp_connection::handle_write(const boost::system::error_code &, size_t)
{

}

std::string make_daytime_string()
{
    std::string string;
    string = "ahoj";
    return string;

}


void tcp_server::start_accept()
{
    // creates a socket
    tcp_connection::pointer new_connection =
      tcp_connection::create(acceptor_.get_io_service());

    // initiates an asynchronous accept operation
    // to wait for a new connection.
    acceptor_.async_accept(new_connection->socket(),
        boost::bind(&tcp_server::handle_accept, this, new_connection,
                    boost::asio::placeholders::error));
}

void tcp_server::handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code &error)
{
    if (!error)
    {
      new_connection->start();
    }

    // Call start_accept() to initiate the next accept operation.
    start_accept();

}
