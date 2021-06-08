#include "listadapter.h"

ListAdapter::ListAdapter(FileExplorerModel *model)
{
    fileModel = model;
}
void ListAdapter::update()
{
    fileModel->updateData();
}
