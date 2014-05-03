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
