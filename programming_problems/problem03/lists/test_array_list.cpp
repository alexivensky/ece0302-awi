#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "array_list.hpp"

//force class expansion
template class ArrayList<int>;

TEST_CASE("Default constructor", "[ArrayList]") {
  ArrayList<int> l1;
  REQUIRE(l1.isEmpty());
  REQUIRE(l1.getLength() == 0);
  REQUIRE(!l1.remove(1));
}

TEST_CASE("Adding and removing", "[ArrayList]") {
  ArrayList<int> l1;
  for (int i = 0; i < 1000; i++) {
    l1.insert(i, i);
    REQUIRE(l1.getEntry(i) == i);
  }
  for (int i = 999; i >= 0; i--) {
    l1.remove(i);
  }
  REQUIRE(l1.isEmpty());
}

TEST_CASE("Copy constructor and = overload", "[ArrayList]") {
  ArrayList<int> l1;
  l1.insert(0, 1);
  l1.insert(1, 4);
  l1.insert(2, 5);
  ArrayList<int> l2(l1);
  REQUIRE(l2.getEntry(0) == 1);
  REQUIRE(l2.getEntry(1) == 4);
  REQUIRE(l2.getEntry(2) == 5);
  ArrayList<int> l3;
  l3 = l1;
  REQUIRE(l3.getEntry(0) == 1);
  REQUIRE(l3.getEntry(1) == 4);
  REQUIRE(l3.getEntry(2) == 5);
}