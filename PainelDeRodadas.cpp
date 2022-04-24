#include "PainelDeRodadas.h"
#include "ui_PainelDeRodadas.h"
#include "conexaodb.h"
#include "QtDebug"
#include "radioidnet.h"
#include "radioamador.h"
#include "QMessageBox"
#include "QClipboard"
#include "frmradioamadordadoscomcomentarios.h"

PainelDeRodadas::PainelDeRodadas(QWidget *parent, QString id_nova_rodada) :
    QDialog(parent),
    ui(new Ui::PainelDeRodadas)
{
    ui->setupUi(this);
    //setStyleSheet("background-color:rgb(40,40,40);color:rgb(255,250,250);");
    setWindowTitle("Painel de Rodada");
    ui->btnRemoverComentario->setEnabled(false);
    // Atualizar Painel Principal da Rodada

    // mostrar dados da rodada
    conexaodb ConDB;
    ConDB.abrir();
    QSqlQuery q;
    qDebug() << id_nova_rodada;
    q.prepare("SELECT rodadas.titulo, rodadasAbertas.edicao, coordenadores.qra, coordenadores.indicativo, rodadasAbertas.comentario FROM rodadas INNER JOIN rodadasAbertas ON rodadas.id = rodadasAbertas.fkrodada INNER JOIN coordenadores ON coordenadores.id = rodadasAbertas.fkcoordenador WHERE rodadasAbertas.id = "+id_nova_rodada);
    q.exec();
    while(q.next()){
        ui->edtCoordenador->setText(q.value(2).toString()+" - "+q.value(3).toString());
        ui->edtEdicao->setText(q.value(1).toString());
        ui->edtFkRodada->setText(id_nova_rodada);
        ui->edtRodada->setText(q.value(0).toString());
        ui->edtComentarios->setText(q.value(4).toString());
    }
   ConDB.fechar();
   AtualizarPainelRodada();
}

PainelDeRodadas::~PainelDeRodadas()
{
    delete ui;
}

void PainelDeRodadas::on_btnSalvarComentariosDaRodada_clicked()
{
    conexaodb ConDB;
    ConDB.abrir();
    QSqlQuery q;
    q.exec("UPDATE rodadasAbertas SET comentario = '"+ui->edtComentarios->toMarkdown()+"' WHERE rodadasAbertas.id = "+ui->edtFkRodada->text()+";");
    ConDB.fechar();
}

void PainelDeRodadas::IncluirNaRodada(QString fkrodada, QString indicativo){
    radioamador ra;
    QString fkradioamador = ra.id(indicativo);
    conexaodb ConDB;

    ConDB.abrir();
        QSqlQuery qInserirRodada;
        qInserirRodada.exec("INSERT INTO rodadasIntegrantes(fkstatus,fkrodadaaberta,fkradioamador) VALUES(1,"+fkrodada+","+fkradioamador+");");
    ConDB.fechar();
    AtualizarPainelRodada();
}

bool PainelDeRodadas::existeRAnaRodada(QString fkrodada, QString indicativo){
    radioamador ra;
    QString idRadioamador = ra.id(indicativo);
    conexaodb ConDB;
    ConDB.abrir();
    QSqlQuery q;
    q.prepare("SELECT fkrodadaaberta, fkradioamador FROM rodadasIntegrantes WHERE fkrodadaaberta = "+fkrodada+" AND fkradioamador = "+idRadioamador+" ;");
    q.exec();
    int cont = 0;
    while(q.next()){
        cont++;
    }

    if(cont > 0 ){
        ConDB.fechar();
        return true;
    }else{
        ConDB.fechar();
        return false;
    }
}

