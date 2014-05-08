#include "server.h"

void tcp_connection::handle_write(const boost::system::error_code &error, size_t bytes_transferred)
{

}

void tcp_connection::handle_read(const boost::system::error_code &error, size_t bytes_transferred)
{

    /*std::string message(data_, bytes_transferred);

    std::cout << "Na server dorazilo:" << message << std::endl;

    if (message == "new")
    {
        message_ = "jsi tu novy!"
        std::cout << "tento klient je neznamy" << std::endl;
    }
    else
    {
        std::cout << "tento klient uz je znamy" << std::endl;
    }*/


}


std::string make_daytime_string()
{
      using namespace std; // For time_t, time and ctime;
      time_t now = time(0);
      return ctime(&now);
}
