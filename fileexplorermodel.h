#ifndef FILEEXPLORERMODEL_H
#define FILEEXPLORERMODEL_H

#include <QAbstractItemModel>
#include <QMap>
#include <QString>
#include "sizecalculator.h"

class FileExplorerModel: public QAbstractItemModel
{
public:
    //конструктор
    FileExplorerModel(QObject *parent = nullptr);
    //функция для возврата кол-ва строк
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    //функция для возврата кол-во столбцов (в нашем случае 3)
    int columnCount(const QModelIndex &parent) const override;
    //функция для получения данных из модели
    QVariant data(const QModelIndex &index, int role) const override;
    //функция для задания имени столбцов
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    // функция для возврата индекса элемента (требуется для того, чтобы класс не был абстрактным)
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    // функция для возврата индекса родителя (требуется для того, чтобы класс не был абстрактным)
    QModelIndex parent(const QModelIndex &child) const override;
    // функция позволяющая изменять данные при необходимости (определяется чтобы запретить изменение данных)
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    // функция которая возвращает флаги элемента
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    // функция возвращающая флаг о наличии потомков (требуется для универсальности модели)
    bool hasChildren(const QModelIndex &parent) const override;
    // функции для обновления данных.
    void updateData();
private:
    //данные о подсчете
    FileData m_data;
    //Текущая (последняя) директория
    QString lastPath;
};

#endif // FILEEXPLORERMODEL_H
