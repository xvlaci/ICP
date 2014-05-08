#include "clientwindow.h"
#include "ui_clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));

    boost::asio::io_service io_service;
    my_client = new client(io_service);
    my_client->client_connect();

    /*boost::asio::io_service io_service;
    client new_client(io_service);
    new_client.client_connect();
    boost::asio::write(new_client.socket(), boost::asio::buffer("ahoj", 4));
    char reply[1024];
    size_t reply_length = boost::asio::read(new_client.socket(),
        boost::asio::buffer(reply, 4));
    //std::cout << "Reply is: ";
    std::cout.write(reply, reply_length);
    std::cout << std::endl;*/
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::returnPressed()
{
    QString qrequest = ui->lineEdit->text();
    std::string request = qrequest.toStdString();
    ui->lineEdit->clear();

    using boost::asio::ip::tcp;

    try
      {

        using namespace std; // For strlen.
        //size_t request_length = strlen(request);
        boost::asio::write(my_client->socket(), boost::asio::buffer(request, request.size()));

        char reply[1024];
        size_t reply_length = boost::asio::read(my_client->socket(),
            boost::asio::buffer(reply, request.size()));
        //std::cout << "Reply is: ";
        std::cout.write(reply, reply_length);
        std::cout << std::endl;
      }
      catch (std::exception& e)
      {
        std::cerr << "Exception: " << e.what() << "\n";
      }
}
