// ID cbdaaf363f8f199871c6a35420714712

#include "task05.h"

Task05::Task05(ex0::HotPotato &pot) 
	: potato{pot} {}

void Task05::butterExcessively() {
	for(int i=0; i<5; i++) {
		potato.addButter();
	}
}
