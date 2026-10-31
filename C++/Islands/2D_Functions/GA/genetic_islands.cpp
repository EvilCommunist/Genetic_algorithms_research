#include "genetic_island.hpp"
#include <algorithm>
#include <iterator>

IslandGA::IslandGA(int pop_size, float mutation, float crossover,
                   pair borders, int iterations) : generator(std::random_device{}()),
                                                   dist(borders.first, borders.second),
                                                   population_size(pop_size),
                                                   p_mutation(mutation),
                                                   p_crossover(crossover),
                                                   max_iter(iterations)
{
}

void IslandGA::InitializePopulation()
{
    for (int i = 0; i < population_size; i++)
    {
        float x_value = static_cast<float>(dist(generator)) / 100.0f;
        current_population.push_back(Unit(x_value));
    }
}

Unit IslandGA::findBest(std::vector<Unit> sample){
    Unit best(0.0);
    for(auto individual: sample){
        if(best.Fitness() > individual.Fitness()){
            best = individual;
        }
    }
    return best;
}

std::vector<Unit> IslandGA::randomChoose()
{
    int contestants_amount = std::min(3, static_cast<int>(current_population.size()));

    std::vector<Unit> chosen;
    chosen.reserve(contestants_amount);

    std::sample(
        current_population.begin(),
        current_population.end(),
        std::back_inserter(chosen),
        contestants_amount,
        generator);

    return chosen;
}

std::vector<Unit> IslandGA::tournament(){
    std::vector<Unit> selected{};
    for(size_t i = 0; i < current_population.size(); i++){
        std::vector<Unit> contestants = randomChoose();
        selected.push_back(findBest(contestants));
    }
    return selected;
}

void IslandGA::Iteration()
{
}