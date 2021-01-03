// ID cbdaaf363f8f199871c6a35420714712

#pragma once

#include <algorithm>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>

namespace ex0 {

////////////////////////////////////////////////////////////////////////////////
// Part 1: Passing a Hot Potato
////////////////////////////////////////////////////////////////////////////////

struct ButterPats {
  explicit ButterPats(int initialCount)
    : count{initialCount}
      { }

  int count;
};


class HotPotato {
public:
  HotPotato(ButterPats) noexcept;

  // These special members get called when moving, copying, or destroying
  // an instance of a class.
  ~HotPotato() noexcept;
  HotPotato(const HotPotato& other) noexcept;
  HotPotato(HotPotato&& other) noexcept;
  HotPotato& operator=(const HotPotato& other) noexcept;
  HotPotato& operator=(HotPotato&& other) noexcept;
  
  ButterPats getButterCount() const noexcept { return butterCount; }
  void addButter() noexcept { ++butterCount.count; }

private:
  ButterPats butterCount;
};



}



