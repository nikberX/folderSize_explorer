#ifndef BARCHARTADAPTER_H
#define BARCHARTADAPTER_H
#include "fileexplorerlistener.h"
#include "barchart.h"
#include <QChart>
//Адаптер для Bar диаграммы. Позволяет связать классы Listener и Chart.
class BarChartAdapter : public FileExplorerListener
{
public:
    //Конструктор. Берёт QChart* из Mainwindow
    BarChartAdapter();
    //переопределенный метод FileExplorerListener для обновления данных
    void update() override;
    //получить объект QChart
    QtCharts::QChart *getChart() {return chart;}
private:
    //хранит указатель на chart из MainWindow
    QtCharts::QChart *chart;
    //Объект для создания barChart
    BarChart chartCreator;
};

#endif // BARCHARTADAPTER_H
