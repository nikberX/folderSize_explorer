#include "fileexplorerobserver.h"

FileExplorerObserver::FileExplorerObserver() : listeners(QList<FileExplorerListener*>())
{

}
//Оповестить всех слушателей
void FileExplorerObserver::notify()
{
    //проходимся по списку слушателей, если элемент списка не nullptr, то вызываем update()
    for(auto iterator = listeners.begin();iterator!=listeners.end();iterator++) {
        if (*iterator==nullptr) {
            continue;
        }
        (*iterator)->update();
    }
}

void FileExplorerObserver::subscribe(FileExplorerListener *listener)
{
    //добавляем слушателя в список
    listeners.append(listener);
}

void FileExplorerObserver::remove(FileExplorerListener *listener) {
    //ищем слушателя и если нашли - удаляем.
    int k=0;
    for(auto iterator = listeners.begin();iterator!=listeners.end();iterator++) {
        if (*iterator==listener) {
            listeners.removeAt(k);
        }
        k++;
    }
}
