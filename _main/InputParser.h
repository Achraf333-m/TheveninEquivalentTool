#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include "Resistor.h"
#include <string>
#include <stdexcept>
#include <sstream>

Resistor ParseSeries(const std::string& expression) {
  std::stringstream ss(expression);
  std::string token;
  Resistor result;

  while (std::getline(ss, token, '+')) {
    if (!token.empty()) {
        result = result + Resistor(std::stod(token));
    }
  }

  return result;
}

Resistor handleSide(const std::string& substring) {
    Resistor res;

    if (substring.find('(') != std::string::npos && substring.find(')') != std::string::npos) {
        size_t start = substring.find('(');
        size_t end = substring.find(')');

        std::string inside = substring.substr(start + 1, end - start - 1);
        res = ParseSeries(inside);
    } else {
        res = Resistor(std::stod(substring));
    }

    return res;
}

Resistor ParseInp(const std::string &input)
{
    size_t parallelSign = input.find("//");

    if (parallelSign == std::string::npos) {
        throw std::runtime_error("Invalid input! Please include '//' for parallel resistance.");
    }

    std::string left = input.substr(0, parallelSign);
    std::string right = input.substr(parallelSign + 2);
    
    Resistor leftRes, rightRes;
    
    // Handling left side
    leftRes = handleSide(left);
    // handling right side
    rightRes = handleSide(right);

    return leftRes || rightRes;
}


#endif