/// This is just a prototype and is not meant for
/// prodduction use
/// I'm just playing around and creating some common data
/// structures

#include "../linked_list/list.hpp"
#include <iostream>
#include <memory>

using namespace std; // not recommended obviously but saves
                     // some keystrokes for now :)

/// Queue is a FIFO or LILO data structure
/// All operations here are O(1) time unless stated
/// otherwise
/// This implementation uses a linked list for dnyamic stack
/// "list" is the linked list here
class Queue {
  public:
    Queue()
        : list(make_unique<List>()) {}

    bool empty() const {
        return list->empty();
    }

    size_t size() const {
        return list->size();
    }

    void push(int x) {
        list->push_back(x);
    }

    void pop() {
        list->pop_front();
    }

    void print() const {
        list->print(", ");
        cout << "\n";
    }

    int front() const {
        return list->head_value();
    }

    int back() const {
        return list->tail_value();
    }

  private:
    unique_ptr<List> list;
};

int main() {
    // Output:
    //    5, 10, 15

    //    10, 15

    //    10, 15, 2, 4

    //    2, 4

    //    4
    Queue queue;
    queue.push(5);
    queue.push(10);
    queue.push(15);
    queue.print();
    queue.pop();
    queue.print();
    queue.push(2);
    queue.push(4);
    queue.print();
    queue.pop();
    queue.pop();
    queue.print();
    queue.pop();
    queue.print();
    return 0;
}
