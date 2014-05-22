/**
@author Martin Vlacil - xvlaci00@stud.fit.vutbr.cz
@author Jan Sedo      - xsedoj00@stud.fit.vutbr.cz
*/


#include "clientwindow.h"
#include "ui_clientwindow.h"

#include "connectdialog.h"

#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>


ClientWindow::ClientWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    this->showMaximized();
    this->setWindowTitle("Bludiste2014 Client");
    ui->disconnectButton->setDisabled(true);
    ui->lineEdit->setDisabled(true);

    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::repaint(std::string board_state)
{
    scene->clear();
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
    for (int y = 0; y < height*20; y+=20)
    {
        for (int x = 0; x < width*20; x+=20)
        {
            c = stream.get();
            if ( c == 10 )
            {
                c = stream.get();
            }

            switch (c)
            {

            case '1':  /* draw wall */
                scene->addRect(x+5,y+5,15,15,QPen(Qt::gray),QBrush(Qt::gray));
                break;

            case '2': /* draw gate */
                scene->addLine(x+5,y+5,x+20,y+5,QPen(Qt::black));
                scene->addLine(x+5,y+13,x+20,y+13,QPen(Qt::black));
                scene->addLine(x+5,y+20,x+20,y+20,QPen(Qt::black));

                scene->addLine(x+5,y+5,x+5,y+20,QPen(Qt::black));
                scene->addLine(x+13,y+5,x+13,y+20,QPen(Qt::black));
                scene->addLine(x+20,y+5,x+20,y+20,QPen(Qt::black));
                break;

            case '3': /* draw key */
                scene->addEllipse(x+8,y+5,8,8,QPen(Qt::darkYellow));
                scene->addLine(x+12,y+13,x+12,y+20,QPen(Qt::darkYellow));
                scene->addLine(x+12,y+18,x+14,y+18,QPen(Qt::darkYellow));
                scene->addLine(x+12,y+20,x+15,y+20,QPen(Qt::darkYellow));
                break;

            case 'a': /* guard looking up */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+10,y+5));
                polygon.append(QPoint(x+15,y+20));
                polygon.append(QPoint (x+5,y+20));
                scene->addPolygon(polygon,QPen(Qt::red),QBrush(Qt::red));
                break;
            }

            case 'b': /* guard looking right */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+5,y+5));
                polygon.append(QPoint(x+20,y+10));
                polygon.append(QPoint (x+5,y+15));
                scene->addPolygon(polygon,QPen(Qt::red),QBrush(Qt::red));
                break;
            }
            case 'c': /* guard looking down */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+10,y+20));
                polygon.append(QPoint(x+15,y+5));
                polygon.append(QPoint (x+5,y+5));
                scene->addPolygon(polygon,QPen(Qt::red),QBrush(Qt::red));
                break;
            }
            case 'd': /* guard looking left */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+20,y+5));
                polygon.append(QPoint(x+5,y+10));
                polygon.append(QPoint (x+20,y+15));
                scene->addPolygon(polygon,QPen(Qt::red),QBrush(Qt::red));
                break;
            }

            case 'e': /* player 1 looking up */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+10,y+5));
                polygon.append(QPoint(x+15,y+20));
                polygon.append(QPoint (x+5,y+20));
                scene->addPolygon(polygon,QPen(Qt::green),QBrush(Qt::green));
                break;
            }
            case 'f': /* player 1 looking right */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+5,y+5));
                polygon.append(QPoint(x+20,y+10));
                polygon.append(QPoint (x+5,y+15));
                scene->addPolygon(polygon,QPen(Qt::green),QBrush(Qt::green));
                break;
            }
            case 'g': /* player 1 looking down */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+10,y+20));
                polygon.append(QPoint(x+15,y+5));
                polygon.append(QPoint (x+5,y+5));
                scene->addPolygon(polygon,QPen(Qt::green),QBrush(Qt::green));
                break;
            }
            case 'h': /* player 1 looking left */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+20,y+5));
                polygon.append(QPoint(x+5,y+10));
                polygon.append(QPoint (x+20,y+15));
                scene->addPolygon(polygon,QPen(Qt::green),QBrush(Qt::green));
                break;
            }

            case 'i': /* player 2 looking up */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+10,y+5));
                polygon.append(QPoint(x+15,y+20));
                polygon.append(QPoint (x+5,y+20));
                scene->addPolygon(polygon,QPen(Qt::darkMagenta),QBrush(Qt::darkMagenta));
                break;
            }
            case 'j': /* player 2 looking right */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+5,y+5));
                polygon.append(QPoint(x+20,y+10));
                polygon.append(QPoint (x+5,y+15));
                scene->addPolygon(polygon,QPen(Qt::darkMagenta),QBrush(Qt::darkMagenta));
                break;
            }
            case 'k': /* player 2 looking down */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+10,y+20));
                polygon.append(QPoint(x+15,y+5));
                polygon.append(QPoint (x+5,y+5));
                scene->addPolygon(polygon,QPen(Qt::darkMagenta),QBrush(Qt::darkMagenta));
                break;
            }
            case 'l': /* player 2 looking left */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+20,y+5));
                polygon.append(QPoint(x+5,y+10));
                polygon.append(QPoint (x+20,y+15));
                scene->addPolygon(polygon,QPen(Qt::darkMagenta),QBrush(Qt::darkMagenta));
                break;
            }

            case 'm': /* player 3 looking up */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+10,y+5));
                polygon.append(QPoint(x+15,y+20));
                polygon.append(QPoint (x+5,y+20));
                scene->addPolygon(polygon,QPen(Qt::darkYellow),QBrush(Qt::darkYellow));
                break;
            }
            case 'n': /* player 3 looking right */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+5,y+5));
                polygon.append(QPoint(x+20,y+10));
                polygon.append(QPoint (x+5,y+15));
                scene->addPolygon(polygon,QPen(Qt::darkYellow),QBrush(Qt::darkYellow));
                break;
            }
            case 'o': /* player 3 looking down */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+10,y+20));
                polygon.append(QPoint(x+15,y+5));
                polygon.append(QPoint (x+5,y+5));
                scene->addPolygon(polygon,QPen(Qt::darkYellow),QBrush(Qt::darkYellow));
                break;
            }
            case 'p': /* player 3 looking left */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+20,y+5));
                polygon.append(QPoint(x+5,y+10));
                polygon.append(QPoint (x+20,y+15));
                scene->addPolygon(polygon,QPen(Qt::darkYellow),QBrush(Qt::darkYellow));
                break;
            }

            case 'q': /* player 4 looking up */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+10,y+5));
                polygon.append(QPoint(x+15,y+20));
                polygon.append(QPoint (x+5,y+20));
                scene->addPolygon(polygon,QPen(Qt::darkGreen),QBrush(Qt::darkGreen));
                break;
            }
            case 'r': /* player 4 looking right */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+5,y+5));
                polygon.append(QPoint(x+20,y+10));
                polygon.append(QPoint (x+5,y+15));
                scene->addPolygon(polygon,QPen(Qt::darkGreen),QBrush(Qt::darkGreen));
                break;
            }
            case 's': /* player 4 looking down */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+10,y+20));
                polygon.append(QPoint(x+15,y+5));
                polygon.append(QPoint (x+5,y+5));
                scene->addPolygon(polygon,QPen(Qt::darkGreen),QBrush(Qt::darkGreen));
                break;
            }
            case 't': /* player 4 looking left */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+20,y+5));
                polygon.append(QPoint(x+5,y+10));
                polygon.append(QPoint (x+20,y+15));
                scene->addPolygon(polygon,QPen(Qt::darkGreen),QBrush(Qt::darkGreen));
                break;
            }








            }
        }

    }

}

