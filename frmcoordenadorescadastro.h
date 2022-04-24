#ifndef FRMCOORDENADORESCADASTRO_H
#define FRMCOORDENADORESCADASTRO_H

#include <QDialog>
#include "conexaodb.h"
#include "radioidnet.h"
#include "QMessageBox"
#include "conexaodb.h"

namespace Ui {
class frmCoordenadoresCadastro;
}

class frmCoordenadoresCadastro : public QDialog
{
    Q_OBJECT

public:
    explicit frmCoordenadoresCadastro(QWidget *parent = nullptr);
    ~frmCoordenadoresCadastro();
    conexaodb ConDB;

private slots:
    void on_edtIndicativo_returnPressed();
    void pesquisaIndicativoDMR();
    void on_edtIndicativo_editingFinished();    
    void on_btnInserir_clicked();

    void on_btnInserir_toggled(bool checked);

    void on_pushButton_clicked();

    void listarCoordenadores();

    void zerarCampos();

    void configurarCampos();

    void on_twgCoordenadores_cellClicked(int row, int column);

    void on_btnNovo_clicked();

    bool temCampoVazio();

    void on_twgCoordenadores_cellActivated(int row, int column);

    void on_twgCoordenadores_clicked(const QModelIndex &index);

    void on_btnGravar_clicked();

    void on_btnAtualizar_clicked();

    void on_btnRemover_clicked();

private:
    Ui::frmCoordenadoresCadastro *ui;
};

#endif // FRMCOORDENADORESCADASTRO_H
