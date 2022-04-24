#include "configuracoes.h"
#include "QString"
#include "QSettings"
#include "QDir"
#include "QDebug"

configuracoes::configuracoes()
{

}

QSettings settings(QString("C:\\MyShackJson\\configuracoes\\MyShackDB-WIN-Rodadas.conf"), QSettings::IniFormat);


QString configuracoes::versaoSistema(){
    settings.beginGroup("MyShackDB");
    QString versao = settings.value("Versao").toString();
    settings.endGroup();
    //qDebug() << versao;
    return versao;
}

QString configuracoes::caminhoUsersDB(){
    settings.beginGroup("Sistema");
    QString caminhoUsersDB = settings.value("caminhoUsersDB").toString();
    settings.endGroup();
    //qDebug() << caminhoUsersDB;
    return caminhoUsersDB;
}

QString configuracoes::urlRAdioIDNet(){
    settings.beginGroup("Sistema");
    QString urlRAdioIDNet = settings.value("urlRAdioIDNet").toString();
    settings.endGroup();
    //qDebug() << urlRAdioIDNet;
    return urlRAdioIDNet;
}

QString configuracoes::caminhoBancoDeDados(){
    settings.beginGroup("Sistema");
    QString caminhoBancoDeDados = settings.value("caminhoBancoDeDados").toString();
    settings.endGroup();
    //qDebug() << caminhoBancoDeDados;
    return caminhoBancoDeDados;
}

QString configuracoes::caminhoTema(){
    settings.beginGroup("Sistema");
    QString caminhoTema = settings.value("tema").toString();
    settings.endGroup();
    //qDebug() << caminhoBancoDeDados;
    return caminhoTema;
}
