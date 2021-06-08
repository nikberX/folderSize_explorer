#ifndef PIECHARTADAPTER_H
#define PIECHARTADAPTER_H
#include "fileexplorerlistener.h"
#include "piechart.h"
#include <QChart>
//Адаптер для Pie диаграммы. Позволяет связать классы Listener и Chart.
class PieChartAdapter : public FileExplorerListener
{
public:
    //Конструктор. Берёт QChart из MainWindow.
    PieChartAdapter();
    //переопределяем метод update класса FileExplorerListener. В этом методе происходит связь 2х интерфейсов:
    //интерфейса класса Listener и Chart
    void update() override;
    //Вернуть объект QChart (для mainWindow)
    QtCharts::QChart *getChart() {return chart;}
private:
    //объект диаграммы из MainWindow
    QtCharts::QChart *chart;
    //объект, создающий диаграмму.
    PieChart chartCreator;
};

#endif // PIECHARTADAPTER_H
