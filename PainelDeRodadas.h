#ifndef PAINELDERODADAS_H
#define PAINELDERODADAS_H

#include <QDialog>

namespace Ui {
class PainelDeRodadas;
}

class PainelDeRodadas : public QDialog
{
    Q_OBJECT

public:
    explicit PainelDeRodadas(QWidget *parent = nullptr, QString id_nova_rodada = "0");
    ~PainelDeRodadas();


private slots:
    void on_btnSalvarComentariosDaRodada_clicked();

    void on_btnAtualizarPainelRodada_clicked();

    void IncluirRadioamadorRodada(QString fkrodada, QString indicativo);

    void on_btnParticiparRodada_clicked();

    void IncluirNaRodada(QString fkrodada, QString indicativo);

    void AtualizarPainelRodada();

    void on_btnAtualizarPainelRodada_released();

    void on_twgIntegrantesRodada_cellActivated(int row, int column);

    void on_twgIntegrantesRodada_cellDoubleClicked(int row, int column);

    void on_twgIntegrantesRodada_cellClicked(int row, int column);

    void on_btnQap_clicked();

    void raQap(QString id_rodada);

    void raQrx(QString id_rodada);

    void raQrt(QString id_rodada);

    void raObs(QString id_rodada, QString obsAtual);

    void on_btnQrx_clicked();

    void on_btnQrt_clicked();

    void on_btnObs_clicked();

    void on_btnDel_clicked();

    void RemoverRAnaRodada(QString id_rodada, QString indicativo);

    void on_btnColarIndicativo_clicked();

    void statusBotoes(bool status);

    bool existeRAnaRodada(QString fkrodada, QString indicativo);

    void on_btnFim_clicked();

    void on_btnEditarRA_clicked();

    void on_edtIndicativo_returnPressed();

    void on_edtIndicativo_cursorPositionChanged(int arg1, int arg2);

    void painelLogParticipacao();

    void painelComentarios();

    void on_btnInserirComentario_clicked();

    void on_twgComentariosRA_clicked(const QModelIndex &index);

    void on_btnRemoverComentario_clicked();

    void on_pushButton_clicked();

private:
    Ui::PainelDeRodadas *ui;
};

#endif // PAINELDERODADAS_H
