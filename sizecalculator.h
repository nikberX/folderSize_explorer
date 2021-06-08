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
    //Тк класс написан с импользованием паттерна singletone то в силу того что модели данных у QChart и View
    //То имеет смысл чтобы они имели прямой доступ к данным.
    //после произведения вычислений (Calculate) класс сохраняет вычисленные данные и оповещает модели, что данные
    //обноволись. Модели используют метод getData для их получения.
    FileData getData();
    //В SizeCalculator есть объект наблюдателя, к которому надо привязать адаптеры в mainWindow. Метод для получения указателя на observer
    FileExplorerObserver* getObserver();
protected:
    //указатель на объект (единственный)
    static SizeCalculator *instance;
private:
    //конструктор в приватной зоне
    SizeCalculator();
    //член-данное, которое хранит указатель на абстрактную стратегию, в которую мы можем помещать конкретные стратегии
    CalculationStrategy *m_strategy;
    //Данные из метода Calculate
    FileData m_data;
    //Наблюдатель
    FileExplorerObserver *observer;
};

#endif // SIZECALCULATOR_H
