#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>

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

private slots:
    void returnPressed();



};

#endif // CLIENTWINDOW_H
