#include <iostream>
#include "TheveninEquivalent.h"
#include <sstream>
#include <fstream>
#include <filesystem>
#include <string>
#include <limits>
#include <iomanip>
#include "InputParser.h"

namespace fs = std::filesystem;

// constructors
TheveninEquivalent::TheveninEquivalent() : loadResistance(0.0), branchCurrent(0.0), TheveninVoltage(0.0), TheveninResistance(0.0), ProblemNumber(0) {}
TheveninEquivalent::TheveninEquivalent(double lr, double bc, double tv, double tr, int cc, int an) : loadResistance(lr), branchCurrent(bc), TheveninVoltage(tv), TheveninResistance(tr), ProblemNumber(an) {}
TheveninEquivalent::TheveninEquivalent(const TheveninEquivalent &other) : loadResistance(other.loadResistance), branchCurrent(other.branchCurrent), TheveninVoltage(other.TheveninVoltage), TheveninResistance(other.TheveninResistance), ProblemNumber(other.ProblemNumber) {}

// setters
void TheveninEquivalent::setProblemNumber()
{
    std::cout << "Enter problem number: ";
    std::cin >> ProblemNumber;
}

// getters
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
int TheveninEquivalent::getProblemNumber() const
{
    return ProblemNumber;
}

// main methods
double TheveninEquivalent::FindTheveninResistance()
{
    std::cout << "\n\n*************** Thevenin Resistance ***************\n\n";

    std::cout << "To begin, turn off all independent sources:\n";
    std::cout << " - Short-circuit all voltage sources (replace them with a wire).\n";
    std::cout << " - Open-circuit all current sources (remove them from the circuit).\n\n";

    std::cout << "Then enter the resistor expression for the simplified circuit (no spaces).\n\n";

    std::cout << "Format:\n";
    std::cout << " * Use parentheses for resisors in series.\n";
    std::cout << " * Use '//' to indicate resistors in parallel.\n\n";

    std::cout << "Examples:\n";
    std::cout << " * For resistors 1, 2, and 3 in series, and in parallel with resistor 4:\n";
    std::cout << "   (R1+R2+R3)//R4\n";
    std::cout << " * For resistors 1, 2, and 3 in series, and in parallel with resistors 4 and 5 in series:\n";
    std::cout << "   (R1+R2+R3)//(R4+R5)\n\n";

    std::cout << "Where R1, R2, etc. are numeric resistor values (e.g., 10, 4.7, 3.3).\n";
    std::cout << "Note: You may need to simplify or group resistors to match one of the above forms.\n\n";

    std::cout << "Enter resistor expression: ";

    std::string userInp;
    //  flushing out the buffer -- error fix
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, userInp);
    TheveninResistance = ParseInp(userInp).getVal();
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "The Thevenin Resistance for the circuit is: " << TheveninResistance << " Ohms" << std::endl;
    return TheveninResistance;
}

double TheveninEquivalent::FindTheveninVoltage()
{
    double branchResistance;
    std::cout << "\n*****Thevenin Voltage*****" << std::endl;
    std::cout << "\nImportant: Use KCL to find the current through the branch of the node just before the terminals.\n"
              << "Remember: KCL states that the sum of all currents going into a node is zero; meaning I1 + I2 + ... + In = 0 \n\n";

    std::cout << "Enter the value of the branch current (A): ";
    std::cin >> branchCurrent;
    std::cout << "\nEnter the value of the resistor in the same branch (Ohms): ";
    std::cin >> branchResistance;
    std::cout << "\n\n....V = I x R....Finding Thevenin voltage....\n\n\n";

    // Ohm's Law
    TheveninVoltage = branchCurrent * branchResistance;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "The Thevenin Voltage is: " << TheveninVoltage << " V." << std::endl;
    return TheveninVoltage;
}

double TheveninEquivalent::CalculatePowerSuppliedToLoad() const
{
    double loadCurrent = TheveninVoltage / (TheveninResistance + loadResistance);
    return loadCurrent * loadCurrent * loadResistance;
}

double TheveninEquivalent::FindPowerSuppliedToLoad()
{
    std::cout << "\n***** Power Supplied to Load *****\n";
    std::cout << "\nTo find the power supplied to the load, we calculate the current through it, square it, and multiply it by the load resistance:\n";
    std::cout << "Note: This comes from Ohm's Law (V = I x R) and the power formula (P = V x I).\n";
    std::cout << "Substituting V in gives: P = I^2 x R.\n\n";
    std::cout << "What is the value of the load resistor: ";
    std::cin >> loadResistance;
    std::cout << "\nUsing the Voltage Division Rule...\n";

    double power = CalculatePowerSuppliedToLoad();

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Power supplied to load is: " << power << " W." << std::endl;

    return power;
}

