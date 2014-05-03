#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "serverwindow.h"

#include "server.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server_thread = new ServerThread(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    //server_window = new ServerWindow(this);
    server_thread->start();
    ui->label->setText("server started");

    //server_window->show();
}


ServerThread::ServerThread(QObject *parent)
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
      tcp_server server(io_service);

      // Run the io_service object to perform asynchronous operations.
      io_service.run();
    }
    catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
}
