#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"

// There should be at least one test per FindPalindrome method

TEST_CASE( "Test adding a non-allowable word", "[FindPalindrome]" )
{
	FindPalindrome b;
	REQUIRE(!b.add("kayak1"));
}

TEST_CASE("test recursion", "[FindPalindrome]"){
	FindPalindrome b;

	REQUIRE(b.add("a"));
	REQUIRE(b.add("AA"));
	REQUIRE(b.add("AaA"));
	REQUIRE(b.number() == 6);
}

TEST_CASE("adding vectors and strings", "[FindPalindrome]") {
	FindPalindrome b;
	vector<string> addVec;
	addVec.push_back("a");
	addVec.push_back("aa");
	addVec.push_back("aaa");
	REQUIRE(b.add(addVec)); //should be able to add because is unique
	REQUIRE(!b.add(addVec)); //should not be able to add because not unique
	vector<string> addVec2 = {"b", "bb", "1"};
	REQUIRE(!b.add(addVec2)); //contains invalid strings
	vector<string> addVec3 = {"b", "bb", "a"};
	REQUIRE(!b.add(addVec3)); //contains repeats
	REQUIRE(b.add("aaaa")); //is unique
	REQUIRE(!b.add("AAA")); //is not unique
	REQUIRE(b.number() == 16);
}

TEST_CASE("testing RFP", "[FindPalindrome]") {
	FindPalindrome b;
    vector<string> addVec;
    addVec.push_back("sit");
    addVec.push_back("on");
    addVec.push_back("a");
    addVec.push_back("pan");
    addVec.push_back("potato");
    addVec.push_back("otis");
    b.add(addVec);
    vector<vector<string> > solutions;
    solutions = b.toVector();
	vector<vector<string> > actualSolution = {{"sit", "on", "a", "potato", "pan", "otis"}};
	REQUIRE(solutions == actualSolution);
	REQUIRE(b.number() == 1);
	b.clear();
	REQUIRE(b.number() == 0);
}

