#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->update();
    this->setStyleSheet("background-color: #82CAFF;");
}

Dialog::~Dialog()
{
    delete ui;

}

void Dialog::paintEvent(QPaintEvent *event)
{
      // code for this exercise goes here
}
