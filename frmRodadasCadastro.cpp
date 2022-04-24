#include "frmRodadasCadastro.h"
#include "ui_frmRodadasCadastro.h"
#include "conexaodb.h"
#include "QMessageBox"

frmRodadasCadastro::frmRodadasCadastro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmRodadasCadastro)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    atualizarPainelRodadas();
    this->setWindowTitle("Cadastro de Rodadas");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    botoes(false);
    ui->btnInserirRodada->setEnabled(false);
}

frmRodadasCadastro::~frmRodadasCadastro()
{
    delete ui;
}

void frmRodadasCadastro::on_twgListaRodadas_cellClicked(int row, int column)
{
    botoes(true);
    ui->edtId->setText(ui->twgListaRodadas->item(ui->twgListaRodadas->currentRow(),0)->text());
    //ui->cmbModo->itemText(ui->twgListaRodadas->item(ui->twgListaRodadas->currentRow(),1)->text());

    int modo;
    if((ui->twgListaRodadas->item(ui->twgListaRodadas->currentRow(),1)->text() == "ANA")){
        modo = 0;
    }else{
        modo = 1;
    }
    ui->cmbModo->setCurrentIndex(modo);

    ui->edtTitulo->setText(ui->twgListaRodadas->item(ui->twgListaRodadas->currentRow(),2)->text());
    ui->edtHorario->setText(ui->twgListaRodadas->item(ui->twgListaRodadas->currentRow(),3)->text());
    ui->edtTgFrequencia->setText(ui->twgListaRodadas->item(ui->twgListaRodadas->currentRow(),4)->text());
    ui->edtCriado->setText(ui->twgListaRodadas->item(ui->twgListaRodadas->currentRow(),5)->text());
    ui->edtModificado->setText(ui->twgListaRodadas->item(ui->twgListaRodadas->currentRow(),6)->text());
}

void frmRodadasCadastro::atualizarPainelRodadas(){
    conexaodb ConDB;
    ConDB.abrir();
        QSqlQuery qpainel;
        qpainel.prepare("SELECT id, modo, titulo, horario, tg_frequencia, criado, modificado, ativo FROM rodadas ORDER BY id;");
        qpainel.exec();

        ui->twgListaRodadas->clear();
        ui->twgListaRodadas->clearContents();
        ui->twgListaRodadas->model()->removeRows(0,ui->twgListaRodadas->rowCount());
        ui->twgListaRodadas->setShowGrid(false);
        ui->twgListaRodadas->setColumnCount(7);
        //x ui->twgListaRodadas->setAlternatingRowColors(true);
        QStringList cabecalho={" id "," Modo "," Título "," Horário "," TG ou Frequência "," Criado "," Modificado "};
        ui->twgListaRodadas->setHorizontalHeaderLabels(cabecalho);
        ui->twgListaRodadas->horizontalHeader()->setVisible(false);


        int cont = 0;

        QBrush corLetra;

        while (qpainel.next()) {

            if (qpainel.value(7).toString() == "0"){
                QColor gray(Qt::gray);
                corLetra.setColor(gray);
            }else{
                QColor black(Qt::black);
                corLetra.setColor(black);
            }

            ui->twgListaRodadas->insertRow(cont);

            ui->twgListaRodadas->setItem(cont,0,new QTableWidgetItem(qpainel.value(0).toString())); //id
            ui->twgListaRodadas->item(cont,0)->setTextAlignment(Qt::AlignCenter);
            ui->twgListaRodadas->item(cont,0)->setForeground(corLetra.color());

            ui->twgListaRodadas->setItem(cont,1,new QTableWidgetItem(qpainel.value(1).toString())); //modo
            ui->twgListaRodadas->item(cont,1)->setTextAlignment(Qt::AlignCenter);
            ui->twgListaRodadas->item(cont,1)->setForeground(corLetra.color());

            ui->twgListaRodadas->setItem(cont,2,new QTableWidgetItem(qpainel.value(2).toString())); //titulo
            ui->twgListaRodadas->item(cont,2)->setForeground(corLetra.color());
            //ui->twgListaRodadas->item(cont,2)->setTextAlignment(Qt::AlignCenter);

            ui->twgListaRodadas->setItem(cont,3,new QTableWidgetItem(qpainel.value(3).toString())); //horario
            ui->twgListaRodadas->item(cont,3)->setForeground(corLetra.color());
            //ui->twgListaRodadas->item(cont,3)->setTextAlignment(Qt::AlignCenter);

            ui->twgListaRodadas->setItem(cont,4,new QTableWidgetItem(qpainel.value(4).toString())); //tg_frequencia
            ui->twgListaRodadas->item(cont,4)->setForeground(corLetra.color());
            //ui->twgListaRodadas->item(cont,4)->setTextAlignment(Qt::AlignCenter);

            ui->twgListaRodadas->setItem(cont,5,new QTableWidgetItem(qpainel.value(5).toString())); //criado
            ui->twgListaRodadas->item(cont,5)->setForeground(corLetra.color());
            //ui->twgListaRodadas->item(cont,5)->setTextAlignment(Qt::AlignCenter);

            ui->twgListaRodadas->setItem(cont,6,new QTableWidgetItem(qpainel.value(6).toString())); //modificado
            ui->twgListaRodadas->item(cont,6)->setForeground(corLetra.color());
            //ui->twgListaRodadas->item(cont,6)->setTextAlignment(Qt::AlignCenter);

            ui->twgListaRodadas->setRowHeight(cont,20);

            cont++;
        }


        ui->twgListaRodadas->resizeColumnToContents(0);
        ui->twgListaRodadas->resizeColumnToContents(1);
        ui->twgListaRodadas->resizeColumnToContents(2);
        ui->twgListaRodadas->resizeColumnToContents(3);
        ui->twgListaRodadas->resizeColumnToContents(4);
        ui->twgListaRodadas->resizeColumnToContents(5);
        ui->twgListaRodadas->resizeColumnToContents(6);

        ui->twgListaRodadas->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->twgListaRodadas->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->twgListaRodadas->verticalHeader()->setVisible(false);
        //x ui->twgListaRodadas->setStyleSheet("QTableView {selection-background-color:blue}");

    ConDB.fechar();
}