void PainelDeRodadas::IncluirRadioamadorRodada(QString fkrodada, QString indicativo){
    if(!existeRAnaRodada( fkrodada, indicativo )){
        conexaodb ConDB;
        ConDB.abrir();
            QSqlQuery qLocalizarRA;
            qLocalizarRA.exec("SELECT indicativo FROM radioamadores WHERE indicativo = '"+indicativo+"';");
            int cont = 0;
            while(qLocalizarRA.next()){
                cont++;
            }
        ConDB.fechar();
        if(cont >= 1){
            IncluirNaRodada(fkrodada, indicativo);

        }else{
            radioidnet dmr;
            QStringList dadosDrm = dmr.obterDados(indicativo);

            if(dadosDrm.size() > 1){
                ConDB.abrir();
                    QSqlQuery qInserirRA;
                    qInserirRA.exec("INSERT INTO radioamadores(indicativo,dmrid,qra,nome,sobrenome,cidade,estado,pais) VALUES('"+indicativo+"','"+dadosDrm[0]+"','"+dadosDrm[3]+"','"+dadosDrm[3]+"','"+dadosDrm[4]+"','"+dadosDrm[5]+"','"+dadosDrm[6]+"','"+dadosDrm[7]+"');");
                ConDB.fechar();
                IncluirNaRodada(fkrodada,indicativo);

            }else{

                ConDB.abrir();
                    QSqlQuery qInserirRA;
                    qInserirRA.exec("INSERT INTO radioamadores(indicativo) VALUES('"+indicativo+"');");
                ConDB.fechar();
                IncluirNaRodada(fkrodada,indicativo);
            }
        }
    }
}

void PainelDeRodadas::statusBotoes(bool status){
    ui->btnAtualizarPainelRodada->setEnabled(status);
    ui->btnDel->setEnabled(status);
    ui->btnObs->setEnabled(status);
    ui->btnQap->setEnabled(status);
    ui->btnQrt->setEnabled(status);
    ui->btnQrx->setEnabled(status);
}

void PainelDeRodadas::painelComentarios(){
    ui->twgComentariosRA->clear();
    ui->twgComentariosRA->clearContents();
    ui->twgComentariosRA->model()->removeRows(0,ui->twgComentariosRA->rowCount());
    ui->twgComentariosRA->setShowGrid(false);
    conexaodb ConDB;
    ConDB.abrir();
        QSqlQuery q;
        q.exec("SELECT radioamadoresComentarios.id, radioamadoresComentarios.comentario FROM radioamadores INNER JOIN radioamadoresComentarios ON radioamadores.id = radioamadoresComentarios.fkradioamador WHERE radioamadores.indicativo = UPPER('"+ui->twgIntegrantesRodada->item(ui->twgIntegrantesRodada->currentRow(),3)->text()+"') ORDER BY radioamadoresComentarios.id DESC;");
        int cont=0;
        ui->twgComentariosRA->setColumnCount(2);
        //x ui->twgComentariosRA->setAlternatingRowColors(true);
        QStringList cabecalho={" Comentário "};
        ui->twgComentariosRA->setHorizontalHeaderLabels(cabecalho);

        while(q.next()){
            ui->twgComentariosRA->insertRow(cont);
            ui->twgComentariosRA->setItem(cont,0,new QTableWidgetItem(q.value(0).toString())); //id
            ui->twgComentariosRA->setItem(cont,1,new QTableWidgetItem(q.value(1).toString())); //Comentarios
            ui->twgComentariosRA->setRowHeight(cont,20);
            cont++;
        }

        //ui->twgComentariosRA->resizeColumnToContents(0);
        ui->twgComentariosRA->setColumnWidth(0,0);
        ui->twgComentariosRA->setColumnWidth(1,400);

        ui->twgComentariosRA->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->twgComentariosRA->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->twgComentariosRA->verticalHeader()->setVisible(false);
        ui->twgComentariosRA->horizontalHeader()->setVisible(false);
        //x ui->twgComentariosRA->setStyleSheet("QTableView {selection-background-color:blue}");

   ConDB.fechar();
}


