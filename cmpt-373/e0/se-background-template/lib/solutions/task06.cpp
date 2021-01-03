// ID cbdaaf363f8f199871c6a35420714712

#include "task06.h"

#include <numeric>

uint32_t task06(std::string val) {
	uint32_t sum = 0;
	for (int i=0; i<(int)val.length(); i++) {
		sum += val[i];
	}
	return sum;
}