#include "frmradioamadordadoscomcomentarios.h"
#include "ui_frmradioamadordadoscomcomentarios.h"
#include "conexaodb.h"

frmRadioamadorDadosComComentarios::frmRadioamadorDadosComComentarios(QWidget *parent, QString indicativo) :
    QDialog(parent),
    ui(new Ui::frmRadioamadorDadosComComentarios)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());

    ui->edtIndicativo->setText(indicativo);
    ui->edtIndicativo->setEnabled(false);
    conexaodb ConDB;
    ConDB.abrir();
    QSqlQuery q;
    q.prepare("SELECT qra, dmrid, nome, sobrenome, cidade, estado, pais, celular, email, comentario, criado, modificado FROM radioamadores WHERE indicativo = UPPER('"+indicativo+"');");
    q.exec();
    while (q.next()) {
        ui->edtQra->setText(q.value(0).toString().toUpper());
        ui->edtDmrId->setText(q.value(1).toString().toUpper());
        ui->edtNome->setText(q.value(2).toString().toUpper());
        ui->edtSobreNome->setText(q.value(3).toString().toUpper());
        ui->edtCidade->setText(q.value(4).toString().toUpper());
        ui->edtEstado->setText(q.value(5).toString().toUpper());
        ui->edtPais->setText(q.value(6).toString().toUpper());
        ui->edtCelular->setText(q.value(7).toString().toUpper());
        ui->edtEmail->setText(q.value(8).toString().toUpper());
        ui->edtComentarios->setText(q.value(9).toString().toLower());
        ui->edtCriado->setText(q.value(10).toString().toUpper());
        ui->edtModificado->setText(q.value(11).toString());
    }
    ConDB.fechar();
}

frmRadioamadorDadosComComentarios::~frmRadioamadorDadosComComentarios()
{
    delete ui;
}


void frmRadioamadorDadosComComentarios::on_btnSalvar_clicked()
{
    conexaodb ConDB;
    ConDB.abrir();
        QSqlQuery q;
        q.prepare("UPDATE radioamadores SET qra = UPPER('"+ui->edtQra->text()+"'), nome = UPPER('"+ui->edtNome->text()+"'), sobrenome = UPPER('"+ui->edtSobreNome->text()+"'), cidade = UPPER('"+ui->edtCidade->text()+"'), estado = UPPER('"+ui->edtEstado->text()+"'), pais = UPPER('"+ui->edtPais->text()+"'), celular = '"+ui->edtCelular->text()+"', email = LOWER('"+ui->edtEmail->text()+"'), comentario = '"+ui->edtComentarios->toMarkdown()+"', modificado = DATETIME('now','localtime') WHERE indicativo = UPPER('"+ui->edtIndicativo->text()+"');");
        q.exec();
    ConDB.fechar();
}

