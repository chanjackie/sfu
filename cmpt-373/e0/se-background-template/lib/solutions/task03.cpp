// ID cbdaaf363f8f199871c6a35420714712

#include "task03.h"

ex0::ButterPats task03(ex0::HotPotato potato) {
	ex0::ButterPats pats = potato.getButterCount();
	pats.count++;
	return pats;
}