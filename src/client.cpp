#include "client.h"



void client::client_connect()
{
    boost::asio::connect(socket_, iterator_);
}

void client::client_init()
{

}

void client::send(std::string s){
    using boost::asio::ip::tcp;

    try
      {
        this->client_connect();
        using namespace std; // For strlen.
        //size_t request_length = strlen(request);
        //if(my_client == NULL){
            //std::cout << this << std::endl;

        boost::asio::write(this->socket(), boost::asio::buffer(s, s.size()));

        char reply[1024];
        size_t reply_length = boost::asio::read(this->socket(),
            boost::asio::buffer(reply, s.size()));
        //std::cout << "Reply is: ";
        std::cout.write(reply, reply_length);
        std::cout << std::endl;
      }
      catch (std::exception& e)
      {
        std::cerr << "Exception: " << e.what() << "\n";
      }


}
