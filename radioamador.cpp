#include "radioamador.h"
#include "conexaodb.h"

radioamador::radioamador()
{

}
QString radioamador::id(QString indicativo){
    conexaodb ConDB;
    ConDB.abrir();
        QSqlQuery query_consulta_ra;
        QString IdRA;
        query_consulta_ra.exec("SELECT id FROM radioamadores WHERE indicativo = '"+indicativo+"';");
        while (query_consulta_ra.next()) {
            IdRA = query_consulta_ra.value(0).toString();
        }
    ConDB.fechar();
    return IdRA;
}

bool radioamador::existeRaLocal(QString indicativo){
    conexaodb ConDB;
    ConDB.abrir();
        QSqlQuery qLocalizarRA;
        qLocalizarRA.exec("SELECT indicativo FROM radioamadores WHERE indicativo = UPPER('"+indicativo+"');");
        int cont = 0;
        while (qLocalizarRA.next()) {
            cont++;
        }
        if(cont == 1){
            return true;
        }else{
            return false;
        }
    ConDB.fechar();
}

bool radioamador::existeArquivoJson(QString indicativo){
    radioidnet dmr;
    QStringList dadosDrm = dmr.obterDados(indicativo);
    qDebug() << dadosDrm;
    if(dadosDrm.count() > 1){
        qDebug() << "EXISTE em json";
        return true;
    }else{
        qDebug() << "nao existe em json";
        return false;
    }
}

/*
void radioamador::IncluirRadioamador(QString indicativo){

        conexaodb ConDB;
        ConDB.abrir();
            QSqlQuery qLocalizarRA;
            qLocalizarRA.exec("SELECT indicativo FROM radioamadores WHERE indicativo = '"+indicativo+"';");
            int cont = 0;
            while(qLocalizarRA.next()){
                cont++;
            }
        ConDB.fechar();
        if(cont >= 1){
            IncluirNaRodada(fkrodada, indicativo);

        }else{
            radioidnet dmr;
            QStringList dadosDrm = dmr.obterDados(indicativo);

            if(dadosDrm.size() > 1){
                ConDB.abrir();
                    QSqlQuery qInserirRA;
                    qInserirRA.exec("INSERT INTO radioamadores(indicativo,dmrid,qra,nome,sobrenome,cidade,estado,pais) VALUES('"+indicativo+"','"+dadosDrm[0]+"','"+dadosDrm[3]+"','"+dadosDrm[3]+"','"+dadosDrm[4]+"','"+dadosDrm[5]+"','"+dadosDrm[6]+"','"+dadosDrm[7]+"');");
                ConDB.fechar();
                IncluirNaRodada(fkrodada,indicativo);

            }else{

                ConDB.abrir();
                    QSqlQuery qInserirRA;
                    qInserirRA.exec("INSERT INTO radioamadores(indicativo) VALUES('"+indicativo+"');");
                ConDB.fechar();
                IncluirNaRodada(fkrodada,indicativo);
            }
        }

}
*/
