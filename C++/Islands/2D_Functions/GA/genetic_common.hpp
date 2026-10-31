#pragma once

#include "unit.hpp"

class GA
{
private:
    int islands_amount;
    int island_population_size;
    float p_mutation;
    float p_crossover;
    int migration_gen_step;

public:
    GA(int islands, int island_pop, float mutation, float crossover, int migration_gen);
    void InitIslands();
    /// @brief На данный момент алгоритм представлен в виде модульного монолита.
    /// Для его работы требуется запустить несколько параллельных потоков в одном месте.
    /// В будущем предполагается архитектура клиент-сервер для выбранного варианта
    /// параллельного алгоритма.
    /// @return Unit - лучший индивид
    Unit run();
};