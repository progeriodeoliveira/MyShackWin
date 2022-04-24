#include "frmRadioamadores.h"
#include "ui_frmRadioamadores.h"
#include "radioamador.h"
#include "conexaodb.h"
#include "QMessageBox"
frmRadioamadores::frmRadioamadores(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmRadioamadores)
{
    ui->setupUi(this);
    this->setWindowTitle("Cadastro de Radioamadores");
    this->setFixedSize(this->size());


    zerarCampos();
    botoesComentarios(false);
    ui->edtPesquisaIndicativo->setFocus();
    //x ui->btnGravarAlteracoes->setEnabled(false);
    ui->btnRemoverRA->setEnabled(false);
    ui->btnAdicionarComentario->setEnabled(false);
    ui->btnRemoverRA->setEnabled(false);
}

frmRadioamadores::~frmRadioamadores()
{
    delete ui;
}

void frmRadioamadores::listarComentarios(){
    ui->twgComentariosRA->clear();
    ui->twgComentariosRA->clearContents();
    ui->twgComentariosRA->model()->removeRows(0,ui->twgComentariosRA->rowCount());
    ui->twgComentariosRA->setShowGrid(false);
    conexaodb ConDB;
    ConDB.abrir();
        QSqlQuery q;

        q.exec("SELECT id, comentario, criado, modificado FROM radioamadoresComentarios WHERE fkradioamador = "+ui->edtId->text()+";");
        int cont=0;
        ui->twgComentariosRA->setColumnCount(4);
        //x ui->twgComentariosRA->setAlternatingRowColors(true);
        QStringList cabecalho={" id "," Comentário "," Criado "," Modificado "};
        ui->twgComentariosRA->setHorizontalHeaderLabels(cabecalho);
        ui->twgComentariosRA->horizontalHeader()->setVisible(false);
        while(q.next()){

            ui->twgComentariosRA->insertRow(cont);
            ui->twgComentariosRA->setItem(cont,0,new QTableWidgetItem(q.value(0).toString())); //id
            ui->twgComentariosRA->setItem(cont,1,new QTableWidgetItem(q.value(1).toString())); //comentario
            ui->twgComentariosRA->setItem(cont,2,new QTableWidgetItem(q.value(2).toString())); //criado
            ui->twgComentariosRA->setItem(cont,3,new QTableWidgetItem(q.value(3).toString())); //modificado
            ui->twgComentariosRA->setRowHeight(cont,20);
            cont++;
        }
        ui->twgComentariosRA->setColumnWidth(0,0);
        ui->twgComentariosRA->resizeColumnToContents(1);
        //ui->twgComentariosRA->setColumnWidth(1,300);
        ui->twgComentariosRA->setColumnWidth(2,0);
        ui->twgComentariosRA->setColumnWidth(3,0);


        ui->twgComentariosRA->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->twgComentariosRA->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->twgComentariosRA->verticalHeader()->setVisible(false);
        //x ui->twgComentariosRA->setStyleSheet("QTableView {selection-background-color:blue}");
    ConDB.fechar();
}

void frmRadioamadores::botoesComentarios(bool status){
    ui->btnRemoverComentarios->setEnabled(status);
}

void frmRadioamadores::zerarCampos(){
    ui->edtId->clear();
    ui->edtId->setFocus();

    ui->edtIndicativo->clear();
    ui->edtQra->clear();
    ui->edtDmrid->clear();
    ui->edtNome->clear();
    ui->edtSobrenome->clear();
    ui->edtCidade->clear();
    ui->edtEstado->clear();
    ui->edtPais->clear();
    ui->edtCelular->clear();
    ui->edtEmail->clear();
    ui->edtCriado->clear();
    ui->edtModificado->clear();
    ui->btnInserirNovoRA->setEnabled(false);
}

bool frmRadioamadores::temCampoVazio(){
    if((ui->edtNome->text().isEmpty()) or (ui->edtSobrenome->text().isEmpty()) or (ui->edtCidade->text().isEmpty()) or (ui->edtEstado->text().isEmpty()) or (ui->edtPais->text().isEmpty())){
        QMessageBox::about(this,"Falta informação","Preencha ao menos Nome, Sobrenome, Cidade e Estado!");
        return true;
    }else{
        return false;
    }
}


