#include <iostream>
#include <string>
using namespace std;
int main() {
    string temp = "abcdef1234!*&@(*!Y@H!I@HJUB!IUSYH)";
    for (int i = 0; i < temp.length(); i++) {
        cout << temp[i] << " " << isalpha(temp[i]) << endl;
    }
    return 0;
}