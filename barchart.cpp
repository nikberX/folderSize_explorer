#include "barchart.h"
#include "FileData.h"
#include "sizecalculator.h"
#include <QChart>
#include <QBarSeries>
#include <QBarSet>
void BarChart::drawChart(QtCharts::QChart *chart)
{
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries(); // создаем набор элементов данных вертикальной диаграммы
    series->setBarWidth(1); // масштаб диаграммы, устанавливаем 100 %

    FileData data = SizeCalculator::getInstance()->getData();

    double othersPercentage = 0;

    for (auto iterator = data.map.begin();iterator!=data.map.end();iterator++)
    {
        QtCharts::QBarSet *set = new QtCharts::QBarSet(iterator.key()); // создаем элемент данных

        set->append(iterator.value()); // присваиваем элементу занимаемую им долю диаграммы

        series->append(set); // добавляем элемент данных в набор
    }

    if (othersPercentage > 0) {
        QtCharts::QBarSet *set = new QtCharts::QBarSet("others"); // создаем элемент данных

        set->append(othersPercentage); // присваиваем элементу занимаемую им долю диаграммы

        series->append(set); // добавляем элемент данных в набор
    }

    chart->addSeries(series); // устанавливаем диаграмме созданный набор элементов
}
