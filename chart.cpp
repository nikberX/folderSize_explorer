#include "chart.h"
#include <QChart>
#include "FileData.h"
#include "sizecalculator.h"
QtCharts::QChart* Chart::createChart() {
    QtCharts::QChart *chart = new QtCharts::QChart();
    drawLegend(chart->legend());
    drawChart(chart);
    return chart;
}

void Chart::drawLegend(QtCharts::QLegend *legend)
{
    legend->setAlignment(Qt::AlignTop);
}

