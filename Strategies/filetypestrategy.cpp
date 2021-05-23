#include "filetypestrategy.h"
#include "exception"
#include <iostream>
FileData FileTypeStrategy::calculate(QString &dirStr)
{
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
    //Объект QFileInfo для удобной работы с поданной дирректорией
    QFileInfo path(dirStr);

    //Пустой контейнер QMap для записи результата работы функции

    FileData resultData(0,QMap<QString,double>());

    //Проверка что путь корректный (набран правильно, существует)
    if (!path.exists()) {
        throw std::runtime_error("PATH ERROR");
    }

    //Проверка на возможность открыть файл или папку (если файл защищен то будет False)
    if (!path.isReadable()) {
        throw std::runtime_error("PERMISSION ERROR");
    }
    //Контейнер QMap который будет хранить в себе пары расширение - место
    //Динамический, тк используется отдельная рекурсивная функция, в которую передается контейнер
    QMap<QString,uint64_t> *fileExtMap = new QMap<QString,uint64_t>();
    //Проверка что поданная директория не указывает на файл
    if (path.isDir()) {
        QDir directory(path.absoluteFilePath());
        //Пустая папка
        if (directory.isEmpty()) {
            delete fileExtMap;
            return resultData;
        }


        //Цикл по папкам в поданной директории. Идет по всем папкам.
        //Игнорирует ярлыки (.lnk), т.к. они будут обработаны ниже как файл
        //Так же игнорирует папки с . и .. перед именем (отдельно тестировал цикл, без этого флага папок на 2 больше, но в интернете внятной информации что это за папки не нашел)
        foreach(QFileInfo folder, directory.entryInfoList(QDir::NoDotAndDotDot| QDir::Dirs | QDir::Hidden | QDir::System | QDir::NoSymLinks)) {
            //здесь переменная QfileInfo folder будет содержать путь до текущей директории и имя папки, поэтому передаем путь к папке в функцию, которая рекурсивно посчитает вес папок
            calculateFolder(folder.absoluteFilePath(),fileExtMap);
        }
        //Цикл по папкам в текущей директории
        foreach(QFileInfo file, directory.entryInfoList(QDir::NoDotAndDotDot | QDir::Files| QDir::System | QDir::Hidden )) {
            QString filenameExt;

            int indexOfDot = file.fileName().lastIndexOf('.');
            if (indexOfDot == -1) {
                //случай когда нет расширения
                filenameExt = "unknown";
            } else {
                //Возвращает подстроку от иднекса до конца (например - video.mp4 , index = 5 , res = .mp4)
                filenameExt = file.fileName().mid(indexOfDot);
            }
            //Добавляем размер к расширению
            fileExtMap->operator[](filenameExt) += file.size();
        }
        uint64_t totalSize = 0;
        QStringList typesStringList;
        //Считаем размер всей папки и собираем типы данных
        for(auto iterator = fileExtMap->begin(); iterator != fileExtMap->end(); iterator++) {
            totalSize += iterator.value();
            typesStringList.append(iterator.key());
        }
        resultData.totalSize = totalSize;
        if (totalSize == 0) {
            //папка ничего не весит
            delete fileExtMap;
            return resultData;
        }
        //Сортируем расширения по алфавиту
        typesStringList.sort();
        //составляем контейнер QMap с парами расширение - процент
        foreach(QString typeStr,typesStringList) {
            uint64_t sizeOfExt = fileExtMap->operator[](typeStr) * 100;
            double percents = double(sizeOfExt)/totalSize;
            resultData.map[typeStr] =percents;
        }

        delete fileExtMap;
        return resultData;
    } else {
        //На вход пришла не папка а путь к файлу.
        QString filenameExt;
        int indexOfDot = path.fileName().lastIndexOf('.');
        if (indexOfDot == -1) {
            filenameExt = "unknown";
        } else {
            //Возвращает подстроку от иднекса до конца (например - video.mp4 , index = 5 , res = .mp4)
            filenameExt = path.fileName().mid(indexOfDot);
        }
        //Если пришел путь к файлу, то он занимает 100 процентов места.
        resultData.map[filenameExt] = 100;
        resultData.totalSize = path.size();
        delete fileExtMap;
        return resultData;
    }
    delete fileExtMap;
    return resultData;
}
//Функция для подсчета размера отдельной папки,
//вынесена как отдельная для удобного использования рекурсии(тк папки могут быть вложенные).
//Можно было бы сделать рекурсивной и функцию выше, но там будет поступать ввод пользователя, который может быть не корректным
//в эту функцию должны приходить только корректные значения, полученные программным путем
void FileTypeStrategy::calculateFolder(QString folderPath, QMap<QString,uint64_t> *fileExtMap)
{
    QDir directory(folderPath);

    //если не пустая папка
    if (!directory.isEmpty()) {
        //цикл по папкам, рекурсия
        foreach(QFileInfo folder, directory.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden | QDir::System | QDir::NoSymLinks)) {
            QString fpath(folder.absoluteFilePath());
            calculateFolder(fpath,fileExtMap);
        }

        //цикл по файлам в папке
        foreach(QFileInfo file, directory.entryInfoList(QDir::NoDotAndDotDot | QDir::Files| QDir::System | QDir::Hidden )) {
            QString filenameExt;
            int indexOfDot = file.fileName().lastIndexOf('.');
            if (indexOfDot == -1) {
                filenameExt = "unknown";
            } else {
                //Возвращает подстроку от иднекса до конца (например - video.mp4 , index = 5 , res = .mp4)
                filenameExt = file.fileName().mid(indexOfDot);
            }
            fileExtMap->operator[](filenameExt) += file.size();
        }
    }
}
