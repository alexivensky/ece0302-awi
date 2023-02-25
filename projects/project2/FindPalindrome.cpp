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
			if (cutTest2(recurCandidate, recurCurrent)) {	
				recursiveFindPalindromes(recurCandidate, recurCurrent); //next layer of recursion
			}
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

FindPalindrome::FindPalindrome() //default constructor 
{
	numPalindromes = 0; //initializes number of answers to zer0
}

FindPalindrome::~FindPalindrome() {} //no dynamic memory to deallocate so destructor is empty

int FindPalindrome::number() const
{
	return numPalindromes; //returns number of answers
}

void FindPalindrome::clear() //resets all member variables 
{
	sentences.clear();
	entries.clear();
	numPalindromes = 0;
}

bool FindPalindrome::cutTest1(const vector<string> & stringVector)
{
	string temp = ""; //empty string
	for (int i = 0; i < stringVector.size(); i++) { //adds contents of vector into one string
		temp += stringVector[i];
	}
	convertToLowerCase(temp); //pretty self explanatory what this does ...
	
	int alphabet[26]; //array that will track the number of instances of each letter in the alphabet
	//if more than one value in the array is odd, this automatically means the string is not a palindrome

	for (int i = 0; i < 26; i++) { alphabet[i] = 0; } //zeroing the array

	for (int i = 0; i < temp.length(); i++) {
		alphabet[temp[i] - 97]++; //increments ASCII(temp[i]) - ASCII(a) when character is found
	}

	int numOdd = 0; //counts number of odd occurences of each letter in alphabet
	for (int i = 0; i < 26; i++) {
		if (alphabet[i] % 2 == 1) { numOdd++; } 
		if (numOdd > 1) { return false; } //if more than one number of odd occurrrences, there is no palindrome
	}
	return true;
}

bool FindPalindrome::cutTest2(const vector<string> & stringVector1,
                              const vector<string> & stringVector2)
{
	//does basically the same thing as cut test 1 except compares the number of occurrences between vectors
	string small, big, temp1 = "", temp2 = "";
	for (int i = 0; i < stringVector1.size(); i++) {
		temp1 += stringVector1[i];
	}
	for (int i = 0; i < stringVector2.size(); i++) {
		temp2 += stringVector2[i];
	}
	convertToLowerCase(temp1);
	convertToLowerCase(temp2);
	if (temp1.size() < temp2.size()) {
		small = temp1;
		big = temp2;
	} else {
		small = temp2;
		big = temp1;
	}
	int alphabet1[26], alphabet2[26];
	for (int i = 0; i < 26; i++) {
		alphabet1[i] = 0;
		alphabet2[i] = 0;
	}
	for (int i = 0; i < small.length(); i++) {
		alphabet1[small[i] - 97]++; //increments ASCII(temp[i]) - ASCII(a) when character is found
	}
	for (int i = 0; i < big.length(); i++) {
		alphabet2[big[i] - 97]++; //increments ASCII(temp[i]) - ASCII(a) when character is found
	}
	for (int i = 0; i < 26; i++) {
		if (alphabet1[i] > alphabet2[i]) { //if different number of occurrences between small and big strings, automatically means there is no palindrome
			return false;
		}
	}
	return true;
}

bool FindPalindrome::add(const string & value)
{
	for (int i = 0; i < value.length(); i++) {
		if (!std::isalpha(value[i])) { //checking that value is only letters
			return false;
		}
	}
	string temp = value, tempEntry;
	convertToLowerCase(temp);

	for (int i = 0; i < entries.size(); i++) { //checking for uniqueness
		tempEntry = entries[i];
		convertToLowerCase(tempEntry);
		if (tempEntry == temp) {
			return false;
		}
	}
	//code below should only execute if value is a valid entry
	
	vector<string> dummy; //empty vector (doesn't even have direction and magnitude, hence the name)
	entries.push_back(value); //adds value to entries if value is valid
	sentences.clear(); //clears answer vector of vectors
	numPalindromes = 0; //resets number of answers
	if (cutTest1(entries)) {
		recursiveFindPalindromes(dummy, entries); //recursively finds palindromes again with new value
	}
	return true; //returns true.
}

bool FindPalindrome::add(const vector<string> & stringVector)
{
	for (int i = 0; i < stringVector.size(); i++) { //checking that each string is only letters
		for (int j = 0; j < stringVector[i].size(); j++) {
			if (!std::isalpha(stringVector[i][j])) {
				return false;
			}
		}
		string temp1 = stringVector[i]; 
		for (int k = i+1; k < stringVector.size(); k++) { //checking for repeats within the vector itself
			string temp2 = stringVector[k];
			convertToLowerCase(temp1);
			convertToLowerCase(temp2);
			if (temp1 == temp2) {
				return false;
			}
		}
		for (int l = 0; l < entries.size(); l++) { //checking for repeats between vector and member vector
			string temp3 = entries[l];
			convertToLowerCase(temp3);
			if (temp1 == temp3) {
				return false;
			}
		}
		entries.push_back(stringVector[i]); //if all tests pass, adds string to entries
	}
	//same procedure as previous add function
	vector<string> dummy; //still dumb bc no direction and magnitude (<- this was meant as a joke)
	sentences.clear();
	numPalindromes = 0;
	if (cutTest1(entries)) {	
		recursiveFindPalindromes(dummy, entries);
	}
	return true;
}

vector< vector<string> > FindPalindrome::toVector() const
{
	return sentences; //returns answer vector
}

