#include "frmListaRodadasAbertas.h"
#include "ui_frmListaRodadasAbertas.h"
#include "conexaodb.h"
#include "QMessageBox"
#include "PainelDeRodadas.h"

frmListaRodadasAbertas::frmListaRodadasAbertas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmListaRodadasAbertas)
{
    ui->setupUi(this);
    atualizarPainelRodadas();
    botoes(false);
    setWindowTitle("Rodadas que se encontram em aberto");
    this->setFixedSize(this->size());

}

frmListaRodadasAbertas::~frmListaRodadasAbertas()
{
    delete ui;
}

void frmListaRodadasAbertas::botoes(bool botoesStatus){
    ui->btnExcluirRodada->setEnabled(botoesStatus);
    ui->btnFecharRodada->setEnabled(botoesStatus);
    ui->btnRetornarRodada->setEnabled(botoesStatus);
}

void frmListaRodadasAbertas::zerarCampos(){
    ui->edtQra->clear();
    ui->edtIndicativo->clear();
    ui->edtHorario->clear();
    ui->edtId->clear();
    ui->edtTitulo->clear();
    ui->edtTgFrequencia->clear();
    ui->edtEdicaoRodada->clear();
    ui->edtDataHoraInicio->clear();
    ui->edtDataHoraFim->clear();
    ui->edtComentarios->clear();
}

void frmListaRodadasAbertas::atualizarPainelRodadas(){

    ui->twgListaRodadasAbertas->clear();
    ui->twgListaRodadasAbertas->clearContents();
    ui->twgListaRodadasAbertas->model()->removeRows(0,ui->twgListaRodadasAbertas->rowCount());
    ui->twgListaRodadasAbertas->setShowGrid(false);

    conexaodb ConDB;
    ConDB.abrir();
    QSqlQuery q;
    q.prepare("SELECT coordenadores.qra, coordenadores.indicativo ,rodadasAbertas.id, rodadas.titulo, rodadas.tg_frequencia, rodadas.horario, rodadasAbertas.edicao, rodadasAbertas.inicio, rodadasAbertas.comentario, rodadasAbertas.fim FROM rodadas INNER JOIN rodadasAbertas ON rodadas.id = rodadasAbertas.fkrodada INNER JOIN coordenadores ON coordenadores.id = rodadasAbertas.fkcoordenador WHERE rodadasAbertas.fim IS NULL");
    if(q.exec()){        
        int cont=0;
        ui->twgListaRodadasAbertas->setColumnCount(10);
        //x ui->twgListaRodadasAbertas->setAlternatingRowColors(true);
        QStringList cabecalho={"QRA","Indicativo","ID da Rodada","Título","TG ou Frequência","Horário","Edição da Rodada","Data Hora de Início", "Comentário", "Data Hora fim da Rodada"};
        ui->twgListaRodadasAbertas->setHorizontalHeaderLabels(cabecalho);
        ui->twgListaRodadasAbertas->horizontalHeader()->setVisible(false);
        while(q.next()){
            ui->twgListaRodadasAbertas->insertRow(cont);
            ui->twgListaRodadasAbertas->setItem(cont,0,new QTableWidgetItem(q.value(0).toString())); //qra
            ui->twgListaRodadasAbertas->setItem(cont,1,new QTableWidgetItem(q.value(1).toString())); //indicativo
            ui->twgListaRodadasAbertas->setItem(cont,2,new QTableWidgetItem(q.value(2).toString())); //id da rodada
            ui->twgListaRodadasAbertas->setItem(cont,3,new QTableWidgetItem(q.value(3).toString())); //Titulo
            ui->twgListaRodadasAbertas->setItem(cont,4,new QTableWidgetItem(q.value(4).toString())); //TG ou Frequencia
            ui->twgListaRodadasAbertas->setItem(cont,5,new QTableWidgetItem(q.value(5).toString())); //Horario
            ui->twgListaRodadasAbertas->setItem(cont,6,new QTableWidgetItem(q.value(6).toString())); //Edicao da Rodada
            ui->twgListaRodadasAbertas->setItem(cont,7,new QTableWidgetItem(q.value(7).toString())); //Data Hora de Inicio
            ui->twgListaRodadasAbertas->setItem(cont,8,new QTableWidgetItem(q.value(8).toString())); //Comentario
            ui->twgListaRodadasAbertas->setItem(cont,9,new QTableWidgetItem(q.value(9).toString())); //Data Hora Fim Rodada
            ui->twgListaRodadasAbertas->setRowHeight(cont,20);
            cont++;
        }
        /*
        ui->twgListaRodadasAbertas->setColumnWidth(0,100);
        ui->twgListaRodadasAbertas->setColumnWidth(1,100);
        ui->twgListaRodadasAbertas->setColumnWidth(2,25);
        ui->twgListaRodadasAbertas->setColumnWidth(3,200);
        ui->twgListaRodadasAbertas->setColumnWidth(4,150);
        ui->twgListaRodadasAbertas->setColumnWidth(5,200);
        ui->twgListaRodadasAbertas->setColumnWidth(6,25);
        ui->twgListaRodadasAbertas->setColumnWidth(7,150);
        ui->twgListaRodadasAbertas->setColumnWidth(8,200);
        ui->twgListaRodadasAbertas->setColumnWidth(9,150);
        */
        ui->twgListaRodadasAbertas->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->twgListaRodadasAbertas->setSelectionBehavior(QAbstractItemView::SelectRows);
        //x ui->twgListaRodadasAbertas->verticalHeader()->setVisible(false);
        //x ui->twgListaRodadasAbertas->setStyleSheet("QTableView {selection-background-color:blue}");
        ui->twgListaRodadasAbertas->resizeColumnToContents(0);
        ui->twgListaRodadasAbertas->resizeColumnToContents(1);
        ui->twgListaRodadasAbertas->resizeColumnToContents(2);
        ui->twgListaRodadasAbertas->resizeColumnToContents(3);
        ui->twgListaRodadasAbertas->resizeColumnToContents(4);
        ui->twgListaRodadasAbertas->resizeColumnToContents(5);
        ui->twgListaRodadasAbertas->resizeColumnToContents(6);
        ui->twgListaRodadasAbertas->resizeColumnToContents(7);
        ui->twgListaRodadasAbertas->resizeColumnToContents(8);
        ui->twgListaRodadasAbertas->resizeColumnToContents(9);

        ConDB.fechar();
    }else{
        QMessageBox::warning(this,"Erro!","Erro ao recuperar as informações do Banco de Dados!");
        ConDB.fechar();
    }
}


