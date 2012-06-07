#include "definitions.hpp"
#include <iostream>
#include <string>
#include <cstdlib>

void error(std::string &message)
{
    std::cerr << message << std::endl;
    exit(EXIT_FAILURE);
}
