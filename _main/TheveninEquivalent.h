#ifndef THEVENINEQUIVALENT_H
#define THEVENINEQUIVALENT_H
#include <string>

class TheveninEquivalent
{
private:
    int SeriesResistorCount;
    int ParallelResistorCount;
    double TheveninResistance;
    double TheveninVoltage;
    double loadResistance;
    double branchCurrent;
    int circuitCounter;
    int assignmentNumber;

protected:
    // if needed for future features or debugging
    static int instanceCount;

public:
    // constructors
    TheveninEquivalent();
    TheveninEquivalent(int, int, double, double, double, double, int, int);
    TheveninEquivalent(const TheveninEquivalent &);

    // setters
    void setParallelResistorCount(int);
    void setSeriesResistorCount(int);
    void setLoadResistance(double);
    void setBranchCurrent(double);
    void setTheveninVoltage(double);
    void setTheveninResistance(double);
    void setAssignmentNumber();

    // getters
    int getParallelResistorCount() const;
    int getSeriesResistorCount() const;
    double getLoadResistance() const;
    double getBranchCurrent() const;
    double getTheveninVoltage() const;
    double getTheveninResistance() const;
    int getInstanceCount() const;
    int getAssignmentNumber() const;

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