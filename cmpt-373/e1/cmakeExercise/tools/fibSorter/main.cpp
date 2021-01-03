#include <iostream>
#include <vector>

#include "SortIntegers.h"

int
main() {
  std::vector integers = {1, 13, 89, 2, 55, 21, 8, 5, 3, 1, 34};
  sortIntegers(integers);
  for (auto integer : integers) {
    std::cout << integer << "\n";
  }
  return 0;
}