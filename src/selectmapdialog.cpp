#include "selectmapdialog.h"
#include "ui_selectmapdialog.h"

SelectMapDialog::SelectMapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectMapDialog)
{
    ui->setupUi(this);
}

SelectMapDialog::~SelectMapDialog()
{
    delete ui;
}

void SelectMapDialog::fillMapDialog(std::string maps)
{
    std::string temp;

    std::stringstream stream(maps);
    std::getline(stream,temp);

    if (temp == "Loads")
        while (std::getline(stream,temp))
        {
            ui->listWidget->addItem(QString::fromStdString(temp));
        }

}

std::string SelectMapDialog::getMap()
{
    selected_map = ui->listWidget->currentItem()->text().toStdString();
    return selected_map;
}

std::string SelectMapDialog::getTime()
{
    time = ui->lineEdit->text().toStdString();
    return time;
}

void SelectMapDialog::on_selectButton_clicked()
{
    this->done(1);
}
