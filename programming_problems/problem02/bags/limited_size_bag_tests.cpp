#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "limited_size_bag.hpp"

// force template expansion for ints
template class LimitedSizeBag<int>;

TEST_CASE("Calling all public members", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;

  b.add(0);
  b.remove(0);
  b.isEmpty();
  b.getCurrentSize();
  b.clear();
  b.getFrequencyOf(0);
  b.contains(0);

}

TEST_CASE("test1", "[LimitedSizeBag]") {
  LimitedSizeBag<int> b;
  REQUIRE(1==1);
}

TEST_CASE("Testing add and remove", "[LimitedSizeBag]") {
  LimitedSizeBag<int> b;
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

TEST_CASE("testing clear, contains, and getCurrentSize", "[LimitedSizeBag]") {
  LimitedSizeBag<int> b;
  for (int i = 0; i < 10; i++) {
    b.add(i);
    REQUIRE(b.contains(i));
    REQUIRE(b.getCurrentSize() == i+1);
  }
  b.clear();
  REQUIRE(b.isEmpty());
}

TEST_CASE("testing remove", "[LimitedSizeBag]") {
  LimitedSizeBag<int> b;
  b.add(1);
  b.add(2);
  REQUIRE(b.contains(1));
  b.remove(1);
  REQUIRE(!b.contains(1));
  REQUIRE(b.getCurrentSize() == 1);
}

TEST_CASE("testing maxsize", "[LimitedSizeBag]") {
  LimitedSizeBag<int> b;
  REQUIRE(b.isEmpty());
  for (int i = 0; i < 1000; i++) {
    b.add(i);
  }
  REQUIRE(b.contains(65));
  REQUIRE(!b.contains(111));
}