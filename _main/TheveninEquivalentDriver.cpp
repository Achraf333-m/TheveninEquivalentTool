#include "TheveninEquivalent.h"
#include <iostream>
#include <string>

void welcome(const TheveninEquivalent& TE);


int main()
{
    TheveninEquivalent TE;
    welcome(TE);
    TE.setProblemNumber();
    TE.FindTheveninResistance();
    TE.FindTheveninVoltage();
    TE.FindPowerSuppliedToLoad();
    TE.ShowEquivalentCircuit();
    TE.suggestions();
    TE.writeToFile();

    return 0;
}

void welcome(const TheveninEquivalent& TE) {
    std::cout << "THEVENIN EQUIVALENCE: PROBLEM #" << TE.getProblemNumber() << "inro\n\n";
    std::cout << "\n\n"
              << "********** WELCOME TO YOUR FAVORITE TOOL: THE THEVENIN EQUIVALENT CIRCUIT FINDER **********"
              << "\n\n"
              << "Let's start by understanding what a 'Thevenin Equivalent' circuit means.\n\n"
              << "Any electrical circuit, no matter how complex, can be simplified into a basic circuit with just one voltage source and one resistor. "
              << "This is known as the *Thevenin Equivalent*.\n\n"
              << "This simplification is useful when we want to analyze how a load resistor behaves in the circuit using Ohm's Law (V = I * R).\n\n"
              << "In practice, what we electrical engineering students do is:\n"
              << "1. Remove the load resistor from the circuit.\n"
              << "2. Measure the voltage across the open terminals with a voltmeter — this gives us the *Thevenin Voltage* (Vth).\n"
              << "3. Then, using the same multimeter, measure the resistance seen from those terminals — that gives us the *Thevenin Resistance* (Rth).\n\n"
              << "Now, instead of dealing with a whole circuit, we can analyze a simple model: just Vth in series with Rth and the load resistor. How cool is that?!\n\n"
              << "In theory, it's a bit different:\n"
              << "We consider the circuit open between nodes A and B (where the load connects). We then:\n"
              << "- Find the equivalent resistance *looking into* those terminals — this is our Thevenin resistance.\n"
              << "- Use KVL or KCL to find the voltage at the node just before the terminals, assuming there's no load and there's no branch continuing past the terminals — this gives us Vth.\n\n"
              << "Ready to simplify some circuits? Let's go!"
              << "\n\n"
              << "**********THEVENIN EQUIVALENT CIRCUIT FINDER**********\n"
              << std::endl;
}
