#include <QApplication>
#include <QMap>
#include <iostream>
#include "sizecalculator.h"
#include "Strategies/filetypestrategy.h"
#include "Strategies/folderstrategy.h"
#include "mainwindow.h"
//Функция для удобного тестирования. Выводит содержимое контейнера
SizeCalculator *SizeCalculator::instance = nullptr;
void printMyMap(FileData map) {
    for(auto iterator = map.map.begin();iterator!=map.map.end();iterator++) {
        std::cout<<"Type: \t"<< iterator.key().toStdString()<<"\t Percents: \t"<<iterator.value();
        std::cout<<"\t\tBytes: "<<static_cast<uint64_t>(map.totalSize*iterator.value())<<std::endl;
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.show();
    return a.exec();
}
