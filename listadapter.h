#ifndef LISTADAPTER_H
#define LISTADAPTER_H
#include "fileexplorerlistener.h"
#include "fileexplorermodel.h"
//Адаптер для отображения в виде таблицы. Связывает интерфейс класса FileExplorerListener и fileModel
class ListAdapter : public FileExplorerListener
{
public:
    //Модель данных создается в mainWindow, поэтому адаптер надо привязать к этой модели.
    //Сделано так для того, чтобы не удалять каждый раз модель и не создавать новую
    ListAdapter(FileExplorerModel *model);
    //Переопределяем метод update класса FileExplorerListener
    void update() override;
private:
    //указатель на модель
    FileExplorerModel *fileModel;
};

#endif // LISTADAPTER_H
