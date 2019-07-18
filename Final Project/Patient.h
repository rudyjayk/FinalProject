#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include "Nurse.h"

using namespace std;

struct Patient {

	Patient(int number, int clock) :
	arrival_time(clock), start_service_time(-1), service_time(-1), priority_num(number)
	{}

	int service_time;
	int arrival_time;
	int start_service_time;
	int priority_num;
	Nurse* assignedCare;

	bool operator<(const Patient& other) const {
		if (this->priority_num < other.priority_num)
			return true;
		else
			return false;
	}
};
#endif