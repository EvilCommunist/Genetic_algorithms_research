#include "genetic_common.hpp"
#include <barrier>

GA::GA(int islands, int island_pop, float mutation, float crossover, int migration_gen,
       int max_it_isl, pair borders) : islands_amount(islands),
                                       island_population_size(island_pop),
                                       p_mutation(mutation),
                                       p_crossover(crossover),
                                       migration_gen_step(migration_gen),
                                       max_iter_per_island(max_it_isl),
                                       search_borders(borders)
{
}

Unit GA::run()
{
    std::vector<IslandGA> islands;
    islands.reserve(islands_amount);
    for (int i = 0; i < islands_amount; ++i)
    {
        islands.emplace_back(island_population_size, p_mutation, p_crossover,
                             search_borders, max_iter_per_island);
        islands.back().InitializePopulation();
    }

    std::vector<std::vector<Unit>> outbox(islands_amount);

    std::barrier sync_point(islands_amount);

    std::vector<std::thread> threads;
    threads.reserve(islands_amount);

    for (int id = 0; id < islands_amount; id++)
    {
        threads.emplace_back([&, id]()
                             {
            IslandGA& island = islands[id];
            int prev_island = (id - 1 + islands_amount) % islands_amount;

            for (int gen = 0; gen < max_iter_per_island; ++gen) {
                island.Iteration();

                if (gen > 0 && gen % migration_gen_step == 0) {
                    outbox[id] = island.MigrateBest();

                    sync_point.arrive_and_wait();

                    island.AcceptMigrants(outbox[prev_island]);

                    sync_point.arrive_and_wait();
                }
            } });
    }

    for (auto &t : threads)
        t.join();

    Unit global_best = islands[0].GetTotalBest();
    for (int i = 1; i < islands_amount; ++i)
    {
        Unit candidate = islands[i].GetTotalBest();
        if (candidate.Fitness() < global_best.Fitness())
        {
            global_best = candidate;
        }
    }
    return global_best;
}