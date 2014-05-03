#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serverwindow.h"
#include "clientwindow.h"

#include "server.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_StartServerButton_clicked()
{
    ServerWindow *window = new ServerWindow;
    window->show();
}

void MainWindow::on_StartClientButton_clicked()
{
    ClientWindow *client_window = new ClientWindow;
    client_window->show();

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
