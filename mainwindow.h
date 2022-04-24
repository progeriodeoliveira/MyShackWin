#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include "QNetworkAccessManager"
#include "QFile"
#include "frmSobre.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSqlDatabase bancoDeDados=QSqlDatabase::addDatabase("QSQLITE");

private slots:
    void on_actionOperadores_triggered();

    void on_actionAbrir_uma_Rodada_triggered();

    void on_actionPainel_de_Rodadas_triggered();

    void on_actionVerificar_Rodadas_em_Aberto_triggered();

    void on_actionRodadas_triggered();


    void on_actionPesquisa_Indicativo_triggered();

    void on_actionSair_2_triggered();

    void on_actionQuantidade_de_Radioamadores_por_Roada_triggered();



    void on_actionIntegrantes_da_Rodada_triggered();



    void on_actionSo_bre_triggered();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
};
#endif // MAINWINDOW_H
