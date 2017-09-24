#include "Solver.h"

int main() {
	while(std::cin) {
		auto config = SolverConfig::readConfigFromStream(std::cin);
		Solver solver(config);
		solver.solve();
	}
	return 0;
}

