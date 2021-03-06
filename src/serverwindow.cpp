/**
@author Martin Vlacil - xvlaci00@stud.fit.vutbr.cz
@author Jan Sedo      - xsedoj00@stud.fit.vutbr.cz
*/


#include "serverwindow.h"
#include "ui_serverwindow.h"

#include "server.h"

ServerWindow::ServerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWindow),
    server_thread(new ServerThread(this))
{
    ui->setupUi(this);
    server_thread->name = "bludiste2014-server";
    server_thread->start();
    ui->textBrowser->append("Server started on port 2345");
    this->setWindowTitle("Bludiste2014 Server");

}

ServerWindow::~ServerWindow()
{
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
        boost::asio::io_service io_service;

        tcp::endpoint listen_endpoint(tcp::v4(), 2345);

        server::Instance(io_service, listen_endpoint);

        //server s(io_service, listen_endpoint);

        io_service.run();
    }
    catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
}
