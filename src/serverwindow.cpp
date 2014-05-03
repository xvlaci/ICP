#include "serverwindow.h"
#include "ui_serverwindow.h"

ServerWindow::ServerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWindow),
    server_thread(new ServerThread(this))
{
    ui->setupUi(this);
    server_thread->name = "bludiste2014-server";
    server_thread->start();
    ui->textBrowser->append("Server started on port 2345");

}

ServerWindow::~ServerWindow()
{
    //server_thread->terminate();
    delete ui;
}

void ServerWindow::closeEvent(QCloseEvent *close)
{
    ui->textBrowser->append("Closing server");
    server_thread->terminate();
}

ServerThread::ServerThread(QWidget *parent)
{

}

void ServerThread::run()
{
    try
    {
      // We need to create a server object to accept incoming client connections.
      boost::asio::io_service io_service;

      // The io_service object provides I/O services, such as sockets,
      // that the server object will use.
      tcp_server server(io_service, 2345);

      // Run the io_service object to perform asynchronous operations.
      io_service.run();
    }
    catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
}
