#ifndef SELECTMAPDIALOG_H
#define SELECTMAPDIALOG_H

#include <QDialog>
#include <iostream>
#include <string>
#include <sstream>

namespace Ui {
class SelectMapDialog;
}

class SelectMapDialog : public QDialog
{
    Q_OBJECT

public:
    SelectMapDialog(QWidget *parent = 0);
    ~SelectMapDialog();

private:
    Ui::SelectMapDialog *ui;

    std::string time;
    std::string selected_map;

public slots:
    void fillMapDialog(std::string maps);
    std::string getMap();
    std::string getTime();


private slots:
    void on_selectButton_clicked();
};

#endif // SELECTMAPDIALOG_H
