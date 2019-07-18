#ifndef WAITINGQUEUE_H_
#define WAITINGQUEUE_H_

#include <queue>
#include <iostream>
#include "Patient.h"
#include "Random.h"

extern Random my_random;

class Waitingqueue {

private:
	double arrival_rate;
	int num_visitors;
	std::vector<string> residents;
	std::priority_queue<Patient *>the_queue;
	
public:
	std::vector<Patient*> resident_record;

	Waitingqueue() : num_visitors(0), arrival_rate(0) {}

	
	void set_arrival_rate(double num) {
		arrival_rate = num;
	}

	int get_visited() {

		return num_visitors;
	}

	void set_residents(vector<string> myVec) {

		residents = myVec;
	}

	void update(int clock) {

		int num = my_random.next_int(20);
		string name = residents[my_random.next_int(residents.size() - 1)];
		int index = 0;

		if (my_random.next_double() < arrival_rate) {
			the_queue.push(new Patient(name,num,clock));

			for (int i = 0; i < resident_record.size(); i++) {
				if (name == resident_record[i]->get_name()) {
					resident_record[i]->num_visits++;
					resident_record[i]->priorityNumbers.push_back(num);
					continue;
				}
				else
					index++;
			}

			if (index == resident_record.size()) {
				resident_record.push_back(new Patient(name, num, clock));
				resident_record[index]->priorityNumbers.push_back(num);
			}
			
			num_visitors++;
		}
		
	}

	friend class Serviceset;
};
#endif