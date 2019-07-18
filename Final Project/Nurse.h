#ifndef NURSE_H
#define NURSE_H

#include "Random.h"

extern Random my_random;

class Nurse {
private:
	int nurseNumber;
	bool isOpen;
public:

	Nurse(int num) : nurseNumber(num), isOpen(true) {}
	
	

	bool getOpen() {
		return isOpen;
	}

	void changeOpen (bool change) {
		this->isOpen = change;
	}
	
	int set_service_time(int priority_num) {
		
		if (priority_num <= 10)
			return my_random.next_int(10);
		else
			return my_random.next_int(20);


	}
	
};
#endif