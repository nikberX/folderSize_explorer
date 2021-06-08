#include "barchart.h"
#include "FileData.h"
#include "sizecalculator.h"
#include <QChart>
#include <QBarSeries>
#include <QBarSet>
void BarChart::drawChart(QtCharts::QChart *chart)
{
    //Создаем Series для BarChart
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
    //Задаем размер
    series->setBarWidth(1);
    //получаем обновленные данные.
    FileData data = SizeCalculator::getInstance()->getData();
    //Считаем категорию others
    double othersPercentage = 0;

    for (auto iterator = data.map.begin();iterator!=data.map.end();iterator++)
    {
        if (iterator.key()=="others"||iterator.value()<5) {
            othersPercentage+=iterator.value();
        } else {
            //Создаем элемент данных
            QtCharts::QBarSet *set = new QtCharts::QBarSet(iterator.key());
            //присваиваем занимаемое значение
            set->append(iterator.value());
            //добавляем в набор
            series->append(set);
        }
    }
    //если есть категория others, добавляем
    if (othersPercentage > 0) {
        QtCharts::QBarSet *set = new QtCharts::QBarSet("others");

        set->append(othersPercentage);

        series->append(set);
    }
    //Связываем chart и series
    chart->addSeries(series);
}
