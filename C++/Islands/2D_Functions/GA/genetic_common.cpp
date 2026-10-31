#include "genetic_common.hpp"

GA::GA(int islands, int island_pop, float mutation, float crossover, int migration_gen)
{
    islands_amount = islands;
    island_population_size = island_pop;
    p_mutation = mutation;
    p_crossover = crossover;
    migration_gen_step = migration_gen;
}