#include "clientwindow.h"
#include "ui_clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));

}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::returnPressed()
{
    ui->lineEdit->clear();
}
