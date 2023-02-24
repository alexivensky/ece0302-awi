#include <string>
using std::string;

#include <iostream>

#include <cctype> // for isalpha

#include <stack> // for std::stack
using std::stack;

#include "algebraic_expressions.hpp"

bool isoperator(char ch) {
  return ((ch == '+') || (ch == '-') || (ch == '/') || (ch == '*'));
}

int endPost(string s, int last) {
  int first = 0;

  if ((first > last)) {
    return -1;
  }

  char ch = s[last];
  if (isalpha(ch)) {
    return last;
  } else {
    if (isoperator(ch)) {
      int lastEnd = endPost(s, last - 1);
      if (lastEnd > -1) {
        return endPost(s, lastEnd - 1);
      } else {
        return -1;
      }
    } else {
      return -1;
    }
  }
}

bool isPost(string s) {
  int firstChar = endPost(s, s.size() - 1);

  return (firstChar == 0);
}

void convert(string &postfix, string &prefix) {
  if (isPost(postfix)) {
    stack<string> convStack;

    int length = postfix.size();

    for (int i = 0; i < length; i++) {
      if (!isoperator(postfix[i])) {
        convStack.push(string(1, postfix[i]));
      } else {
        string o1, o2, temp;
        o1 = convStack.top();
        convStack.pop();
        o2 = convStack.top();
        convStack.pop();
        temp = postfix[i] + o2 + o1;
        convStack.push(temp);
      }
    }
    prefix = "";
    while (!convStack.empty()) {
      prefix += convStack.top();
      convStack.pop();
    }
  }
}
