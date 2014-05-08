#include "clientwindow.h"
#include "ui_clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));


    my_client = new client(io_service);
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

    my_client->send(request);
}