void PainelDeRodadas::painelLogParticipacao(){
    ui->twgLogParticipacao->clear();
    ui->twgLogParticipacao->clearContents();
    ui->twgLogParticipacao->model()->removeRows(0,ui->twgLogParticipacao->rowCount());
    ui->twgLogParticipacao->setShowGrid(false);
    conexaodb ConDB;
    ConDB.abrir();
        QSqlQuery q;
        q.exec("SELECT rodadasTitulo, COUNT(*) AS qtdParticipacao FROM estatisticasRodadasView WHERE radioamadoresIndicativo = UPPER('"+ui->twgIntegrantesRodada->item(ui->twgIntegrantesRodada->currentRow(),3)->text()+"') GROUP BY rodadasTitulo ORDER BY 2 DESC;");
        int cont=0;
        ui->twgLogParticipacao->setColumnCount(2);
        //x ui->twgLogParticipacao->setAlternatingRowColors(true);
        QStringList cabecalho={" Rodada  "," # "};
        ui->twgLogParticipacao->setHorizontalHeaderLabels(cabecalho);
        while(q.next()){
            ui->twgLogParticipacao->insertRow(cont);
            ui->twgLogParticipacao->setItem(cont,0,new QTableWidgetItem(q.value(0).toString())); //Titulo
            ui->twgLogParticipacao->setItem(cont,1,new QTableWidgetItem(q.value(1).toString())); //Edicao
            ui->twgLogParticipacao->item(cont,1)->setTextAlignment(Qt::AlignCenter);

            ui->twgLogParticipacao->setRowHeight(cont,20);
            cont++;
        }

        ui->twgLogParticipacao->setColumnWidth(0,500);
        ui->twgLogParticipacao->setColumnWidth(1,50);
        //ui->twgLogParticipacao->resizeColumnToContents(0);
        //ui->twgLogParticipacao->resizeColumnToContents(1);

        ui->twgLogParticipacao->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->twgLogParticipacao->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->twgLogParticipacao->verticalHeader()->setVisible(false);
        ui->twgLogParticipacao->horizontalHeader()->setVisible(false);
        //x ui->twgLogParticipacao->setStyleSheet("QTableView {selection-background-color:blue}");

   ConDB.fechar();
}


