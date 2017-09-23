#include "Solver.h"

int main() {
	auto config = SolverConfig::readConfigFromFile("config.json");
	Solver solver(config);
	solver.solve();
	return 0;
}

