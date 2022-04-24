#include "radioidnet.h"
#include "configuracoes.h"
#include "QFileInfo"
#include "qnetwork.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>
#include <QFile>
#include <QTextStream>
#include <QFileSystemWatcher>
#include "downloadmgr.h"
#include "stdio.h"
#include "QNetworkAccessManager"
#include "QNetworkReply"
#include "QObject"
#include "configuracoes.h"
#include "QList"
#include "QStringList"


radioidnet::radioidnet()
{

}
// Atributos
QString radioidnet::obterId(QString indicativo){
    configuracoes config;
    QFile arquivoUsersJson(config.caminhoUsersDB());
    if (!arquivoUsersJson.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Nao consegui abrir";
    }
    QTextStream stream(&arquivoUsersJson);
    QString dadosUsersJson = arquivoUsersJson.readAll();
    QJsonParseError jsonError;
    QJsonDocument docUsersJson = QJsonDocument::fromJson(dadosUsersJson.toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError && !docUsersJson.isNull()) {
        qDebug() << "Erro no Formato JSon!" << jsonError.error;
    }
    // inicio busca
    QJsonObject usersRootObj = docUsersJson.object();
    QJsonValue usersRaiz = usersRootObj.value("users");
    if (usersRaiz.type() == QJsonValue::Array) {
        QJsonArray usersArray = usersRaiz.toArray();
        for (int i = 0; i < usersArray.count(); i++) {
            QJsonValue likeValueChild = usersArray.at(i);
            if (likeValueChild.type() == QJsonValue::Object) {
                QJsonObject likeObj = likeValueChild.toObject();
                QJsonValue callsign = likeObj.value("callsign");
                if (callsign == indicativo){
                    QJsonValue id = likeObj.value("id").toInteger();
                    return QString::number(id.toInteger());
                }
            }
        }
    }
    return "0";
}

QString radioidnet::obterRadio_id(QString indicativo){
    configuracoes config;
    QFile arquivoUsersJson(config.caminhoUsersDB());
    if (!arquivoUsersJson.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Nao consegui abrir";
    }
    QTextStream stream(&arquivoUsersJson);
    QString dadosUsersJson = arquivoUsersJson.readAll();
    QJsonParseError jsonError;
    QJsonDocument docUsersJson = QJsonDocument::fromJson(dadosUsersJson.toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError && !docUsersJson.isNull()) {
        qDebug() << "Erro no Formato JSon!" << jsonError.error;
    }
    // inicio busca
    QJsonObject usersRootObj = docUsersJson.object();
    QJsonValue usersRaiz = usersRootObj.value("users");
    if (usersRaiz.type() == QJsonValue::Array) {
        QJsonArray usersArray = usersRaiz.toArray();
        for (int i = 0; i < usersArray.count(); i++) {
            QJsonValue likeValueChild = usersArray.at(i);
            if (likeValueChild.type() == QJsonValue::Object) {
                QJsonObject likeObj = likeValueChild.toObject();
                QJsonValue callsign = likeObj.value("callsign");
                if (callsign == indicativo){
                    QJsonValue radio_id = likeObj.value("radio_id").toInteger();
                    return QString::number(radio_id.toInteger());
                }
            }
        }
    }
    return "0";
}

QString radioidnet::obterNome(QString indicativo){
    configuracoes config;
    QFile arquivoUsersJson(config.caminhoUsersDB());
    if (!arquivoUsersJson.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Nao consegui abrir";
    }
    QTextStream stream(&arquivoUsersJson);
    QString dadosUsersJson = arquivoUsersJson.readAll();
    QJsonParseError jsonError;
    QJsonDocument docUsersJson = QJsonDocument::fromJson(dadosUsersJson.toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError && !docUsersJson.isNull()) {
        qDebug() << "Erro no Formato JSon!" << jsonError.error;
    }
    // inicio busca
    QJsonObject usersRootObj = docUsersJson.object();
    QJsonValue usersRaiz = usersRootObj.value("users");
    if (usersRaiz.type() == QJsonValue::Array) {
        QJsonArray usersArray = usersRaiz.toArray();
        for (int i = 0; i < usersArray.count(); i++) {
            QJsonValue likeValueChild = usersArray.at(i);
            if (likeValueChild.type() == QJsonValue::Object) {
                QJsonObject likeObj = likeValueChild.toObject();
                QJsonValue callsign = likeObj.value("callsign");
                if (callsign == indicativo){
                    QJsonValue nome = likeObj.value("name").toString().toUpper();
                    return nome.toString();
                }
            }
        }
    }
    return "0";
}

