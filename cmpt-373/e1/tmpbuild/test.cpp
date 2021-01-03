#include <iostream>
#include <vector>
#include "SortIntegers.h"
int main() { 
  std::vector integers = {6, 3, 1, 15, 11, 16};
  sortIntegers(integers);
  for (auto integer : integers) { std::cout << integer << "\n"; }
  return 0;
}
