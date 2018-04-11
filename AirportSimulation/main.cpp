#include "Simulator.h"

Simulator airport;

int main() {

	airport.enter_data();
	airport.run_simulation();
	airport.show_stats();

	system("PAUSE");

	return 0;
}