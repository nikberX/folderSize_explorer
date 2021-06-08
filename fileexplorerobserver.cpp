#include "fileexplorerobserver.h"

FileExplorerObserver::FileExplorerObserver() : listeners(QList<FileExplorerListener*>())
{

}

void FileExplorerObserver::notify()
{
    for(auto iterator = listeners.begin();iterator!=listeners.end();iterator++) {
        if (*iterator==nullptr) {
            continue;
        }
        (*iterator)->update();
    }
}

void FileExplorerObserver::subscribe(FileExplorerListener *listener)
{
    listeners.append(listener);
}

void FileExplorerObserver::remove(FileExplorerListener *listener) {
    int k=0;
    for(auto iterator = listeners.begin();iterator!=listeners.end();iterator++) {
        if (*iterator==listener) {
            listeners.removeAt(k);
        }
        k++;
    }
}
