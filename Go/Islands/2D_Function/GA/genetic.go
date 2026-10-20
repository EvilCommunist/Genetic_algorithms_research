package ga

import (
	"math/rand"
	"slices"
	"sync"
)

// main genetic algorithm class for 2-dimensional functions extremum
type GA struct {
	island_amount          int
	island_population_size int
	p_mutation             float32
	p_crossover            float32
	center_of_distribution int

	populations [][]Unit
	Best_units  []Unit
}

func InitGA(islands int, population_per_island int, mutation float32, crossover float32, center int) *GA {
	return &GA{
		island_amount:          islands,
		island_population_size: population_per_island,
		p_mutation:             mutation,
		p_crossover:            crossover,
		center_of_distribution: center,
		populations:            make([][]Unit, islands), // возможно, вынести в острова?
	}
}

func (ga *GA) InitFirstIsanders() { // Переделать на работу с объектами островов???
	wg := sync.WaitGroup{}
	wg.Add(ga.island_amount)
	for i := range ga.island_amount {
		go func(num int) {
			defer wg.Done()
			island_population := make([]Unit, ga.island_population_size)
			for j := range ga.island_amount {
				value := rand.Float32()
				island_population[j] = *InitUnit(value)
			}
			ga.populations[num] = island_population
		}(i)
	}
	wg.Wait()
}

func (ga *GA) randomSample(length int, islanders []Unit) []Unit { // возможно потребуется вынести операцию в остров
	contestantsAmount := min(3, length)
	usedIndexes := make([]int, 0)
	chosen := make([]Unit, 0)

	for range contestantsAmount {
		index := rand.Intn(length)
		for !slices.Contains(usedIndexes, index) {
			index = rand.Intn(length)
		}
		chosen = append(chosen, islanders[index])
		usedIndexes = append(usedIndexes, index)
	}

	return chosen
}

func (ga *GA) commonTournament(islanders []Unit) {
	// [THINK] Алгоритм должен работать по островной системе: генетические операции на
	// протяжении N поколений работают изолированно, периодически пересекаясь
	// TODO: tournament function (see https://github.com/EvilCommunist/Neuro-Simulator/blob/main/kernel/math/heuristicsAlg/geneticalgorithm.cpp#L66)
}
