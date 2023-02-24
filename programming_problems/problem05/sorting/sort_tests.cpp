#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linked_list.hpp"
#include "sort.hpp"

// write your test cases here
TEST_CASE("Test case", "sorting"){

  LinkedList<int> lst;

  lst.insert(0, 100);
  lst.insert(1, 4);
  lst.insert(2, 10);
  lst.insert(3, 25);
  lst.insert(4, 11);

  LinkedList<int> sorted = sort(lst);

  // check sorted list
  REQUIRE(sorted.getEntry(0) == 4);
  REQUIRE(sorted.getEntry(1) == 10);
  REQUIRE(sorted.getEntry(2) == 11);
  REQUIRE(sorted.getEntry(3) == 25);
  REQUIRE(sorted.getEntry(4) == 100);
  
}


TEST_CASE("Test case 2", "sorting"){

  LinkedList<int> lst;

  lst.insert(0, 1);
  lst.insert(1, 5);
  lst.insert(2, 4);
  lst.insert(3, 3);
  lst.insert(4, 2);

  LinkedList<int> sorted = sort(lst);

  // check sorted list
  REQUIRE(sorted.getEntry(0) == 1);
  REQUIRE(sorted.getEntry(1) == 2);
  REQUIRE(sorted.getEntry(2) == 3);
  REQUIRE(sorted.getEntry(3) == 4);
  REQUIRE(sorted.getEntry(4) == 5);
  
}

TEST_CASE("Test case 3", "sorting"){

  LinkedList<int> lst;

  lst.insert(0, 1);
  lst.insert(1, 1);
  lst.insert(2, 1);
  lst.insert(3, 1);
  lst.insert(4, 1);

  LinkedList<int> sorted = sort(lst);

  // check sorted list
  REQUIRE(sorted.getEntry(0) == 1);
  REQUIRE(sorted.getEntry(1) == 1);
  REQUIRE(sorted.getEntry(2) == 1);
  REQUIRE(sorted.getEntry(3) == 1);
  REQUIRE(sorted.getEntry(4) == 1);
  
}

TEST_CASE("Test case 4", "sorting"){

  LinkedList<int> lst;

  lst.insert(0, 5);
  lst.insert(1, 4);
  lst.insert(2, 3);
  lst.insert(3, 2);
  lst.insert(4, 1);

  LinkedList<int> sorted = sort(lst);

  // check sorted list
  REQUIRE(sorted.getEntry(0) == 1);
  REQUIRE(sorted.getEntry(1) == 2);
  REQUIRE(sorted.getEntry(2) == 3);
  REQUIRE(sorted.getEntry(3) == 4);
  REQUIRE(sorted.getEntry(4) == 5);
  
}
