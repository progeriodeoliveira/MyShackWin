#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFile>
#include <QDebug>
#include <configuracoes.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // configuracoes de tema
    configuracoes conf;
    QFile File(conf.caminhoTema());
    if(File.open(QFile::ReadOnly)){
        QString StyleSheet = QLatin1String(File.readAll());
        qApp->setStyleSheet(StyleSheet);
    }else{
        qDebug() << "nao abriu";
        qDebug() << conf.caminhoTema();
    }

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "MyShackDB-Rodadas-Marki_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    MainWindow w;
    w.show();
    return a.exec();

}

