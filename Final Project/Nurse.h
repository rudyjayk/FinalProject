#ifndef NURSE_H
#define NURSE_H

#include "Random.h"

extern Random my_random; //So we can use the public variable used in simulator.h

//This class is the base class of the inheritance between a nurse and doctor
class Nurse {
private:
	int nurseNumber; //for reference
	bool isOpen; //Boolean to show if nurse/ doctor is open
public:

	//Base constructor
	//Input: int num = used for reference=
	// Sets isOpen to true because a nurse/ docotr is always open in the beginning
	Nurse(int num) : nurseNumber(num), isOpen(true) {}
	
	
	//Getter method that returns isOpen
	//Returns a bool
	bool getOpen() {
		return isOpen;
	}

	//A setter method
	//Input: bool change = will set isOpen to change
	//This method changes what isOpen is based on what change is
	void changeOpen (bool change) {
		this->isOpen = change;
	}
	
	//A method to set the service time of the patient
	//Input: int priority_num = used with a conditional to see if the nurse can treat the patient
	int set_service_time(int priority_num) {
		
		if (priority_num <= 10)
			return my_random.next_int(10); //Creates a random number between 0-10
		else
			return -1; //returns a negative if priority number is greater than 10
					   //The negative will help in Serviceset.h	


	}
	
};
#endif