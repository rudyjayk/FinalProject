#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <ios>
#include <fstream>
#include "Waitingqueue.h"
#include "Serviceset.h"
#include "Random.h"

Random my_random;  // Global variable 

class Simulator
{
private:
	int total_time1;  // Total time to run simulation
	int clock;       // current time
	std::vector<std::string> residents; //vector of residents that are taken from a .txt file

	// waiting queue --> service queue 
	Waitingqueue * waiting_queue;
	Serviceset * service_set;

	//This method is copied from the Airport Simulator for Homework 7
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

	//Base constructor for Simulator class
	//Dynamically initializes the waiting_queue and service_set pointers
	Simulator() {
		waiting_queue = new Waitingqueue();
		service_set = new Serviceset();

	}

	//Method that takes 2000 names from a file and stores it in a vector
	void create_data() {
		std::fstream file; //Creates a file
		std::string str;
		file.open("C:\\Users\\rudyj\\Desktop\\Final Project\\Final Project\\Final Project\\residentsOf273ville.txt"); //Opens file

		while (!file.eof()) {//Goes through file and takes strings and pushes them to a vector
			file >> str;
			residents.push_back(str);
		}
		

	}

	//Method that prompts user to enter data that is used to determine simulation
	void enter_data()
	{

		std::cout << "Welcome CS273 to the Simple Emergency Room Simulator\n\n";
		std::cout << "We are CS273ville, a small but hardworking emergency room!\n";
		std::cout << "Please follow the instructions and enter a number when prompted!\n";


		int rate = read_int("Please enter the patient arrival rate (patient/hour): ", 1, 59); //prompts user to enter arrival rate
		double arrival_rate = rate / 60.0;

		int num_doctors = read_int("Please enter the number of Doctors: ", 0, INT_MAX); //prompts user to enter num of doctors and num of nurses
		int num_nurses = read_int("Please enter the number of Nurses: ", 0, INT_MAX); 
		

		total_time1 = read_int("Please enter the simulation time (hours): ", 1, INT_MAX); //prompts user to enter simulation time in hours
		total_time1 *= 60;

		// set the arrival_rate and residents for waiting_queue
		waiting_queue->set_arrival_rate(arrival_rate);
		waiting_queue->set_residents(residents);

		//Sets waiting queue for service_set
		service_set->set_waiting_queue(waiting_queue);

		//Creates caregivers for service_set
		service_set->create_caregivers(num_doctors, num_nurses);

	}

	//Method that increments clock and calls each update function in waiting queue and service set
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

	//Method that prompts user to choose what they want to do from a menu
	void menu()
	{
		int num = 1;

		while (num > 0) {
			num = read_int("Choose a type of information to be displayed \n1) Number of patients visited \n2) Number of patients treated \n3) Total treat time \n4) Average treat time \n5) Choose a patient \n**Enter a negative to exit** \n", INT_MIN, 6); //prompts user to enter choice

			//Uses a switch to react to the user input
			switch (num) {
				case (1): {
					std::cout << "Number of patients visited: " << waiting_queue->get_visited() << std::endl << std::endl; //Total amount of people visited
					break;

				}
				case (2): {
					std::cout << "Number of patients treated: " << service_set->get_num_served() << std::endl << std::endl; //Number of patients actually treated
					break;

				}
				case (3): {
					std::cout << "Total treat time for all patients in service queue: " << service_set->get_total_time() << std::endl << std::endl; //Total time it takes for all patients to be treated
					break;

				}
				case (4): {
					std::cout << "Average treat time for all patients in  service queue: " << service_set->get_total_time() / service_set->get_num_served() << std::endl << std::endl; //Average time it takes for patients to be treated
					break;
				}
				case (5): {

					//Prints out all names that have visited the emergency room to user
					for (int i = 0; i < waiting_queue->resident_record.size(); i++) {
						std::cout << i + 1 << ") " << waiting_queue->resident_record[i]->name << std::endl;
					}
					int index = read_int("Select a patient: ", 1, waiting_queue->resident_record.size()) - 1; //prompts user to select patient

					//Prints out patient information
					std::cout << "Patient: " << waiting_queue->resident_record[index]->name << std::endl;
					std::cout << "Number of times visited: " << waiting_queue->resident_record[index]->num_visits << std::endl;
					std::cout << "Severity of each illness: ";

					//For loop used to print out all priority numbers
					for (int i = 0; i < waiting_queue->resident_record[index]->priorityNumbers.size(); i++) {
						std::cout << waiting_queue->resident_record[index]->priorityNumbers[i] << " ";
					}

					std::cout << std::endl << std::endl;
					break;

				}

			}
		}
	
		std::cout << std::endl;
		
	}
	
};
#endif