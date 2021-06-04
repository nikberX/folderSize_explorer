#ifndef SIZECALCULATOR_H
#define SIZECALCULATOR_H
#include <calculationstrategy.h>


//Класс-контекст для применения стратегий. Предоставляет интерфейс к функциям стратегий (посчитать размер).
class SizeCalculator
{
public:
    static SizeCalculator* getInstance();
    SizeCalculator(SizeCalculator&) = delete;
    void operator=(const SizeCalculator&) = delete;
    //деструтор (см. .cpp файл)
    ~SizeCalculator();
    //Функция для смены стратегии
    void setCalculationStrategy(CalculationStrategy *strategy);
    //посчитать размер в зависимости от заданной стратегии
    FileData Calculate(QString &path);
protected:
    static SizeCalculator *instance;
private:
    SizeCalculator();
    //член-данное, которое хранит указатель на абстрактную стратегию, в которую мы можем помещать конкретные стратегии
    CalculationStrategy *m_strategy;
};

#endif // SIZECALCULATOR_H
