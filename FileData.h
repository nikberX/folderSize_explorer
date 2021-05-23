#ifndef FILEDATA_H
#define FILEDATA_H
#include <QMap>
#include <QString>
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
