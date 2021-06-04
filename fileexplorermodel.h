#ifndef FILEEXPLORERMODEL_H
#define FILEEXPLORERMODEL_H

#include <QAbstractItemModel>
#include <QMap>
#include <QString>
#include "sizecalculator.h"

class FileExplorerModel: public QAbstractItemModel
{
public:
    FileExplorerModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    // функция, которая возвращает индекс элемента (требуется для того, чтобы класс не был абстрактным), на входе int - строка + int - столбец + QModelIndex& - ссылка на индекс родителя, на выходе QModelIndex - индекс элемента
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    // функция, которая возвращает индекс родителя (требуется для того, чтобы класс не был абстрактным), на входе QModelIndex& - ссылка на индекс элемента, на выходе QModelIndex - индекс родителя
    QModelIndex parent(const QModelIndex &child) const override;
    // функция, которая позволяет изменять данные при необходимости (здесь определяется ради того, чтобы не допустить изменения данных), на входе QModelIndex& - ссылка на индекс элемента + QVariant& - ссылка на изменённые данные + int - роль, на выходе bool - флаг об успешности изменения данных
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    // функция, которая возвращает флаги элемента, QModelIndex& - ссылка на индекс элемента, на выходе Qt::ItemFlags - флаги
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    // функция, возвращающая флаг о наличии потомков (требуется для универсальности модели), на входе QModelIndex& - ссылка на индекс элемента, на выходе bool - флаг о наличии потомков
    bool hasChildren(const QModelIndex &parent) const override;
    void updateData(QString path);
private:
    FileData m_data;
};

#endif // FILEEXPLORERMODEL_H
