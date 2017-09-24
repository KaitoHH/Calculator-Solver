#include "Solver.h"

int main() {
	auto config = SolverConfig::readConfigFromStream(std::cin);
	Solver solver(config);
	solver.solve();
	return 0;
}

