#include "listadapter.h"

ListAdapter::ListAdapter(FileExplorerModel *model)
{
    fileModel = model;
}
void ListAdapter::update()
{
    //Вызываем метод обновления данных модели. Метод возьмет данные из SizeCalculator
    fileModel->updateData();
}
