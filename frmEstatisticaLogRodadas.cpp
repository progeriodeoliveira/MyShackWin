#include "frmEstatisticaLogRodadas.h"
#include "ui_frmEstatisticaLogRodadas.h"
#include "conexaodb.h"


frmEstatisticaLogRodadas::frmEstatisticaLogRodadas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmEstatisticaLogRodadas)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
/*
    QLineSeries *series = new QLineSeries();

    conexaodb ConDB;
    ConDB.abrir();
        QSqlQuery q;
        q.exec("SELECT rodadasTitulo, COUNT(*) FROM estatisticasRodadasView WHERE radioamadoresIndicativo = 'PU2KGA' GROUP BY rodadasTitulo;");
        while(q.next()){
            *series << QPoint(q.value(0).toPoint(),q.value(1).toPoint());
        }
    ConDB.fechar();

    //*series << QPointF(11,1) << QPointF(13,3) << QPointF(17,6)<< QPointF(18,3) << QPointF(20,2);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Titulo Principal");
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->horizontalFrame);
*/
    QPieSeries *series = new QPieSeries();

    conexaodb ConDB;
    ConDB.abrir();
        QSqlQuery q;
        q.exec("SELECT rodadasTitulo, COUNT(*) FROM estatisticasRodadasView GROUP BY rodadasTitulo");

        while(q.next()){
            series->append(q.value(0).toString(), q.value(1).toInt());                            
        }

    ConDB.fechar();

    QChart *GraficoPizza = new QChart();
    //chart->legend()->hide();
    GraficoPizza->addSeries(series);
    GraficoPizza->setTitle("Rodada e Quantidade de Participantes");

    QChartView *VisualizacaoGraficoPizza = new QChartView(GraficoPizza);
    VisualizacaoGraficoPizza->setRenderHint(QPainter::Antialiasing);
    VisualizacaoGraficoPizza->setParent(ui->hztFrameGraficoPizza);
    VisualizacaoGraficoPizza->resize(350,350);

}

frmEstatisticaLogRodadas::~frmEstatisticaLogRodadas()
{
    delete ui;
}
