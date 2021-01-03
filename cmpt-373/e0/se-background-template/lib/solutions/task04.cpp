// ID cbdaaf363f8f199871c6a35420714712

#include "task04.h"

ex0::ButterPats task04(ex0::HotPotato potato) {
	ex0::HotPotato newPotato = potato;
	newPotato.addButter();
	return newPotato.getButterCount();
}