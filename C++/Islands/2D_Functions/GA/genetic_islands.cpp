#include "genetic_island.hpp"
#include <algorithm>
#include <iterator>

constexpr auto migrants_percentage = 0.2f;

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
    
    best_history.push_back(findBest(current_population));
}

Unit IslandGA::findBest(std::vector<Unit> &sample)
{
    Unit best = sample[0];
    for (auto individual : sample)
    {
        if (best.Fitness() > individual.Fitness())
        {
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

std::vector<Unit> IslandGA::tournament()
{
    std::vector<Unit> selected{};
    for (size_t i = 0; i < current_population.size(); i++)
    {
        std::vector<Unit> contestants = randomChoose();
        selected.push_back(findBest(contestants));
    }
    return selected;
}

void IslandGA::Iteration()
{
    std::vector<Unit> selected = tournament();

    std::vector<Unit> offspring;
    offspring.reserve(population_size);

    std::uniform_real_distribution<float> chance_dist(0.0f, 1.0f);

    for (size_t i = 0; i + 1 < selected.size(); i += 2)
    {

        if (chance_dist(generator) < p_crossover)
        {
            Unit child1 = selected[i].MakeChild(selected[i + 1], generator);
            Unit child2 = selected[i + 1].MakeChild(selected[i], generator);

            if (chance_dist(generator) < p_mutation)
                child1.Mutate(generator);
            if (chance_dist(generator) < p_mutation)
                child2.Mutate(generator);

            offspring.push_back(std::move(child1));
            offspring.push_back(std::move(child2));
        }
        else
        {
            Unit copy1 = selected[i];
            Unit copy2 = selected[i + 1];

            if (chance_dist(generator) < p_mutation)
                copy1.Mutate(generator);
            if (chance_dist(generator) < p_mutation)
                copy2.Mutate(generator);

            offspring.push_back(std::move(copy1));
            offspring.push_back(std::move(copy2));
        }
    }

    if (selected.size() % 2 != 0)
    {
        Unit last_child = selected.back();
        if (chance_dist(generator) < p_mutation)
            last_child.Mutate(generator);
        offspring.push_back(std::move(last_child));
    }

    std::vector<Unit> combined = current_population;
    combined.insert(combined.end(),
                    std::make_move_iterator(offspring.begin()),
                    std::make_move_iterator(offspring.end()));

    std::sort(combined.begin(), combined.end(), [](const Unit &a, const Unit &b)
              {
                  return a.Fitness() < b.Fitness(); // Минимизация фитнесс функции (F(x) -> 0)
              });

    combined.resize(population_size);

    current_population = std::move(combined);

    best_history.push_back(current_population[0]);
}

std::vector<Unit> IslandGA::MigrateBest()
{
    std::vector<Unit> migrants(current_population.begin(),
                               current_population.begin() + current_population.size() * migrants_percentage);
    return migrants;
}

void IslandGA::AcceptMigrants(std::vector<Unit> &migrants)
{
    // Гарантировано, что на всех островах одинаковые по численности популяции и
    // мигрантов меньше чем аборигенов (20%)
    auto replace_start_it = current_population.end() - migrants.size();
    std::move(migrants.begin(), migrants.begin() + migrants.size(), replace_start_it);
}