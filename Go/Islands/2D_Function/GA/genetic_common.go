// genetic_common.go
package ga

import (
	"context"
	"sync"

	"github.com/marusama/cyclicbarrier"
)

type GA struct {
	islands_amount         int
	island_population_size int
	p_mutation             float32
	p_crossover            float32
	migration_gen_step     int
	max_iter_per_island    int
	search_borders         [2]float32
}

func NewGA(islands, islandPop int, mutation, crossover float32,
	migrationGen, maxIter int, borders [2]float32) *GA {
	return &GA{
		islands_amount:         islands,
		island_population_size: islandPop,
		p_mutation:             mutation,
		p_crossover:            crossover,
		migration_gen_step:     migrationGen,
		max_iter_per_island:    maxIter,
		search_borders:         borders,
	}
}

func (g *GA) Run() Unit {
	islands := make([]*GAIsland, g.islands_amount)
	for i := 0; i < g.islands_amount; i++ {
		islands[i] = &GAIsland{
			population_size:        g.island_population_size,
			p_mutation:             g.p_mutation,
			p_crossover:            g.p_crossover,
			center_of_distribution: 0,
			left_border:            g.search_borders[0],
			right_border:           g.search_borders[1],
			population:             make([]Unit, g.island_population_size),
			best_units:             make([]Unit, 0, g.max_iter_per_island),
			max_iteration:          g.max_iter_per_island,
		}
		islands[i].InitFirstIsanders()
	}

	outboxes := make([][]Unit, g.islands_amount)
	var wg sync.WaitGroup
	wg.Add(g.islands_amount)

	barrier := cyclicbarrier.New(g.islands_amount)
	barrierContext := context.Background()

	for id := 0; id < g.islands_amount; id++ {
		go func(id int) {
			defer wg.Done()
			island := islands[id]
			prev := (id - 1 + g.islands_amount) % g.islands_amount

			for gen := 0; gen < g.max_iter_per_island; gen++ {
				island.Iteration()

				if gen > 0 && gen%g.migration_gen_step == 0 {
					migrants := island.MigrateBest()
					outboxes[id] = migrants

					err := barrier.Await(barrierContext)
					if err != nil {
						panic(err)
					}

					island.AcceptMigrants(outboxes[prev])

					err = barrier.Await(barrierContext)
					if err != nil {
						panic(err)
					}
				}
			}
		}(id)
	}
	wg.Wait()

	globalBest := islands[0].GetTotalBest()
	for i := 1; i < g.islands_amount; i++ {
		candidate := islands[i].GetTotalBest()
		if candidate.Fitness() < globalBest.Fitness() {
			globalBest = candidate
		}
	}
	return globalBest
}
