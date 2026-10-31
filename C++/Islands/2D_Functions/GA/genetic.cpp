#include "genetic.hpp"

GA::GA(int islands, int island_pop, float mutation, float crossover)
{
    island_amount = islands;
    island_population_size = island_pop;
    p_mutation = mutation;
    p_crossover = crossover;
}