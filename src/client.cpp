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
            message += "COMMAND:::GO:::";
        else if (s == "stop")
            message += "COMMAND:::STOP:::";
        else if (s == "left")
            message += "COMMAND:::LEFT:::";
        else if (s == "right")
            message += "COMMAND:::RIGHT:::";
        else if (s == "down")
            message += "COMMAND:::DOWN:::";
        else if (s == "up")
            message += "COMMAND:::UP:::";
        else if (s == "pick")
            message += "COMMAND:::PICK:::";
        else if (s == "open")
            message += "COMMAND:::OPEN:::";
        else if (s.find("load") == 0){
            message += "LOAD:::";
            message += s[5];
        }
        else if (s.find("save") == 0){
            message += "SAVE:::";
            message += s.substr(5,s.length()-4);
        }

        message += "\n";

        std::cout << message << std::endl;

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