void frmRadioamadores::recuperarDadosLocais(){
    conexaodb ConDB;
    ConDB.abrir();
        QSqlQuery q;
        q.exec("SELECT id, indicativo, qra, dmrid, nome, sobrenome, cidade, estado, pais, celular, email, criado, modificado FROM radioamadores WHERE indicativo = UPPER('"+ui->edtPesquisaIndicativo->text()+"');");
        while (q.next()) {
            ui->edtId->setText(q.value(0).toString());
            ui->edtIndicativo->setText(q.value(1).toString());
            ui->edtQra->setText(q.value(2).toString());
            ui->edtDmrid->setText(q.value(3).toString());
            ui->edtNome->setText(q.value(4).toString());
            ui->edtSobrenome->setText(q.value(5).toString());
            ui->edtCidade->setText(q.value(6).toString());
            ui->edtEstado->setText(q.value(7).toString());
            ui->edtPais->setText(q.value(8).toString());
            ui->edtCelular->setText(q.value(9).toString());
            ui->edtEmail->setText(q.value(10).toString());
            ui->edtCriado->setText(q.value(11).toString());
            ui->edtModificado->setText(q.value(12).toString());
            ui->btnInserirNovoRA->setEnabled(false);
        }
    ConDB.fechar();
    listarComentarios();
    ui->btnInserirNovoRA->setEnabled(false);
    ui->edtPesquisaIndicativo->setFocus();
}

void frmRadioamadores::LocalizarRA(){
    zerarCampos();
    botoesComentarios(false);
    radioamador ra;
    if(ra.existeRaLocal(ui->edtPesquisaIndicativo->text())){
        //x ui->btnGravarAlteracoes->setEnabled(true);
        ui->btnRemoverRA->setEnabled(true);
        recuperarDadosLocais();
        ui->btnAdicionarComentario->setEnabled(true);
    }else{
        radioamador ra;
        radioidnet dmr;
        if(ra.existeArquivoJson(ui->edtPesquisaIndicativo->text())){
            QStringList dadosDmr = dmr.obterDados(ui->edtPesquisaIndicativo->text());
            conexaodb ConDB;
            ConDB.abrir();
                QSqlQuery i;
                i.exec("INSERT INTO radioamadores(indicativo,dmrid,qra,nome,sobrenome,cidade,estado,pais) VALUES(UPPER('"+ui->edtPesquisaIndicativo->text()+"'),'"+dadosDmr[0]+"','"+dadosDmr[3]+"','"+dadosDmr[3]+"','"+dadosDmr[4]+"','"+dadosDmr[5]+"','"+dadosDmr[6]+"','"+dadosDmr[7]+"');");
            ConDB.fechar();
            recuperarDadosLocais();
            //x ui->btnGravarAlteracoes->setEnabled(true);
            ui->btnAdicionarComentario->setEnabled(true);
            ui->btnRemoverRA->setEnabled(true);

        }else{
            QMessageBox::about(this,"Novo Radioamador","Indicativo NÃO LOCALIZADO na Base de Dados Local e na Base de Dados DRM!");
            ui->btnInserirNovoRA->setEnabled(true);
            //x ui->btnGravarAlteracoes->setEnabled(false);
            ui->edtIndicativo->setText(ui->edtPesquisaIndicativo->text());
            ui->btnAdicionarComentario->setEnabled(false);
            ui->btnRemoverRA->setEnabled(false);
        }
    }
}

void frmRadioamadores::on_btnLocalizaInsereRA_clicked()
{
    LocalizarRA();
}


void frmRadioamadores::on_btnInserirNovoRA_clicked()
{
    if(temCampoVazio()){
        ui->edtPesquisaIndicativo->setFocus();
    }else{
        conexaodb ConDB;
        ConDB.abrir();
            QSqlQuery i;
            i.exec("INSERT INTO radioamadores(indicativo,dmrid,qra,nome,sobrenome,cidade,estado,pais,email,celular) VALUES(UPPER('"+ui->edtPesquisaIndicativo->text()+"'),UPPER('"+ui->edtDmrid->text()+"'),UPPER('"+ui->edtQra->text()+"'),UPPER('"+ui->edtNome->text()+"'),UPPER('"+ui->edtSobrenome->text()+"'),UPPER('"+ui->edtCidade->text()+"'),UPPER('"+ui->edtEstado->text()+"'),UPPER('"+ui->edtPais->text()+"'),UPPER('"+ui->edtEmail->text()+"'),'"+ui->edtCelular->text()+"');");
        ConDB.fechar();
        recuperarDadosLocais();
        botoesComentarios(true);
        ui->btnRemoverRA->setEnabled(true);
    }
}


