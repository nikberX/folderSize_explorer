#include "piechart.h"
#include "FileData.h"
#include "sizecalculator.h"
#include <QPieSeries>
#include <QPieSlice>
void PieChart::drawChart(QtCharts::QChart *chart)
{
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    series->setPieSize(1);
    FileData data = SizeCalculator::getInstance()->getData();
    double othersPercentage = 0;
    for (auto iterator = data.map.begin();iterator!=data.map.end();iterator++)
    {
        if (iterator.value()<5) {
            othersPercentage+=iterator.value();
        } else {
            series->append(new QtCharts::QPieSlice(iterator.key(),iterator.value()));
        }
    }
    if (othersPercentage>0) {
        series->append(new QtCharts::QPieSlice("others", othersPercentage));
    }
    chart->addSeries(series);
}
