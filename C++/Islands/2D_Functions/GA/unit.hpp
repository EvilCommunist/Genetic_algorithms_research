#pragma once
#include <random>
#include <function.hpp>

constexpr auto delta = 0.000001f;

class Unit
{
private:
    float point;
    float fitness;

    inline void calculateFitness() { fitness = std::abs((F(this->point + delta) 
        - F(this->point)) / delta); }

public:
    Unit(float value);
    /// @brief Функция кроссинговера, принимает ссылку на генератор для избежания
    /// его реинициализации при каждой операции. Генератор создаётся один на поток,
    /// в будущем - один на устройство, где производится фрагмент распределённых
    /// вычислений
    /// @param another_unit - второй родитель
    /// @param gen - ссылка на генератор случайных числе данного потока / устройства
    /// @return Unit - новая особь
    Unit MakeChild(Unit &another_unit, std::mt19937 &gen);
    void Mutate(std::mt19937 &gen);
    inline float Fitness() const { return fitness; }
    inline float Point() const { return point; }
};