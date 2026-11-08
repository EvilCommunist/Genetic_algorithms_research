package ga

import (
	"math/rand/v2"
	"slices"
)

// main genetic algorithm class for 2-dimensional functions extremum
type GAIsland struct {
	population_size        int
	p_mutation             float32
	p_crossover            float32
	center_of_distribution int
	population             []Unit
	best_units             []Unit
	left_border            float32
	right_border           float32
	max_iteration          int
}

func InitGA(islands int, population int, mutation float32,
	crossover float32, center int) *GAIsland {
	return &GAIsland{
		population_size:        population,
		p_mutation:             mutation,
		p_crossover:            crossover,
		center_of_distribution: center,
		population:             make([]Unit, islands),
	}
}

func (ga *GAIsland) InitFirstIsanders() {
	ga.population = make([]Unit, ga.population_size)
	for i := range ga.population_size {
		value := rand.Float32()
		ga.population[i] = *InitUnit(value)
	}
}

func (ga *GAIsland) findBest(sample []Unit) Unit {
	best := sample[0]
	for _, ind := range sample {
		if ind.Fitness() < best.Fitness() {
			best = ind
		}
	}
	return best
}

func (ga *GAIsland) GetTotalBest() Unit {
	return ga.findBest(ga.best_units)
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

func (ga *GAIsland) tournament() []Unit {
	selected := make([]Unit, ga.population_size)
	for i := 0; i < ga.population_size; i++ {
		contestants := ga.randomSample(3, ga.population)
		selected[i] = ga.findBest(contestants)
	}
	return selected
}

func (ga *GAIsland) checkAndFixBorders(unit *Unit) {
	if unit.Point() < ga.left_border {
		*unit = *InitUnit(ga.left_border)
	} else if unit.Point() > ga.right_border {
		*unit = *InitUnit(ga.right_border)
	}
}

func (ga *GAIsland) Iteration() {
	selected := ga.tournament()
	offspring := make([]Unit, 0, ga.population_size)

	for i := 0; i+1 < len(selected); i += 2 {
		var child1, child2 Unit
		if rand.Float32() < ga.p_crossover {
			child1 = selected[i].Crossover(selected[i+1])
			child2 = selected[i+1].Crossover(selected[i])
		} else {
			child1 = selected[i]
			child2 = selected[i+1]
		}

		if rand.Float32() < ga.p_mutation {
			child1.Mutate()
		}
		ga.checkAndFixBorders(&child1)

		if rand.Float32() < ga.p_mutation {
			child2.Mutate()
		}
		ga.checkAndFixBorders(&child2)

		offspring = append(offspring, child1, child2)
	}

	if len(selected)%2 != 0 {
		last := selected[len(selected)-1]
		if rand.Float32() < ga.p_mutation {
			last.Mutate()
		}
		ga.checkAndFixBorders(&last)
		offspring = append(offspring, last)
	}

	combined := make([]Unit, 0, len(ga.population)+len(offspring))
	combined = append(combined, ga.population...)
	combined = append(combined, offspring...)

	slices.SortFunc(combined, func(a, b Unit) int {
		if a.Fitness() < b.Fitness() {
			return -1
		} else if a.Fitness() > b.Fitness() {
			return 1
		}
		return 0
	})

	ga.population = combined[:ga.population_size]
	ga.best_units = append(ga.best_units, ga.population[0])
}

func (ga *GAIsland) MigrateBest() []Unit {
	count := int(float32(ga.population_size) * 0.2)
	migrants := make([]Unit, count)
	copy(migrants, ga.population[:count])
	return migrants
}

func (ga *GAIsland) AcceptMigrants(migrants []Unit) {
	if len(migrants) == 0 {
		return
	}
	start := ga.population_size - len(migrants)
	copy(ga.population[start:], migrants)
}
