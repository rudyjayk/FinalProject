#include "Simulator.h"

Simulator hospital;

int main() {

	hospital.enter_data();
	hospital.run_simulation();
	hospital.show_stats();

	return 0;
}