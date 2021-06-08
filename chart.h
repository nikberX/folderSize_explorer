#ifndef CHART_H
#define CHART_H
#include <QLegend>
#include "sizecalculator.h"

class Chart
{
public:
    QtCharts::QChart *createChart();
    virtual void drawChart(QtCharts::QChart*) = 0;
    void drawLegend(QtCharts::QLegend *legend);
};

#endif // CHART_H
