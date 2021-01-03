// ID cbdaaf363f8f199871c6a35420714712

#include <numeric>
#include <string_view>
#include <vector>

#include "task07.h"

std::string task07(std::string keyString, std::unordered_map<char, const std::string> map) 
{
	std::string result = "";
	for (int i=0; i<(int)keyString.length(); i++) {
		if (map.find(keyString[i]) == map.end()) {
			result += keyString[i];
			continue;
		}
		result += map[keyString[i]];
	}
	return result;
}