void frmListaRodadasAbertas::on_twgListaRodadasAbertas_cellClicked(int row, int column)
{
    ui->edtQra->setText(ui->twgListaRodadasAbertas->item(ui->twgListaRodadasAbertas->currentRow(),0)->text());
    ui->edtIndicativo->setText(ui->twgListaRodadasAbertas->item(ui->twgListaRodadasAbertas->currentRow(),1)->text());
    ui->edtId->setText(ui->twgListaRodadasAbertas->item(ui->twgListaRodadasAbertas->currentRow(),2)->text());
    ui->edtTitulo->setText(ui->twgListaRodadasAbertas->item(ui->twgListaRodadasAbertas->currentRow(),3)->text());
    ui->edtTgFrequencia->setText(ui->twgListaRodadasAbertas->item(ui->twgListaRodadasAbertas->currentRow(),4)->text());
    ui->edtHorario->setText(ui->twgListaRodadasAbertas->item(ui->twgListaRodadasAbertas->currentRow(),5)->text());
    ui->edtEdicaoRodada->setText(ui->twgListaRodadasAbertas->item(ui->twgListaRodadasAbertas->currentRow(),6)->text());
    ui->edtDataHoraInicio->setText(ui->twgListaRodadasAbertas->item(ui->twgListaRodadasAbertas->currentRow(),7)->text());
    ui->edtComentarios->setText(ui->twgListaRodadasAbertas->item(ui->twgListaRodadasAbertas->currentRow(),8)->text());
    ui->edtDataHoraFim->setText(ui->twgListaRodadasAbertas->item(ui->twgListaRodadasAbertas->currentRow(),9)->text());
}


