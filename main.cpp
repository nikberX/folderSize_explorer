#include <QCoreApplication>
#include <QMap>
#include <iostream>
#include "sizecalculator.h"
#include "Strategies/filetypestrategy.h"
#include "Strategies/folderstrategy.h"
void printMyMap(FileData map) {
    for(auto iterator = map.map.begin();iterator!=map.map.end();iterator++) {
        std::cout<<"Type: \t"<< iterator.key().toStdString()<<"\t Percents: \t"<<iterator.value();
        std::cout<<"\t\tBytes: "<<static_cast<uint64_t>(map.totalSize*iterator.value())<<std::endl;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CalculationStrategy *strategy1 = new FileTypeStrategy();
    CalculationStrategy *strategy2 = new FolderStrategy();

    SizeCalculator calculator(strategy2);
    QString testPathStr("D:/test");

    printMyMap(calculator.Calculate(testPathStr));

    delete strategy1;

    return a.exec();
}
