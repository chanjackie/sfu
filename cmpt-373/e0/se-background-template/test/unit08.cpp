#include "doctest.h"
#include "task08.h"


TEST_CASE("Get absent") {
  const int VALUE = 5;
  OrderedList list;
  OrderedList::Node* found = list.getNode(VALUE);

  CHECK(found == nullptr);
}


TEST_CASE("Add one") {
  const int VALUE = 5;
  OrderedList list;
  OrderedList::Node* added = list.add(VALUE);

  CHECK(added != nullptr);
  CHECK(added->getValue() == VALUE);
}


TEST_CASE("Remove one") {
  const int VALUE = 5;
  OrderedList list;
  OrderedList::Node* added = list.add(VALUE);

  CHECK(added != nullptr);
  CHECK(added->getValue() == VALUE);

  OrderedList::Node* found = list.getNode(VALUE);

  CHECK(found == added);

  added->remove();
  found = list.getNode(VALUE);

  CHECK(found == nullptr);
}


TEST_CASE("Add a few, then remove") {
  const std::array VALUES = { 8, 9, 3 ,6, 4};
  const int ABSENT_VALUE = 13;
  OrderedList list;

  for (const auto value : VALUES) {
    OrderedList::Node* const added = list.add(value);
    CHECK(added != nullptr);
    CHECK(added->getValue() == value);
  }

  for (const auto value : VALUES) {
    OrderedList::Node* const found = list.getNode(value);
    CHECK(found != nullptr);
    CHECK(found->getValue() == value);
  }
  
  OrderedList::Node* const shouldNotFind = list.getNode(ABSENT_VALUE);
  CHECK(shouldNotFind == nullptr);

  for (const auto value : VALUES) {
    OrderedList::Node* found = list.getNode(value);
    CHECK(found != nullptr);
    CHECK(found->getValue() == value);
    found->remove();

    OrderedList::Node* alsoShouldNotFind = list.getNode(value);
    CHECK(alsoShouldNotFind == nullptr);
  }
}


TEST_CASE("Add a few, then extract") {
  const std::array VALUES = { 9, 8, 3 ,6, 4};
  std::array ORDERED_VALUES = VALUES;
  OrderedList list;

  std::sort(ORDERED_VALUES.begin(), ORDERED_VALUES.end());

  for (const auto value : VALUES) {
    OrderedList::Node* const added = list.add(value);
    CHECK(added != nullptr);
    CHECK(added->getValue() == value);
  }

  for (const auto value : VALUES) {
    OrderedList::Node* const found = list.getNode(value);
    CHECK(found != nullptr);
    CHECK(found->getValue() == value);
  }
  
  OrderedList::Node* currentNode = list.getNode(ORDERED_VALUES[0]);
  for (const auto value : ORDERED_VALUES) {
    CHECK(currentNode);
    CHECK(currentNode->getValue() == value);
    currentNode = currentNode->getNext();
  }
}


