#include "Solver.h"
#include <iostream>
#include <fstream>
#include <memory>
using namespace rapidjson;
int main()
{
    config_ptr config (SolverConfig::readConfigFromFile("config.json"));
    Solver solver(config);
    return 0;
}

