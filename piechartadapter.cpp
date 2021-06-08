#include "piechartadapter.h"
#include <QDebug>
PieChartAdapter::PieChartAdapter()
{
    //Создаем пустую диаграмму
    chart = chartCreator.createChart();
}

void PieChartAdapter::update() {
    chart = chartCreator.createChart();
}
