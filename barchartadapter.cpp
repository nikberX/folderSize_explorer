#include "barchartadapter.h"
#include <QDebug>
BarChartAdapter::BarChartAdapter()
{
    //создаем пустую диаграмму
    chart = chartCreator.createChart();
}

void BarChartAdapter::update()
{
    chart = chartCreator.createChart();
}
