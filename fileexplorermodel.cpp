#include "fileexplorermodel.h"
#include "Strategies/filetypestrategy.h"
#include <QDebug>
//Конструктор
FileExplorerModel::FileExplorerModel(QObject *parent) : m_data(0,QMap<QString,double>())
{

}
//Возвращаем размер QMap в m_data
int FileExplorerModel::rowCount(const QModelIndex &parent) const {
    return m_data.map.size();
}
//всегда возвращает 3, тк 3 столбца
int FileExplorerModel::columnCount(const QModelIndex &parent) const {
    return 3;
}

QVariant FileExplorerModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) { // проверка на отоброжаемость роли
        return QVariant();
    }
    if (orientation == Qt::Vertical) { // проверка на вертикальную ориентацию
        return section + 1;
    }
    switch (section) { // проверка столбца
    case 0:
        return "Название";
    case 1:
        return "Размер";
    case 2:
        return "В процентах";
    }
    return QVariant();
}
//функция получения данных
QVariant FileExplorerModel::data(const QModelIndex &index, int role) const
{
    //проверка валидности индекса
    if (!index.isValid()) return QVariant();
    if (index.row() >= m_data.map.size()) return QVariant();
    //Проверка роли
    if (role != Qt::DisplayRole && role != Qt::EditRole) {
        return QVariant();
    }
    //если всё хорошо, смотрим в каком столбце находимся и ищем нужный элемент в QMap
    //переменная для подсчета индекса (тк index.row - число)
    int k = 0;
    if (index.column() == 0) {
        //цикл по QMap для названий и типов
        for(auto iterator = m_data.map.begin();iterator!=m_data.map.end();iterator++) {
            //если дошли до элемента на k строке, возвращаем значение (тип или имя)
            if (k == index.row()) return iterator.key();
            k++;
        }
    } else if (index.column() == 1) {
        //цикл по QMap для размера групп
        for(auto iterator = m_data.map.begin();iterator!=m_data.map.end();iterator++) {
            //если дошли до элемента на k строке, возвращаем размер
            if (k == index.row()) {
                //размер в байтах
                qint64 size = static_cast<long>(iterator.value()*m_data.totalSize);
                //Отображаем в KB или MB (меньше 1 KB отображается как 1 KB, как в проводнике)
                //Здесь 1024*1024 = 1 MB. Если размер меньше, значит в KB иначе в MB
                if (size < 1024*1024) {
                    if (size < 1024) {
                        return QString("1 KB");
                    } else {
                        return QString(QString::number(size/1024) + " KB");
                    }
                } else {
                    return QString(QString::number(size/(1024*1024)) + " MB");
                }
            }
            k++;
        }
    } else if (index.column() == 2) {
        //Цикл по QMap для отображения процентов
        for(auto iterator = m_data.map.begin();iterator!=m_data.map.end();iterator++) {
            //если дошли до k строчки
            if (k == index.row()) {
                //записываем проценты
                double percents = iterator.value();
                //Выводим в красивом для пользователя виде
                if (percents < 0.01) {
                    return QString(" < 1%");
                } else {
                    QString value = QString::number(percents);
                    //т.к. берётся подстрока 5 символов, то добавляем 5 символов в конце чтобы она точно существовала
                    value.append(" ");value.append(" ");value.append(" ");value.append(" ");value.append(" ");
                    value = value.left(5) + "%";
                    return value;
                }

            }
            k++;
        }
    }

    return QVariant();
}


void FileExplorerModel::updateData()
{
    //сообщаем о смене данных
    beginResetModel();
    //После добавления наблюдателя не нужно обновлять данные через mainWindow
    //mainWindow посылает запрос калькулятору, чтобы он посчитал новый путь и после расчета калькулятор сам
    //уведомит все модели, что данные изменились и они обновят свои данные.
    m_data = SizeCalculator::getInstance()->getData();
    //сообщаем о конце смены данных
    endResetModel();
}

//изменить данные нельзя. return false
bool FileExplorerModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    return false;
}
//возвращаем флаги
Qt::ItemFlags FileExplorerModel::flags(const QModelIndex &index) const {
    return QAbstractItemModel::flags(index);
}
//возвращаем сгенерированный индекс
QModelIndex FileExplorerModel::index(int row, int column, const QModelIndex &parent) const {
    return createIndex(row, column, nullptr);
}
//модель не предполагает наличие родителей
QModelIndex FileExplorerModel::parent(const QModelIndex &child) const {
    return QModelIndex();
}

bool FileExplorerModel::hasChildren(const QModelIndex &parent = QModelIndex()) const {
    return parent == QModelIndex();
}
