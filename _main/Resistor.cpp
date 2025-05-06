#include "Resistor.h"
#include <iostream>

Resistor::Resistor() : value(0.0)
{
}
Resistor::Resistor(double val) : value(val)
{
}
Resistor::Resistor(const Resistor &other) : value(other.value)
{
}

// setters
void Resistor::setVal(double val)
{
    value = val;
}
// getters
double Resistor::getVal() const
{
    return value;
}

// Series Resistance
Resistor Resistor::operator+(const Resistor &other)
{
    double seriesReq = value + other.value;
    return Resistor(seriesReq);
}
// Parallel Resistance
Resistor Resistor::operator||(const Resistor &other)
{
    double parallelReq = 1 / (1 / value + 1 / other.value);
    return Resistor(parallelReq);
}