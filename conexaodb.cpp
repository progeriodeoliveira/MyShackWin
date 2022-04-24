#include "conexaodb.h"


conexaodb::conexaodb()
{
    bancoDeDados = QSqlDatabase::addDatabase("QSQLITE");
}

void conexaodb::fechar(){
    bancoDeDados.close();
}

bool conexaodb::abrir(){
    configuracoes config;
    QString banco=config.caminhoBancoDeDados();
    bancoDeDados.setDatabaseName(banco);
    if(!bancoDeDados.open()){
        return false;
    }else{
        return true;
    }
}

