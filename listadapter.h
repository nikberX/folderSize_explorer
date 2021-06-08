#ifndef LISTADAPTER_H
#define LISTADAPTER_H
#include "fileexplorerlistener.h"
#include "fileexplorermodel.h"
class ListAdapter : public FileExplorerListener
{
public:
    ListAdapter(FileExplorerModel *model);
    void update() override;
private:
    FileExplorerModel *fileModel;
};

#endif // LISTADAPTER_H
