#ifndef FILETYPESTRATEGY_H
#define FILETYPESTRATEGY_H
#include "calculationstrategy.h"

//класс стратегии разбиения по файлам
class FileTypeStrategy : public CalculationStrategy
{
public:
    FileTypeStrategy() {};

    //Перегруженная функция расчета базовой стратегии. Возвращает контейнер-словарь QMap,
    //в котором ключ - формат файла
    //значение - занимаемое им пространство в процентах
    FileData calculate(QString &dir) override;
private:
    //отдельная функция для рекурсивного подсчета. (см .cpp файл)
    void calculateFolder(QString folderPath, QMap<QString,uint64_t> *fileExtMap);

};

#endif // FILETYPESTRATEGY_H
