#include "barchartadapter.h"

BarChartAdapter::BarChartAdapter()
{
    chart = chartCreator.createChart();
}

void BarChartAdapter::update()
{
    delete chart;
    chart = chartCreator.createChart();
}
