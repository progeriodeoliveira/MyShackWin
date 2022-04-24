#ifndef FRMLISTARODADASABERTAS_H
#define FRMLISTARODADASABERTAS_H

#include <QDialog>

namespace Ui {
class frmListaRodadasAbertas;
}

class frmListaRodadasAbertas : public QDialog
{
    Q_OBJECT

public:
    explicit frmListaRodadasAbertas(QWidget *parent = nullptr);
    ~frmListaRodadasAbertas();

private slots:
    void on_twgListaRodadasAbertas_cellClicked(int row, int column);

    void on_btnRetornarRodada_clicked();

    void on_btnFecharRodada_clicked();

    void atualizarPainelRodadas();

    void on_btnAtualizarDados_clicked();

    void on_btnExcluirRodada_clicked();

    void botoes(bool botoesStatus);

    void on_twgListaRodadasAbertas_clicked(const QModelIndex &index);

    void zerarCampos();

    void on_btnSair_clicked();

private:
    Ui::frmListaRodadasAbertas *ui;
};

#endif // FRMLISTARODADASABERTAS_H
