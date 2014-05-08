#include "client.h"



void client::client_connect()
{
    boost::asio::connect(socket_, iterator_);
}

void client::client_init()
{

}