void TheveninEquivalent::suggestions()
{
    std::cout << "\n\n*** Improvements and Suggestions ***\n\n";
    std::cout << "To check if this circuit can be optimized, we compare the actual power supplied to the load with the *maximum possible power*.\n";
    std::cout << "According to the Maximum Power Transfer Theorem, power is maximized when the load resistance equals the Thevenin resistance.\n\n";
    double maxPowerToLoad = (TheveninVoltage * TheveninVoltage) / (4 * TheveninResistance);
    double actualPowerToLoad = CalculatePowerSuppliedToLoad();

    // avoiding floating point error here
    if ((maxPowerToLoad - actualPowerToLoad) < 1e-2)
    {
        std::cout << "Your circuit is supplying near maximum power: " << maxPowerToLoad << " W to your load; no further improvements are needed!\n";
    }
    else
    {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Your circuit is supplying " << actualPowerToLoad << " W which is not the maximum possible power.\n";
        std::cout << "Consider adjusting the load resistance to " << TheveninResistance << " Ohms for maximum power absorption.";
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
        diagram << "[" << loadResistance << " Ohms]";
    }
    else
    {
        diagram << "(No Load)";
    }

    diagram << "\n";
    diagram << "        (" << TheveninVoltage << " V)                              |\n";
    diagram << "         [-]                                 |\n";
    diagram << "           |                                 |\n";
    diagram << "           +---------------------------------+ B\n";

    std::cout << diagram.str();
}


// writing into file
// finding whether user is in the repo or running the .exe file directly from downloads.

void TheveninEquivalent::writeToPath(std::string& path) {
    std::ofstream circuits(path, std::ios::app);
    if (!circuits.is_open())
        {
            std::cerr << "Error opening file for writing! Please try again." << std::endl;
        }
    double rating = (CalculatePowerSuppliedToLoad() / ((TheveninVoltage * TheveninVoltage) / (4 * TheveninResistance))) * 100;
        std::cout << std::fixed << std::setprecision(2);
        circuits << "\n\nProblem #" << ProblemNumber << "\n\n";
        circuits << "Thevenin Voltage: " << TheveninVoltage << " V.\n";
        circuits << "Thevenin Resistance: " << TheveninResistance << " Ohms.\n";
        circuits << "Load Resistance: " << loadResistance << " Ohms.\n";
        circuits << "Power Supplied to Load: " << CalculatePowerSuppliedToLoad() << " W.\n";
        circuits << "Maximum Possible Power to Load: " << (TheveninVoltage * TheveninVoltage) / (4 * TheveninResistance) << " W.\n";
        circuits << "Load's Power Absorption Rating: " << rating << ".\n\n";
        circuits << "Comments: " << (rating < 98 ? "Load resistance is sub-optimal, adjust it to match the Thevenin Resistance." : "Load resistance is almost optimal, no further improvements are needed.") << std::endl;
        circuits << "********************\n\n\n";
        std::cout << "\n\n[DONE!] Saved to file: " << path << std::endl;
}

std::string getDesktopPath() {
    #ifdef _WIN32
    char* onedrive = std::getenv("ONEDRIVE");
        char* userProfile = std::getenv("USERPROFILE");
        if (onedrive) {
            return std::string(onedrive) + "\\Desktop\\TheveninEquivalentLogs.txt";
        }
        else if (userProfile) {
            return std::string(userProfile) + "\\Desktop\\TheveninEquivalentLogs.txt";
        } else {
            throw std::runtime_error("Error writing into file. Try running in the repo folder (clone)");
        }
    #else 
        char* home = std::getenv("HOME");

        if (home) {
            return std::string(home) + "/Desktop/TheveninEquivalentLogs.txt";
        } else {
            throw std::runtime_error("Error writing into file. Try running in the repo folder (clone)");
        }

    #endif 
}


void TheveninEquivalent::writeToFile()
{
    // here I am making sure I am in repo (assuming a user cloned it)
    if (fs::exists("circuits.txt")) {
        std::string repo_path = "circuits.txt";
        writeToPath(repo_path);
    } else {
        try {
            std::string desktop_path = getDesktopPath();
            writeToPath(desktop_path);
        } catch (const std::runtime_error& e) {
            std::cout << "\n[ERROR] " << e.what();
        }

    }
}