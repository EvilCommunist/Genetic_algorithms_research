#pragma once

class Unit
{
private:
    float point;

public:
    Unit(float value);
    Unit operator+(Unit &another_unit);
    float Fitness();
    void Mutate();
};