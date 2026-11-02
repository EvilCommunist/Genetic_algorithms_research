package ga

import (
	"math"
	"math/rand/v2"
)

const (
	min_percentage = 30
	max_percentage = 70

	min_mutation_range     = -10000
	max_mutation_range     = 10000
	mutation_division_coef = 100

	delta = 0.000001
)

// unit (chromosome) is a float value on X axis
type Unit struct {
	point float32
	fitness float32
}

func InitUnit(value float32) *Unit {
	unit := &Unit{
		point: value,
	}
	unit.calculateFitness()
	return unit
}

func (u *Unit) Crossover(another_u Unit) Unit {
	dna_percentage := float32(min_percentage+rand.IntN(max_percentage-min_percentage)) / 100 // 30%-70%
	child := Unit{
		point: u.point*dna_percentage + another_u.point*(1-dna_percentage),
	}
	child.calculateFitness()
	return child
}

func (u *Unit) Mutate() {
	u.point = u.point + float32(rand.IntN(max_mutation_range-min_mutation_range)+
		min_mutation_range)/mutation_division_coef
	u.calculateFitness()
}

func (u *Unit) calculateFitness() {
	u.fitness = float32(math.Abs(float64((F(u.point+delta) - F(u.point)) / delta)))
}

func (u *Unit) Fitness() float32 {
	return u.fitness
}

func (u *Unit) Point() float32 {
	return u.point
}