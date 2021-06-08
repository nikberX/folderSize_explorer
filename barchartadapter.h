#ifndef BARCHARTADAPTER_H
#define BARCHARTADAPTER_H
#include "fileexplorerlistener.h"
#include "barchart.h"
#include <QChart>
class BarChartAdapter : public FileExplorerListener
{
public:
    BarChartAdapter();
    void update() override;
    QtCharts::QChart *getChart() {return chart;}
private:
    QtCharts::QChart *chart;
    BarChart chartCreator;
};

#endif // BARCHARTADAPTER_H
