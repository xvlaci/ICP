/**
@author Martin Vlacil - xvlaci00@stud.fit.vutbr.cz
@author Jan Sedo      - xsedoj00@stud.fit.vutbr.cz
*/


#include "connectdialog.h"
#include "ui_connectdialog.h"

ConnectDialog::ConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);

    this->setWindowTitle("Connect");
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

std::string ConnectDialog::getServer()
{
    std::string srv = this->server.toStdString();
    return srv;
}

std::string ConnectDialog::getPort()
{
    std::string p = this->port.toStdString();
    return p;

}

void ConnectDialog::on_pushButtonConect_clicked()
{
    this->server = ui->lineEditServer->text();
    this->port = ui->lineEditPort->text();

    this->done(1);
}