void PainelDeRodadas::AtualizarPainelRodada(){
    ui->twgIntegrantesRodada->clear();
    ui->twgIntegrantesRodada->clearContents();
    ui->twgIntegrantesRodada->model()->removeRows(0,ui->twgIntegrantesRodada->rowCount());
    ui->twgIntegrantesRodada->setShowGrid(false);

    statusBotoes(false);

    conexaodb ConDB;
    ConDB.abrir();
    QSqlQuery qpainel;



    qpainel.prepare("SELECT rodadasIntegrantes.id, rodadasIntegrantes.obs, rodadasStatus.status, radioamadores.indicativo, radioamadores.qra, radioamadores.nome, radioamadores.sobrenome, radioamadores.cidade, radioamadores.estado, radioamadores.pais, rodadasIntegrantes.cambiodh, rodadasIntegrantes.filadh, rodadasIntegrantes.qapdh,rodadasIntegrantes.cambioqtd, rodadasIntegrantes.qrxdh, rodadasIntegrantes.qrtdh FROM radioamadores INNER JOIN rodadasIntegrantes ON radioamadores.id = rodadasIntegrantes.fkradioamador INNER JOIN rodadasStatus ON rodadasStatus.id = rodadasIntegrantes.fkstatus WHERE rodadasIntegrantes.fkrodadaaberta = "+ui->edtFkRodada->text()+" ORDER BY rodadasIntegrantes.fkstatus, rodadasIntegrantes.cambiodh DESC;");
    if (qpainel.exec()){
        int cont=0;
        ui->twgIntegrantesRodada->setColumnCount(16);
        //ui->twgIntegrantesRodada->setAlternatingRowColors(true);
        QStringList cabecalho={" id "," obs "," Status "," Indicativo "," QRA "," Nome "," Sobrenome "," Cidade "," Estado ", " Pais ", " Cambio Data Hora "," Fila Data Hora "," QAP Data Hora "," Quantidade Cambio "," QRX Data Hora "," QRT Data Hora "};
        //x ui->twgIntegrantesRodada->setHorizontalHeaderLabels(cabecalho);
        cont = 0;

        QBrush corLetra, corFundo;

        while(qpainel.next()){

            ui->twgIntegrantesRodada->insertRow(cont);

            // cores padroes da tabela
            QColor black(Qt::black);
            corLetra.setColor(black);
            QColor transparent(Qt::transparent);
            corFundo.setColor(transparent);
            //

            if (qpainel.value(2).toString() == "FILA"){
                QColor black(Qt::black);
                corLetra.setColor(black);
                QColor yellow(Qt::yellow);
                corFundo.setColor(yellow);
            }

            if(qpainel.value(2).toString() == "QRX"){
                QColor black(Qt::black);
                corLetra.setColor(black);
                QColor gray(Qt::gray);
                corFundo.setColor(gray);
            }

            if(qpainel.value(2).toString() == "QRT"){
                QColor black(Qt::black);
                corLetra.setColor(black);
                QColor lightgray(Qt::lightGray);
                corFundo.setColor(lightgray);
            }

            if(qpainel.value(1).toString() == "!"){
                QColor white(Qt::white);
                corLetra.setColor(white);
                QColor red(Qt::red);
                corFundo.setColor(red);
            }

            ui->twgIntegrantesRodada->setItem(cont,0,new QTableWidgetItem(qpainel.value(0).toString())); //id
            ui->twgIntegrantesRodada->item(cont,0)->setTextAlignment(Qt::AlignCenter);
            ui->twgIntegrantesRodada->item(cont,0)->setForeground(corLetra.color());
            ui->twgIntegrantesRodada->item(cont,0)->setBackground(corFundo.color());

            ui->twgIntegrantesRodada->setItem(cont,1,new QTableWidgetItem(qpainel.value(1).toString())); //obs
            ui->twgIntegrantesRodada->item(cont,1)->setTextAlignment(Qt::AlignCenter);
            ui->twgIntegrantesRodada->item(cont,1)->setForeground(corLetra.color());
            ui->twgIntegrantesRodada->item(cont,1)->setBackground(corFundo.color());

            ui->twgIntegrantesRodada->setItem(cont,2,new QTableWidgetItem(qpainel.value(2).toString())); //status
            ui->twgIntegrantesRodada->item(cont,2)->setTextAlignment(Qt::AlignCenter);
            ui->twgIntegrantesRodada->item(cont,2)->setForeground(corLetra.color());
            ui->twgIntegrantesRodada->item(cont,2)->setBackground(corFundo.color());

            ui->twgIntegrantesRodada->setItem(cont,3,new QTableWidgetItem(qpainel.value(3).toString())); //Indicativo
            ui->twgIntegrantesRodada->item(cont,3)->setForeground(corLetra.color());
            ui->twgIntegrantesRodada->item(cont,3)->setBackground(corFundo.color());

            ui->twgIntegrantesRodada->setItem(cont,4,new QTableWidgetItem(qpainel.value(4).toString())); //QRA
            ui->twgIntegrantesRodada->item(cont,4)->setForeground(corLetra.color());
            ui->twgIntegrantesRodada->item(cont,4)->setBackground(corFundo.color());

            ui->twgIntegrantesRodada->setItem(cont,5,new QTableWidgetItem(qpainel.value(5).toString())); //Nome
            ui->twgIntegrantesRodada->item(cont,5)->setForeground(corLetra.color());
            ui->twgIntegrantesRodada->item(cont,5)->setBackground(corFundo.color());

            ui->twgIntegrantesRodada->setItem(cont,6,new QTableWidgetItem(qpainel.value(6).toString())); //Sobrenome
            ui->twgIntegrantesRodada->item(cont,6)->setForeground(corLetra.color());
            ui->twgIntegrantesRodada->item(cont,6)->setBackground(corFundo.color());

            ui->twgIntegrantesRodada->setItem(cont,7,new QTableWidgetItem(qpainel.value(7).toString())); //Cidade
            ui->twgIntegrantesRodada->item(cont,7)->setForeground(corLetra.color());
            ui->twgIntegrantesRodada->item(cont,7)->setBackground(corFundo.color());

            ui->twgIntegrantesRodada->setItem(cont,8,new QTableWidgetItem(qpainel.value(8).toString())); //Estado
            ui->twgIntegrantesRodada->item(cont,8)->setTextAlignment(Qt::AlignCenter);
            ui->twgIntegrantesRodada->item(cont,8)->setForeground(corLetra.color());
            ui->twgIntegrantesRodada->item(cont,8)->setBackground(corFundo.color());

            ui->twgIntegrantesRodada->setItem(cont,9,new QTableWidgetItem(qpainel.value(9).toString())); //Pais
            ui->twgIntegrantesRodada->item(cont,9)->setTextAlignment(Qt::AlignCenter);
            ui->twgIntegrantesRodada->item(cont,9)->setForeground(corLetra.color());
            ui->twgIntegrantesRodada->item(cont,9)->setBackground(corFundo.color());

            ui->twgIntegrantesRodada->setItem(cont,10,new QTableWidgetItem(qpainel.value(10).toString())); //Cambio Data Hora
            ui->twgIntegrantesRodada->item(cont,10)->setTextAlignment(Qt::AlignCenter);
            ui->twgIntegrantesRodada->item(cont,10)->setForeground(corLetra.color());
            ui->twgIntegrantesRodada->item(cont,10)->setBackground(corFundo.color());

            ui->twgIntegrantesRodada->setItem(cont,11,new QTableWidgetItem(qpainel.value(11).toString())); //FILA Data Hora
            ui->twgIntegrantesRodada->item(cont,11)->setTextAlignment(Qt::AlignCenter);
            ui->twgIntegrantesRodada->item(cont,11)->setForeground(corLetra.color());
            ui->twgIntegrantesRodada->item(cont,11)->setBackground(corFundo.color());

            ui->twgIntegrantesRodada->setItem(cont,12,new QTableWidgetItem(qpainel.value(12).toString())); //QAP Data Hora
            ui->twgIntegrantesRodada->item(cont,12)->setTextAlignment(Qt::AlignCenter);
            ui->twgIntegrantesRodada->item(cont,12)->setForeground(corLetra.color());
            ui->twgIntegrantesRodada->item(cont,12)->setBackground(corFundo.color());

            ui->twgIntegrantesRodada->setItem(cont,13,new QTableWidgetItem(qpainel.value(13).toString())); //Quantidade Cambio
            ui->twgIntegrantesRodada->item(cont,13)->setTextAlignment(Qt::AlignCenter);
            ui->twgIntegrantesRodada->item(cont,13)->setForeground(corLetra.color());
            ui->twgIntegrantesRodada->item(cont,13)->setBackground(corFundo.color());

            ui->twgIntegrantesRodada->setItem(cont,14,new QTableWidgetItem(qpainel.value(14).toString())); //QRX Data Hora
            ui->twgIntegrantesRodada->item(cont,14)->setTextAlignment(Qt::AlignCenter);
            ui->twgIntegrantesRodada->item(cont,14)->setForeground(corLetra.color());
            ui->twgIntegrantesRodada->item(cont,14)->setBackground(corFundo.color());

            ui->twgIntegrantesRodada->setItem(cont,15,new QTableWidgetItem(qpainel.value(14).toString())); //QRX Data Hora
            ui->twgIntegrantesRodada->item(cont,15)->setTextAlignment(Qt::AlignCenter);
            ui->twgIntegrantesRodada->item(cont,15)->setForeground(corLetra.color());
            ui->twgIntegrantesRodada->item(cont,15)->setBackground(corFundo.color());

            ui->twgIntegrantesRodada->setRowHeight(cont,20);
            cont++;
        }        
        ui->twgIntegrantesRodada->resizeColumnToContents(0);
        ui->twgIntegrantesRodada->resizeColumnToContents(1);
        ui->twgIntegrantesRodada->resizeColumnToContents(2);
        //ui->twgIntegrantesRodada->resizeColumnToContents(3);
        ui->twgIntegrantesRodada->setColumnWidth(3,100);
        ui->twgIntegrantesRodada->resizeColumnToContents(4);
        ui->twgIntegrantesRodada->setColumnWidth(4,200);
        ui->twgIntegrantesRodada->resizeColumnToContents(5);
        ui->twgIntegrantesRodada->resizeColumnToContents(6);
        ui->twgIntegrantesRodada->resizeColumnToContents(7);
        ui->twgIntegrantesRodada->resizeColumnToContents(8);
        ui->twgIntegrantesRodada->resizeColumnToContents(9);        
        ui->twgIntegrantesRodada->resizeColumnToContents(10);
        ui->twgIntegrantesRodada->resizeColumnToContents(11);
        ui->twgIntegrantesRodada->resizeColumnToContents(12);
        ui->twgIntegrantesRodada->resizeColumnToContents(13);
        ui->twgIntegrantesRodada->resizeColumnToContents(14);

        /*
        ui->twgIntegrantesRodada->setColumnWidth(0,100);
        ui->twgIntegrantesRodada->setColumnWidth(1,100);
        ui->twgIntegrantesRodada->setColumnWidth(2,25);
        ui->twgIntegrantesRodada->setColumnWidth(3,200);
        ui->twgIntegrantesRodada->setColumnWidth(4,150);
        ui->twgIntegrantesRodada->setColumnWidth(5,200);
        ui->twgIntegrantesRodada->setColumnWidth(6,25);
        ui->twgIntegrantesRodada->setColumnWidth(7,150);
        ui->twgIntegrantesRodada->setColumnWidth(8,200);
        ui->twgIntegrantesRodada->setColumnWidth(9,150);
        */
        ui->twgIntegrantesRodada->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->twgIntegrantesRodada->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->twgIntegrantesRodada->verticalHeader()->setVisible(false);
        ui->twgIntegrantesRodada->horizontalHeader()->setVisible(false);
        //x ui->twgIntegrantesRodada->setStyleSheet("QTableView {selection-background-color:blue}");
        ConDB.fechar();
        ui->edtIndicativo->clear();
        ui->edtIndicativo->setFocus();
    }
    // dados estatisticos da barra de status
    ConDB.abrir();
        QSqlQuery total, fila, qap, qrx, qrt;

        total.exec("SELECT COUNT(*) FROM rodadasIntegrantes WHERE fkrodadaaberta = "+ui->edtFkRodada->text()+";");
        while (total.next()) {
            ui->lblTotalParticipantes->setText("Amigos Radioamadores :: "+total.value(0).toString());
        }

        fila.exec("SELECT COUNT(*) FROM rodadasIntegrantes WHERE fkstatus = 1 AND fkrodadaaberta = "+ui->edtFkRodada->text()+";");
        while (fila.next()) {
            ui->lblEstatisticaFila->setText("Fila :: "+fila.value(0).toString());
        }

        qap.exec("SELECT COUNT(*) FROM rodadasIntegrantes WHERE fkstatus = 2 AND fkrodadaaberta = "+ui->edtFkRodada->text()+";");
        while (qap.next()) {            
            ui->lblEstatisticaQap->setText("QAP :: "+qap.value(0).toString());
        }

        qrx.exec("SELECT COUNT(*) FROM rodadasIntegrantes WHERE fkstatus = 3 AND fkrodadaaberta = "+ui->edtFkRodada->text()+";");
        while (qrx.next()) {
            ui->lblEstatisticaQrx->setText("QRX :: "+qrx.value(0).toString());
        }

        qrt.exec("SELECT COUNT(*) FROM rodadasIntegrantes WHERE fkstatus = 4 AND fkrodadaaberta = "+ui->edtFkRodada->text()+";");
        while (qrt.next()) {
            ui->lblEstatisticaQrt->setText("QRT :: "+qrt.value(0).toString());
        }
    ConDB.fechar();
}

