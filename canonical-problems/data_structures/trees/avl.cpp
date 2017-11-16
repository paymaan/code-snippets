/// This is just a prototype and is not meant for
/// prodduction use
/// I'm just playing around and creating some common data
/// structures

#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

using namespace std; // not recommended obviously but saves
                     // some keystrokes for now :)

class Node {
  public:
    Node(int a_key, shared_ptr<Node> a_left = nullptr,
         shared_ptr<Node> a_right = nullptr,
         shared_ptr<Node> a_parent = nullptr)
        : key(a_key)
        , height(-1) // by default, node is nullptr, which
                     // has height -1
        , left(a_left)
        , right(a_right)
        , parent(a_parent) {}
    int key;
    int height;
    shared_ptr<Node> left;
    shared_ptr<Node> right;
    shared_ptr<Node> parent;
};

void print(const vector<int>& list) {
    for (auto e : list)
        cout << e << " ";
    cout << "\n";
}

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

    void insert(const int val) {
        auto n = bst_insert(val);
        rebalance(n);
    }

    vector<int> sorted_list() const {
        vector<int> sorted;
        sorted_list_helper(m_root, sorted);
        return sorted;
    }

    int height() const {
        return height_helper(m_root);
    }

  private:
    void sorted_list_helper(const shared_ptr<Node>& root,
                            vector<int>& sorted) const {
        if (!root)
            return;
        sorted_list_helper(root->left, sorted);
        sorted.push_back(root->key);
        sorted_list_helper(root->right, sorted);
    }

    int height_helper(const shared_ptr<Node>& n) const {
        if (!n)
            return -1;
        return n->height;
    }

    void update_height(const shared_ptr<Node>& n) {
        if (!n)
            return;
        n->height = max(height_helper(n->left),
                        height_helper(n->right)) +
                    1;
    }

    shared_ptr<Node> bst_insert(const int val) {
        // if there is no root, create one
        if (!m_root) {
            m_root = make_shared<Node>(val);
            return m_root;
        }
        return bst_insert_helper(m_root, m_root->parent,
                                 val);
    }

    shared_ptr<Node>
    bst_insert_helper(shared_ptr<Node>& root,
                      shared_ptr<Node>& parent,
                      const int val) {
        if (!root) {
            root = make_shared<Node>(val);
            root->parent = parent;
            return root;
        }
        if (val <= root->key) {
            return bst_insert_helper(root->left, root, val);
        } else { // val > root->key
            return bst_insert_helper(root->right, root,
                                     val);
        }
    }

    void rebalance(shared_ptr<Node>& given_node) {
        shared_ptr<Node> n = given_node;
        while (n) {
            // update height
            update_height(n);
            // actual rebalance by rotation
            const int balance = height_helper(n->right) -
                                height_helper(n->left);
            if (balance >= 2) { // right heavy
                if (height_helper(n->right->right) >=
                    height_helper(
                        n->right->left)) { // right-right
                    left_rotate(n);
                } else { // right-left
                    right_rotate(n->right);
                    left_rotate(n);
                }
            } else if (balance <= -2) { // left heavy
                if (height_helper(n->left->left) >=
                    height_helper(
                        n->left->right)) { // left-left
                    right_rotate(n);
                } else { // left-right
                    left_rotate(n->left);
                    right_rotate(n);
                }
            }

            // go upwards from n
            n = n->parent;
        }
    }

    /// For rotate, we don't change "x" and "y" pointers
    /// since that would complicate parent relantionship
    /// between
    /// "x" and "y" pointee objects as well as to the
    /// outisde tree.
    /// A better way is to just treat the pointee objects as
    /// the same,
    /// change their left and right pointers, and at the
    /// end, swap key values.
    /// We also need to change the parent relationships of
    /// pointee children themselves
    /// i.e. A,B,C in 6.006 notes.
    void left_rotate(shared_ptr<Node>& x) {
        if (x && x->right) {
            auto y = x->right;
            // keep pointers i.e. x and y same but
            // change pointee objects left and right
            // pointers
            x->right = y->right;
            y->right = y->left;
            y->left = x->left;
            x->left = y;
            // swap keys
            int temp = y->key;
            y->key = x->key;
            x->key = temp;
            // update A,B,C parents
            if (y->left)
                y->left->parent = y;
            if (x->right)
                x->right->parent = x;
        }
    }

    /// Similar to left_rotate above
    void right_rotate(shared_ptr<Node>& y) {
        if (y && y->left) {
            auto x = y->left;

            y->left = x->left;
            x->left = x->right;
            x->right = y->right;
            y->right = x;

            int temp = y->key;
            y->key = x->key;
            x->key = temp;

            if (y->left)
                y->left->parent = y;
            if (x->right)
                x->right->parent = x;
        }
    }

    shared_ptr<Node> m_root;
};

int main() {
    // Output:
    // height: 4
    // 2 3 5 7 14 15 17 27 35 47 58
    AVLTree avl;

    avl.insert(5);
    avl.insert(15);
    avl.insert(2);
    avl.insert(7);
    avl.insert(14);
    avl.insert(17);
    avl.insert(35);
    avl.insert(27);
    avl.insert(3);
    avl.insert(47);
    avl.insert(58);

    cout << "height: " << avl.height() << endl;
    print(avl.sorted_list());

    return 0;
}