void frmRadioamadores::on_btnGravarAlteracoes_clicked()
{
    if(temCampoVazio()){
        ui->edtPesquisaIndicativo->setFocus();
    }else{
        conexaodb ConDB;
        ConDB.abrir();
            QSqlQuery u;
            u.exec("UPDATE radioamadores SET indicativo = UPPER('"+ui->edtIndicativo->text()+"'), qra = UPPER('"+ui->edtQra->text()+"'), nome = UPPER('"+ui->edtNome->text()+"'), sobrenome = UPPER('"+ui->edtSobrenome->text()+"'), cidade = UPPER('"+ui->edtCidade->text()+"'), estado = UPPER('"+ui->edtEstado->text()+"'), pais = UPPER('"+ui->edtPais->text()+"'), celular = '"+ui->edtCelular->text()+"', email = LOWER('"+ui->edtEmail->text()+"'), modificado = DATETIME('now','localtime') WHERE indicativo = UPPER('"+ui->edtPesquisaIndicativo->text()+"');");
        ConDB.fechar();
        recuperarDadosLocais();
        botoesComentarios(true);
        ui->btnRemoverRA->setEnabled(true);
    }


}


void frmRadioamadores::on_btnAdicionarComentario_clicked()
{    
    if ((ui->edtComentario->text().isEmpty()) or (ui->edtId->text().isEmpty())) {
        ui->edtComentario->setFocus();
    } else {
        conexaodb ConDB;
        ConDB.abrir();
            QSqlQuery i;
            i.exec("INSERT INTO radioamadoresComentarios(fkradioamador,comentario) VALUES ("+ui->edtId->text()+",UPPER('"+ui->edtComentario->text()+"'));");
        ConDB.fechar();
        recuperarDadosLocais();
        ui->edtComentario->clear();
    }
}


void frmRadioamadores::on_btnRemoverComentarios_clicked()
{
    if(ui->twgComentariosRA->item(ui->twgComentariosRA->currentRow(),0)->text().isEmpty()){
        QMessageBox::about(this,"Selecione o Comentário","Selecione o Comentário a ser Excluido!");
    }else{
        conexaodb ConDB;
        ConDB.abrir();
            QSqlQuery d;
            d.exec("DELETE FROM radioamadoresComentarios WHERE id = "+ui->twgComentariosRA->item(ui->twgComentariosRA->currentRow(),0)->text()+";");
        ConDB.fechar();
        recuperarDadosLocais();
        listarComentarios();
        botoesComentarios(false);
    }
}


void frmRadioamadores::on_twgComentariosRA_cellClicked(int row, int column)
{
    botoesComentarios(true);
}


void frmRadioamadores::on_btnRemoverRA_clicked()
{
    if(!(ui->edtId->text().isEmpty())){
        QMessageBox::StandardButton resposta;
        resposta = QMessageBox::question(this, "Remover Radioamador", "Excluir o Radioamador "+ui->edtQra->text()+" "+ui->edtIndicativo->text()+"?", QMessageBox::Yes|QMessageBox::No);
        if (resposta == QMessageBox::Yes) {
            conexaodb ConDB;
            ConDB.abrir();
                QSqlQuery d;
                d.exec("DELETE FROM radioamadores WHERE id = "+ui->edtId->text()+";");
            ConDB.fechar();
            zerarCampos();
            botoesComentarios(false);
        }
    }else{
        QMessageBox::about(this,"Remover Radioamador","Não há Radioamador Selecionado para ser Excluido!");
    }

}


void frmRadioamadores::on_edtPesquisaIndicativo_returnPressed()
{
    LocalizarRA();
}

