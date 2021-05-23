#ifndef FOLDERSTRATEGY_H
#define FOLDERSTRATEGY_H
#include "calculationstrategy.h"

class FolderStrategy : public CalculationStrategy
{
public:
    //Перегруженная функция расчета базовой стратегии. Возвращает контейнер-словарь QMap,
    //в котором ключ - Имя папки
    //значение - занимаемое папкой пространство в процентах
    FileData calculate(QString dirStr) override;

    void calculateFolder(QString folderPath, QMap<QString,uint64_t> *folderNameMap, QString mapKey);
};
#endif // FOLDERSTRATEGY_H