void frmRodadasCadastro::on_pushButton_clicked()
{

}


void frmRodadasCadastro::on_btnGravarAlteracoes_clicked()
{
    conexaodb ConDB;
    ConDB.abrir();
        QSqlQuery u;
        u.exec("UPDATE rodadas SET modo = '"+ui->cmbModo->currentText()+"', titulo = '"+ui->edtTitulo->text()+"' , tg_frequencia = '"+ui->edtTgFrequencia->text()+"' ,horario = '"+ui->edtHorario->text()+"' , modificado = DATETIME('now','localtime') WHERE id = "+ui->edtId->text()+";");
    ConDB.fechar();
    atualizarPainelRodadas();
    botoes(false);
}


void frmRodadasCadastro::on_btnSair_clicked()
{
    this->close();
}


void frmRodadasCadastro::on_btnArquivar_clicked()
{
    if(!(ui->edtId->text().isEmpty())){
        conexaodb ConDB;
        ConDB.abrir();
        QSqlQuery upd;
        upd.exec("UPDATE rodadas SET ativo = not(ativo) WHERE id = "+ui->edtId->text()+";");
        ConDB.fechar();
        atualizarPainelRodadas();
        botoes(false);
    }
}

void frmRodadasCadastro::zerarCampos(){
    ui->edtCriado->clear();
    ui->edtHorario->clear();
    ui->edtId->clear();
    ui->edtModificado->clear();
    ui->edtTgFrequencia->clear();
    ui->edtTitulo->clear();
    ui->edtTitulo->setFocus();
}

void frmRodadasCadastro::on_btnLimparCampos_clicked()
{
    zerarCampos();
    ui->btnInserirRodada->setEnabled(true);
    botoes(false);
}

bool frmRodadasCadastro::temCampoVazio(){
    if((ui->edtTitulo->text().isEmpty()) or (ui->edtTgFrequencia->text().isEmpty()) or (ui->edtHorario->text().isEmpty())){
        return true;
    }else{
        return false;
    }
}

void frmRodadasCadastro::botoes(bool status){
    ui->btnArquivar->setEnabled(status);
    ui->btnGravarAlteracoes->setEnabled(status);

    ui->btnLimparCampos->setEnabled(status);
}

void frmRodadasCadastro::on_btnInserirRodada_clicked()
{
    if(temCampoVazio()){
        atualizarPainelRodadas();
        QMessageBox::about(this,"Falta informação","Preencha os Campos Título da Rodada, TG ou Frequência e Horário da Rodada!");
    }else{
        conexaodb ConDB;
        ConDB.abrir();
        QSqlQuery inserirRodada;
        inserirRodada.exec("INSERT INTO rodadas(modo,titulo,horario,tg_frequencia) VALUES('"+ui->cmbModo->currentText()+"','"+ui->edtTitulo->text()+"','"+ui->edtHorario->text()+"','"+ui->edtTgFrequencia->text()+"');");
        ConDB.fechar();
        zerarCampos();
        atualizarPainelRodadas();
        ui->btnInserirRodada->setEnabled(false);
        botoes(false);
    }
}

