#ifndef FILEEXPLOREROBSERVER_H
#define FILEEXPLOREROBSERVER_H
#include "fileexplorerlistener.h"
#include <QList>
//Класс-наблюдатель. Нужен для наблюдения за работой SizeCalculator и оповещения об окончании выполнения расчета моделей.
class FileExplorerObserver
{
public:
    //Конструткор
    FileExplorerObserver();
    //метод для оповещения всех слушателей
    void notify();
    //метод подписки на оповещения класса-слушателя
    void subscribe(FileExplorerListener*);
    //метод удаления из оповещения
    void remove(FileExplorerListener*);
private:
    //Контейнер с указателями на слушателей.
    QList<FileExplorerListener*> listeners;
};

#endif // FILEEXPLOREROBSERVER_H
