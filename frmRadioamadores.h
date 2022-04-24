#ifndef FRMRADIOAMADORES_H
#define FRMRADIOAMADORES_H

#include <QDialog>

namespace Ui {
class frmRadioamadores;
}

class frmRadioamadores : public QDialog
{
    Q_OBJECT

public:
    explicit frmRadioamadores(QWidget *parent = nullptr);
    ~frmRadioamadores();

private slots:
    void on_btnLocalizaInsereRA_clicked();
    void zerarCampos();
    void recuperarDadosLocais();

    void on_btnInserirNovoRA_clicked();

    void on_btnGravarAlteracoes_clicked();

    void on_btnAdicionarComentario_clicked();

    void listarComentarios();

    void on_btnRemoverComentarios_clicked();

    void botoesComentarios(bool status);

    void on_twgComentariosRA_cellClicked(int row, int column);

    void on_btnRemoverRA_clicked();

    bool temCampoVazio();

    void on_edtPesquisaIndicativo_returnPressed();

    void LocalizarRA();

private:
    Ui::frmRadioamadores *ui;
};

#endif // FRMRADIOAMADORES_H
