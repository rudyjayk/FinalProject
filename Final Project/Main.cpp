/**FinalProject.sln

This program represents a emergency room simulator.
The user will be prompted with some questions and program will react
accordingly to the users's input

This program shows my understanding of what I learned throughout this class
It utilizes a multiset, vectors, inheritance, polymorphism and more ideas throughout
this program

Last Edited By: Rudyjay Keopuhiwa
07/19/2019
*/

#include "Simulator.h"

Simulator hospital; //Global variable

int main() {

	//Runs simulation
	hospital.create_data();
	hospital.enter_data();
	hospital.run_simulation();
	hospital.menu();

	return 0;
}