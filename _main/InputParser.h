#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include "Resistor.h"
#include <string>
#include <stdexcept>
#include <sstream>

Resistor ParseInp(const std::string &input)
{
    size_t parenthesis_start = input.find('(');
    size_t parenthesis_end = input.find(')');

    if (parenthesis_start == std::string::npos || parenthesis_end == std::string::npos || parenthesis_end <= parenthesis_start) {
        throw std::runtime_error("Invalid input! Please include '(...) for series resistance.'");
    }

    std::string seriesRes = input.substr(parenthesis_start + 1, parenthesis_end - parenthesis_start - 1);
    // here we're skipping ')//'
    std::string parallel = input.substr(parenthesis_end + 3);

    std::stringstream ss(seriesRes);
    std::string token;

    // handling series equivalent
    Resistor SeriesReq;

    while (std::getline(ss, token, '+')) {
        double val = std::stod(token);
        SeriesReq = SeriesReq + Resistor(val);
    }

    // handling parallel equivalent
    Resistor ParallelReq(std::stod(parallel));

    Resistor TotalReq = SeriesReq || ParallelReq;

    return TotalReq;
}


#endif