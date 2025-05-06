#include <iostream>
#include "TheveninEquivalent.h"
#include <sstream>
#include <fstream>
#include <string>
#include "InputParser.h";

int TheveninEquivalent::instanceCount = 0;

// constructors
TheveninEquivalent::TheveninEquivalent() : SeriesResistorCount(0), ParallelResistorCount(0), loadResistance(0.0), branchCurrent(0.0), TheveninVoltage(0.0), TheveninResistance(0.0), circuitCounter(0), assignmentNumber(0) {
    instanceCount++;
}
TheveninEquivalent::TheveninEquivalent(int src, int prc, double lr, double bc, double tv, double tr, int cc, int an) : SeriesResistorCount(src), ParallelResistorCount(prc), loadResistance(lr), branchCurrent(bc), TheveninVoltage(tv), TheveninResistance(tr), circuitCounter(cc), assignmentNumber(an) {
    instanceCount++;
}
TheveninEquivalent::TheveninEquivalent(const TheveninEquivalent &other) : ParallelResistorCount(other.ParallelResistorCount), SeriesResistorCount(other.SeriesResistorCount), loadResistance(other.loadResistance), branchCurrent(other.branchCurrent), TheveninVoltage(other.TheveninVoltage), TheveninResistance(other.TheveninResistance), circuitCounter(other.circuitCounter), assignmentNumber(other.assignmentNumber) {
    instanceCount++;
};


// setters
void TheveninEquivalent::setSeriesResistorCount(int src)
{
    SeriesResistorCount = src;
}
void TheveninEquivalent::setParallelResistorCount(int prc)
{
    ParallelResistorCount = prc;
}
void TheveninEquivalent::setLoadResistance(double lr)
{
    loadResistance = lr;
}
void TheveninEquivalent::setBranchCurrent(double bc)
{
    branchCurrent = bc;
}
void TheveninEquivalent::setTheveninVoltage(double tv)
{
    TheveninVoltage = tv;
}
void TheveninEquivalent::setTheveninResistance(double tr)
{
    TheveninResistance = tr;
}
void TheveninEquivalent::setAssignmentNumber() {
    std::cout << "Enter assignment number: ";
    std::cin >> assignmentNumber;
}

// getters
int TheveninEquivalent::getSeriesResistorCount() const
{
    return SeriesResistorCount;
}
int TheveninEquivalent::getParallelResistorCount() const
{
    return ParallelResistorCount;
}
double TheveninEquivalent::getLoadResistance() const
{
    return loadResistance;
}
double TheveninEquivalent::getBranchCurrent() const
{
    return branchCurrent;
}
double TheveninEquivalent::getTheveninVoltage() const
{
    return TheveninVoltage;
}
double TheveninEquivalent::getTheveninResistance() const
{
    return TheveninResistance;
}
int TheveninEquivalent::getInstanceCount() const {
    return instanceCount;
}

int TheveninEquivalent::getAssignmentNumber() const {
    return assignmentNumber;
}

// main methods
double TheveninEquivalent::FindTheveninResistance()
{
 std::cout << "\n\n*************** Thevenin Resistance ***************\n\n";
 std::cout << "Enter the circuit's resistor expression, no space.\ne.g. if resistor 1, 2, and 3 are in series and in parallel with resistor 4, the input would be: (R1+R2+R3)//R4\n\nResitor expression:";
 std::string userInp;
 std::getline(std::cin, userInp);
 TheveninResistance = ParseInp(userInp).getVal();
 std::cout << "The Thevenin Resistance for the circuit is: " << TheveninResistance << " Ohm's" << std::endl;
}

double TheveninEquivalent::FindTheveninVoltage()
{
    double branchResistance;
    std::cout << "\n*****Thevenin Voltage*****" << std::endl;
    std::cout << "\nImportant: Use KCL to find the current through the branch of the node just before the terminals.\n"
              << "Remember: KCL states that the sum of all currents going into a node is zero; meaning I1 + I2 + ... + In = 0 \n\n";

    std::cout << "Enter the value of the branch current: ";
    std::cin >> branchCurrent;
    std::cout << "\nEnter the value of the resistor in the same branch: ";
    std::cin >> branchResistance;
    std::cout << "\n\nFinding Thevenin voltage....\n\n\n";

    // Ohm's Law
    TheveninVoltage = branchCurrent * branchResistance;

    std::cout << "The Thevenin Voltage is: " << TheveninVoltage << "V." << std::endl;
    return TheveninVoltage;
}

