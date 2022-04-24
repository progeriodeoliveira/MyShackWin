#ifndef FRMRADIOAMADORDADOSCOMCOMENTARIOS_H
#define FRMRADIOAMADORDADOSCOMCOMENTARIOS_H

#include <QDialog>

namespace Ui {
class frmRadioamadorDadosComComentarios;
}

class frmRadioamadorDadosComComentarios : public QDialog
{
    Q_OBJECT

public:
    explicit frmRadioamadorDadosComComentarios(QWidget *parent = nullptr, QString indicativo = "0");
    ~frmRadioamadorDadosComComentarios();

private slots:
    void on_btnSalvar_clicked();

private:
    Ui::frmRadioamadorDadosComComentarios *ui;
};

#endif // FRMRADIOAMADORDADOSCOMCOMENTARIOS_H
