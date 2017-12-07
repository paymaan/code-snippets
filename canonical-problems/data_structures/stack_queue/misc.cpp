#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

using namespace std;

bool IsWellFormed(const string& str) {
    stack<char> left_chars;
    unordered_map<char, char> paren_map = {
        {'(', ')'}, {'{', '}'}, {'[', ']'}};
    for (const char c : str) {
        // if can find left paren, add it to stack
        if (paren_map.find(c) != paren_map.end()) {
            left_chars.push(c);
        } else { // else right paren must match
                 // top of stack OR we collapse
            if (left_chars.empty() ||
                paren_map[left_chars.top()] != c) {
                return false;
            }
            left_chars.pop();
        }
    }
    return left_chars.empty();
}

bool IsWellFormed_WoMap(const string& str) {
    stack<char> right_chars;
    for (const char c : str) {
        if (c == '(') {
            right_chars.push(')');
        } else if (c == '{') {
            right_chars.push('}');
        } else if (c == '[') {
            right_chars.push(']');
        } else { // right paren
            if (right_chars.empty() ||
                right_chars.top() != c) {
                return false;
            }
            right_chars.pop();
        }
    }
    return right_chars.empty();
}

int main() {
    cout << IsWellFormed("((){[[]]}[{}])") << endl;
    return 0;
}
