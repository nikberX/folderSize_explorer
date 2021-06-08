#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QFileSystemModel>

#include <QTreeView>
#include <QListView>
#include <QTableView>
#include <QDebug>
#include "fileexplorermodel.h"
#include "Strategies/filetypestrategy.h"
#include "Strategies/folderstrategy.h"
#include "listadapter.h"
#include "piechartadapter.h"
#include "barchartadapter.h"
#include <QChartView>
#include <QSplitter>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QSplitter *splitter;
    //Панель меню
    QMenuBar *menuBar;
    //Объекты QMenu, добавляемые в QMenuBar. Отдельно для смены группировки и смены отображения
    QMenu *changeStrategyMenu;
    QMenu *changeViewMenu;
    //кнопки в меню. при нажатии активируется сиграл triggered()
    QAction *fileStrategyAction;
    QAction *folderStrategyAction;

    QAction *listViewAction;
    QAction *circleChartViewAction;
    QAction *barChartViewAction;
    //Модель для данных компьютера
    QFileSystemModel *dirModel;
    //Модель для данных, сгенерированных алгоритмом подсчета размера
    FileExplorerModel *fileModel;


    //вид для отображения директории
    QTreeView *treeView;
    //вид для отображения данных алгоритма
    QTableView *listView;
    QtCharts::QChartView *chartView;

    //объекты конкретных стратегий
    FolderStrategy *folderStrategy;
    FileTypeStrategy *fileStrategy;

    //Адаптеры
    ListAdapter *listAdapter;
    PieChartAdapter *pieChartAdapter;
    BarChartAdapter *barChartAdapter;


    QString lastPath;

private slots:
    //Слоты нажатия кнопок меню
    void onFileStrategyClick();
    void onFolderStrategyClick();

    void onlistViewClick();
    void onCircleChartViewClick();
    void onBarChartViewClick();

    //Слот изменения выделения вида директории (вызывается если пользователь кликает мышью на QTreeView
    void onSelectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected);
};

#endif // MAINWINDOW_H
