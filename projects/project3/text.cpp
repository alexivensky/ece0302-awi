#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    string input = "/";
    for (int i = 0; i < input.length() - 1; i++) {
        if (input[i] == '/') {
            cout << false;
        }
        if (input[i] == '?') {
            cout << false;
        }
    }
    if (input[input.length() - 1] != '/') {
        cout << false;
    }
    cout << true;

    return 0;
}