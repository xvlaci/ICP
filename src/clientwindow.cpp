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
    ui->disconnectButton->setDisabled(true);
    ui->lineEdit->setDisabled(true);

    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    /* zkusebni mapa - v normalnim pripade prijde od serveru */
    std::string string;

    std::ifstream f;
    f.open("zkusebni_mapa");
    if (f.is_open()) {
        getline( f, string, '\0');
    }
    f.close();

    this->repaint(string);

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

            if (c == '1') /* draw walls */
            {
                scene->addRect(x+5,y+5,15,15,QPen(Qt::gray),QBrush(Qt::gray));
            }
            if (c == '2') /* draw gates */
            {
                scene->addLine(x+5,y+5,x+20,y+5,QPen(Qt::black));
                scene->addLine(x+5,y+13,x+20,y+13,QPen(Qt::black));
                scene->addLine(x+5,y+20,x+20,y+20,QPen(Qt::black));

                scene->addLine(x+5,y+5,x+5,y+20,QPen(Qt::black));
                scene->addLine(x+13,y+5,x+13,y+20,QPen(Qt::black));
                scene->addLine(x+20,y+5,x+20,y+20,QPen(Qt::black));
            }
            if (c == '3') /* draw keys */
            {
                scene->addEllipse(x+8,y+5,8,8,QPen(Qt::darkYellow));
                scene->addLine(x+12,y+13,x+12,y+20,QPen(Qt::darkYellow));
                scene->addLine(x+12,y+18,x+14,y+18,QPen(Qt::darkYellow));
                scene->addLine(x+12,y+20,x+15,y+20,QPen(Qt::darkYellow));
            }
            if (c == 'a') /* guard looking up */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+10,y+5));
                polygon.append(QPoint(x+15,y+20));
                polygon.append(QPoint (x+5,y+20));
                scene->addPolygon(polygon,QPen(Qt::red),QBrush(Qt::red));

            }
            if (c == 'b') /* guard looking right */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+5,y+5));
                polygon.append(QPoint(x+20,y+10));
                polygon.append(QPoint (x+5,y+15));
                scene->addPolygon(polygon,QPen(Qt::red),QBrush(Qt::red));

            }
            if (c == 'c') /* guard looking down */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+10,y+20));
                polygon.append(QPoint(x+15,y+5));
                polygon.append(QPoint (x+5,y+5));
                scene->addPolygon(polygon,QPen(Qt::red),QBrush(Qt::red));

            }
            if (c == 'd') /* guard looking left */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+20,y+5));
                polygon.append(QPoint(x+5,y+10));
                polygon.append(QPoint (x+20,y+15));
                scene->addPolygon(polygon,QPen(Qt::red),QBrush(Qt::red));

            }
            if (c == 'e') /* player looking up */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+10,y+5));
                polygon.append(QPoint(x+15,y+20));
                polygon.append(QPoint (x+5,y+20));
                scene->addPolygon(polygon,QPen(Qt::red),QBrush(Qt::green));

            }
            if (c == 'f') /* player looking right */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+5,y+5));
                polygon.append(QPoint(x+20,y+10));
                polygon.append(QPoint (x+5,y+15));
                scene->addPolygon(polygon,QPen(Qt::red),QBrush(Qt::green));

            }
            if (c == 'g') /* player looking down */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+10,y+20));
                polygon.append(QPoint(x+15,y+5));
                polygon.append(QPoint (x+5,y+5));
                scene->addPolygon(polygon,QPen(Qt::red),QBrush(Qt::green));

            }
            if (c == 'h') /* player looking left */
            {
                QPolygon polygon;
                polygon.append(QPoint(x+20,y+5));
                polygon.append(QPoint(x+5,y+10));
                polygon.append(QPoint (x+20,y+15));
                scene->addPolygon(polygon,QPen(Qt::red),QBrush(Qt::green));

            }
        }

    }

}

void ClientWindow::start_connection()
{
    my_client = new client(io_service, server, port);

    me = this;

    void *i;
    int rc = pthread_create(&this->thread, NULL, ClientWindow::JHWrapper, static_cast<void *>(i));

    if (rc){
        std::cout << "Error:unable to create thread," << rc << std::endl;
        exit(-1);
    }

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

    my_client->send(request);
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
