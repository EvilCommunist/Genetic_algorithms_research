#include <iostream>
#include <chrono>
#include "genetic_common.hpp"

int main(int argc, char *argv[])
{
    // Значения по умолчанию
    int islands = 4;
    int island_pop = 100;
    float mutation = 0.3f;
    float crossover = 0.7f;
    int migration_gen = 20;
    int max_iter = 150;
    float border_min = -20.0f;
    float border_max = 20.0f;

    if (argc == 9)
    {
        try
        {
            islands = std::stoi(argv[1]);
            island_pop = std::stoi(argv[2]);
            mutation = std::stof(argv[3]);
            crossover = std::stof(argv[4]);
            migration_gen = std::stoi(argv[5]);
            max_iter = std::stoi(argv[6]);
            border_min = std::stof(argv[7]);
            border_max = std::stof(argv[8]);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Ошибка парсинга аргументов: " << e.what() << std::endl;
            return 1;
        }
    }
    else if (argc != 1)
    {
        std::cerr << "Использование: " << argv[0]
                  << " [islands] [island_pop] [mutation] [crossover] [migration_gen] [max_iter] [border_min] [border_max]"
                  << std::endl;
        return 1;
    }

    GA ga(islands, island_pop, mutation, crossover,
          migration_gen, max_iter, {border_min, border_max});
    auto start = std::chrono::high_resolution_clock::now();
    auto result = ga.run();
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    std::cout << "[{\"time\": " << elapsed.count()
              << "}, {\"res\": " << result.Point() << "}]" << std::endl;
}