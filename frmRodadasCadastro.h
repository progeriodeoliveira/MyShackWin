#ifndef FRMRODADASCADASTRO_H
#define FRMRODADASCADASTRO_H

#include <QDialog>

namespace Ui {
class frmRodadasCadastro;
}

class frmRodadasCadastro : public QDialog
{
    Q_OBJECT

public:
    explicit frmRodadasCadastro(QWidget *parent = nullptr);
    ~frmRodadasCadastro();

private slots:
    void on_twgListaRodadas_cellClicked(int row, int column);

    void on_pushButton_clicked();

    void on_btnGravarAlteracoes_clicked();

    void atualizarPainelRodadas();

    void on_btnSair_clicked();

    void on_btnArquivar_clicked();

    void on_btnLimparCampos_clicked();

    void zerarCampos();

    void on_btnInserirRodada_clicked();

    bool temCampoVazio();

    void botoes(bool status);

private:
    Ui::frmRodadasCadastro *ui;
};

#endif // FRMRODADASCADASTRO_H
