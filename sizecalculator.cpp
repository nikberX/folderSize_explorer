#include "sizecalculator.h"

SizeCalculator *SizeCalculator::getInstance()
{
    //если объект ещё не был создан, создаем новый
    if (instance==nullptr) {
        instance = new SizeCalculator();
    }
    return instance;
}

SizeCalculator::SizeCalculator() : m_data(0,QMap<QString,double>())
{
    observer = new FileExplorerObserver();
    m_strategy = nullptr;
}
//в паттерне стратегия мы не должны управлять временем жизни стратегии
SizeCalculator::~SizeCalculator()
{
    m_strategy = nullptr;
    delete observer;
}
void SizeCalculator::setCalculationStrategy(CalculationStrategy *strategy)
{
    m_strategy = strategy;
}

FileData SizeCalculator::getData()
{
    return m_data;
}
//посчитать размер
void SizeCalculator::Calculate(QString &path) {
    if (m_strategy == nullptr) {
        throw std::runtime_error("No strategy is set");
    }
    try {
        m_data = m_strategy->calculate(path);
        observer->notify();
    } catch (std::runtime_error &exc) {
        throw exc;
    }
}

FileExplorerObserver* SizeCalculator::getObserver() {
    return observer;
}
