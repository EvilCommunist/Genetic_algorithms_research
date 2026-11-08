package ga

func F(x float32) float32 { // could be set somehow dynamically
	return 0.5 * (x*x*x*x - 16.0*x*x + 5.0*x)
}
