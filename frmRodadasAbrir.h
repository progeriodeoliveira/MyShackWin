#ifndef FRMRODADASABRIR_H
#define FRMRODADASABRIR_H

#include <QDialog>

namespace Ui {
class frmRodadasAbrir;
}

class frmRodadasAbrir : public QDialog
{
    Q_OBJECT

public:
    explicit frmRodadasAbrir(QWidget *parent = nullptr);
    ~frmRodadasAbrir();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_twgRodadas_cellActivated(int row, int column);

    void on_twgRodadas_cellClicked(int row, int column);

    void on_btnSair_clicked();

private:
    Ui::frmRodadasAbrir *ui;
};

#endif // FRMRODADASABRIR_H
