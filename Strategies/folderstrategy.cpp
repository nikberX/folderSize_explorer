#include "folderstrategy.h"
#include <iostream>
FileData FolderStrategy::calculate(QString dirStr)
{


    //Объект QFileInfo для удобной работы с поданной дирректорией
    QFileInfo path(dirStr);

    //Пустой контейнер QMap для записи результата работы функции
    FileData resultData(0,QMap<QString,double>());

    //Проверка что путь корректный (набран правильно, существует)
    if (!path.exists()) {
        std::cout<<path.absoluteFilePath().toStdString()<<std::endl;
        throw std::runtime_error("PATH ERROR");
    }

    //Проверка на возможность открыть файл или папку (если файл защищен то будет False)
    if (!path.isReadable()) {
        throw std::runtime_error("PERMISSION ERROR");
    }
    //Проверяем что подали не пустую строку
    if (dirStr.isEmpty()) {
        throw std::runtime_error("EMPTY DIRECTORY");
    } else {
        //В конце строки должен стоять слеш (Если директория будет указывать на папку без слеша, например
        // D:/test/1 то не сработает функция проверки папки на пустую (dir().isEmpty())
        if (dirStr[dirStr.length()-1] != '/') {
            dirStr.append('/');
        }
    }
    path = QFileInfo(dirStr);
    //Контейнер QMap который будет хранить в себе пары расширение - место
    //Динамический, тк используется отдельная рекурсивная функция, в которую передается контейнер
    QMap<QString,uint64_t> *folderNameMap = new QMap<QString,uint64_t>();
    //Проверка что поданная директория не указывает на файл
    if (path.isDir()) {
        QDir directory(path.absoluteFilePath());
        //Пустая папка
        if (directory.isEmpty()) {
            delete folderNameMap;
            return resultData;
        }

        QStringList folderNameStringList;
        uint64_t totalSize = 0;
        //Цикл по папкам в поданной директории. Идет по всем папкам.
        //Игнорирует ярлыки (.lnk), т.к. они будут обработаны ниже как файл
        //Так же игнорирует папки с . и .. перед именем (отдельно тестировал цикл, без этого флага папок на 2 больше, но в интернете внятной информации что это за папки не нашел)
        foreach(QFileInfo folder, directory.entryInfoList(QDir::NoDotAndDotDot| QDir::Dirs | QDir::Hidden | QDir::System | QDir::NoSymLinks)) {
            //здесь переменная QfileInfo folder будет содержать путь до текущей директории и имя папки, поэтому передаем путь к папке в функцию, которая рекурсивно посчитает вес папок
            calculateFolder(folder.absoluteFilePath(),folderNameMap, folder.fileName());
            folderNameStringList.append(folder.fileName());
            totalSize+=folderNameMap->operator[](folder.fileName());
        }
        //Цикл по папкам в текущей директории
        folderNameMap->operator[]("Current") = 0;
        folderNameStringList.append("Current");

        foreach(QFileInfo file, directory.entryInfoList(QDir::NoDotAndDotDot | QDir::Files| QDir::System | QDir::Hidden )) {
            folderNameMap->operator[]("Current") += file.size();
            totalSize+=file.size();
        }


        if (totalSize == 0) {
            //папка ничего не весит
            delete folderNameMap;
            return resultData;
        }

        resultData.totalSize=totalSize;
        //Сортируем расширения по алфавиту
        //составляем контейнер QMap с парами расширение - процент
        foreach(QString typeStr, folderNameStringList) {
            uint64_t sizeOfExt = folderNameMap->operator[](typeStr) * 100;
            double percents = double(sizeOfExt)/totalSize;
            resultData.map[typeStr] =percents;
        }

        delete folderNameMap;
        return resultData;
    } else {
        //Если пришел путь к файлу, то он занимает 100 процентов места.
        resultData.map["Current"] = 100;
        resultData.totalSize = path.size();
        delete folderNameMap;
        return resultData;
    }
    delete folderNameMap;
    return resultData;
}
//Аналогично счету по типам файлов, вес директории нужно считать рекурсивно.
//mapKey отвечает за ключ контейнера QMap, в который будет добавляться общий размер
void FolderStrategy::calculateFolder(QString folderPath, QMap<QString, uint64_t> *folderNameMap, QString mapKey)
{
    QDir directory(folderPath);

    //если не пустая папка
    if (!directory.isEmpty()) {
        //цикл по папкам, рекурсия
        foreach(QFileInfo folder, directory.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden | QDir::System | QDir::NoSymLinks)) {
            QString fpath(folder.absoluteFilePath());
            calculateFolder(fpath, folderNameMap, mapKey);
        }

        //цикл по файлам в папке, считаем размер.
        foreach(QFileInfo file, directory.entryInfoList(QDir::NoDotAndDotDot | QDir::Files| QDir::System | QDir::Hidden )) {
            folderNameMap->operator[](mapKey) += file.size();
        }
    }
}
