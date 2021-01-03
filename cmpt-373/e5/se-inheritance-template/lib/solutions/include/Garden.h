#pragma once

#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>

// NOTE: In order to compile, you must have the basic interface for Flower
// available within task03.h!
#include "task03.h"


class Garden {
public:

  static constexpr size_t MAX_NEIGHBOR_COUNT = 8;

  void
  plant(std::unique_ptr<Flower> flower) noexcept {
    auto flowerLocationIsFilled = [this] (auto& toCheck) {
      return flowers.end() != std::find_if(flowers.begin(), flowers.end(),
        [&toCheck] (auto& planted) { return planted->getLocation() == toCheck->getLocation(); });
    };
    assert(!flowerLocationIsFilled(flower) && "Flower added to occupied space.");
    flowers.push_back(std::move(flower));
  }

  [[nodiscard]] std::vector<const Flower*>
  getNeighborsOf(const ex5::task3::Location target) const noexcept {
    // Note: We are assuming that overflow will never actually happen.
    // Handling overflow in practice would involve additional boundary condition
    // checking.
    std::vector<const Flower*> neighbors;
    neighbors.reserve(8);
    // Efficient transform_if would be done via ranges and views in C++20.
    for (auto& flower : flowers) {
      auto location = flower->getLocation();
      if (abs(location.getRow() - target.getRow()) <= 1
          && abs(location.getColumn() - target.getColumn()) <= 1) {
        neighbors.push_back(flower.get());
      }
    }
    return neighbors;
  }

private:
  std::vector<std::unique_ptr<Flower>> flowers;
};