void PainelDeRodadas::on_btnAtualizarPainelRodada_clicked()
{
    AtualizarPainelRodada();
}


void PainelDeRodadas::on_btnParticiparRodada_clicked()
{
    if(ui->edtIndicativo->text().isEmpty()){
        ui->edtIndicativo->setFocus();
    }else{
        IncluirRadioamadorRodada(ui->edtFkRodada->text(),ui->edtIndicativo->text().toUpper());
    }
}


void PainelDeRodadas::on_btnAtualizarPainelRodada_released()
{

}


void PainelDeRodadas::on_twgIntegrantesRodada_cellActivated(int row, int column)
{

}


void PainelDeRodadas::on_twgIntegrantesRodada_cellDoubleClicked(int row, int column)
{

}


void PainelDeRodadas::on_twgIntegrantesRodada_cellClicked(int row, int column)
{
    QClipboard *CopiarParaMemoria = QApplication::clipboard();
    CopiarParaMemoria->setText(ui->twgIntegrantesRodada->item(ui->twgIntegrantesRodada->currentRow(),3)->text());
    ui->lblIndicativoComentarios->setText("Indicativo Selecionado :: "+ui->twgIntegrantesRodada->item(ui->twgIntegrantesRodada->currentRow(),3)->text());
    statusBotoes(true);
    painelLogParticipacao();
    painelComentarios();
}

