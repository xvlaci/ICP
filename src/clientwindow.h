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

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <pthread.h>
#include <time.h>
#include <boost/date_time/posix_time/posix_time.hpp>

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
    ClientWindow * me;
    ClientWindow * getMe(){
        return this->me;
    }

private:
    Ui::ClientWindow *ui;
    client *my_client;
    boost::asio::io_service io_service;
    QGraphicsScene *scene;

    std::string server;
    std::string port;

    void repaint(std::string board_state);
    void start_connection();
    pthread_t thread;
    void * repainter(void *threadid){
        //while(true){
          //  sleep(1);

         //   ClientWindow * he = ClientWindow::getMe();

           // client * cl = he->my_client;
            //std::string s = cl->getState();
            //std::cout << "Takze to fakt pada tady" << std::endl;
            //if(this->my_client->state_[0] != 'q'){
              //  std::cout << "Este jedna moznost" << std::endl;
            //}
                //repaint(this->my_client->state_);
            //std::cout << "Nebo taky ne?" << std::endl;
        //}
        pthread_exit(NULL);
    }

    static void * JHWrapper(void *self){
       ClientWindow *that = static_cast<ClientWindow*>(self);
       return that->repainter(self);
    }



private slots:
    void returnPressed();
    void on_connectButton_clicked();




    void on_disconnectButton_clicked();
};

#endif // CLIENTWINDOW_H
