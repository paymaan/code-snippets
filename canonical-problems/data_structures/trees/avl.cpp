/// This is just a prototype and is not meant for
/// prodduction use
/// I'm just playing around and creating some common data
/// structures

#include <cassert>
#include <iostream>
#include <memory>

using namespace std; // not recommended obviously but saves
                     // some keystrokes for now :)

class Node {
  public:
    Node(int a_key, shared_ptr<Node> a_left = nullptr,
         shared_ptr<Node> a_right = nullptr)
        : key(a_key)
        , left(a_left)
        , right(a_right) {}
    int key;
    shared_ptr<Node> left;
    shared_ptr<Node> right;
};

int main() {
  return 0;
}
