#include <QApplication>
#include <QMap>
#include <iostream>
#include "sizecalculator.h"
#include "Strategies/filetypestrategy.h"
#include "Strategies/folderstrategy.h"
#include "mainwindow.h"

SizeCalculator *SizeCalculator::instance = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.show();
    return a.exec();
}
