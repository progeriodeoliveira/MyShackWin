#include "frmcoordenadorescadastro.h"
#include "ui_frmcoordenadorescadastro.h"
#include "conexaodb.h"
#include "radioidnet.h"
#include "QMessageBox"


frmCoordenadoresCadastro::frmCoordenadoresCadastro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmCoordenadoresCadastro)
{
    ui->setupUi(this);
    listarCoordenadores();
    ui->btnGravar->setEnabled(false);
    ui->btnRemover->setEnabled(false);
    ui->btnInserir->setEnabled(true);
    ui->edtIndicativo->setFocus();
    this->setWindowTitle("Cadastro de Coordenadores");
    this->setFixedSize(this->size());
}

frmCoordenadoresCadastro::~frmCoordenadoresCadastro()
{
    delete ui;
}

void frmCoordenadoresCadastro::zerarCampos(){
    ui->edtIndicativo->clear();
    ui->edtDMRId->clear();
    ui->edtQra->clear();
    ui->edtNome->clear();
    ui->edtSobrenome->clear();
    ui->edtEmail->clear();
    ui->edtCelular->clear();
    ui->edtCidade->clear();
    ui->edtEstado->clear();
    ui->edtPais->clear();
}

void frmCoordenadoresCadastro::pesquisaIndicativoDMR(){
    radioidnet dmr;
    QString indicativo = ui->edtIndicativo->text().toUpper();
    QStringList dados = dmr.obterDados(indicativo);
    //dados << 0 QString::number(id.toInteger()) << 1 QString::number(radio_id.toInteger()) << 2 surname.toString().toUpper() << 3 name.toString().toUpper() << 4 fname.toString().toUpper() << 5 city.toString().toUpper() << 6 state.toString().toUpper() << 7 country.toString().toUpper() << 8 remarks.toString().toUpper();

    if (ui->edtIndicativo->text().isEmpty()){
        QMessageBox::about(this,"Preencha o Indicativo","Você pode preencher o Indicativo que os dados serão localizados!");
    }else if (dados.size() > 0){
        ui->edtDMRId->setText(dados[0]);
        ui->edtQra->setText(dados[2]);
        ui->edtNome->setText(dados[3]);
        ui->edtSobrenome->setText(dados[4]);
        ui->edtCidade->setText(dados[5]);
        ui->edtEstado->setText(dados[6]);
        ui->edtPais->setText(dados[7]);
    }
}

void frmCoordenadoresCadastro::on_edtIndicativo_returnPressed()
{
    pesquisaIndicativoDMR();
}


void frmCoordenadoresCadastro::on_edtIndicativo_editingFinished()
{
    pesquisaIndicativoDMR();
}

void frmCoordenadoresCadastro::configurarCampos(){
    //id, indicativo, dmrid, qra, nome, sobrenome, email, celular, cidade, estado, pais, modificado, ativo, criado = 14 campos
    ui->edtId->setText(ui->twgCoordenadores->item(ui->twgCoordenadores->currentRow(),0)->text()); //indicativo
    ui->edtIndicativo->setText(ui->twgCoordenadores->item(ui->twgCoordenadores->currentRow(),1)->text()); //indicativo
    ui->edtDMRId->setText(ui->twgCoordenadores->item(ui->twgCoordenadores->currentRow(),2)->text()); //dmrid
    ui->edtQra->setText(ui->twgCoordenadores->item(ui->twgCoordenadores->currentRow(),3)->text()); //qra
    ui->edtNome->setText(ui->twgCoordenadores->item(ui->twgCoordenadores->currentRow(),4)->text()); //nome
    ui->edtSobrenome->setText(ui->twgCoordenadores->item(ui->twgCoordenadores->currentRow(),5)->text()); //sobrenome
    ui->edtEmail->setText(ui->twgCoordenadores->item(ui->twgCoordenadores->currentRow(),6)->text()); //email
    ui->edtCelular->setText(ui->twgCoordenadores->item(ui->twgCoordenadores->currentRow(),7)->text()); //celular
    ui->edtCidade->setText(ui->twgCoordenadores->item(ui->twgCoordenadores->currentRow(),8)->text()); //cidade
    ui->edtEstado->setText(ui->twgCoordenadores->item(ui->twgCoordenadores->currentRow(),9)->text()); //estado
    ui->edtPais->setText(ui->twgCoordenadores->item(ui->twgCoordenadores->currentRow(),10)->text()); //pais
    ui->edtModificado->setText(ui->twgCoordenadores->item(ui->twgCoordenadores->currentRow(),11)->text()); //modificado
    ui->edtCriado->setText(ui->twgCoordenadores->item(ui->twgCoordenadores->currentRow(),13)->text()); //criado
}

