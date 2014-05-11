#include "client.h"



void client::client_connect()
{
    boost::asio::connect(socket_, iterator_);
}

void client::client_init()
{
    using boost::asio::ip::tcp;

    try
      {

        std::string message("new\n");
        this->client_connect();
        using namespace std;
        //std::cout << message << std::endl;
        boost::asio::write(this->socket(), boost::asio::buffer(message, message.size()));

        char reply[1024];
        size_t reply_length = boost::asio::read(this->socket(),
            boost::asio::buffer(reply, 1024));
        //std::cout << "Reply is: ";
        //std::cout << reply;
        //std::cout << std::endl;

        client_id = reply[0];


      }
      catch (std::exception& e)
      {
        std::cerr << "Exception: " << e.what() << "\n";
      }
}

void client::send(std::string s){
    using boost::asio::ip::tcp;

    try
      {


        std::string message;
        message += client_id;
        message += ":::";
        if(s == "go")
            s = "COMMAND:::GO:::";
        else if (s == "stop")
            s = "COMMAND:::STOP:::";
        else if (s == "left")
            s = "COMMAND:::LEFT:::";
        else if (s == "right")
            s = "COMMAND:::RIGHT:::";
        else if (s == "down")
            s = "COMMAND:::DOWN:::";
        else if (s == "up")
            s = "COMMAND:::UP:::";
        else if (s == "pick")
            s = "COMMAND:::PICK:::";
        else if (s == "open")
            s = "COMMAND:::OPEN:::";
        else if (s == "load")
            s = "LOAD:::";



                    ;
        message += s;
        message += "\n";

        this->client_connect();
        using namespace std;

        boost::asio::write(this->socket(), boost::asio::buffer(message, message.size()));

        char reply[1024];
        size_t reply_length = boost::asio::read(this->socket(),
            boost::asio::buffer(reply, 1024));
        //std::cout << "Reply is: ";
        //std::cout << reply;
        //std::cout << std::endl;
      }
      catch (std::exception& e)
      {
        std::cerr << "Exception: " << e.what() << "\n";
      }


}
