/**
@author Martin Vlacil - xvlaci00@stud.fit.vutbr.cz
@author Jan Sedo      - xsedoj00@stud.fit.vutbr.cz
*/


#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QWidget>
#include <QThread>

class ServerThread : public QThread
{
    Q_OBJECT

public:
    explicit ServerThread(QWidget *parent = 0);
    void run();
    QString name;

};

namespace Ui {
class ServerWindow;
}

class ServerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = 0);
    ~ServerWindow();

private:
    void closeEvent(QCloseEvent *close);
    Ui::ServerWindow *ui;
    ServerThread *server_thread;
};

#endif // SERVERWINDOW_H
