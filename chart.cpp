#include "chart.h"
#include <QChart>
#include "FileData.h"
#include "sizecalculator.h"
QtCharts::QChart* Chart::createChart() {
    //Создаем объект chart
    QtCharts::QChart *chart = new QtCharts::QChart();
    //рисуем легенду
    drawLegend(chart->legend());
    //Вызываем шаблонный метод и заносим в chart Series своей диаграммы
    drawChart(chart);
    //возвращаем объект chart
    return chart;
}

void Chart::drawLegend(QtCharts::QLegend *legend)
{
    legend->setAlignment(Qt::AlignLeft);
}

