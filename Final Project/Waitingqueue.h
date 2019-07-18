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
	int total_wait;
	int num_served;
	std::priority_queue<Patient *>the_queue;
public:
	Waitingqueue() : total_wait(0), num_served(0), arrival_rate(0) {}

	
	void set_arrival_rate(double num) {
		arrival_rate = num;
	}


	void update(int clock) {

		int num = my_random.next_int(20);
		

		if (my_random.next_double() < arrival_rate) {
			the_queue.push(new Patient(num,clock));
			
		}
		
	}

	friend class Serviceset;
};
#endif