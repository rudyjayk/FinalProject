#ifndef SERVICESET_H
#define SERVICESET_H

#include <set>
#include <vector>
#include "Waitingqueue.h"
#include "Random.h"
#include "Patient.h"
#include "Nurse.h"
#include "Doctor.h"


extern Random my_random;

class Serviceset {
private:
	int total_time;
	int number_served;
	Waitingqueue* waitingqueue;
	std::multiset<Patient*> the_set;
	std::vector<Nurse*> caregivers;
public:
	int doctors;
	int nurses;

	Serviceset() : total_time(0), number_served(0){}


	void set_waiting_queue(Waitingqueue* waitingqueue) {
		this->waitingqueue = waitingqueue;
	}


	void create_caregivers(int doctors, int nurses) {
		for (int i = 0; i < doctors; i++) {
			caregivers.push_back(new Doctor(i));
		}
		for (int i = 0; i < nurses; i++) {
			caregivers.push_back(new Nurse(i));
		}
	}

	int get_num_served() {
		return number_served;
	}

	int get_total_time() {
		return total_time;
	}

	void update(int clock) {
		
		if (!the_set.empty()) {
			
			std::multiset<Patient*> copy;
			std::multiset<Patient*>::iterator it;
			copy = the_set;
			

			for (int i = 0; i < the_set.size(); i++) {
				
				it = copy.begin();
				Patient* patient = *it;		
				
					if ((clock - patient->start_service_time) > patient->service_time) {
						
						patient->assignedCare->changeOpen(true);

						the_set.erase(the_set.find(patient));
						
						int index;
						index = clock - patient->arrival_time;
						total_time += index;
						number_served++;
						
						
						delete patient;
						
					}
					copy.erase(it);
			}
			
		}
		if (the_set.size() < caregivers.size()) {
			
			if (!waitingqueue->the_queue.empty()) {


				Patient* patient = waitingqueue->the_queue.top();

				for (int i = 0; i < caregivers.size(); i++) {
					if (caregivers[i]->getOpen() == true) {
						caregivers[i]->changeOpen(false);
						patient->assignedCare = caregivers[i];
						break;
					}
						
				}
				patient->service_time = patient->assignedCare->set_service_time(patient->priority_num);

				waitingqueue->the_queue.pop();

				patient->start_service_time = clock;
				

				the_set.insert(patient);
			}
			
		}
	}
};
#endif