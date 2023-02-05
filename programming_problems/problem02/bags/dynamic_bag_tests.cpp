#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "dynamic_bag.hpp"

// force template expansion for ints
template class DynamicBag<int>;

TEST_CASE("Calling all public members", "[DynamicBag]"){
  DynamicBag<int> b;

  b.add(0);
  b.remove(0);
  b.isEmpty();
  b.getCurrentSize();
  b.clear();
  b.getFrequencyOf(0);
  b.contains(0);
}

TEST_CASE("Testing add and remove", "[DynamicBag]") {
  DynamicBag<int> b;
  REQUIRE(b.isEmpty());
  b.add(0);
  REQUIRE(b.contains(0));
  REQUIRE(!b.contains(-1));
  REQUIRE(!b.isEmpty());
  REQUIRE(b.getCurrentSize() == 1);
  b.remove(0);
  REQUIRE(!b.contains(0));
  REQUIRE(b.isEmpty());
}

TEST_CASE("testing clear, contains, and getCurrentSize", "[DynamicBag]") {
  DynamicBag<int> b;
  for (int i = 0; i < 1000; i++) {
    b.add(i);
    REQUIRE(b.contains(i));
    REQUIRE(b.getCurrentSize() == i+1);
  }
  b.clear();
  REQUIRE(b.isEmpty());
}

TEST_CASE("copy constructor and = overload", "[DynamicBag]") {
  DynamicBag<int> b1;
  b1.add(1);
  b1.add(300);
  b1.add(4);
  DynamicBag<int>b2(b1);
  REQUIRE(b2.getCurrentSize() == 3);
  DynamicBag<int> b3;
  b3 = b1;
  REQUIRE(b3.getCurrentSize() == 3);
}

TEST_CASE("testing remove", "[DynamicBag]") {
  DynamicBag<int> b;
  b.add(1);
  b.add(2);
  REQUIRE(b.contains(1));
  b.remove(1);
  REQUIRE(!b.contains(1));
  REQUIRE(b.getCurrentSize() == 1);
}