bool frmCoordenadoresCadastro::temCampoVazio(){
    if((ui->edtIndicativo->text().isEmpty()) or (ui->edtNome->text().isEmpty()) or (ui->edtSobrenome->text().isEmpty()) or (ui->edtQra->text().isEmpty()) or (ui->edtPais->text().isEmpty())){
        return true;
    }else{
        return false;
    }
}
void frmCoordenadoresCadastro::on_btnInserir_clicked()
{
    conexaodb ConDB;
    if(!ConDB.abrir()){
        QMessageBox::warning(this,"Erro!","Erro ao abrir o Banco de Dados!");
        //qDebug() << ConDB.abrir();
    }else{
        QString indicativo = ui->edtIndicativo->text().toUpper();
        QString dmrid = ui->edtDMRId->text();
        QString qra = ui->edtQra->text().toUpper();
        QString nome = ui->edtNome->text().toUpper();
        QString sobrenome = ui->edtSobrenome->text().toUpper();
        QString email = ui->edtEmail->text().toLower();
        QString celular = ui->edtCelular->text();
        QString cidade = ui->edtCidade->text().toUpper();
        QString estado = ui->edtEstado->text().toUpper();
        QString pais = ui->edtPais->text().toUpper();

        if (temCampoVazio()){
            QMessageBox::warning(this,"Prenchimento de dados","Por favor, preencha todos os campos!");
        } else {
            QSqlQuery queryInsert;
            queryInsert.prepare("INSERT INTO coordenadores(indicativo,dmrid,qra,nome,sobrenome,email,celular,cidade,estado,pais) VALUES('"+indicativo+"','"+dmrid+"','"+qra+"','"+nome+"','"+sobrenome+"','"+email+"','"+celular+"','"+cidade+"','"+estado+"','"+pais+"');");
            queryInsert.exec();
            ConDB.fechar();
            ui->edtIndicativo->clear();
            ui->edtDMRId->clear();
            ui->edtQra->clear();
            ui->edtNome->clear();
            ui->edtSobrenome->clear();
            ui->edtEmail->clear();
            ui->edtCelular->clear();
            ui->edtCidade->clear();
            ui->edtEstado->clear();
            ui->edtPais->clear();
            ui->edtIndicativo->setFocus();
            listarCoordenadores();
        }
    }

}

