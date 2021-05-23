#include <QCoreApplication>
#include <QMap>
#include <iostream>
#include "sizecalculator.h"
#include "Strategies/filetypestrategy.h"
#include "Strategies/folderstrategy.h"
//Функция для удобного тестирования. Выводит содержимое контейнера
void printMyMap(FileData map) {
    for(auto iterator = map.map.begin();iterator!=map.map.end();iterator++) {
        std::cout<<"Type: \t"<< iterator.key().toStdString()<<"\t Percents: \t"<<iterator.value();
        std::cout<<"\t\tBytes: "<<static_cast<uint64_t>(map.totalSize*iterator.value())<<std::endl;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CalculationStrategy *strategyFile = new FileTypeStrategy();
    CalculationStrategy *strategyFolder = new FolderStrategy();

    SizeCalculator calculator;
    //тесты
    //В переменной testPathStr нужно указать директорию, в которой лежат тесты (приложена к программе)
    //Тест 1 - пустая папка
    //Ожидание - пустой объект
    //результат - пустой объект
    //Тест 2 - папка с файлами
    //Ожидание - обе стратегии отработали нормально.
    //результат - стратегии отработали нормально
    //Тест 3 - папка с вложениями, не пустая
    //Ожидание - обе стратегии отработали нормально.
    //результат - стратегии отработали нормально
    //Тест 4 - пустая папка с вложениями (не пустыми)
    //Ожидание - обе стратегии отработали нормально.
    //результат - стратегии отработали нормально
    //Тест 5 - Не пустая папка с вложениями(пустыми)
    //Ожидание - обе стратегии отработали нормально.
    //результат - стратегии отработали нормально
    //Тест 6 - много вложений, файлов.
    //Ожидание - обе стратегии отработали нормально.
    //результат - стратегии отработали нормально
    //тест 7 - один файл
    //Ожидание - обе стратегии отработали нормально.
    //результат - стратегии отработали нормально

    QString testPathStr("D:/test/Tests");
    for (int i = 1;i<7;i++) {
        try {
            std::cout<<"TEST "<< i << "!!! \n FILETYPE CALCULATION: \n";
            QString path = testPathStr + "/test" + static_cast<char>('0'+i);
            calculator.setCalculationStrategy(strategyFile);
            printMyMap(calculator.Calculate(path));
            std::cout<<"\n\nFOLDERTYPE CALCULATION: \n";
            calculator.setCalculationStrategy(strategyFolder);
            printMyMap(calculator.Calculate(path));
            std::cout<<"END TEST " << i << std::endl;
        }  catch (std::runtime_error &exc) {
            std::cout<<exc.what()<<std::endl;
        }
    }

    std::cout<<"TEST 7 !!! \n FILETYPE CALCULATION: \n";
    QString path = testPathStr + "/test7.txt";

    calculator.setCalculationStrategy(strategyFile);
    printMyMap(calculator.Calculate(path));
    std::cout<<"\n\nFOLDERTYPE CALCULATION: \n";
    calculator.setCalculationStrategy(strategyFolder);

    printMyMap(calculator.Calculate(path));
    std::cout<<"END TEST 7" << std::endl;

    //test 8 - неправильная дирректория (не существует или набрана неверно)
    //ожидание - исключение (2 раза)
    //результат - исключение (2 раза)
    QString wrongPath("this is wrong path");
    try {
        calculator.setCalculationStrategy(strategyFile);
        calculator.Calculate(wrongPath);
    }  catch (std::runtime_error &exc) {
        std::cout<<exc.what()<<std::endl;
    }
    try {
        calculator.setCalculationStrategy(strategyFolder);
        calculator.Calculate(wrongPath);
    }  catch (std::runtime_error &exc) {
        std::cout<<exc.what()<<std::endl;
    }
    delete strategyFile;
    delete strategyFolder;

    return a.exec();
}
