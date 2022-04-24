#ifndef FRMESTATISTICALOGRODADAS_H
#define FRMESTATISTICALOGRODADAS_H
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QPieSlice>

#include <QtCharts>


#include <QDialog>

namespace Ui {
class frmEstatisticaLogRodadas;
}

class frmEstatisticaLogRodadas : public QDialog
{
    Q_OBJECT

public:
    explicit frmEstatisticaLogRodadas(QWidget *parent = nullptr);
    ~frmEstatisticaLogRodadas();

private:
    Ui::frmEstatisticaLogRodadas *ui;
};

#endif // FRMESTATISTICALOGRODADAS_H