void frmCoordenadoresCadastro::listarCoordenadores(){
    ui->twgCoordenadores->clear();
    ui->twgCoordenadores->clearContents();
    ui->twgCoordenadores->model()->removeRows(0,ui->twgCoordenadores->rowCount());
    ui->twgCoordenadores->setShowGrid(false);
    conexaodb ConDB;
    ConDB.abrir();
        QSqlQuery q;

        q.exec("SELECT id, indicativo, dmrid, qra, nome, sobrenome, email, celular, cidade, estado, pais, modificado, ativo, criado FROM coordenadores;");        
        int cont=0;
        ui->twgCoordenadores->setColumnCount(14);
        //x ui->twgCoordenadores->setAlternatingRowColors(true);
        QStringList cabecalho={" id "," Indicativo "," dmrid "," QRA "," Nome "," Sobrenome "," E-Mail "," Celular "," Cidade "," Estado "," País "," Modificado "," ativo "," Criado "};
        ui->twgCoordenadores->setHorizontalHeaderLabels(cabecalho);
        ui->twgCoordenadores->horizontalHeader()->setVisible(false);
        while(q.next()){

            ui->twgCoordenadores->insertRow(cont);
            ui->twgCoordenadores->setItem(cont,0,new QTableWidgetItem(q.value(0).toString())); //id
            ui->twgCoordenadores->setItem(cont,1,new QTableWidgetItem(q.value(1).toString())); //indicativo
            ui->twgCoordenadores->setItem(cont,2,new QTableWidgetItem(q.value(2).toString())); //dmrid
            ui->twgCoordenadores->setItem(cont,3,new QTableWidgetItem(q.value(3).toString())); //qra
            ui->twgCoordenadores->setItem(cont,4,new QTableWidgetItem(q.value(4).toString())); //nome
            ui->twgCoordenadores->setItem(cont,5,new QTableWidgetItem(q.value(5).toString())); //sobrenome
            ui->twgCoordenadores->setItem(cont,6,new QTableWidgetItem(q.value(6).toString())); //e-mail
            ui->twgCoordenadores->setItem(cont,7,new QTableWidgetItem(q.value(7).toString())); //celular
            ui->twgCoordenadores->setItem(cont,8,new QTableWidgetItem(q.value(8).toString())); //cidade
            ui->twgCoordenadores->setItem(cont,9,new QTableWidgetItem(q.value(9).toString())); //estado
            ui->twgCoordenadores->setItem(cont,10,new QTableWidgetItem(q.value(10).toString())); //pais
            ui->twgCoordenadores->setItem(cont,11,new QTableWidgetItem(q.value(11).toString())); //modificado
            ui->twgCoordenadores->setItem(cont,12,new QTableWidgetItem(q.value(12).toString())); //ativo
            ui->twgCoordenadores->setItem(cont,13,new QTableWidgetItem(q.value(13).toString())); //criado

            ui->twgCoordenadores->setRowHeight(cont,20);
            cont++;
        }

        ui->twgCoordenadores->resizeColumnToContents(0);
        ui->twgCoordenadores->resizeColumnToContents(1);
        ui->twgCoordenadores->resizeColumnToContents(2);
        ui->twgCoordenadores->resizeColumnToContents(3);
        ui->twgCoordenadores->resizeColumnToContents(4);
        ui->twgCoordenadores->resizeColumnToContents(5);
        ui->twgCoordenadores->resizeColumnToContents(6);
        ui->twgCoordenadores->resizeColumnToContents(7);
        ui->twgCoordenadores->resizeColumnToContents(8);
        ui->twgCoordenadores->resizeColumnToContents(9);
        ui->twgCoordenadores->resizeColumnToContents(10);
        ui->twgCoordenadores->resizeColumnToContents(11);
        ui->twgCoordenadores->resizeColumnToContents(12);
        ui->twgCoordenadores->resizeColumnToContents(13);



        ui->twgCoordenadores->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->twgCoordenadores->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->twgCoordenadores->verticalHeader()->setVisible(false);
        //x ui->twgCoordenadores->setStyleSheet("QTableView {selection-background-color:blue}");
    ConDB.fechar();
}


void frmCoordenadoresCadastro::on_btnInserir_toggled(bool checked)
{

}


void frmCoordenadoresCadastro::on_pushButton_clicked()
{
    QSqlDatabase bancoDeDados=QSqlDatabase::addDatabase("QSQLITE");
    configuracoes config;
    QString banco=config.caminhoBancoDeDados();
    bancoDeDados.setDatabaseName(banco);
    if(!bancoDeDados.open()){
        qDebug() << bancoDeDados.lastError();
    }else{
       qDebug() << "Abriu!";
       QString indicativo = ui->edtIndicativo->text().toUpper();
       QString dmrid = ui->edtDMRId->text();
       QString qra = ui->edtQra->text();
       QString nome = ui->edtNome->text();
       QString sobrenome = ui->edtSobrenome->text();
       QString email = ui->edtEmail->text();
       QString celular = ui->edtCelular->text();
       QString cidade = ui->edtCidade->text();
       QString estado = ui->edtEstado->text();
       QString pais = ui->edtPais->text();
       QSqlQuery queryInsert;
       queryInsert.prepare("INSERT INTO coordenadores(indicativo,dmrid,qra,nome,sobrenome,email,celular,cidade,estado,pais) VALUES('"+indicativo+"','"+dmrid+"','"+qra+"','"+nome+"','"+sobrenome+"','"+email+"','"+celular+"','"+cidade+"','"+estado+"','"+pais+"');");
       queryInsert.exec();
    }
}


