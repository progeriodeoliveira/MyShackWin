#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configuracoes.h"
#include "QtDebug"
#include "QNetworkReply"
#include "configuracoes.h"
#include "QFile"
#include "QFileInfo"
#include "QTextStream"
#include "radioidnet.h"
#include "QDebug"
#include "frmcoordenadorescadastro.h"
#include "frmRodadasAbrir.h"
#include "PainelDeRodadas.h"
#include "configuracoes.h"
#include "frmListaRodadasAbertas.h"
#include "frmRodadasCadastro.h"
#include "QLabel"
#include "QLineEdit"
#include "QSize"
#include "frmradioamadordadoscomcomentarios.h"
#include "frmRadioamadores.h"
#include "frmEstatisticaLogRodadas.h"
#include "QFile"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setStyleSheet("background-color: rgb(30,30,30);");


    configuracoes config;
    setWindowTitle(config.versaoSistema());
    //x ui->menubar->setStyleSheet("QMenuBar {background-color: rgb(69,69,69);}QMenuBar::item {spacing: 3px;padding: 2px 10px; color: rgb(255,255,255);  border-radius: 2px;} QMenuBar::item:pressed {background: rgb( 0, 0, 0);} QMenu { background-color: #ABABAB;   border: 1px solid black; margin: 2px; } QMenu::item { background-color: transparent; } QMenu::item:selected { background-color: #000000; color: rgb(255,255,255);}");
    //x ui->statusbar->setStyleSheet("background-color: rgba(200, 200, 200, 255);");

    // atualizacao users.json -> UsersDB.json

    static QFileInfo ArquivoUsersDBLocal (config.caminhoUsersDB());
    QDateTime dataCriacaoArqruivo = ArquivoUsersDBLocal.lastModified();
    QDate dataAtual = QDate::currentDate();
    if (dataAtual.toString("dd-MM-yyyy") != dataCriacaoArqruivo.toString("dd-MM-yyyy")){
        manager = new QNetworkAccessManager(this);
        connect(manager, &QNetworkAccessManager::finished, this, [&](QNetworkReply *reply){
            QByteArray dados = reply->readAll();
            QString str = QString::fromLatin1(dados);
            QString filename = config.caminhoUsersDB();
            QFile file(filename);
            if(file.open(QFile::WriteOnly | QFile::Text)) {
                QTextStream stream(&file);
                stream << str;
                file.close();
            }
        });
        manager->get(QNetworkRequest(QUrl(config.urlRAdioIDNet())));
    }
    //QLabel* lblPesquisaIndicativo = new QLabel(this);
    //ui->statusbar->addWidget(lblPesquisaIndicativo);
    //lblPesquisaIndicativo->setText("Pesquisa Indicativo: ");
    //lblPesquisaIndicativo->setStyleSheet("color: rgb(237, 212, 0);background-color: rgb(69,69,69);");
    //x ui->statusbar->setStyleSheet("background-color: rgb(69,69,69);");

    //QLineEdit* edtIndicativoConsultaRapida = new QLineEdit(this);
    //ui->statusbar->addWidget(edtIndicativoConsultaRapida);
    //edtIndicativoConsultaRapida->setStyleSheet("color: rgb(115, 210, 22);background-color: rgb(69,69,69);");

    //edtIndicativoConsultaRapida->setFixedWidth(100);
    //edtIndicativoConsultaRapida->setText("pu2nfo");
    //
    // debug

    /*
    QString indicativo = "PT7FWD";
    radioidnet dmr;
    QStringList dados = dmr.obterDados(indicativo);
    qDebug() << dados.size();
    if (dados.count() > 1 ){
        qDebug() << "Registro: "<< dados;
        qDebug() << "Dados 0: "<< dados[0];
        qDebug() << "Dados 1: "<< dados[1];
        qDebug() << "Dados 2: "<< dados[2];
        qDebug() << "Dados 3: "<< dados[3];
        qDebug() << "Dados 4: "<< dados[4];
        qDebug() << "Dados 5: "<< dados[5];
        qDebug() << "Dados 6: "<< dados[6];
        qDebug() << "Dados 7: "<< dados[7];
        qDebug() << "Dados 8: "<< dados[8];
    }

    */
}



MainWindow::~MainWindow()
{
    delete ui;

}



void MainWindow::on_actionOperadores_triggered()
{
    frmCoordenadoresCadastro formCoordenadores;
    formCoordenadores.exec();
}



void MainWindow::on_actionAbrir_uma_Rodada_triggered()
{
    frmRodadasAbrir formRodadasAbrir;
    formRodadasAbrir.exec();
}


void MainWindow::on_actionPainel_de_Rodadas_triggered()
{
    PainelDeRodadas PainelRodadas;
    PainelRodadas.exec();
}


void MainWindow::on_actionVerificar_Rodadas_em_Aberto_triggered()
{
    frmListaRodadasAbertas ListaRodadasAbertas;
    ListaRodadasAbertas.exec();
}


void MainWindow::on_actionRodadas_triggered()
{
    frmRodadasCadastro frmCadastroRodadas;
    frmCadastroRodadas.exec();
}


void MainWindow::on_actionPesquisa_Indicativo_triggered()
{
    frmRadioamadores frmRA;
    frmRA.exec();
}


void MainWindow::on_actionSair_2_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionQuantidade_de_Radioamadores_por_Roada_triggered()
{
    frmEstatisticaLogRodadas frmEstatistica;
    frmEstatistica.exec();
}


void MainWindow::on_actionIntegrantes_da_Rodada_triggered()
{

}




void MainWindow::on_actionSo_bre_triggered()
{
    frmSobre formSobre;
    formSobre.exec();
}