void ClientWindow::start_connection()
{


    me = this;

    void *i;
    int rc = pthread_create(&this->thread, NULL, ClientWindow::JHWrapper, static_cast<void *>(i));

    if (rc){
        std::cout << "Error:unable to create thread," << rc << std::endl;
        exit(-1);
    }

    my_client = new client(io_service, server, port);

    if (my_client->is_connected == true)
    {
        ui->disconnectButton->setDisabled(false);
        ui->lineEdit->setDisabled(false);

        QMessageBox::information(
            this,
            tr("Vyber mapy"),
            tr("Connected. Tady by mel byt vyber mapy.") );




    }
    else
    {
        QMessageBox::critical(
            this,
            tr("Error"),
            tr("Could not connect to server.") );

    }




}

void ClientWindow::returnPressed()
{
    QString qrequest = ui->lineEdit->text();
    std::string request = qrequest.toStdString();
    ui->lineEdit->clear();

    my_client->send(request);
    if(request == "load"){
        std::cout << my_client->getLoads() << std::endl;
    }
    if(my_client->state_[0] != 'q')
    {
        repaint(my_client->state_);
    }

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

void ClientWindow::on_disconnectButton_clicked()
{
    scene->clear();
    ui->disconnectButton->setDisabled(true);
    ui->lineEdit->setDisabled(true);
}
