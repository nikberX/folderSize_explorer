#ifndef SIZECALCULATOR_H
#define SIZECALCULATOR_H
#include <calculationstrategy.h>
#include "fileexplorerobserver.h"

//Класс-контекст для применения стратегий. Предоставляет интерфейс к функциям стратегий (посчитать размер).
//реализован в соответствии с паттерном singletone
class SizeCalculator
{
public:
    //получить указатель на объект
    static SizeCalculator* getInstance();
    //запрещаем копирование
    SizeCalculator(SizeCalculator&) = delete;
    void operator=(const SizeCalculator&) = delete;
    //деструтор (см. .cpp файл)
    ~SizeCalculator();
    //Функция для смены стратегии
    void setCalculationStrategy(CalculationStrategy *strategy);
    //посчитать размер в зависимости от заданной стратегии
    void Calculate(QString &path);
    FileData getData();
    FileExplorerObserver* getObserver();
protected:
    //указатель на объект (единственный)
    static SizeCalculator *instance;
private:
    //конструктор в приватной зоне
    SizeCalculator();
    //член-данное, которое хранит указатель на абстрактную стратегию, в которую мы можем помещать конкретные стратегии
    CalculationStrategy *m_strategy;
    FileData m_data;
    FileExplorerObserver *observer;
};

#endif // SIZECALCULATOR_H
