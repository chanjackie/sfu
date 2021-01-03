
#pragma once

#include <algorithm>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>

namespace ex4 {


////////////////////////////////////////////////////////////////////////////////
// Part 2: Info Blobs
////////////////////////////////////////////////////////////////////////////////

enum class Emotion : char {
  HAPPY, SAD, PERPLEXED, STRESSED
};

enum class Action : char {
  RUN, LAUGH, WORRY, WEEP, PLAN, PLOT, READ
};


class InfoBlob {
public:
  InfoBlob(int entropy, float spin, Emotion emotion) noexcept
    : entropy{entropy},
      spin{spin},
      emotion{emotion}
      { }

  int getEntropy()     const noexcept { return entropy; }
  float getSpin()      const noexcept { return spin; }
  Emotion getEmotion() const noexcept { return emotion; }

  // Note: In C++20, comparison operations can be automatically generated.
  // The spaceship operator, <=>, can be filled in for you.
  // We, however, are using C++17.
  bool
  operator==(const InfoBlob& other) const noexcept {
    return entropy == other.entropy
      && spin == other.spin
      && emotion == other.emotion;
  }

private:
  int entropy;
  float spin;
  Emotion emotion;
};


////////////////////////////////////////////////////////////////////////////////
// Part 3: Planters
////////////////////////////////////////////////////////////////////////////////


struct Plant {
  int plantiness = 0;

  Plant(int plantiness)
    : plantiness{plantiness}
      { }

  bool
  operator==(const Plant& other) const noexcept {
    return plantiness == other.plantiness;
  }
};


class Planter {
public:
  Planter(std::initializer_list<Plant> plants)
    : plants{plants}
      { }

  const std::vector<Plant>&
  getPlants() const noexcept {
    return plants;
  }

private:
  std::vector<Plant> plants;
};


////////////////////////////////////////////////////////////////////////////////
// Test and pretty printing support
////////////////////////////////////////////////////////////////////////////////


constexpr inline std::string_view
to_string(const ex4::Emotion emotion) noexcept {
  switch (emotion) {
    case ex4::Emotion::HAPPY:     return "HAPPY";
    case ex4::Emotion::PERPLEXED: return "PERPLEXED";
    case ex4::Emotion::SAD:       return "SAD";
    case ex4::Emotion::STRESSED:  return "STRESSED";
  }
  __builtin_unreachable();
}


constexpr inline std::string_view
to_string(const ex4::Action action) noexcept {
  switch (action) {
    case ex4::Action::RUN:   return "RUN";
    case ex4::Action::LAUGH: return "LAUGH";
    case ex4::Action::WORRY: return "WORRY";
    case ex4::Action::WEEP:  return "WEEP";
    case ex4::Action::PLAN:  return "PLAN";
    case ex4::Action::PLOT:  return "PLOT";
    case ex4::Action::READ:  return "READ";
  }
  __builtin_unreachable();
}


inline std::ostream&
operator<<(std::ostream& os, const Emotion& emotion) {
  return os << to_string(emotion);
}


inline std::ostream&
operator<<(std::ostream& os, const Action& action) {
  return os << to_string(action);
}


inline std::ostream&
operator<< (std::ostream& os, const InfoBlob& blob) {
  return os << "Blob{" << blob.getEntropy()
            << ","     << blob.getSpin()
            << ","     << to_string(blob.getEmotion())
            << "}";
}


inline std::ostream&
operator<< (std::ostream& os, const Plant& plant) {
  return os << plant.plantiness;
}


inline std::ostream&
operator<< (std::ostream& os, const std::pair<size_t, size_t>& edge) {
  return os << "(" << edge.first << "," << edge.second << ")";
}


template<class T>
inline std::ostream&
operator<<(std::ostream& os, const std::vector<T>& items) {
  os << "[ ";
  std::copy(items.begin(), items.end(), std::ostream_iterator<T>{os, " "});
  os << "]";
  return os;
}


}



