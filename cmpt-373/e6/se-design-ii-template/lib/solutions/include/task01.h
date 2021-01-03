#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>

class Structure;

// Make sure to define your printElement function, too.

void printElement(std::ostream& out, const Structure& s);


// Define your `Structure` class here

class Structure {
public:
	Structure() = default;
	virtual void add(auto& object) = 0;
	virtual void print(std::ostream& out) = 0;
protected:
	vector<Structure> objects;
};


class IntStructure : public Structure {
public:
	IntStructure() : Structure() {}
	void add()
};