void PainelDeRodadas::raQap(QString id_rodada){
    conexaodb ConDB;
    ConDB.abrir();
        QSqlQuery q;
        q.prepare("UPDATE rodadasIntegrantes SET fkstatus = 2, cambiodh = time('now','localtime'), qapdh = time('now','localtime'), cambioqtd = cambioqtd +1 WHERE id = "+id_rodada+";");
        q.exec();
    ConDB.fechar();
    AtualizarPainelRodada();
}

void PainelDeRodadas::raQrx(QString id_rodada){
    conexaodb ConDB;
    ConDB.abrir();
        QSqlQuery q;
        q.prepare("UPDATE rodadasIntegrantes SET fkstatus = 3, cambiodh = time('now','localtime'), qrxdh = time('now','localtime') WHERE id = "+id_rodada+";");
        q.exec();
    ConDB.fechar();
    AtualizarPainelRodada();
}

void PainelDeRodadas::raQrt(QString id_rodada){
    conexaodb ConDB;
    ConDB.abrir();
        QSqlQuery q;
        q.prepare("UPDATE rodadasIntegrantes SET fkstatus = 4, cambiodh = time('now','localtime'), qrtdh = time('now','localtime') WHERE id = "+id_rodada+";");
        q.exec();
    ConDB.fechar();
    AtualizarPainelRodada();
}

