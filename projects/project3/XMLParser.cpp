// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
    @file XMLParser.cpp */

#include <string>
#include <assert.h>
#include "XMLParser.hpp"

// TODO: Implement the constructor here
XMLParser::XMLParser()
{
    //allocating memory for private member data structures
    elementNameBag = new Bag<std::string>();
    parseStack = new Stack<std::string>();
    
}  // end default constructor

// TODO: Implement the destructor here
XMLParser::~XMLParser()
{
    clear();
    delete elementNameBag;
    delete parseStack;
}  // end destructor
// TODO: Implement the tokenizeInputString method
bool XMLParser::tokenizeInputString(const std::string &inputString)
{
    string temp = ""; //temp string to store current token of interest
    TokenStruct t; //temp TokenStruct

    //checks for illegal closing tags
    for (int i = 0; i < inputString.length(); i++) {
        if (inputString[i] == '>') {
            clear();
            return false;
        }
        //ignoring returns
        if (inputString[i] == '\n' || inputString[i] == '\r') {
            continue;
        }
        //checking tags
        if (inputString[i] == '<') {
            //if there is anything stored in temp, first check if it is entirely white space.
            //if temp is not entirely white space, mark it as content and push to tokenizedInputVector
            if (temp.size() > 0) {  
                t.tokenString = temp;
                t.tokenType = CONTENT;
                bool nonWhiteSpace = 0; 
                for (int i = 0; i < temp.length(); i++) {
                    if (temp[i] != ' ') {
                        nonWhiteSpace = 1; //temp is not entirely white space
                    }
                }
                if (nonWhiteSpace) {
                    tokenizedInputVector.push_back(t);
                }
                temp = ""; //reset temp string
            }
            i++; //skipping to next character in string
            
            while (inputString[i] != '>') { //iterates through the rest of the tag
                if (inputString[i] == '<') { //checking for illegal nesting
                    clear();
                    return false;
                }
                if (i == (inputString.length()-1)) { //breaks if tag never gets closed
                    clear();
                    return false;
                }
                temp += inputString[i]; //adding to temp with each iteration
                i++; //iterating ...
            }
 
            if (temp.length() == 0) { //if tag is completely empty, return false
                clear();
                return false;
            }
            //checking tag type using helper functions
            if (isStartTag(temp)) {
                t.tokenType = START_TAG;
                t.tokenString = removeAttributes(temp);
                if (!isValidString(removeAttributes(temp))) {
                    clear();
                    return false;
                }
                tokenizedInputVector.push_back(t);
                elementNameBag->add(removeAttributes(temp));
                temp = "";
            } else if (isEndTag(temp)) {
                t.tokenType = END_TAG;
                t.tokenString = temp.substr(1, temp.length());
                if (!isValidString(removeAttributes(temp.substr(1, temp.length())))) {
                    clear();
                    return false;
                }
                tokenizedInputVector.push_back(t);
                //unclear whether or not this is needed ... does not affect tests in any way
                //elementNameBag->add(temp);
                temp = "";
            } else if (isEmptyTag(temp)) {
                t.tokenType = EMPTY_TAG;
                t.tokenString = removeAttributes(temp.substr(0, temp.length() - 1));
                if (!isValidString(removeAttributes(temp.substr(0, temp.length() - 1)))) {
                    clear();
                    return false;
                }
                tokenizedInputVector.push_back(t);
                elementNameBag->add(removeAttributes(temp.substr(0, temp.length() - 1)));
                temp = "";
            } else if (isDecTag(temp)) {
                t.tokenType = DECLARATION;
                t.tokenString = temp.substr(1, temp.length() - 2);
                tokenizedInputVector.push_back(t);
                // same as before
                //elementNameBag->add(temp);
                temp = "";
            } else { //if tag is not valid, return false
                clear();
                return false;
            }
        } else { //if not currently in tag
            temp += inputString[i]; //adding to temp
            //if we reach the end of the inputString, we mark this as content.
            //this should end up returning false from the parser, but is valid for the tokenizer
            if (i == inputString.length()-1) {
                t.tokenString = temp;
                t.tokenType = CONTENT;
                bool nonWhiteSpace = 0;
                for (int i = 0; i < temp.length(); i++) { //also checking for whitespace at the end of the string,
                // which can be ignored.
                    if (temp[i] != ' ') {
                        nonWhiteSpace = 1;
                    }
                }
                if (nonWhiteSpace) {
                    tokenizedInputVector.push_back(t);
                }
            }
        }
    }
    tokenized = 1;
	return true;
}  // end

