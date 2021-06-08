#ifndef PIECHART_H
#define PIECHART_H
#include "chart.h"
#include <QtCharts/QChart>
class PieChart : public Chart
{
public:
    void drawChart(QtCharts::QChart*) override;
};

#endif // PIECHART_H
