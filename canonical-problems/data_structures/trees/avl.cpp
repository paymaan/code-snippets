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
        , height(-1) // by default, node is nullptr, which
                     // has height -1
        , left(a_left)
        , right(a_right) {}
    int key;
    int height;
    shared_ptr<Node> left;
    shared_ptr<Node> right;
};

/// AVL tree is a kind of a BST tree
/// It's a superset of BST in terms of functionality
/// It maintains BST invariant and AVL invariant that
/// for every node, left subtree height and right subtree
/// height differ by at most 1. That's why we store the
/// height at every node.
/// AVL is basically a self balancing BST.
/// The following methods were not implemented because
/// they are the same as BST:
/// search, find_min, find_max, find_next_larger,
/// find_prev_smaller, height
class AVLTree {
  public:
    AVLTree()
        : m_root(nullptr) {}

    void insert(const int val) {}

    std::vector<int> sorted_list() const {
      return {};
    }

  private:
    shared_ptr<Node> m_root;
};

int main() {
    return 0;
}
