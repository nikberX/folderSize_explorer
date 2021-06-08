#ifndef PIECHARTADAPTER_H
#define PIECHARTADAPTER_H
#include "fileexplorerlistener.h"
#include "piechart.h"
#include <QChart>

class PieChartAdapter : public FileExplorerListener
{
public:
    PieChartAdapter();
    void update() override;
    QtCharts::QChart *getChart() {return chart;}
private:
    QtCharts::QChart *chart;
    PieChart chartCreator;
};

#endif // PIECHARTADAPTER_H
