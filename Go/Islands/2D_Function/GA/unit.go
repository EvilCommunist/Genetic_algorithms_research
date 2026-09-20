package ga

import "math/rand"

const (
	min_percentage = 30
	max_percentage = 70

	min_mutation_range     = -10000
	max_mutation_range     = 10000
	mutation_division_coef = 100
)

// unit (chromosome) is a float value on X axis
type Unit struct {
	point float32
}

func InitUnit(value float32) *Unit {
	return &Unit{
		point: value,
	}
}

func (u *Unit) Crossover(another_u Unit) Unit {
	dna_percentage := float32(min_percentage+rand.Intn(max_percentage-min_percentage)) / 100 // 30%-70%

	return Unit{
		point: u.point*dna_percentage + another_u.point*(1-dna_percentage),
	}
}

func (u *Unit) Mutate() {
	u.point = u.point + float32(rand.Intn(max_mutation_range-min_mutation_range)+
		min_mutation_range)/mutation_division_coef
}

func (u *Unit) Fitness() {
	// TODO
}