void PainelDeRodadas::raObs(QString id_rodada, QString obsAtual){
    conexaodb ConDB;
    ConDB.abrir();
        QSqlQuery q;
        q.prepare("UPDATE rodadasIntegrantes SET obs = '"+obsAtual+"' WHERE id = "+id_rodada+";");
        q.exec();
    ConDB.fechar();
    AtualizarPainelRodada();
}

void PainelDeRodadas::RemoverRAnaRodada(QString id_rodada, QString indicativo){
    radioamador ra;
    QString fkradioamador = ra.id(indicativo);
    conexaodb ConDB;
    ConDB.abrir();
        QSqlQuery q;
        q.prepare("DELETE FROM rodadasIntegrantes WHERE id = "+id_rodada+" AND fkradioamador = "+fkradioamador+";");
        q.exec();
    ConDB.fechar();
    AtualizarPainelRodada();
}

void PainelDeRodadas::on_btnQap_clicked()
{
    raQap(ui->twgIntegrantesRodada->item(ui->twgIntegrantesRodada->currentRow(),0)->text());
}


void PainelDeRodadas::on_btnQrx_clicked()
{
    raQrx(ui->twgIntegrantesRodada->item(ui->twgIntegrantesRodada->currentRow(),0)->text());
}


void PainelDeRodadas::on_btnQrt_clicked()
{
    raQrt(ui->twgIntegrantesRodada->item(ui->twgIntegrantesRodada->currentRow(),0)->text());
}


void PainelDeRodadas::on_btnObs_clicked()
{
    if(ui->twgIntegrantesRodada->item(ui->twgIntegrantesRodada->currentRow(),1)->text() == "!"){
        raObs(ui->twgIntegrantesRodada->item(ui->twgIntegrantesRodada->currentRow(),0)->text(),"-");
    }else{
        raObs(ui->twgIntegrantesRodada->item(ui->twgIntegrantesRodada->currentRow(),0)->text(),"!");
    }
}


