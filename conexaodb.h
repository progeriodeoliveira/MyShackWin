#ifndef CONEXAODB_H
#define CONEXAODB_H

#include "QtSql"
#include "configuracoes.h"

class conexaodb
{
public:
    conexaodb();
    void fechar();
    bool abrir();
    QSqlDatabase bancoDeDados;

};

#endif // CONEXAODB_H
