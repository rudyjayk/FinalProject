#ifndef WAITINGQUEUE_H_
#define WAITINGQUEUE_H_

#include <queue>
#include <iostream>
#include "Patient.h"
#include "Random.h"

extern Random my_random; //Used to access global instance of Random

//This class is used to be a waiting queue for patients that arrive at the emergency room
class Waitingqueue {

private:
	double arrival_rate; //Patient/hour
	int num_visitors; //Total number of visitors
	std::vector<std::string> residents; //Resident names
	std::priority_queue<Patient *>the_queue; //Waitingqueue that holds allm patients that visit
	
public:
	std::vector<Patient*> resident_record; //Stores patient pointers so we can have access after simulation

	//Base constructor for Waitinngqueue class
	//Initializes num_visitors and arrical_rate to 0
	Waitingqueue() : num_visitors(0), arrival_rate(0) {}

	//Setter method for arrival rate
	//Sets arrival_rate to a double which comes from the user input
	void set_arrival_rate(double num) {
		arrival_rate = num;
	}

	//Getter method that returns num_visitors
	int get_visited() {

		return num_visitors;
	}

	//Setter method that is called in simulator.h to set the vector of resident names
	void set_residents(std::vector<std::string> myVec) {

		residents = myVec;
	}

	//Method that is called within the simulator.h file
	//This is another method that is mainly used throughout the simulation
	//Input: clock - used to represent time, within this method it is used to set service time
	void update(int clock) {

		int num = my_random.next_int(20); //Used to set severity illness
		std::string name = residents[my_random.next_int(residents.size() - 1)]; //Used to get a random name for patietn
		int index = 0;

		//Checks if a patient can be added
		if (my_random.next_double() < arrival_rate) {
			the_queue.push(new Patient(name,num,clock));

			//For loop that checks to see if the patient has already visited the hospital
			for (int i = 0; i < resident_record.size(); i++) {
				if (name == resident_record[i]->name) {
					resident_record[i]->num_visits++;
					resident_record[i]->priorityNumbers.push_back(num);
					continue;
				}
				else
					index++;
			}

			//If the patient hasn't already visited then adds patient to resident_record and updated the priority number vector
			if (index == resident_record.size()) {
				resident_record.push_back(new Patient(name, num, clock));
				resident_record[index]->priorityNumbers.push_back(num);
			}
			
			//Increment number of visitors
			num_visitors++;
		}
		
	}

	friend class Serviceset;
};
#endif