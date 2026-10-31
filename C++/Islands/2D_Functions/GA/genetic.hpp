#pragma once

class GA
{
private:
    int island_amount;
    int island_population_size;
    float p_mutation;
    float p_crossover;

public:
    GA(int islands, int island_pop, float mutation, float crossover);
    //void InitIslands();
};