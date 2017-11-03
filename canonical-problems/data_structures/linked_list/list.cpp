/// This is just a prototype and is not meant for
/// prodduction use
/// I'm just playing around and creating some common data
/// structures

#include <iostream>
#include <memory>

using namespace std; // not recommended obviously but saves
                     // some keystrokes for now :)

class ListNode {
  public:
    ListNode(int x)
        : value(x)
        , next(nullptr) {}
    int value;
    shared_ptr<ListNode> next;
};

class List {
  public:
    List()
        : head(nullptr)
        , tail(nullptr)
        , length(0) {}

    void push_back(int x) {
        if (empty()) {
            head = make_shared<ListNode>(x);
            tail = head;
        } else {
            tail->next = make_shared<ListNode>(x);
            tail = tail->next;
        }
        ++length;
    }

    void push_front(int x) {
        if (empty()) {
            head = make_shared<ListNode>(x);
            tail = head;
        } else {
            auto temp_head = head;
            head = make_shared<ListNode>(x);
            head->next = temp_head;
        }
	++length;
    }

    void pop_back() {}

    void pop_front() {}

    bool empty() {
        return length == 0;
    }

    size_t size() {
        return length;
    }

    void print() {
        while (head) {
            // print current node's value
            cout << head->value;
            const bool last_node = !head->next;
            if (!last_node)
                cout << " -> ";
            // move head to next node
            head = head->next;
        }
        cout << "\n";
    }

  private:
    shared_ptr<ListNode> head;
    shared_ptr<ListNode> tail;
    size_t length;
};

int main() {
    List list;
    list.push_back(5);
    list.push_back(15);
    list.push_back(25);
    list.push_front(30);
    list.push_front(45);
    list.push_back(50);
    list.print();
    cout << "size: " << list.size() << "\n";
    return 0;
}
