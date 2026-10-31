#include <unit.hpp>

constexpr auto min_percentage = 30;
constexpr auto max_percentage = 70;

constexpr auto min_mutation_range = -10000;
constexpr auto max_mutation_range = 10000;
constexpr auto mutation_division_coef = 100;

Unit::Unit(float value) : point(value)
{
    calculateFitness();
}

Unit Unit::MakeChild(Unit &another_unit, std::mt19937 &gen)
{
    std::uniform_int_distribution<int> dist(min_percentage, max_percentage - 1);
    float dna_percentage = static_cast<float>(dist(gen)) / 100.0f;
    return Unit(
        this->point * dna_percentage + another_unit.point * (1.0f - dna_percentage));
}

void Unit::Mutate(std::mt19937 &gen)
{
    std::uniform_int_distribution<int> dist(min_mutation_range, max_mutation_range - 1);
    float mutation_amount = static_cast<float>(dist(gen)) / mutation_division_coef;
    this->point += mutation_amount;

    calculateFitness();
}
