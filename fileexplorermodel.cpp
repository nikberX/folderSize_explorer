#include "fileexplorermodel.h"
#include "Strategies/filetypestrategy.h"
#include <QDebug>

FileExplorerModel::FileExplorerModel(QObject *parent) : m_data(0,QMap<QString,double>())
{

}
int FileExplorerModel::rowCount(const QModelIndex &parent) const {
    return m_data.map.size();
}
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
    switch (section) { // проверка секции
    case 0:
        return "Название";
    case 1:
        return "Размер";
    case 2:
        return "В процентах";
    }
    return QVariant();
}

QVariant FileExplorerModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();
    if (index.row() >= m_data.map.size()) return QVariant();
    if (role != Qt::DisplayRole && role != Qt::EditRole) {
        return QVariant();
    }

    int k = 0;
    if (index.column() == 0) {
        for(auto iterator = m_data.map.begin();iterator!=m_data.map.end();iterator++) {
            if (k == index.row()) return iterator.key();
            k++;
        }
    } else if (index.column() == 1) {
        for(auto iterator = m_data.map.begin();iterator!=m_data.map.end();iterator++) {
            if (k == index.row()) {
                qint64 size = static_cast<long>(iterator.value()*m_data.totalSize);
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
        for(auto iterator = m_data.map.begin();iterator!=m_data.map.end();iterator++) {
            if (k == index.row()) {
                double percents = iterator.value();
                if (percents < 0.01) {
                    return QString(" < 1%");
                } else {
                    QString value = QString::number(percents);
                    value.append(" ");value.append(" ");value.append(" ");value.append(" ");
                    value = value.left(5) + "%";
                    return value;
                }

            }
            k++;
        }
    }

    return QVariant();
}

void FileExplorerModel::updateData(QString path)
{
    m_data = SizeCalculator::getInstance()->Calculate(path);
}


bool FileExplorerModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    return false;
}

Qt::ItemFlags FileExplorerModel::flags(const QModelIndex &index) const {
    return QAbstractItemModel::flags(index);
}

QModelIndex FileExplorerModel::index(int row, int column, const QModelIndex &parent) const {
    return createIndex(row, column, nullptr);
}

QModelIndex FileExplorerModel::parent(const QModelIndex &child) const {
    return QModelIndex();
}

bool FileExplorerModel::hasChildren(const QModelIndex &parent = QModelIndex()) const {
    return parent == QModelIndex();
}
