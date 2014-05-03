#include "server.h"


void session::start()
{
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
                            boost::bind(&session::handle_read, this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}

std::string session::GetData()
{
    std::string string(data_);
    return string;
}

void session::handle_read(const boost::system::error_code &error, size_t bytes_transferred)
{
    if (!error)
    {
      boost::asio::async_write(socket_,
                               boost::asio::buffer(data_, bytes_transferred),
                               boost::bind(&session::handle_write, this,
                                           boost::asio::placeholders::error));
    }
    else
    {
      delete this;
    }

}

void session::handle_write(const boost::system::error_code &error)
{
    if (!error)
    {
      socket_.async_read_some(boost::asio::buffer(data_, max_length),
                              boost::bind(&session::handle_read, this,
                                          boost::asio::placeholders::error,
                                          boost::asio::placeholders::bytes_transferred));

      //std::cout << data_ << std::endl;

      /*
       * tohle nefunguje protoze ten buffer se roztahuje a zustavaji v nem zpravy z minule */

      std::string ahoj(data_);
      if (ahoj == "aa")
      {
          std::cout << "Server: hura" << std::endl;
      }
      else
      {
          std::cout << "Server: neni to aa" << std::endl;
      }

    }
    else
    {
      delete this;
    }

}


void tcp_server::start_accept()
{
    session* new_session = new session(io_service_);
    acceptor_.async_accept(new_session->socket(),
                           boost::bind(&tcp_server::handle_accept, this, new_session,
                                       boost::asio::placeholders::error));
}

void tcp_server::handle_accept(session *new_session, const boost::system::error_code &error)
{
    if (!error)
    {
        new_session->start();
    }
    else
    {
        delete new_session;
    }

    start_accept();
}
