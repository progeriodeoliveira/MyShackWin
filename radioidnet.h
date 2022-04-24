#ifndef RADIOIDNET_H
#define RADIOIDNET_H

#include "QNetworkAccessManager"
#include "QList"

class radioidnet
{
public:
    radioidnet();
    QString obterId(QString indicativo);
    QString obterRadio_id(QString indicativo);
    QString obterNome(QString indicativo);
    QString obterApelido(QString indicativo);
    QString obterSobrenome(QString indicativo);
    QString obterCidade(QString indicativo);
    QString obterEstado(QString indicativo);
    QString obterPais(QString indicativo);
    QString obterObservacoes(QString indicativo);
    QStringList obterDados(QString indicativo);


private:

};

#endif // RADIOIDNET_H
