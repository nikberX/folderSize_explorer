#ifndef PIECHART_H
#define PIECHART_H
#include "chart.h"
#include <QtCharts/QChart>
//Шаблонный метод для диаграмм. Метод создания диаграммы PieChart
class PieChart : public Chart
{
public:
    //Переопределяем шаблонный метод для создания PieChart.
    void drawChart(QtCharts::QChart*) override;
};

#endif // PIECHART_H
