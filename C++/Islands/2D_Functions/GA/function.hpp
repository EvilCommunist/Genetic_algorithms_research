#pragma once

constexpr double PI = 3.14159265358979323846;
constexpr double E  = 2.71828182845904523536;

/// @brief Функция, для которой осуществляется поиск экстремума.
/// Подумать над динамическим определением функции?
/// @param x - точка на оси абсцисс
/// @return - точка на оси ординат согласно заданной функции
inline float F(float x)
{
    // return x * x - x / 2;
    // constexpr double A = 10.0;
    // return A + (x * x - A * std::cos(2 * PI * x));
    return 0.5f * (x * x * x * x - 16.0f * x * x + 5.0f * x);
}