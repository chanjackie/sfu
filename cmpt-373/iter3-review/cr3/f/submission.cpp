// HPP

#ifndef AST_DSLVALUE_H
#define AST_DSLVALUE_H

#include <compare>
#include <json.hpp>
#include <map>
#include <optional>
#include <random>
#include <set>
#include <type_traits>
#include <variant>
#include <vector>

namespace AST {

using Json = nlohmann::json;

class DSLValue;

using List = std::vector<DSLValue>;
using Map = std::map<std::string, DSLValue>;
struct Nil {};

template <typename T>
concept BaseType = std::is_same_v<std::remove_cvref_t<T>, bool> ||
                   std::is_same_v<std::remove_cvref_t<T>, std::string> ||
                   std::is_same_v<std::remove_cvref_t<T>, int> ||
                   std::is_same_v<std::remove_cvref_t<T>, double>;

template <typename T>
concept DSLType = BaseType<T> || std::is_same_v<std::remove_cvref_t<T>, List> ||
                  std::is_same_v<std::remove_cvref_t<T>, Map>;

template <typename T>
concept DSL = std::is_same_v<DSLValue, std::remove_cvref_t<T>>;

template <typename F, typename... Types>
concept BoundedUnaryOperation = requires(F &&f, Types &&... types) {
  (std::invoke(std::forward<F>(f), std::forward<Types>(types)), ...);
};

template <typename F, typename Type1, typename... Types2>
requires requires(F &&f, Type1 &&type, Types2 &&... types) {
  (std::invoke(std::forward<F>(f), std::forward<Type1>(type),
               std::forward<Types2>(types)),
   ...);
}
constexpr inline void NestedApply(F &&f, Type1 &&type, Types2 &&... types) {
  return;
}

template <typename F, typename... Types1>
concept BoundedSymmetricBinaryOperation = requires(F &&f, Types1 &&... types1,
                                                   Types1 &&... types2) {
  (NestedApply(f, std::forward<Types1>(types1),
               std::forward<Types1>(types2)...),
   ...);
};

template <typename F>
concept UnaryDSLOperation =
    BoundedUnaryOperation<F, std::monostate, bool, int, double, std::string,
                          List, Map>;

template <typename F>
concept BinaryDSLOperation =
    BoundedSymmetricBinaryOperation<F, std::monostate, bool, int, double,
                                    std::string, List, Map>;

class DSLValue {
private:
  using InternalType =
      std::variant<std::monostate, bool, std::string, int, double, List, Map>;
  InternalType value;

public:
  enum class Type { LIST, MAP, BOOLEAN, NUMBER, STRING, NIL };

  // Constructors
  DSLValue() noexcept = default;
  DSLValue(const Json &json) noexcept;
  template <DSLType T>
  DSLValue(T &&value) noexcept : value{std::forward<T>(value)} {};
  DSLValue(const DSLValue &other) noexcept { value = other.value; }
  DSLValue(DSLValue &&other) noexcept { value = std::move(other.value); }
  template <DSLType T> DSLValue &operator=(T &&a) noexcept {
    value = std::forward<T>(a);
    return *this;
  }

  DSLValue &operator=(const DSLValue &other) noexcept {
    if (this != &other) {
      this->value = other.value;
    }
    return *this;
  }

  DSLValue &operator=(DSLValue &&other) noexcept {
    if (this != &other) {
      this->value = std::move(other.value);
    }
    return *this;
  }

  DSLValue &operator=(const Json &json) noexcept {
    *this = DSLValue{json};
    return *this;
  }

  template <UnaryDSLOperation F> decltype(auto) unaryOperation(F &&f) {
    return std::visit(f, value);
  }

  template <UnaryDSLOperation F> decltype(auto) unaryOperation(F &&f) const {
    return std::visit(f, value);
  }

  template <DSL U, BinaryDSLOperation F>
  decltype(auto) binaryOperation(U &&other, F &&f) {
    return std::visit(f, value, other.value);
  }

