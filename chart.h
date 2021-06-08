#ifndef CHART_H
#define CHART_H
#include <QLegend>
#include "sizecalculator.h"
//базовый класс для создания Chart. Применен шаблонный метод, поэтому drawChart - виртуальная функция.
//Наследники переопределят метод drawChart и будут создавать свою диаграмму
class Chart
{
public:
    //Создание метода. В конце вызывается drawLegend() и drawChart()
    QtCharts::QChart *createChart();
    //Виртуальный шаблонный метод для переопределения.
    virtual void drawChart(QtCharts::QChart*) = 0;
    void drawLegend(QtCharts::QLegend *legend);
};

#endif // CHART_H
