#include "mainwindow.h"
#include "fileexplorermodel.h"
#include "QSplitter"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    //Создаем конкретные объекты стратегий
    folderStrategy = new FolderStrategy();
    fileStrategy = new FileTypeStrategy();
    //Задаем файловую группировку как группировку по умолчанию
    SizeCalculator::getInstance()->setCalculationStrategy(fileStrategy);

    //Создаем объект панели меню
    menuBar = new QMenuBar();
    //привязываем объект к окну
    setMenuBar(menuBar);
    //задаем геометрию окна
    setGeometry(100,100,800,500);
    //создаем разделы меню группировка и вид
    changeStrategyMenu = new QMenu("Группировка");
    changeViewMenu = new QMenu("Вид");

    //Действия в разделе группировка
    fileStrategyAction = new QAction("По файлам");
    folderStrategyAction = new QAction("По папкам");
    //Привязываем действия к разделу
    changeStrategyMenu->addAction(fileStrategyAction);
    changeStrategyMenu->addAction(folderStrategyAction);

    //Добавляем в панель меню меню группировки
    menuBar->addMenu(changeStrategyMenu);

    //Аналогичные действия с разделом меню "Вид"
    listViewAction = new QAction("Таблица");
    circleChartViewAction = new QAction("Столбчатая диаграмма");
    barChartViewAction = new QAction("Круговая диаграмма");

    changeViewMenu->addAction(listViewAction);
    changeViewMenu->addAction(barChartViewAction);
    changeViewMenu->addAction(circleChartViewAction);

    menuBar->addMenu(changeViewMenu);

    //Домашняя папка как директория по-умолчанию
    QString homePath = QDir::homePath();


    //Создаем модель файловой системы
    dirModel =  new QFileSystemModel(this);
    //задаем фильты (показывать все директории, не показывать файлы . и ..
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    //задаем домашнюю папку как корневую для модели
    dirModel->setRootPath(homePath);

    //создаем виджеты для отображения моделей
    treeView = new QTreeView();
    listView = new QTableView();
    chartView = new QtCharts::QChartView();
    //создаем модель для отображения данных подсчета
    fileModel = new FileExplorerModel(this);
    //Виджет-контейнер для красивого размещения видов
    splitter = new QSplitter(this);

    //привязываем модели к виду
    treeView->setModel(dirModel);
    listView->setModel(fileModel);
    //добавляем виджеты вида в QSplitter
    splitter->addWidget(treeView);
    splitter->addWidget(listView);

    //Делаем виджет QSplitter центральным
    setCentralWidget(splitter);

    //Связываем сигналы-слоты кнопок меню.
    //для группировок
    connect(fileStrategyAction    , SIGNAL(triggered()), this, SLOT(onFileStrategyClick()  ) );
    connect(folderStrategyAction  , SIGNAL(triggered()), this, SLOT(onFolderStrategyClick()) );
    //для отображения
    connect(listViewAction          , SIGNAL(triggered()), this, SLOT(onlistViewClick()));
    connect(barChartViewAction      , SIGNAL(triggered()), this, SLOT(onCircleChartViewClick()));
    connect(circleChartViewAction   , SIGNAL(triggered()), this, SLOT(onBarChartViewClick()));

    //Создаем адаптеры и добавляем их в наблюдатель
    listAdapter = new ListAdapter(fileModel);
    pieChartAdapter = new PieChartAdapter();
    barChartAdapter = new BarChartAdapter();

    SizeCalculator::getInstance()->getObserver()->subscribe(listAdapter);
    SizeCalculator::getInstance()->getObserver()->subscribe(pieChartAdapter);
    SizeCalculator::getInstance()->getObserver()->subscribe(barChartAdapter);

    //Выполняем соединения слота и сигнала который вызывается когда осуществляется выбор элемента в TreeView
    QItemSelectionModel *selectionModel = treeView->selectionModel();
    connect(selectionModel, SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this, SLOT(onSelectionChangedSlot(const QItemSelection &, const QItemSelection &)));

    viewNum = MainWindow::LIST;
}
MainWindow::~MainWindow()
{
    //Удаляем конкретные объекты стратегий и адаптеры. Остальное привязано к MainWindow и удалится само.
    delete folderStrategy;
    delete fileStrategy;
    delete listAdapter;
    delete barChartAdapter;
    delete pieChartAdapter;
    delete listView;
    delete chartView;
}

void MainWindow::onFileStrategyClick()
{
    //qDebug() << "file strategy set\n";

    //Производим смену стратегии в калькуляторе, обновляем данные в модели
    SizeCalculator::getInstance()->setCalculationStrategy(fileStrategy);
    SizeCalculator::getInstance()->Calculate(lastPath);
    splitter->replaceWidget(1,listView);
    switch (viewNum) {
    case BAR:
        chartView->setChart(barChartAdapter->getChart());
        splitter->replaceWidget(1,chartView);
        break;
    case PIE:
        chartView->setChart(pieChartAdapter->getChart());
        splitter->replaceWidget(1,chartView);
        break;
    default:
        break;
    }
}

void MainWindow::onFolderStrategyClick()
{
    //qDebug() << "folder strategy set\n";
    //Производим смену стратегии в калькуляторе, обновляем данные
    SizeCalculator::getInstance()->setCalculationStrategy(folderStrategy);
    SizeCalculator::getInstance()->Calculate(lastPath);
    splitter->replaceWidget(1,listView);
    switch (viewNum) {
    case BAR:
        chartView->setChart(barChartAdapter->getChart());
        splitter->replaceWidget(1,chartView);
        break;
    case PIE:
        delete chartView;
        chartView = new QtCharts::QChartView();
        chartView->setChart(pieChartAdapter->getChart());
        splitter->replaceWidget(1,chartView);
        break;
    default:
        break;
    }
}

void MainWindow::onSelectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{

    Q_UNUSED(deselected);
    //Получаем объект индекса выбранного элемента
    QModelIndexList indexs =  selected.indexes();
    //Строка для записи пути до выбранного элемента
    QString filePath = "";


   //записываем путь в строку
   if (indexs.count() >= 1) {
        QModelIndex ix =  indexs.constFirst();
        filePath = dirModel->filePath(ix);
   }
   //обновляем данные в модели
   lastPath = filePath;
   SizeCalculator::getInstance()->Calculate(filePath);
   splitter->replaceWidget(1,listView);

   switch (viewNum) {
   case BAR:
       barChartAdapter->update();
       chartView->setChart(barChartAdapter->getChart());
       splitter->replaceWidget(1,chartView);
       break;
   case PIE:
       pieChartAdapter->update();
       chartView->setChart(pieChartAdapter->getChart());
       splitter->replaceWidget(1,chartView);
       break;
   default:
       break;
   }
}


void MainWindow::onlistViewClick()
{
    listAdapter->update();
    splitter->replaceWidget(1,listView);
}
void MainWindow::onCircleChartViewClick()
{
    pieChartAdapter->update();
    chartView->setChart(pieChartAdapter->getChart());
    splitter->replaceWidget(1,chartView);
    viewNum = PIE;
}
void MainWindow::onBarChartViewClick()
{
    barChartAdapter->update();
    chartView->setChart(barChartAdapter->getChart());
    splitter->replaceWidget(1,chartView);
    viewNum = BAR;
}

