#ifndef RESISTOR_H
#define RESISTOR_H


class Resistor
{
private:
    double value;
public:
    Resistor();
    Resistor(double val);
    Resistor(const Resistor& other);

    // setters
    void setVal(double val);
    // getters
    double getVal() const;

    // Series Resistance
    Resistor operator+(const Resistor& other);
    // Parallel Resistance
    Resistor operator||(const Resistor& other);

    ~Resistor() {};
};

#endif