QString radioidnet::obterApelido(QString indicativo){
    configuracoes config;
    QFile arquivoUsersJson(config.caminhoUsersDB());
    if (!arquivoUsersJson.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Nao consegui abrir";
    }
    QTextStream stream(&arquivoUsersJson);
    QString dadosUsersJson = arquivoUsersJson.readAll();
    QJsonParseError jsonError;
    QJsonDocument docUsersJson = QJsonDocument::fromJson(dadosUsersJson.toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError && !docUsersJson.isNull()) {
        qDebug() << "Erro no Formato JSon!" << jsonError.error;
    }
    // inicio busca
    QJsonObject usersRootObj = docUsersJson.object();
    QJsonValue usersRaiz = usersRootObj.value("users");
    if (usersRaiz.type() == QJsonValue::Array) {
        QJsonArray usersArray = usersRaiz.toArray();
        for (int i = 0; i < usersArray.count(); i++) {
            QJsonValue likeValueChild = usersArray.at(i);
            if (likeValueChild.type() == QJsonValue::Object) {
                QJsonObject likeObj = likeValueChild.toObject();
                QJsonValue callsign = likeObj.value("callsign");
                if (callsign == indicativo){
                    QJsonValue apelido = likeObj.value("fname").toString().toUpper();
                    return apelido.toString();
                }
            }
        }
    }
    return "0";
}


QString radioidnet::obterSobrenome(QString indicativo){
    configuracoes config;
    QFile arquivoUsersJson(config.caminhoUsersDB());
    if (!arquivoUsersJson.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Nao consegui abrir";
    }
    QTextStream stream(&arquivoUsersJson);
    QString dadosUsersJson = arquivoUsersJson.readAll();
    QJsonParseError jsonError;
    QJsonDocument docUsersJson = QJsonDocument::fromJson(dadosUsersJson.toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError && !docUsersJson.isNull()) {
        qDebug() << "Erro no Formato JSon!" << jsonError.error;
    }
    // inicio busca
    QJsonObject usersRootObj = docUsersJson.object();
    QJsonValue usersRaiz = usersRootObj.value("users");
    if (usersRaiz.type() == QJsonValue::Array) {
        QJsonArray usersArray = usersRaiz.toArray();
        for (int i = 0; i < usersArray.count(); i++) {
            QJsonValue likeValueChild = usersArray.at(i);
            if (likeValueChild.type() == QJsonValue::Object) {
                QJsonObject likeObj = likeValueChild.toObject();
                QJsonValue callsign = likeObj.value("callsign");
                if (callsign == indicativo){
                    QJsonValue sobreNome = likeObj.value("surname").toString().toUpper();
                    return sobreNome.toString();
                }
            }
        }
    }
    return "0";
}

QString radioidnet::obterCidade(QString indicativo){
    configuracoes config;
    QFile arquivoUsersJson(config.caminhoUsersDB());
    if (!arquivoUsersJson.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Nao consegui abrir";
    }
    QTextStream stream(&arquivoUsersJson);
    QString dadosUsersJson = arquivoUsersJson.readAll();
    QJsonParseError jsonError;
    QJsonDocument docUsersJson = QJsonDocument::fromJson(dadosUsersJson.toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError && !docUsersJson.isNull()) {
        qDebug() << "Erro no Formato JSon!" << jsonError.error;
    }
    // inicio busca
    QJsonObject usersRootObj = docUsersJson.object();
    QJsonValue usersRaiz = usersRootObj.value("users");
    if (usersRaiz.type() == QJsonValue::Array) {
        QJsonArray usersArray = usersRaiz.toArray();
        for (int i = 0; i < usersArray.count(); i++) {
            QJsonValue likeValueChild = usersArray.at(i);
            if (likeValueChild.type() == QJsonValue::Object) {
                QJsonObject likeObj = likeValueChild.toObject();
                QJsonValue callsign = likeObj.value("callsign");
                if (callsign == indicativo){
                    QJsonValue cidade = likeObj.value("city").toString().toUpper();
                    return cidade.toString();
                }
            }
        }
    }
    return "0";
}

QString radioidnet::obterEstado(QString indicativo){
    configuracoes config;
    QFile arquivoUsersJson(config.caminhoUsersDB());
    if (!arquivoUsersJson.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Nao consegui abrir";
    }
    QTextStream stream(&arquivoUsersJson);
    QString dadosUsersJson = arquivoUsersJson.readAll();
    QJsonParseError jsonError;
    QJsonDocument docUsersJson = QJsonDocument::fromJson(dadosUsersJson.toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError && !docUsersJson.isNull()) {
        qDebug() << "Erro no Formato JSon!" << jsonError.error;
    }
    // inicio busca
    QJsonObject usersRootObj = docUsersJson.object();
    QJsonValue usersRaiz = usersRootObj.value("users");
    if (usersRaiz.type() == QJsonValue::Array) {
        QJsonArray usersArray = usersRaiz.toArray();
        for (int i = 0; i < usersArray.count(); i++) {
            QJsonValue likeValueChild = usersArray.at(i);
            if (likeValueChild.type() == QJsonValue::Object) {
                QJsonObject likeObj = likeValueChild.toObject();
                QJsonValue callsign = likeObj.value("callsign");
                if (callsign == indicativo){
                    QJsonValue estado = likeObj.value("state").toString().toUpper();
                    return estado.toString();
                }
            }
        }
    }
    return "0";
}


