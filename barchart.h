#ifndef BARCHART_H
#define BARCHART_H
#include "chart.h"
#include <QtCharts/QChart>
class BarChart : public Chart
{
public:
    void drawChart(QtCharts::QChart*) override;
};

#endif // BARCHART_H
