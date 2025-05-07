#ifndef THEVENINEQUIVALENT_H
#define THEVENINEQUIVALENT_H
#include <string>

class TheveninEquivalent
{
private:
    double TheveninResistance;
    double TheveninVoltage;
    double loadResistance;
    double branchCurrent;
    int circuitCounter;
    int ProblemNumber;
    
public:
    // constructors
    TheveninEquivalent();
    TheveninEquivalent(double, double, double, double, int, int);
    TheveninEquivalent(const TheveninEquivalent &);

    // setters
    void setProblemNumber();

    // getters
    double getLoadResistance() const;
    double getBranchCurrent() const;
    double getTheveninVoltage() const;
    double getTheveninResistance() const;
    int getInstanceCount() const;
    int getProblemNumber() const;

    // main methods
    double FindTheveninResistance();
    double FindTheveninVoltage();
    double FindPowerSuppliedToLoad();
    double CalculatePowerSuppliedToLoad() const;
    void suggestions();
    void ShowEquivalentCircuit();
    void writeToFile();

    ~TheveninEquivalent() {};
};

#endif