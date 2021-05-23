#ifndef CALCULATIONSTRATEGY_H
#define CALCULATIONSTRATEGY_H
#include <QMap>
#include <QDir>
#include <QFileInfo>
#include "FileData.h"
//Базовый класс-интерфейс стратегий. Конкретные стратегии наследуются от этого класса
class CalculationStrategy
{
public:
    virtual ~CalculationStrategy() {};
    virtual FileData calculate(QString dir) = 0;
};

#endif // CALCULATIONSTRATEGY_H