QString radioidnet::obterPais(QString indicativo){
    configuracoes config;
    QFile arquivoUsersJson(config.caminhoUsersDB());
    if (!arquivoUsersJson.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Nao consegui abrir";
    }
    QTextStream stream(&arquivoUsersJson);
    QString dadosUsersJson = arquivoUsersJson.readAll();
    QJsonParseError jsonError;
    QJsonDocument docUsersJson = QJsonDocument::fromJson(dadosUsersJson.toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError && !docUsersJson.isNull()) {
        qDebug() << "Erro no Formato JSon!" << jsonError.error;
    }
    // inicio busca
    QJsonObject usersRootObj = docUsersJson.object();
    QJsonValue usersRaiz = usersRootObj.value("users");
    if (usersRaiz.type() == QJsonValue::Array) {
        QJsonArray usersArray = usersRaiz.toArray();
        for (int i = 0; i < usersArray.count(); i++) {
            QJsonValue likeValueChild = usersArray.at(i);
            if (likeValueChild.type() == QJsonValue::Object) {
                QJsonObject likeObj = likeValueChild.toObject();
                QJsonValue callsign = likeObj.value("callsign");
                if (callsign == indicativo){
                    QJsonValue pais = likeObj.value("country").toString().toUpper();
                    return pais.toString();
                }
            }
        }
    }
    return "0";
}

QString radioidnet::obterObservacoes(QString indicativo){
    configuracoes config;
    QFile arquivoUsersJson(config.caminhoUsersDB());
    if (!arquivoUsersJson.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Nao consegui abrir";
    }
    QTextStream stream(&arquivoUsersJson);
    QString dadosUsersJson = arquivoUsersJson.readAll();
    QJsonParseError jsonError;
    QJsonDocument docUsersJson = QJsonDocument::fromJson(dadosUsersJson.toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError && !docUsersJson.isNull()) {
        qDebug() << "Erro no Formato JSon!" << jsonError.error;
    }
    // inicio busca
    QJsonObject usersRootObj = docUsersJson.object();
    QJsonValue usersRaiz = usersRootObj.value("users");
    if (usersRaiz.type() == QJsonValue::Array) {
        QJsonArray usersArray = usersRaiz.toArray();
        for (int i = 0; i < usersArray.count(); i++) {
            QJsonValue likeValueChild = usersArray.at(i);
            if (likeValueChild.type() == QJsonValue::Object) {
                QJsonObject likeObj = likeValueChild.toObject();
                QJsonValue callsign = likeObj.value("callsign");
                if (callsign == indicativo){
                    QJsonValue observacoes = likeObj.value("remarks").toString().toUpper();
                    return observacoes.toString();
                }
            }
        }
    }
    return "0";
}

QStringList radioidnet::obterDados(QString indicativo){
    QStringList dados;
    configuracoes config;
    QFile arquivoUsersJson(config.caminhoUsersDB());
    if (!arquivoUsersJson.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Nao consegui abrir";
    }
    QTextStream stream(&arquivoUsersJson);
    QString dadosUsersJson = arquivoUsersJson.readAll();
    QJsonParseError jsonError;
    QJsonDocument docUsersJson = QJsonDocument::fromJson(dadosUsersJson.toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError && !docUsersJson.isNull()) {
        qDebug() << "Erro no Formato JSon!" << jsonError.error;
    }
    // inicio busca
    QJsonObject usersRootObj = docUsersJson.object();
    QJsonValue usersRaiz = usersRootObj.value("users");
    if (usersRaiz.type() == QJsonValue::Array) {
        QJsonArray usersArray = usersRaiz.toArray();
        for (int i = 0; i < usersArray.count(); i++) {
            QJsonValue likeValueChild = usersArray.at(i);
            if (likeValueChild.type() == QJsonValue::Object) {
                QJsonObject likeObj = likeValueChild.toObject();
                QJsonValue callsign = likeObj.value("callsign");
                if (callsign == indicativo.toUpper()){
                    QJsonValue id = likeObj.value("id");
                    QJsonValue radio_id = likeObj.value("radio_id");
                    QJsonValue surname = likeObj.value("surname").toString().toUpper();
                    QJsonValue name = likeObj.value("name").toString().toUpper();
                    QJsonValue fname = likeObj.value("fname").toString().toUpper();
                    QJsonValue city = likeObj.value("city").toString().toUpper();
                    QJsonValue state = likeObj.value("state").toString().toUpper();
                    QJsonValue country = likeObj.value("country").toString().toUpper();
                    QJsonValue remarks = likeObj.value("remarks").toString().toUpper();
                    //dados << QString::number(id.toInteger()) << QString::number(radio_id.toInteger()) << surname.toString().toUpper() << name.toString().toUpper() << fname.toString().toUpper() << city.toString().toUpper() << state.toString().toUpper() << country.toString().toUpper() << remarks.toString().toUpper();
                    dados << QString::number(id.toInteger()) << QString::number(radio_id.toInteger()) << surname.toString().toUpper() << name.toString().toUpper() << fname.toString().toUpper() << city.toString().toUpper() << state.toString().toUpper() << country.toString().toUpper() << remarks.toString().toUpper();
                    return dados;
                    break;
                    // igual a 9 achou o registro, ou maior que 1
                    // 0 nao achou nada
                }
            }
        }
        dados << "0";
        return dados;
    }
}

// Métodos

