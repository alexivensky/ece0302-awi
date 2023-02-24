#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linked_list.hpp"

template class LinkedList<int>;

TEST_CASE( "TODO", "[LinkedList]" ) {

    LinkedList<int> list;
}

TEST_CASE("Default constructor", "[LinkedList]") {
  LinkedList<int> l1;
  REQUIRE(l1.isEmpty());
  REQUIRE(l1.getLength() == 0);
  REQUIRE(!l1.remove(1));
}

TEST_CASE("Adding", "[LinkedList]") {
  LinkedList<int> l1;
  for (int i = 0; i < 1000; i++) {
    l1.insert(i, i);
    REQUIRE(l1.getEntry(i) == i);
    l1.remove(i);
  }
  REQUIRE(l1.isEmpty());
}

TEST_CASE("removing", "[LinkedList]") {
  LinkedList<int> l1;
  l1.insert(0, 1);
  l1.insert(1, 5);
  l1.remove(1);
  l1.remove(0);
  REQUIRE(l1.isEmpty());
}

TEST_CASE("Copy constructor and = overload", "[LinkedList]") {
  LinkedList<int> l1;
  l1.insert(0, 1);
  l1.insert(1, 4);
  l1.insert(2, 5);
  LinkedList<int> l2(l1);
  REQUIRE(l2.getEntry(0) == 1);
  REQUIRE(l2.getEntry(1) == 4);
  REQUIRE(l2.getEntry(2) == 5);
  LinkedList<int> l3;
  l3 = l1;
  REQUIRE(l3.getEntry(0) == 1);
  REQUIRE(l3.getEntry(1) == 4);
  REQUIRE(l3.getEntry(2) == 5);
}