// TODO: Implement the parseTokenizedInput method here
bool XMLParser::parseTokenizedInput()
{
    if (!tokenized) { //if tokenizer has failed, no point parsing.
        return false;
    }
    //if there is content at the front or back of the vector, it is automatically wrong
    if (tokenizedInputVector[0].tokenType == CONTENT || tokenizedInputVector[tokenizedInputVector.size()-1].tokenType == CONTENT) {
        return false;
    }
    //extremely convoluted way of checking validity of declaration tags
    //declaration tags should only be at the beginning of the file, but there can be any number of them
    //which is why I did it this way
    int numDecs = 0;
    bool dec = 1;
    for (int j = 0; j < tokenizedInputVector.size(); j++) {
        if (tokenizedInputVector[j].tokenType == DECLARATION) {
            numDecs++;
        }
        if (numDecs-1 != j) {
            dec = 0;
        }
        if (!dec && tokenizedInputVector[j].tokenType == DECLARATION) {
            return false;
        }
    }
    //now we can actually check for start/end validity using the stack
    for (int i = 0; i < tokenizedInputVector.size(); i++) {
        //empty tags don't matter at all in terms of placement,
        //content tokens don't matter either as long as they are inside of other tags,
        //which we have verified.
        if (tokenizedInputVector[i].tokenType == EMPTY_TAG || tokenizedInputVector[i].tokenType == CONTENT) {
            continue;
        //if we encounter a start tag, push it to the stack
        } else if (tokenizedInputVector[i].tokenType == START_TAG) {
            parseStack->push(tokenizedInputVector[i].tokenString);
        //if we encounter an end tag:
        //peek the stack. this should correspond with the most recent start tag and match the current end tag ideally
        //if it does not, something is wrong, so we return false
        } else if (tokenizedInputVector[i].tokenType == END_TAG) {
            string curLabel = tokenizedInputVector[i].tokenString;
            //if we encounter an end tag and the stack is empty, it is definitely wrong
            //this conditional also prevents a logic error from peeking and popping an empty stack
            if (parseStack->isEmpty()) {
                clear();
                return false;
            }
            //comparing labels
            string stackLabel = parseStack->peek();
            if (curLabel != stackLabel) {
                clear();
                return false;
            } else {
                parseStack->pop();
            }
        }
    }
    //at the end, the stack should be empty. if it is not, something is wrong
    if (parseStack->isEmpty()) {
        parsed = 1;
        return true;
    }
    clear();
    return false;
}

// TODO: Implement the clear method here
void XMLParser::clear()
{
    elementNameBag->clear();
    parseStack->clear();
    tokenizedInputVector.clear();
    tokenized = 0;
    parsed = 0;
}

vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
    return tokenizedInputVector;
}

// TODO: Implement the containsElementName method
bool XMLParser::containsElementName(const std::string &inputString) const
{
    if (!tokenized || !parsed) {
        throw logic_error("Not tokenized or parsed");
        return false;
    } else {
        return elementNameBag->contains(inputString);
    }
}

// TODO: Implement the frequencyElementName method
int XMLParser::frequencyElementName(const std::string &inputString) const
{
    if (!tokenized || !parsed) {
        throw logic_error("Not tokenized or parsed");
        return false;
    } else {
        return elementNameBag->getFrequencyOf(inputString);
    }
}

bool XMLParser::isValidString(std::string inputString) {
    std::string invalid[] = {"!","\"","#","$","%","&","'","(",")","*","+",
                                ",","/",";","<","=",">","?","@","[","\\","]"
                                "^","`","{","|","}","~"};
    std::string begin[] = {"-",",",".","0","1","2","3","4","5","6","7","8","9"};
    for (int i = 0; i < 13; i++) {
        if (inputString[0] == *begin[i].c_str()) {
            return false;
        }
    }
    for (int i = 0; i < inputString.length(); i++) {
        for (int j = 0; j < 28; j++) {
            if (inputString[i] == *invalid[j].c_str()) {
                return false;
            }
        }
    }
    return true;
}

bool XMLParser::isStartTag(std::string input) {
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '/' || input[i] == '?') {
            return false;
        }
    }
    return true;
}

bool XMLParser::isEndTag(std::string input) {
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '/' && i != 0 || input[i] == '?') {
            return false;
        }
    }
    if (input[0] != '/') {
        return false;
    }
    return true;
}

bool XMLParser::isEmptyTag(std::string input) {
    for (int i = 0; i < input.length() - 1; i++) {
        if (input[i] == '/') {
            return false;
        }
        if (input[i] == '?') {
            return false;
        }
    }
    if (input[input.length() - 1] != '/') {
        return false;
    }
    return true;
}

bool XMLParser::isDecTag(std::string input) {
    int len = input.length();
    return input[0] == '?' && input[len-1] == '?';
}

std::string XMLParser::removeAttributes(std::string input) {
    std::string returnString;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] != ' ') {
            returnString += input[i];
        } else {
            return returnString;
        }
    }
    return returnString;
}