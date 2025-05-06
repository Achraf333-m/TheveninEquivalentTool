   std::cout << "\n*****Thevenin Resistance*****" << std::endl;
    std::cout << "\nIn your circuit:\n How many resistors are in series? \n";
    std::cin >> SeriesResistorCount;
    std::cout << "How many are in parallel?\n";
    std::cin >> ParallelResistorCount;

    double userInput;
    double parallelSum = 0;
    double SeriesSum = 0;

    // find the equivalent resistance for resistors in series
    for (int i = 0; i < SeriesResistorCount; i++)
    {
        std::cout << "\nEnter the value of R-series-" << i + 1 << ": ";
        std::cin >> userInput;

        if (std::cin.fail())
        {
            std::cout << "Invalid value entered. Please enter a valid number.\n";
            i--;
        }

        std::cout << std::endl;
        SeriesSum += userInput;
    }

    // find the equivalent resistance for resistors in parallel
    for (int i = 0; i < ParallelResistorCount; i++)
    {
        std::cout << "\nEnter the value of R-parallel-" << i + 1 << ": ";
        std::cin >> userInput;

        if (std::cin.fail())
        {
            std::cout << "Invalid value entered. Please enter a valid number.\n";
            i--;
        }

        parallelSum += (1 / userInput);
    }

    TheveninResistance = SeriesSum + (1 / parallelSum);

    std::cout << "The Thevenin Resistance: " << TheveninResistance << " Ohms." << std::endl;
    return TheveninResistance;