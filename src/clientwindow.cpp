#include "clientwindow.h"
#include "ui_clientwindow.h"

#include "connectdialog.h"

#include <iostream>
#include <boost/lexical_cast.hpp>

ClientWindow::ClientWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    ui->disconnectButton->setDisabled(true);
    ui->lineEdit->setDisabled(true);

    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);


    std::string message("8\n5\n11111111\n10000001\n10011001\n10000001\n11111111\n");
    this->repaint(message);

}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void * ClientWindow::newMapState(void *threadid)
{
    my_client = new client(io_service, server, port);

}

void ClientWindow::repaint(std::string board_state)
{
    std::stringstream stream(board_state);
    std::string temp;

    int width;
    int height;

    try
    {
        std::getline(stream, temp);
        width = boost::lexical_cast<int>( temp );
        std::getline(stream, temp);
        height = boost::lexical_cast<int> ( temp );
    }
    catch( boost::bad_lexical_cast const& )
    {
        std::cout << "Error: input string was not valid" << std::endl;
    }

    char c;
    for (int y = 0; y < height*50; y+=50)
    {
        for (int x = 0; x < width*50; x+=50)
        {
            c = stream.get();
            if ( c == 10 )
            {
                c = stream.get();
            }

            if (c == '1')
            {
                scene->addRect(x+5,y+5,40,40,QPen(Qt::gray),QBrush(Qt::gray));
            }
        }

    }

}

void ClientWindow::start_connection()
{
    void * i;
    int rc = pthread_create(&this->thread, NULL, ClientWindow::JHWrapper, static_cast<void *>(i));

    if (rc){
        std::cout << "Error:unable to create thread," << rc << std::endl;
        exit(-1);
    }
    //pthread_exit(NULL);
    /* if connected */
    ui->disconnectButton->setDisabled(false);
    ui->lineEdit->setDisabled(false);

    /* else */
    /* popup ze se nepodarilo pripojit */

    /* todo: udelat funkcni disconnect tlacitko */


}

void ClientWindow::returnPressed()
{
    QString qrequest = ui->lineEdit->text();
    std::string request = qrequest.toStdString();
    ui->lineEdit->clear();

    scene->clear();

    my_client->send(request);
}

void ClientWindow::on_connectButton_clicked()
{
    ConnectDialog cDialog;
    cDialog.setModal(true);
    if(cDialog.exec() == 1)
    {

        this->server = cDialog.getServer();
        this->port = cDialog.getPort();

        this->start_connection();
    }
    else
    {
        std::cout << "nic nezadano" << std::endl;
    }



}
