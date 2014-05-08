#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serverwindow.h"
#include "clientwindow.h"

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
