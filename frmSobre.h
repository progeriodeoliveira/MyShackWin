#ifndef FRMSOBRE_H
#define FRMSOBRE_H

#include <QDialog>

namespace Ui {
class frmSobre;
}

class frmSobre : public QDialog
{
    Q_OBJECT

public:
    explicit frmSobre(QWidget *parent = nullptr);
    ~frmSobre();

private:
    Ui::frmSobre *ui;
};

#endif // FRMSOBRE_H
