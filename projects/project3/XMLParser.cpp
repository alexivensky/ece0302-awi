// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
    @file XMLParser.cpp */

#include <string>
#include <assert.h>
#include "XMLParser.hpp"

// TODO: Implement the constructor here
XMLParser::XMLParser()
{
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
    string temp = "";
    TokenStruct t;

    for (int i = 0; i < inputString.length(); i++) {
        if (inputString[i] == '>') {
            clear();
            return false;
        }
        if (inputString[i] == ' ' || inputString[i] == '\n' || inputString[i] == '\r') {
            continue;
        }

        if (inputString[i] == '<') {
            if (temp.size() > 0) { 
                t.tokenString = temp;
                t.tokenType = CONTENT;
                tokenizedInputVector.push_back(t);
                temp = "";
            }
            i++;
            
            while (inputString[i] != '>') {
                if (inputString[i] == '<') {
                    clear();
                    return false;
                }
                if (i == (inputString.length()-1)) {
                    clear();
                    return false;
                }
                temp += inputString[i];
                i++;
            }
            //NOW use helper functions to determine tag type
            if (temp.length() == 0) {
                clear();
                return false;
            }
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
                elementNameBag->add(temp);
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
                elementNameBag->add(temp);
                temp = "";
            } else {
                clear();
                return false;
            }
        } else {
            temp += inputString[i]; 
            if (i == inputString.length()-1) {
                t.tokenString = temp;
                t.tokenType = CONTENT;
                tokenizedInputVector.push_back(t);
            }
        }
    }
    tokenized = 1;
	return true;
}  // end

// TODO: Implement the parseTokenizedInput method here
bool XMLParser::parseTokenizedInput()
{
    if (!tokenized) {
        return false;
    }
    if (tokenizedInputVector[0].tokenType == CONTENT || tokenizedInputVector[tokenizedInputVector.size()-1].tokenType == CONTENT) {
        return false;
    }
    for (int i = 0; i < tokenizedInputVector.size(); i++) {
        if (tokenizedInputVector[i].tokenType == DECLARATION || tokenizedInputVector[i].tokenType == EMPTY_TAG || tokenizedInputVector[i].tokenType == CONTENT) {
            continue;
        } else if (tokenizedInputVector[i].tokenType == START_TAG) {
            parseStack->push(tokenizedInputVector[i].tokenString);
        } else if (tokenizedInputVector[i].tokenType == END_TAG) {
            string curLabel = tokenizedInputVector[i].tokenString;
            if (parseStack->isEmpty()) {
                clear();
                return false;
            }
            string stackLabel = parseStack->peek();
            if (curLabel != stackLabel) {
                clear();
                return false;
            } else {
                parseStack->pop();
            }
        }
    }
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