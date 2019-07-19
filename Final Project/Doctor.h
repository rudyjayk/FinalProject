#ifndef DOCTOR_H
#define DOCTOR_H


#include "Nurse.h"

//This class is inherited from the nurse class

class Doctor : public Nurse {
public:
	
	//Base constructor
	//Input: int num = used for as a reference
	//Calls the constructor foe the nurse class
	Doctor(int num) : Nurse(num) {}

	//Method to set a service time for the patient
	//Since a doctor can treat a patient for any priority level then this method will only
	//	generate a random number between 1-20
	void set_service_time(Patient* patient) {
	
		patient->service_time = my_random.next_int(20);


	}
};
#endif