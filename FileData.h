#ifndef FILEDATA_H
#define FILEDATA_H
#include <QMap>
#include <QString>
//Структура для хранения результата подсчета. Хранит контейнер QMap, где пары имя - проценты и вес всей директории
struct FileData
{
    uint64_t totalSize;
    QMap<QString,double> map;

    FileData(uint64_t size, QMap<QString,double> _map) {
        totalSize = size;
        map = _map;
    }
};

#endif // FILEDATA_H
