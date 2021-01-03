
#include <numeric>
#include <unordered_map>

#include "Support.h"

using Spelling = ex6::task2::Spelling;

static std::unordered_map<char, size_t>
getFrequencies(const std::string& str) noexcept {
  std::unordered_map<char, size_t> frequencies;
  for (auto c : str) {
    frequencies[c] += 1;
  }
  return frequencies;
}


namespace ex6::task2 {

size_t
similarity(const Spelling& first, const Spelling& second) noexcept {
  std::unordered_map<char, size_t> frequencies1 = getFrequencies(first.word);
  std::unordered_map<char, size_t> frequencies2 = getFrequencies(second.word);
  size_t difference = 0;
  // NOTE: This is not the most efficient way to do this.
  // unordered_map is inefficient anyway, so we are asserting that we do not
  // really care about the performance of this code.
  for (const auto& [c, count] : frequencies1) {
    difference += (count - frequencies2[c]);
    frequencies2.erase(c);
  }
  return std::accumulate(frequencies2.begin(), frequencies2.end(), difference,
    [] (size_t sofar, auto kvPair) { return sofar + kvPair.second; });
}

}
