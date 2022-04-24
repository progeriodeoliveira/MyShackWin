#ifndef RADIOAMADOR_H
#define RADIOAMADOR_H

#include <QObject>
#include "radioidnet.h"

class radioamador
{
public:
    radioamador();
    QString id(QString indicativo);
    bool existeRaLocal(QString indicativo);
    bool existeArquivoJson(QString indicativo);
};

#endif // RADIOAMADOR_H
