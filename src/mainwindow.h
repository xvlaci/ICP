#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_StartServerButton_clicked();
    void on_StartClientButton_clicked();

private:
    Ui::MainWindow *ui;
    //ServerWindow *server_window;

};

#endif // MAINWINDOW_H
