#pragma once

#include "unit.hpp"
#include "genetic_island.hpp"

class GA
{
private:
    int islands_amount;
    int island_population_size;
    float p_mutation;
    float p_crossover;
    int migration_gen_step;
    int max_iter_per_island;
    pair search_borders;

public:
    GA(int islands, int island_pop, float mutation, float crossover,
       int migration_gen, int max_it_isl, pair borders);
    // [THINK] В будущем вероятно лучше вынести инициализацию островов в отдельную функцию.
    // Для клиент-серверной архитектуры в этом есть логика?
    // ____________________________________________________________________________________
    /// @brief На данный момент алгоритм представлен в виде модульного монолита.
    /// Для его работы требуется запустить несколько параллельных потоков в одном месте.
    /// В будущем предполагается архитектура клиент-сервер для выбранного варианта
    /// параллельного алгоритма.
    /// @return Unit - лучший индивид
    Unit run();
};