void frmCoordenadoresCadastro::on_twgCoordenadores_cellClicked(int row, int column)
{

}


void frmCoordenadoresCadastro::on_btnNovo_clicked()
{

    zerarCampos();
    ui->btnRemover->setEnabled(false);
    ui->btnGravar->setEnabled(false);
    ui->btnNovo->setEnabled(false);
    ui->btnInserir->setEnabled(true);

    ui->btnAtualizar->setFocus();
    ui->edtIndicativo->setFocus();

    listarCoordenadores();
}


void frmCoordenadoresCadastro::on_twgCoordenadores_cellActivated(int row, int column)
{

}


void frmCoordenadoresCadastro::on_twgCoordenadores_clicked(const QModelIndex &index)
{
    configurarCampos();
    ui->btnNovo->setEnabled(true);
    ui->btnGravar->setEnabled(true);
    ui->btnRemover->setEnabled(true);

}


void frmCoordenadoresCadastro::on_btnGravar_clicked()
{
    if(!temCampoVazio()){
        conexaodb ConDB;
        ConDB.abrir();
            QSqlQuery u;
            u.exec("UPDATE coordenadores SET qra = UPPER('"+ui->edtQra->text()+"') ,dmrid = UPPER('"+ui->edtDMRId->text()+"'),nome = UPPER('"+ui->edtNome->text()+"'),sobrenome = UPPER('"+ui->edtSobrenome->text()+"'),cidade = UPPER('"+ui->edtCidade->text()+"'),estado = UPPER('"+ui->edtEstado->text()+"'),pais = UPPER('"+ui->edtPais->text()+"'),email = LOWER('"+ui->edtEmail->text()+"'), celular = '"+ui->edtCelular->text()+"', modificado = DATETIME('now','localtime') WHERE indicativo = UPPER('"+ui->edtIndicativo->text()+"');");
            listarCoordenadores();
            ui->btnNovo->setEnabled(true);
            ui->btnGravar->setEnabled(true);
            ui->btnRemover->setEnabled(true);

        ConDB.fechar();
    }else{
        QMessageBox::about(this,"Preencha os campos","Preencha o Indicativo, QRA, Nome, Sobrenome, Cidade, Estado e País!");
    }

}


void frmCoordenadoresCadastro::on_btnAtualizar_clicked()
{
    listarCoordenadores();
}


void frmCoordenadoresCadastro::on_btnRemover_clicked()
{
    if(!(ui->edtIndicativo->text().isEmpty())){
        QMessageBox::StandardButton resposta;
        resposta = QMessageBox::question(this, "Remover Coordenador", "Excluir o Coordenador "+ui->edtQra->text()+" "+ui->edtIndicativo->text()+"?", QMessageBox::Yes|QMessageBox::No);
        if (resposta == QMessageBox::Yes) {
            conexaodb ConDB;
            ConDB.abrir();
                QSqlQuery d;
                d.exec("DELETE FROM coordenadores WHERE indicativo = UPPER('"+ui->edtIndicativo->text()+"');");
            ConDB.fechar();
            ui->btnGravar->setEnabled(false);
            ui->btnInserir->setEnabled(false);
            ui->btnNovo->setEnabled(true);
            ui->btnRemover->setEnabled(false);
            listarCoordenadores();
        }else{
            ui->btnGravar->setEnabled(false);
            ui->btnInserir->setEnabled(false);
            ui->btnNovo->setEnabled(true);
            ui->btnRemover->setEnabled(true);
            listarCoordenadores();
        }
    }else{
        listarCoordenadores();
    }

}

