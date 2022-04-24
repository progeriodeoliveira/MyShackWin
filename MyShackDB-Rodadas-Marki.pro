QT       += core gui sql network charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    PainelDeRodadas.cpp \
    conexaodb.cpp \
    configuracoes.cpp \
    coordenadores.cpp \
    frmEstatisticaLogRodadas.cpp \
    frmListaRodadasAbertas.cpp \
    frmRadioamadores.cpp \
    frmRodadasAbrir.cpp \
    frmRodadasCadastro.cpp \
    frmSobre.cpp \
    frmcoordenadorescadastro.cpp \
    frmradioamadordadoscomcomentarios.cpp \
    main.cpp \
    mainwindow.cpp \
    radioamador.cpp \
    radioidnet.cpp

HEADERS += \
    PainelDeRodadas.h \
    conexaodb.h \
    configuracoes.h \
    coordenadores.h \
    frmEstatisticaLogRodadas.h \
    frmListaRodadasAbertas.h \
    frmRadioamadores.h \
    frmRodadasAbrir.h \
    frmRodadasCadastro.h \
    frmSobre.h \
    frmcoordenadorescadastro.h \
    frmradioamadordadoscomcomentarios.h \
    mainwindow.h \
    radioamador.h \
    radioidnet.h

FORMS += \
    PainelDeRodadas.ui \
    frmEstatisticaLogRodadas.ui \
    frmListaRodadasAbertas.ui \
    frmRadioamadores.ui \
    frmRodadasAbrir.ui \
    frmRodadasCadastro.ui \
    frmSobre.ui \
    frmcoordenadorescadastro.ui \
    frmradioamadordadoscomcomentarios.ui \
    mainwindow.ui

TRANSLATIONS += \
    MyShackDB-Rodadas-Marki_pt_BR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Recursos.qrc \
    imgs/imagens.qrc

DISTFILES += \
    imgs/salvar.png