double TheveninEquivalent::CalculatePowerSuppliedToLoad() const {
    double loadCurrent = TheveninVoltage / (TheveninResistance + loadResistance);
    return loadCurrent * loadCurrent * loadResistance;
}

double TheveninEquivalent::FindPowerSuppliedToLoad()
{
    std::cout << "\n***** Power Supplied to Load *****\n";
    std::cout << "\nTo find the power supplied to the load, we calculate the current through it, square it, and multiply by the load resistance:\n";
    std::cout << "Note: This comes from Ohm’s Law (V = I * R) and the power formula (P = V * I).\n";
    std::cout << "Substituting V gives: P = I^2 * R.\n\n";
    std::cout << "What is the value of the load resistor?\n";
    std::cin >> loadResistance;
    std::cout << "\nUsing the Voltage Division Rule...\n";

    double power = CalculatePowerSuppliedToLoad();

    std::cout << "Power supplied to load is: " << power << "W." << std::endl;

    return power;
}

void TheveninEquivalent::suggestions()
{
    std::cout << "\n\n*** Improvements and Suggestions ***\n\n";
    std::cout << "To check if this circuit can be optimized, compare the actual power supplied to the load with the *maximum possible power*.\n";
    std::cout << "According to the Maximum Power Transfer Theorem, power is maximized when the load resistance equals the Thevenin resistance.\n";
    double maxPowerToLoad = (TheveninVoltage * TheveninVoltage) / (4 * TheveninResistance);
    double actualPowerToLoad = CalculatePowerSuppliedToLoad();

    if ((maxPowerToLoad - actualPowerToLoad) < 1e-2)
    {
        std::cout << "Your circuit is supplying near maximum power: " << maxPowerToLoad << " W to your load; no further improvements are needed!\n";
    }
    else
    {
        std::cout << "Your circuit is supplying " << actualPowerToLoad << " W which is not the maximum possible power.\n";
        std::cout << "Consider adjusting the load resistance to match " << TheveninResistance << " Ohms for maximum power absorption.";
    }
}

void TheveninEquivalent::ShowEquivalentCircuit()
{
    std::ostringstream diagram;

    diagram << "\n\n********   Thevenin Equivalent Circuit Illustration   ********\n\n";
    diagram << "           +-----------[" << TheveninResistance << "  Ohms]-----------+ A\n";
    diagram << "           |                                 |\n";
    diagram << "         [+]                                ";

    if (loadResistance > 0)
    {
        diagram << "[" << loadResistance << "  Ohms]";
    }
    else
    {
        diagram << "(No Load)";
    }

    diagram << "\n";
    diagram << "        ("<< TheveninVoltage << " V)         |\n";
    diagram << "         [-]                                 |\n";
    diagram << "           |                                 |\n";
    diagram << "           +---------------------------------+ B\n";

    std::cout << diagram.str();
}

void TheveninEquivalent::writeToFile()
{
    circuitCounter++;
    std::ofstream circuits("\\result_files\\circuits.txt", std::ios::app);
    
    if (!circuits.is_open()) {
        std::cerr << "Error opening file for writing! Please try again." << std::endl;
    }
    if (instanceCount == 1) {
        circuits << "Thevenin Circuits Log\n\n\n";
    }
    circuits << "\n\nAssignment #" << assignmentNumber << "\n\n";
    circuits << "********Circuit number " << circuitCounter << "********\n\n";
    circuits << "Thevenin Voltage: " << TheveninVoltage << " V.\n";
    circuits << "Thevenin Resistance: " << TheveninResistance << "  Ohms.\n";
    circuits << "Load Resistance: " << loadResistance << "  Ohms.\n";
    circuits << "Power Supplied to Load: " << CalculatePowerSuppliedToLoad() <<" W.\n";
    circuits << "Maximum Possible Power to Load: " << (TheveninVoltage * TheveninVoltage) / (4 * TheveninResistance) << " W.\n";
    circuits << "Load's Power Absorption Rating: " << (CalculatePowerSuppliedToLoad() / ((TheveninVoltage * TheveninVoltage) / (4 * TheveninResistance) )) * 100 << ".\n\n";
    circuits << "********************\n\n\n";
    std::cout << "Saved to file!" << std::endl;
}