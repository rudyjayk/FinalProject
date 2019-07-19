#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include "Nurse.h"

//This is a struct because it was convenient to have all member methods and variables public to everything
struct Patient {

	//Base constructor for the Patient struct
	//Input: str - a string that represent name of patient
	//		 number - number that is generated randomly that represents priority number
	//		 clock - time of when the patient was created
	//Output: arrival_time = clock
	//		  start_service_time, service_time = -1
	//		  num_visits = 1 
	Patient(std::string str, int number, int clock) :
	arrival_time(clock), start_service_time(-1), service_time(-1), priority_num(number), name(str), num_visits(1)
	{}

	int service_time; //Randomly generated and used to determine how long it takes to treat a patient
	int arrival_time; //Time when the patient arrives
	int start_service_time; //Start time of treatment
	int priority_num; //Severity of illness also randomly generated
	int num_visits; //Holds number of visits for patient instance
	std::vector<int>priorityNumbers; //If patient visits more than once it holds all severity of illness numbers
	std::string name; //Name of patient
	Nurse* assignedCare; //Assigned nurse or doctor of patient

	//Operator overload for the '<' operator
	//Mainly used so that within a priority queue of patients they can be compared coorectly
	//A unit test is used to demonstrate the operator
	bool operator<(const Patient& other) const {
		if (this->priority_num < other.priority_num)
			return true;
		else
			return false;
	}
};
#endif