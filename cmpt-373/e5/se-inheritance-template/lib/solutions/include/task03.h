#pragma once

#include "Support.h"

#include <memory>

// Forward declaring these types makes it possible to use pointers
// and references to them even when the types themselves are not fully defined.
// Intuitively, we don't need to know all of the fields of a class if we only
// need to hold pointers to it. If we were to pass a `Garden` around by value
// instead, we would need the full type definition in order for the code to
// compile because the compiler would need to know the exact sizes and types
// of the fields within Garden.

class Flower;
class Garden;


std::unique_ptr<Flower>
createSunflower(ex5::task3::Location location, ex5::task3::Color);


std::unique_ptr<Flower>
createMycoheterotroph(ex5::task3::Location location, ex5::task3::Color);


std::unique_ptr<Flower>
createRafflesia(ex5::task3::Location location, ex5::task3::Color);


// You should be able to add a complete type declaration for `Flower` and any
// other types you wish to create here. The exact implementations of methods
// can reside in task03.cpp.


