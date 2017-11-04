/// This is just a prototype and is not meant for
/// prodduction use
/// I'm just playing around and creating some common data
/// structures

#include "../linked_list/list.hpp"
#include <iostream>
#include <memory>

using namespace std; // not recommended obviously but saves
                     // some keystrokes for now :)

/// Stack is a FILO or LIFO data structure
/// All operations here are O(1) time unless stated
/// otherwise
/// This implementation uses a linked list for dnyamic stack
/// "list" is the linked list here
class Stack {
  public:
    Stack()
        : list(make_unique<List>()) {}

    bool empty() const {
        return list->empty();
    }

    size_t size() const {
        return list->size();
    }

    int top() const {
        return list->head_value();
    }

    void push(int x) {
        list->push_front(x);
    }

    void pop() {
        list->pop_front();
    }

    void print() const {
        // print vertically
        list->print("\n");
        cout << "\n";
    }

  private:
    unique_ptr<List> list;
};

int main() {
    Stack stack;
    stack.push(5);
    stack.push(10);
    stack.push(15);
    stack.print();
    stack.pop();
    stack.print();
    stack.push(2);
    stack.push(4);
    stack.print();
    stack.pop();
    stack.pop();
    stack.print();
    stack.pop();
    stack.print();
    return 0;
}
