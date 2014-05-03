#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

//#include "serverwindow.h"

class ServerThread : public QThread
{
    Q_OBJECT

public:
    explicit ServerThread(QObject *parent = 0);
    void run();

};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    ServerThread *server_thread;

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    //ServerWindow *server_window;

};

#endif // MAINWINDOW_H
