#include "piechart.h"
#include "FileData.h"
#include "sizecalculator.h"
#include <QPieSeries>
#include <QPieSlice>
void PieChart::drawChart(QtCharts::QChart *chart)
{
    //Создаем объект PieSeries (служит для записи данных диаграммы и привязке к chart)
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    //задаем размер
    series->setPieSize(1);
    //Получаем обновленные данные из SizeCalculator
    FileData data = SizeCalculator::getInstance()->getData();
    //Вычисляем проценты Others
    double othersPercentage = 0;
    for (auto iterator = data.map.begin();iterator!=data.map.end();iterator++)
    {
        //файлы с маленькими процентами группируем.
        if (iterator.value()<5||(iterator.key()=="others")) {
            othersPercentage+=iterator.value();
        } else {
            //Иначе добавляем значения в Series
            series->append(new QtCharts::QPieSlice(iterator.key(),iterator.value()));
        }
    }
    //Если есть файлы, попадающие под категорию others, добавляем эту категорию в series
    if (othersPercentage>0) {
        series->append(new QtCharts::QPieSlice("others", othersPercentage));
    }
    //связываем chart и series
    chart->addSeries(series);
}
