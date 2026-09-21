package ga

// main genetic algorithm class for 2-dimensional functions extremum
type GA struct {
	island_amount          int
	island_population_size int
	p_mutation             float32
	p_crossover            float32

	populations [][]Unit
	Best_units  []Unit
}

func InitGA(islands int, population_per_island int, mutation float32, crossover float32) *GA {
	return &GA{
		island_amount:          islands,
		island_population_size: population_per_island,
		p_mutation:             mutation,
		p_crossover:            crossover,
	}
}

func (ga *GA) InitFirstIsnaders() {
	// TODO
}
