/**
@author Martin Vlacil - xvlaci00@stud.fit.vutbr.cz
@author Jan Sedo      - xsedoj00@stud.fit.vutbr.cz
*/


#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QMessageBox>

#include "client.h"

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = 0);
    ~ClientWindow();

private:
    Ui::ClientWindow *ui;
    client *my_client;
    boost::asio::io_service io_service;
    QGraphicsScene *scene;

    std::string server;
    std::string port;

    void repaint(std::string board_state);
    void start_connection();



private slots:
    void returnPressed();
    void on_connectButton_clicked();




    void on_disconnectButton_clicked();


signals:
    void sendmaps(std::string m);


};

#endif // CLIENTWINDOW_H
