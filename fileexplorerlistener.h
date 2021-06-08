#ifndef FILEEXPLORERLISTENER_H
#define FILEEXPLORERLISTENER_H

//Класс-слушатель наблюдателя
class FileExplorerListener
{
public:
    //Виртуальный метод для обновления. Классы, которые должны обновляться наследуются от слушателя.
virtual void update() = 0;
};

#endif // FILEEXPLORERLISTENER_H