void PainelDeRodadas::on_btnDel_clicked()
{
    QMessageBox::StandardButton resposta;
    QString RadioAmadorExcluir = ui->twgIntegrantesRodada->item(ui->twgIntegrantesRodada->currentRow(),3)->text()+" "+ui->twgIntegrantesRodada->item(ui->twgIntegrantesRodada->currentRow(),4)->text();
    resposta = QMessageBox::question(this, "Remoção de Integrante da Rodada", "Excluir o Radioamador da Rodada Atual?", QMessageBox::Yes|QMessageBox::No);
    if (resposta == QMessageBox::Yes ){
        RemoverRAnaRodada(ui->twgIntegrantesRodada->item(ui->twgIntegrantesRodada->currentRow(),0)->text(),ui->twgIntegrantesRodada->item(ui->twgIntegrantesRodada->currentRow(),3)->text());
    }
}


void PainelDeRodadas::on_btnColarIndicativo_clicked()
{
    ui->edtIndicativo->clear();
    ui->edtIndicativo->paste();
}


void PainelDeRodadas::on_btnFim_clicked()
{
    QMessageBox::StandardButton resposta;
    resposta = QMessageBox::question(this, "Fechar a Rodada", "Tem que deseja FECHAR Rodada ?", QMessageBox::Yes|QMessageBox::No);
    if (resposta == QMessageBox::Yes ){
        QString idrodada = ui->edtFkRodada->text();
        conexaodb ConDB;
        ConDB.abrir();
            QSqlQuery q;
            q.exec("INSERT INTO estatisticasRodadasAbertas SELECT * FROM rodadasAbertas WHERE id = "+idrodada+";");
            q.exec("INSERT INTO estatisticasRodadasIntegrantes SELECT * FROM rodadasIntegrantes WHERE fkrodadaaberta = "+idrodada+";");
            q.exec("DELETE FROM rodadasIntegrantes WHERE fkrodadaaberta = "+idrodada+";");
            q.exec("DELETE FROM rodadasAbertas WHERE id = "+idrodada+";");
            q.exec("UPDATE estatisticasRodadasAbertas SET fim = DATETIME('now','localtime') WHERE id = "+idrodada+";");
        ConDB.fechar();
        AtualizarPainelRodada();
    }
}


void PainelDeRodadas::on_btnEditarRA_clicked()
{
    frmRadioamadorDadosComComentarios frmRa(this, ui->twgIntegrantesRodada->item(ui->twgIntegrantesRodada->currentRow(),3)->text());
    frmRa.exec();
}


void PainelDeRodadas::on_edtIndicativo_returnPressed()
{

}


void PainelDeRodadas::on_edtIndicativo_cursorPositionChanged(int arg1, int arg2)
{

}


void PainelDeRodadas::on_btnInserirComentario_clicked()
{
    if(ui->edtComentariosRA->text().isEmpty()){
        ui->edtComentariosRA->setFocus();
    }else{
        radioamador ra;
        QString idRa = ra.id(ui->twgIntegrantesRodada->item(ui->twgIntegrantesRodada->currentRow(),3)->text());
        conexaodb ConDB;
        ConDB.abrir();
            QSqlQuery ins;
            ins.exec("INSERT INTO radioamadoresComentarios(fkradioamador, comentario) VALUES("+idRa+",UPPER('"+ui->edtComentariosRA->text()+"'));");
            ui->edtComentariosRA->clear();
        ConDB.fechar();
        ui->edtComentariosRA->setFocus();
        painelComentarios();
    }
}


void PainelDeRodadas::on_twgComentariosRA_clicked(const QModelIndex &index)
{
    ui->btnRemoverComentario->setEnabled(true);
}


void PainelDeRodadas::on_btnRemoverComentario_clicked()
{
    conexaodb ConDB;
    ConDB.abrir();
        QSqlQuery d;
        d.exec("DELETE FROM radioamadoresComentarios WHERE id = "+ui->twgComentariosRA->item(ui->twgComentariosRA->currentRow(),0)->text()+";");
    ConDB.fechar();
    painelComentarios();
    ui->btnRemoverComentario->setEnabled(false);
    ui->edtComentariosRA->setFocus();
}


void PainelDeRodadas::on_pushButton_clicked()
{
    this->close();
}