  template <DSL U, BinaryDSLOperation F>
  decltype(auto) binaryOperation(const U &other, F &&f) const {
    return std::visit(f, value, other.value);
  }

  std::optional<std::reference_wrapper<const DSLValue>>
  at(const std::string &key) const noexcept;

  std::optional<std::reference_wrapper<DSLValue>>
  operator[](const std::string &key) noexcept;

  std::optional<std::reference_wrapper<DSLValue>>
  operator[](size_t index) noexcept;

  std::optional<std::reference_wrapper<const DSLValue>>
  operator[](size_t index) const noexcept;

  std::optional<DSLValue> createSlice(const std::string &key) const noexcept;
  size_t size() const noexcept;

  friend std::partial_ordering
  operator<=>(const DSLValue &x, const DSLValue &y) noexcept = default;
};

bool isSortableType(const DSLValue &x) noexcept;
bool isSameType(const DSLValue &x, const DSLValue &y) noexcept;
void extend(DSL auto &&to, DSL auto &&from) noexcept;
void reverse(DSL auto &&x) noexcept;
void shuffle(DSL auto &&x) noexcept;
void sort(DSL auto &&x) noexcept;
void sort(DSL auto &&x, const std::string &key) noexcept;
void discard(DSL auto &&x, size_t count) noexcept;
void deal(DSL auto &&from, DSL auto &&to, size_t count) noexcept;
std::ostream &operator<<(std::ostream &os, const DSLValue &x) noexcept;

} // namespace AST

// CPP

#include "DSLValue.h"
#include <functional>
#include <iostream>
#include <ranges>
#include <sstream>

using namespace std;

namespace {
using namespace AST;

struct MutableAt {
  const string &key;
  explicit MutableAt(const string &key) noexcept : key{key} {};
  using returnType = optional<reference_wrapper<DSLValue>>;

  auto operator()(Map &map) noexcept -> returnType {
    auto it = map.find(key);
    return (it == map.end()) ? nullopt : returnType{it->second};
  }
  auto operator()(auto &&discard) noexcept -> returnType { return nullopt; }
};

struct At {
  const string &key;
  explicit At(const string &key) noexcept : key{key} {};
  using returnType = optional<reference_wrapper<const DSLValue>>;

  auto operator()(const Map &map) noexcept -> returnType {
    auto it = map.find(key);
    return (it == map.end()) ? nullopt : returnType{it->second};
  }
  auto operator()(const auto &discard) noexcept -> returnType {
    return nullopt;
  }
};

struct MutableListIndex {
  size_t index;
  explicit MutableListIndex(size_t index) : index{index} {};
  using returnType = optional<reference_wrapper<DSLValue>>;

  auto operator()(List &list) noexcept -> returnType {
    return index < list.size() ? returnType{list[index]} : nullopt;
  }
  auto operator()(auto &&discard) noexcept -> returnType { return nullopt; }
};

struct ListIndex {
  size_t index;
  explicit ListIndex(size_t index) : index{index} {};
  using returnType = optional<reference_wrapper<const DSLValue>>;

  auto operator()(const List &list) noexcept -> returnType {
    return index < list.size() ? returnType{list[index]} : nullopt;
  }
  auto operator()(const auto &discard) noexcept -> returnType {
    return nullopt;
  }
};

struct Size {
  explicit Size() = default;

  auto operator()(const Map &map) noexcept -> size_t { return map.size(); }
  auto operator()(const List &list) noexcept -> size_t { return list.size(); }
  auto operator()(const auto &discard) noexcept -> size_t { return 0; }
};

struct Slice {
  const string &key;
  explicit Slice(const string &key) : key{key} {};
  using returnType = optional<DSLValue>;

  auto operator()(const Map &map) noexcept -> returnType {
    auto it = map | ranges::views::filter([this](const auto &x) {
                return x.first == key;
              }) |
              ranges::views::transform([](const auto &x) { return x.second; });
    DSLValue returnValue = List{it.begin(), it.end()};
    return (returnValue.size() == map.size()) ? returnType{returnValue}
                                              : nullopt;
  }
  auto operator()(const auto &discard) noexcept -> returnType {
    return nullopt;
  }
};

struct Extend {
  explicit Extend() = default;

