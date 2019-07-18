#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <ios>
#include "Waitingqueue.h"
#include "Serviceset.h"
#include "Random.h"

Random my_random;  // Global variable 

class Simulator
{
private:
	int total_time1;  // total time to run simulation
	int clock;       // current time
	

	// waiting queue --> service queue 
	Waitingqueue * waiting_queue;
	Serviceset * service_set;

	// Remember me!
	int read_int(const std::string& prompt, int low, int high)
	{
		if (low >= high) // invalid range
			throw std::invalid_argument("invalid range specified");

		std::cin.exceptions(std::ios_base::failbit);
		int num = 0;
		while (true) {
			try {
				while (true) {
					std::cout << prompt;
					std::cin >> num;
					if (num >= low && num <= high) { // within the specified range
						std::cout << std::endl;
						return num;
					}
				}
			}
			catch (std::ios_base::failure) {
				std::cout << "Bad numeric string -- try again\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			}
		}
	}

public:

	Simulator() {
		waiting_queue = new Waitingqueue();
		service_set = new Serviceset();

	}

	void enter_data()
	{

		std::cout << "Welcome CS273 to the Simple Emergency Room Simulator.\n\n";
		std::cout << "We are CS273ville, a small but feisty emrgency room!\n";


		int rate = read_int("Please enter the patient arrival rate (patient/hour): ", 1, 59);
		double arrival_rate = rate / 60.0;

		int num_doctors = read_int("Please enter the number of Doctors: ", 0, INT_MAX);
		int num_nurses = read_int("Please enter the number of Nurses: ", 0, INT_MAX);
		

		total_time1 = read_int("Please enter the simulation time (hours): ", 1, INT_MAX);
		total_time1 *= 60;

		// set the arrival_rate for the landing queue
		waiting_queue->set_arrival_rate(arrival_rate);

		service_set->set_waiting_queue(waiting_queue);

		service_set->create_caregivers(num_doctors, num_nurses);

	}

	void run_simulation()
	{
		
		// run the simulation
		for (clock = 0; clock < total_time1; ++clock)
		{
			// for each time interval ...
			waiting_queue->update(clock);
			service_set->update(clock);
			
		}
		
	}

	void show_stats()
	{
		
		std::cout << "Number of patients served in the service queue: " << service_set->get_num_served() << std::endl;
		std::cout << "Total wait time for all patients in service queue: " << service_set->get_total_time() << std::endl;
		// FIXME: Calculate and display the average wait time for the departure queue
		std::cout << "Average wait time for all patients in  service queue: " << service_set->get_total_time() / service_set->get_num_served() << std::endl;

		std::cout << std::endl;
		
	}
	
};
#endif