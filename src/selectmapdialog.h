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

public slots:
    void fillMapDialog(std::string maps);


};

#endif // SELECTMAPDIALOG_H
