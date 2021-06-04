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
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QFileSystemModel *folderModel;
    QMenuBar *menuBar;
    QMenu *changeStrategyMenu;
    QMenu *changeViewMenu;
    QAction *fileStrategyAction;
    QAction *folderStrategyAction;
    QAction *listViewAction;
    QAction *circleChartViewAction;
    QAction *barChartViewAction;

    QFileSystemModel *dirModel;
    FileExplorerModel *fileModel;

    QTreeView *treeView;

    QTableView *listView;

    FolderStrategy *folderStrategy;
    FileTypeStrategy *fileStrategy;

    QString lastPath;

signals:
private slots:
    void onFileStrategyClick();
    void onFolderStrategyClick();

    void onlistViewClick();
    void onCircleChartViewClick();
    void onBarChartViewClick();

    void onSelectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected);



};

#endif // MAINWINDOW_H
