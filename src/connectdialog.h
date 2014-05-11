#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = 0);
    ~ConnectDialog();

    std::string getServer();
    std::string getPort();

private:
    Ui::ConnectDialog *ui;

    QString server;
    QString port;

signals:
    void sigconnect();

private slots:
    void on_pushButtonConect_clicked();
};

#endif // CONNECTDIALOG_H