  auto operator()(List &to, List &from) noexcept {
    ranges::move(from, to.end());
    from.clear();
  }
  auto operator()(auto &&x, auto &&y) noexcept { return; }
};

struct Reverse {
  explicit Reverse() = default;

  auto operator()(List &list) noexcept { ranges::reverse(list); }
  auto operator()(auto &&discard) noexcept { return; }
};

struct Shuffle {
  explicit Shuffle() = default;

  auto operator()(List &list) noexcept {
    std::random_device rd;
    std::mt19937 generate{rd()};
    ranges::shuffle(list, generate);
    return;
  }
  auto operator()(auto &&discard) noexcept { return; }
};

// Some more structs related to sorting...

};

} // namespace

namespace AST {

optional<reference_wrapper<DSLValue>>
DSLValue::operator[](const string &key) noexcept {
  return unaryOperation(MutableAt{key});
}

optional<reference_wrapper<const DSLValue>>
DSLValue::at(const std::string &key) const noexcept {
  return unaryOperation(At(key));
}

optional<reference_wrapper<DSLValue>>
DSLValue::operator[](size_t index) noexcept {
  return unaryOperation(MutableListIndex{index});
}

optional<reference_wrapper<const DSLValue>>
DSLValue::operator[](size_t index) const noexcept {
  return unaryOperation(ListIndex{index});
}

optional<DSLValue>
DSLValue::createSlice(const std::string &key) const noexcept {
  return unaryOperation(Slice{key});
}

size_t DSLValue::size() const noexcept { return unaryOperation(Size{}); }
void extend(DSL auto &&to, DSL auto &&from) noexcept {
  to.binaryOperation(from, Extend{});
}
void reverse(DSL auto &&x) noexcept { x.unaryOperation(Reverse{}); }
void shuffle(DSL auto &&x) noexcept { x.unaryOperation(Shuffle{}); }
void sort(DSL auto &&x) noexcept { x.unaryOperation(Sort{}); }
void sort(DSL auto &&x, const std::string &key) noexcept {
  x.unaryOperation(SortWithKey{key});
}
bool isSameType(const DSLValue &x, const DSLValue &y) noexcept {
  return x.binaryOperation(y, SameType{});
}
bool isSortableType(const DSLValue &x) noexcept {
  return x.unaryOperation(SortableType{});
}
void discard(DSL auto &&x, size_t count) noexcept {
  return x.unaryOperation(Discard{count});
}
void deal(DSL auto &&from, DSL auto &&to, size_t count) noexcept {
  return to.binaryOperation(Deal{count});
}
ostream &operator<<(ostream &os, const DSLValue &x) noexcept {
  return x.unaryOperation(Print{os});
}
DSLValue::DSLValue(const Json &json) noexcept {
  if (json.is_null()) {
    value = std::monostate{};
  } else if (json.is_boolean()) {
    value = json.get<bool>();
  } else if (json.is_number_integer()) {
    value = json.get<int>();
  } else if (json.is_number_float()) {
    value = json.get<double>();
  } else if (json.is_string()) {
    value = json.get<std::string>();
  } else if (json.is_array()) {
    List list;
    list.reserve(static_cast<size_t>(json.size()));
    std::transform(json.begin(), json.end(), back_inserter(list),
                   [](const auto &x) { return DSLValue{x}; });
    value = std::move(list);
  } else if (json.is_object()) {
    Map map;
    std::transform(
        json.items().begin(), json.items().end(), std::inserter(map, map.end()),
        [](auto &x) { return std::make_pair(x.key(), DSLValue{x.value()}); });
    value = std::move(map);
  } else {
    assert("json is of unknown type");
    value = std::monostate{};
  }
}

} // namespace AST

#endif
