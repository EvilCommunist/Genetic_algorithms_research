package ga

import (
	"math/rand/v2"
)

// main genetic algorithm class for 2-dimensional functions extremum
type GAIsland struct {
	island_amount          int
	island_population_size int
	p_mutation             float32
	p_crossover            float32
	center_of_distribution int

	population []Unit
	best_units  []Unit
}

func InitGA(islands int, population_per_island int, mutation float32,
	crossover float32, center int) *GAIsland {
	return &GAIsland{
		island_amount:          islands,
		island_population_size: population_per_island,
		p_mutation:             mutation,
		p_crossover:            crossover,
		center_of_distribution: center,
		population:            make([]Unit, islands),
	}
}

func (ga *GAIsland) InitFirstIsanders() {
	ga.population = make([]Unit, ga.island_population_size)
	for i := range ga.island_amount {
		value := rand.Float32()
		ga.population[i] = *InitUnit(value)
	}
}

func (ga *GAIsland) randomSample(length int, islanders []Unit) []Unit {
	contestantsAmount := min(3, length)
    perm := rand.Perm(length)
    chosen := make([]Unit, contestantsAmount)
    for i := 0; i < contestantsAmount; i++ {
        chosen[i] = islanders[perm[i]]
    }
    return chosen
}

func (ga *GAIsland) tournament() {
	// [THINK] Алгоритм должен работать по островной системе: генетические операции на
	// протяжении N поколений работают изолированно, периодически пересекаясь
	// TODO: tournament function (see https://github.com/EvilCommunist/Neuro-Simulator/blob/main/kernel/math/heuristicsAlg/geneticalgorithm.cpp#L66)
}
