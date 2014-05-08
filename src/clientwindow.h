#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

#include <QWidget>

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


private slots:
    void returnPressed();



};

#endif // CLIENTWINDOW_H