void frmListaRodadasAbertas::on_btnRetornarRodada_clicked()
{
    botoes(false);
    if(!(ui->edtId->text().isEmpty())){
        QString id_da_rodada = ui->twgListaRodadasAbertas->item(ui->twgListaRodadasAbertas->currentRow(),2)->text();
        PainelDeRodadas Painel(this,id_da_rodada);
        Painel.exec();
        this->close();
    }
}


void frmListaRodadasAbertas::on_btnFecharRodada_clicked()
{
    if(!(ui->edtId->text().isEmpty())){
        QMessageBox::StandardButton resposta;
        QString idrodada = ui->twgListaRodadasAbertas->item(ui->twgListaRodadasAbertas->currentRow(),2)->text();
        QString titulo = ui->twgListaRodadasAbertas->item(ui->twgListaRodadasAbertas->currentRow(),3)->text();
        QString coordenador = ui->twgListaRodadasAbertas->item(ui->twgListaRodadasAbertas->currentRow(),0)->text()+"/"+ui->twgListaRodadasAbertas->item(ui->twgListaRodadasAbertas->currentRow(),1)->text();
        resposta = QMessageBox::question(this, "Fechar a Rodada", "Tem que deseja FECHAR Rodada "+titulo+" coordenada por "+coordenador+"?", QMessageBox::Yes|QMessageBox::No);
        if (resposta == QMessageBox::Yes ){
            // Fechar a Rodada
            //rodadasAbertas
            conexaodb ConDB;
            ConDB.abrir();
                QSqlQuery q;
                q.exec("INSERT INTO estatisticasRodadasAbertas SELECT * FROM rodadasAbertas WHERE id = "+idrodada+";");
                q.exec("INSERT INTO estatisticasRodadasIntegrantes SELECT * FROM rodadasIntegrantes WHERE fkrodadaaberta = "+idrodada+";");
                q.exec("DELETE FROM rodadasIntegrantes WHERE fkrodadaaberta = "+idrodada+";");
                q.exec("DELETE FROM rodadasAbertas WHERE id = "+idrodada+";");
                q.exec("UPDATE estatisticasRodadasAbertas SET fim = DATETIME('now','localtime') WHERE id = "+idrodada+";");

            ConDB.fechar();
            atualizarPainelRodadas();
            botoes(false);
        }
    }else{
        QMessageBox::about(this,"Fechar Rodada","Selecione a Rodada a ser Fechada!");
        atualizarPainelRodadas();
    }

}

void frmListaRodadasAbertas::on_btnAtualizarDados_clicked()
{
    atualizarPainelRodadas();
    botoes(false);
    ui->btnAtualizarDados->setEnabled(true);
}

void frmListaRodadasAbertas::on_btnExcluirRodada_clicked()
{
    if(ui->edtId->text().isEmpty()){
        QMessageBox::about(this,"Excluir Rodada","Selecione a Rodada a ser Excluida!");
        botoes(false);
    }else{
        QMessageBox::StandardButton resp;
        resp = QMessageBox::question(this, "EXCLUSÃO DE RODADA", "Tem que deseja EXCLUIR a RODADA "+ui->edtTitulo->text()+" EDIÇÃO "+ui->edtEdicaoRodada->text()+"?", QMessageBox::Yes|QMessageBox::No);
        if(resp == QMessageBox::Yes){
            conexaodb ConDB;
            ConDB.abrir();
                QSqlQuery rodadasIntegrantes, rodadasAbertas;
                rodadasIntegrantes.exec("DELETE FROM rodadasIntegrantes WHERE fkrodadaaberta = "+ui->edtId->text()+";");
                rodadasAbertas.exec("DELETE FROM rodadasAbertas WHERE id = "+ui->edtId->text()+";");
                atualizarPainelRodadas();
            ConDB.fechar();
            botoes(false);
            zerarCampos();
        }else{
            atualizarPainelRodadas();
            botoes(false);
        }
    }
}


void frmListaRodadasAbertas::on_twgListaRodadasAbertas_clicked(const QModelIndex &index)
{
    botoes(true);
}

void frmListaRodadasAbertas::on_btnSair_clicked()
{
    this->close();
}

