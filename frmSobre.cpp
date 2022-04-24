#include "frmSobre.h"
#include "ui_frmSobre.h"

frmSobre::frmSobre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmSobre)
{
    ui->setupUi(this);
    setWindowTitle("Sobre o Sistema MyShack Windows");
    this->setFixedSize(this->size());
}

frmSobre::~frmSobre()
{
    delete ui;
}
