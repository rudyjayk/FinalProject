#ifndef DOCTOR_H
#define DOCTOR_H


#include "Nurse.h"

class Doctor : public Nurse {
public:
	
	Doctor(int num) : Nurse(num) {}


	void set_service_time(Patient* patient) {
	
		patient->service_time = my_random.next_int(20);


	}
};
#endif