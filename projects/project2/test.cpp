#include <iostream>
#include <string>
#include <vector>
#include "FindPalindrome.cpp"
using namespace std;
int main() {
    FindPalindrome b;
    vector<string> addVec;
    addVec.push_back("sit");
    addVec.push_back("on");
    addVec.push_back("a");
    addVec.push_back("potato");
    addVec.push_back("pan");
    addVec.push_back("otis");
    b.add(addVec);
    vector<vector<string> > solutions;
    solutions = b.toVector();
    for (int i = 0; i < solutions.size(); i++) {
        cout << i << " ";
        for (int j = 0; j < solutions[i].size(); j++) {
            cout << solutions[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}