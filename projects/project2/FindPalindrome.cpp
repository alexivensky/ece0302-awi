#include <string>
#include <vector>
#include <iostream>
#include "FindPalindrome.hpp"

using namespace std;

//------------------- HELPER FUNCTIONS -----------------------------------------

// non-class helper functions go here, should be declared as "static" so that
// their scope is limited

// helper function to convert string to lower case
static void convertToLowerCase(string & value)
{
	for (int i=0; i<value.size(); i++) {
		value[i] = tolower(value[i]);
	}
}

//------------------- PRIVATE CLASS METHODS ------------------------------------

// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(vector<string>
        candidateStringVector, vector<string> currentStringVector)
{
	int currSize = currentStringVector.size();  //called "S" in problem statement, used to keep track of number of recursive calls
	int canSize = candidateStringVector.size(); //size of candidate string vector
	//base case when currentStringVector is empty
	if (currSize == 0) {
		string temp = ""; //temp variable to hold potential sentence palindrome solution
		for (int i = 0; i < canSize; i++) {
			temp += candidateStringVector[i];
		}
		if (isPalindrome(temp)) {
			numPalindromes++; //updating member variable
			sentences.push_back(candidateStringVector); //adding solution to solution vector
		}
	} else {
		for (int i = 0; i < currSize; i++) { //S layers of recursion
			vector<string> recurCandidate = candidateStringVector; //recursive iteration of candidate
			vector<string> recurCurrent = currentStringVector; //recursive iteration of current
			recurCandidate.push_back(recurCurrent[i]); //places one element from current into candidate with each layer of recursion
			recurCurrent.erase(recurCurrent.begin() + i); //removes element just placed into candidate from current
			recursiveFindPalindromes(recurCandidate, recurCurrent); //next layer of recursion
		}
	}
	
	return;
}

// private function to determine if a string is a palindrome (given, you
// may change this if you want)
bool FindPalindrome::isPalindrome(string currentString) const
{
	locale loc;
	// make sure that the string is lower case...
	convertToLowerCase(currentString);
	// see if the characters are symmetric...
	int stringLength = currentString.size();
	for (int i=0; i<stringLength/2; i++) {
		if (currentString[i] != currentString[stringLength - i - 1]) {
			return false;
		}
	}
	return true;
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome()
{
	numPalindromes = 0;
}

FindPalindrome::~FindPalindrome() {}

int FindPalindrome::number() const
{
	// TODO need to implement this...
	return 10;
}

void FindPalindrome::clear()
{
	// TODO need to implement this...
}

bool FindPalindrome::cutTest1(const vector<string> & stringVector)
{
	// TODO need to implement this...
	return false;
}

bool FindPalindrome::cutTest2(const vector<string> & stringVector1,
                              const vector<string> & stringVector2)
{
	// TODO need to implement this...
	return false;
}

bool FindPalindrome::add(const string & value)
{
	// TODO need to implement this...
	return false;
}

bool FindPalindrome::add(const vector<string> & stringVector)
{
	// TODO need to implement this...
	return false;
}

vector< vector<string> > FindPalindrome::toVector() const
{
	// TODO need to implement this...
	vector<vector<string>> returnThingie;
	return returnThingie;
}

