package main

import (
	ga "ext_function_2d/GA"
	"fmt"
	"os"
	"strconv"
	"time"
)

func main() {
	// Значения по умолчанию (как в C++ версии)
	islands := 4
	islandPop := 100
	mutation := float32(0.3)
	crossover := float32(0.7)
	migrationGen := 20
	maxIter := 150
	borderMin := float32(-20.0)
	borderMax := float32(20.0)

	if len(os.Args) == 9 {
		var err error

		islands, err = strconv.Atoi(os.Args[1])
		if err != nil {
			panic("Ошибка: islands должно быть целым числом")
		}

		islandPop, err = strconv.Atoi(os.Args[2])
		if err != nil {
			panic("Ошибка: island_pop должно быть целым числом")
		}

		m, err := strconv.ParseFloat(os.Args[3], 32)
		if err != nil {
			panic("Ошибка: mutation должно быть числом")
		}
		mutation = float32(m)

		c, err := strconv.ParseFloat(os.Args[4], 32)
		if err != nil {
			panic("Ошибка: crossover должно быть числом")
		}
		crossover = float32(c)

		migrationGen, err = strconv.Atoi(os.Args[5])
		if err != nil {
			panic("Ошибка: migration_gen должно быть целым числом")
		}

		maxIter, err = strconv.Atoi(os.Args[6])
		if err != nil {
			panic("Ошибка: max_iter должно быть целым числом")
		}

		bMin, err := strconv.ParseFloat(os.Args[7], 32)
		if err != nil {
			panic("Ошибка: border_min должно быть числом")
		}
		borderMin = float32(bMin)

		bMax, err := strconv.ParseFloat(os.Args[8], 32)
		if err != nil {
			panic("Ошибка: border_max должно быть числом")
		}
		borderMax = float32(bMax)

	} else if len(os.Args) != 1 {
		fmt.Printf("Использование: %s [islands] [island_pop] [mutation] [crossover] [migration_gen] [max_iter] [border_min] [border_max]\n", os.Args[0])
		os.Exit(1)
	}

	geneticAlg := ga.NewGA(
		islands,
		islandPop,
		mutation,
		crossover,
		migrationGen,
		maxIter,
		[2]float32{borderMin, borderMax},
	)

	start := time.Now()
	result := geneticAlg.Run()
	elapsed := time.Since(start).Seconds()

	fmt.Printf("[{\"time\": %f}, {\"res\": %f}]\n", elapsed, result.Point())
}
