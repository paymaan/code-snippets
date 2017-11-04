/// This is just a prototype and is not meant for
/// prodduction use
/// I'm just playing around and creating some common data
/// structures

#include <cassert>
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

/// Singly linked list
/// All operations here are O(1) time unless stated
/// otherwise
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

    /// O(n) but can be made O(1) if we track node before
    /// tail i.e. second last node
    void pop_back() {
        if (!empty()) {
            if (size() == 1) {
                pop_front();
                return;
            }
            auto it = head;
            // after this loop, "it" will point to second
            // last node
            while (!(it && it->next && !it->next->next))
                it = it->next;
            it->next = nullptr;
            --length;
        }
    }

    void pop_front() {
        if (!empty()) {
            head = head->next;
            --length;
        }
    }

    bool empty() const {
        return length == 0;
    }

    size_t size() const {
        return length;
    }

    void
    print(const std::string& sep = string(" -> ")) const {
        auto it = head;
        while (it) {
            // print current node's value
            cout << it->value;
            const bool last_node = !it->next;
            if (!last_node)
                cout << sep;
            // move it to next node
            it = it->next;
        }
        cout << "\n";
    }

    int head_value() const {
        assert(head);
        return head->value;
    }

    int tail_value() const {
        assert(tail);
        return tail->value;
    }

  private:
    shared_ptr<ListNode> head;
    shared_ptr<ListNode> tail;
    size_t length;
};
