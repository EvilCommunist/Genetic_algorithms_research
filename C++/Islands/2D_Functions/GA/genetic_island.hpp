#pragma once

#include "unit.hpp"
#include <random>
#include <vector>
#include <utility>

using pair = std::pair<float, float>;

class IslandGA
{
private:
    int population_size;
    float p_mutation;
    float p_crossover;
    std::mt19937 generator;
    std::vector<Unit> current_population;
    std::vector<Unit> best_history;
    std::uniform_int_distribution<int> dist; 
    int max_iter;

    Unit findBest(std::vector<Unit> sample);
    std::vector<Unit> randomChoose();
    std::vector<Unit> tournament();


public:
    IslandGA(int pop_size, float mutation, float crossover, pair borders, int iterations);
    void InitializePopulation();
    void Iteration();
    /// @brief Раз в N поколений острова обмениваются лучшими особями для генетического
    /// разнообразия и улучшения популяции. Предполагается делать копии мигрантов, а не их
    /// перемещение, чтобы острова-отправители не теряли качество обитателей.
    /// @return вектор особей - мигранты
    std::vector<Unit> MigrateBest();
    void AcceptMigrants(std::vector<Unit> migrants);
};