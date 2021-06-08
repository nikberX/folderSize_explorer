#ifndef FILEEXPLOREROBSERVER_H
#define FILEEXPLOREROBSERVER_H
#include "fileexplorerlistener.h"
#include <QList>
class FileExplorerObserver
{
public:
    FileExplorerObserver();
    void notify();
    void subscribe(FileExplorerListener*);
    void remove(FileExplorerListener*);
private:
    QList<FileExplorerListener*> listeners;
};

#endif // FILEEXPLOREROBSERVER_H
