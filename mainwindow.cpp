#include "mainwindow.h"
#include "fileexplorermodel.h"
#include "QSplitter"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    folderStrategy = new FolderStrategy();
    fileStrategy = new FileTypeStrategy();

    SizeCalculator::getInstance()->setCalculationStrategy(fileStrategy);

    menuBar = new QMenuBar();
    //viewMenuBar = new QMenuBar(this);
    //strategyMenuBar->setGeometry(0,0,800,20);
    setMenuBar(menuBar);
    setGeometry(100,100,800,500);
    changeStrategyMenu = new QMenu("Группировка");
    changeViewMenu = new QMenu("Вид");

    fileStrategyAction = new QAction("По файлам");
    folderStrategyAction = new QAction("По папкам");

    changeStrategyMenu->addAction(fileStrategyAction);
    changeStrategyMenu->addAction(folderStrategyAction);

    menuBar->addMenu(changeStrategyMenu);

    listViewAction = new QAction("Таблица");
    circleChartViewAction = new QAction("Столбчатая диаграмма");
    barChartViewAction = new QAction("Круговая диаграмма");

    changeViewMenu->addAction(listViewAction);
    changeViewMenu->addAction(barChartViewAction);
    changeViewMenu->addAction(circleChartViewAction);

    menuBar->addMenu(changeViewMenu);

    QString homePath = QDir::homePath();
    // Определим  файловой системы:
    dirModel =  new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath(homePath);

    treeView = new QTreeView();
    listView = new QTableView();

    fileModel = new FileExplorerModel(this);
    fileModel->updateData("D:/2021 minecraft");
    QSplitter *splitter = new QSplitter(this);


    qDebug() << homePath;
    treeView->setModel(dirModel);

    splitter->addWidget(treeView);
    splitter->addWidget(listView);

    setCentralWidget(splitter);

    qDebug() << "win created\n";

    connect(fileStrategyAction    , SIGNAL(triggered()), this, SLOT(onFileStrategyClick()  ) );
    connect(folderStrategyAction  , SIGNAL(triggered()), this, SLOT(onFolderStrategyClick()) );

    connect(listViewAction          , SIGNAL(triggered()), this, SLOT(onlistViewClick()));
    connect(barChartViewAction      , SIGNAL(triggered()), this, SLOT(onCircleChartViewClick()));
    connect(circleChartViewAction   , SIGNAL(triggered()), this, SLOT(onBarChartViewClick()));

    QItemSelectionModel *selectionModel = treeView->selectionModel();

    QModelIndex indexHomePath = dirModel->index(homePath);
    QFileInfo fileInfo = dirModel->fileInfo(indexHomePath);

    //Выполняем соединения слота и сигнала который вызывается когда осуществляется выбор элемента в TreeView
    connect(selectionModel, SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this, SLOT(onSelectionChangedSlot(const QItemSelection &, const QItemSelection &)));
    lastPath = homePath;
}
MainWindow::~MainWindow()
{

}

void MainWindow::onFileStrategyClick()
{
    if (listView->model() == nullptr) {

    } else {
        delete fileModel;
        fileModel = new FileExplorerModel();
    }
    qDebug() << "file strategy set\n";
    SizeCalculator::getInstance()->setCalculationStrategy(fileStrategy);
    fileModel->updateData(lastPath);
    listView->setModel(fileModel);

}

void MainWindow::onFolderStrategyClick()
{
    if (listView->model() == nullptr) {

    } else {
        delete fileModel;
        fileModel = new FileExplorerModel();
    }
    qDebug() << "folder strategy set\n";
    SizeCalculator::getInstance()->setCalculationStrategy(folderStrategy);
    fileModel->updateData(lastPath);
    if (listView->model() == nullptr) {
        listView->setModel(fileModel);
    }
}

void MainWindow::onSelectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
    //Q_UNUSED(selected);
    Q_UNUSED(deselected);
    QModelIndex index = treeView->selectionModel()->currentIndex();
    QModelIndexList indexs =  selected.indexes();
    QString filePath = "";

    // Размещаем инфо в statusbar относительно выделенного модельного индекса

   if (indexs.count() >= 1) {
        QModelIndex ix =  indexs.constFirst();
        filePath = dirModel->filePath(ix);
   }

   if (listView->model() == nullptr) {

   } else {
       delete fileModel;
       fileModel = new FileExplorerModel();
   }
   qDebug() << "HERE";
   fileModel->updateData(filePath);
   listView->setModel(fileModel);
   lastPath = filePath;
}

void MainWindow::onlistViewClick()
{
    qDebug() << "list view\n";
}
void MainWindow::onCircleChartViewClick()
{
    qDebug() << "circle view\n";
}
void MainWindow::onBarChartViewClick()
{
    qDebug() << "bar view\n";
}

