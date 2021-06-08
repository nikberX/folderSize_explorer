#include "piechartadapter.h"

PieChartAdapter::PieChartAdapter()
{
    chart = chartCreator.createChart();
}

void PieChartAdapter::update() {
    delete chart;
    chart = chartCreator.createChart();
}
