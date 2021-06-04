#include "sizecalculator.h"

SizeCalculator *SizeCalculator::getInstance()
{
    //если объект ещё не был создан, создаем новый
    if (instance==nullptr) {
        instance = new SizeCalculator();
    }
    return instance;
}

SizeCalculator::SizeCalculator()
{
    m_strategy = nullptr;
}
//в паттерне стратегия мы не должны управлять временем жизни стратегии
SizeCalculator::~SizeCalculator()
{
    m_strategy = nullptr;
}
void SizeCalculator::setCalculationStrategy(CalculationStrategy *strategy)
{
    m_strategy = strategy;
}
//посчитать размер
FileData SizeCalculator::Calculate(QString &path) {
    if (m_strategy == nullptr) {
        throw std::runtime_error("No strategy is set");
    }
    try {
        return m_strategy->calculate(path);
    } catch (std::runtime_error &exc) {
        throw exc;
    }
}
