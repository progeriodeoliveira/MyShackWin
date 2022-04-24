#include "frmRodadasAbrir.h"
#include "ui_frmRodadasAbrir.h"
#include "conexaodb.h"
#include "QMessageBox"
#include "conexaodb.h"
#include "QtDebug"
#include "PainelDeRodadas.h"

frmRodadasAbrir::frmRodadasAbrir(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmRodadasAbrir)
{
    ui->setupUi(this);
    this->setWindowTitle("Abrir Rodada");
    this->setFixedSize(this->size());
    conexaodb ConDB;
    ConDB.abrir();
    QSqlQuery q;
    q.prepare("SELECT id, modo, titulo, horario, tg_frequencia FROM rodadas WHERE ativo = '1';");
    if(q.exec()){
        int cont=0;
        ui->twgRodadas->setColumnCount(5);
        //x ui->twgRodadas->setAlternatingRowColors(true);
        QStringList cabecalho={"#id","Modalidade","Título","Horário","Frequência"};
        ui->twgRodadas->setHorizontalHeaderLabels(cabecalho);
        ui->twgRodadas->horizontalHeader()->setVisible(false);

        while(q.next()){
            ui->twgRodadas->insertRow(cont);
            ui->twgRodadas->setItem(cont,0,new QTableWidgetItem(q.value(0).toString()));
            ui->twgRodadas->setItem(cont,1,new QTableWidgetItem(q.value(1).toString()));
            ui->twgRodadas->setItem(cont,2,new QTableWidgetItem(q.value(2).toString()));
            ui->twgRodadas->setItem(cont,3,new QTableWidgetItem(q.value(3).toString()));
            ui->twgRodadas->setItem(cont,4,new QTableWidgetItem(q.value(4).toString()));
            ui->twgRodadas->setRowHeight(cont,20);
            cont++;
        }
        ui->twgRodadas->setColumnWidth(0,25);
        ui->twgRodadas->setColumnWidth(1,100);
        ui->twgRodadas->setColumnWidth(2,300);
        ui->twgRodadas->setColumnWidth(3,300);
        ui->twgRodadas->setColumnWidth(4,200);
        ui->twgRodadas->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->twgRodadas->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->twgRodadas->verticalHeader()->setVisible(false);
        //ui->twgRodadas->setStyleSheet("QTableView {selection-background-color:blue}");
        ConDB.fechar();
    }else{
        QMessageBox::warning(this,"Erro!","Erro ao recuperar as informações do Banco de Dados!");
        ConDB.fechar();
    }
    ConDB.abrir();
    q.prepare("SELECT id, qra, indicativo FROM coordenadores ORDER BY qra;");
    if (q.exec()){
        while(q.next()){
            QString id = q.value(0).toString();
            QString qra = q.value(1).toString();
            QString indicativo = q.value(2).toString();
            ui->cmbIdCoordenador->addItem(qra+" - "+indicativo,id);

        }
        ConDB.fechar();
    }else{
        QMessageBox::warning(this,"Erro!","Erro ao recuperar as informações do Banco de Dados!");
        ConDB.fechar();
    }

}

frmRodadasAbrir::~frmRodadasAbrir()
{
    delete ui;
}

void frmRodadasAbrir::on_pushButton_clicked()
{
    QString coordenador = ui->cmbIdCoordenador->currentText();
    QString fkcoordenador = ui->cmbIdCoordenador->currentData().toString();
    QString fkrodada = ui->twgRodadas->item(ui->twgRodadas->currentRow(),0)->text();
    QString rodada = ui->twgRodadas->item(ui->twgRodadas->currentRow(),2)->text();
    QString edicao = ui->edtEdicaoRodada->text();

    if (coordenador.isEmpty() or fkrodada.isEmpty() or rodada.isEmpty() or edicao.isEmpty()){
        QMessageBox::warning(this,"Erro!","Selecione Rodada, Coordenador e Informe a Edição da Rodada!");
    }else{
        QMessageBox::StandardButton resposta;
        resposta = QMessageBox::question(this, "Abertura de Rodada", coordenador+"\n abrir Rodada "+rodada+"?", QMessageBox::Yes|QMessageBox::No);
        if (resposta == QMessageBox::Yes ){
            conexaodb ConDB;
            ConDB.abrir();
            QSqlQuery q, idRodadaAberta;
            q.prepare("INSERT INTO rodadasAbertas(fkrodada,fkcoordenador,edicao)VALUES("+fkrodada+","+fkcoordenador+",'"+edicao+"');");
            q.exec();

            idRodadaAberta.prepare("SELECT last_insert_rowid();");
            idRodadaAberta.exec();
            QString idRA ;
            while(idRodadaAberta.next()){
                    idRA = idRodadaAberta.value(0).toString();
            }
            ConDB.fechar();
            // abrindo o formulario
            QString id_da_rodada = ui->twgRodadas->item(ui->twgRodadas->currentRow(),0)->text();
            qDebug() << id_da_rodada;
            PainelDeRodadas Painel(this,idRA);
            Painel.exec();
            this->close();
        }
    }

}


void frmRodadasAbrir::on_pushButton_2_clicked()
{
    qDebug() << ui->cmbIdCoordenador->currentData();

}


void frmRodadasAbrir::on_twgRodadas_cellActivated(int row, int column)
{

}


void frmRodadasAbrir::on_twgRodadas_cellClicked(int row, int column)
{

}


void frmRodadasAbrir::on_btnSair_clicked()
{
    this->close();
}

