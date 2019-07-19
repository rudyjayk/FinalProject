#ifndef SERVICESET_H
#define SERVICESET_H

#include <set> 
#include <vector>
#include "Waitingqueue.h"
#include "Random.h"
#include "Patient.h"
#include "Nurse.h"
#include "Doctor.h"


extern Random my_random; //Used so we can access the global instance of the Random class

//This class is used as set and to represent who is being treated
class Serviceset {
private:
	int total_time; //Total wait time for all patients
	int number_served; //Total number served
	Waitingqueue* waitingqueue; //Waiting queue instance
	std::multiset<Patient*> the_set; //Whatever patient gets inserted into this multiset is being treated
	std::vector<Nurse*> caregivers; //This is used to identify what nurse or doctor can be opened or assigned to a patient
public:
	int doctors; //Number of doctors
	int nurses; //Number of nurses

	//Base constructor for the serviceset class
	//Initializes total_time and number_served to 0
	Serviceset() : total_time(0), number_served(0){}

	//Setter method that sets the waiting queue of the serviceset instance
	//This method is called in the simulator.h file
	void set_waiting_queue(Waitingqueue* waitingqueue) {
		this->waitingqueue = waitingqueue;
	}

	//Method that takes the amount of doctors and nurses and creates a instance of each 
	//Also pushes each instance into a vector of Nurse pointers
	//Input: doctors - number of doctors
	//		 nurses - number of nurses
	void create_caregivers(int doctors, int nurses) {
		for (int i = 0; i < doctors; i++) {
			caregivers.push_back(new Doctor(i));
		}
		for (int i = 0; i < nurses; i++) {
			caregivers.push_back(new Nurse(i));
		}
	}

	//Getter method
	//Method that returns the amount of patients served
	int get_num_served() {
		return number_served;
	}

	//Getter method
	//Method that returns the total amount of time waited
	int get_total_time() {
		return total_time;
	}

	//Method that is called within the simulator.h file
	//This method is mainly used throughout the simulation
	//Input: clock - used to represent time, within this method it is used to set service time
	void update(int clock) {
		
		//Checks to see if the_set is empty
		if (!the_set.empty()) {
			
			//Creates another multiset to copy the_set
			//Also creates a iterator which is used to access elements in the_set
			std::multiset<Patient*> copy;
			std::multiset<Patient*>::iterator it;
			copy = the_set;
			
			//For loop to check all patients in multiset is completly treated
			for (int i = 0; i < the_set.size(); i++) {
				
				it = copy.begin();
				Patient* patient = *it;		
				
					//If the patient is treated it will erase them from the_set
					if ((clock - patient->start_service_time) > patient->service_time) {
						
						patient->assignedCare->changeOpen(true); //Also changes the nurse / doctor instance open to true

						the_set.erase(the_set.find(patient));
						
						int index;
						index = clock - patient->arrival_time;
						total_time += index; //calculates total time being treated
						number_served++;
						
						
						//Deletes patient because of dynamic memory
						delete patient;
						
					}
					//erase the top of the copy set and loops
					copy.erase(it);
			}
			
		}
		//Checks to see if there is enough nurses and doctors to treat another patient at the same time 
		if (the_set.size() < caregivers.size()) {
			
			//Checks to see if the waiting queue is not empty
			if (!waitingqueue->the_queue.empty()) {

				//Sets a patient pointer to the top of waiting queue
				Patient* patient = waitingqueue->the_queue.top();

				//Looks for a nurse or doctor to go and treat the patient
				for (int i = 0; i < caregivers.size(); i++) {
					if (caregivers[i]->getOpen() == true) { //changes the boolean
						caregivers[i]->changeOpen(false);
						patient->assignedCare = caregivers[i];
						patient->service_time = patient->assignedCare->set_service_time(patient->priority_num);
						if (patient->service_time < 0) { //Checks to see if nurse can treat that patient based on severity of illness
							caregivers[i]->changeOpen(true); //changes boolean back
							continue;
						}
						break;
					}
				}
				
				waitingqueue->the_queue.pop(); //Erases element of queue

				patient->start_service_time = clock; //Sets the start service time to clock
				

				the_set.insert(patient); //And patient is being inserted into set to be treated
			}
			
		}
	}
};
#endif