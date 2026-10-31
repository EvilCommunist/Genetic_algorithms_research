#include <unit.hpp>

Unit::Unit(float value)
{
    point = value;
}

Unit Unit::operator+(Unit &another_unit)
{
    return Unit(0.0); // TODO: реализовать скрещивание
}

void Unit::Mutate()
{
    // TODO: реализовать мутацию
}

float Unit::Fitness(){
    return 0.0; // производная
}
