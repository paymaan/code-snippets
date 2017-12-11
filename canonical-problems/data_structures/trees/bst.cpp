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
         shared_ptr<Node> a_right = nullptr)
        : key(a_key)
        , left(a_left)
        , right(a_right) {}
    int key;
    shared_ptr<Node> left;
    shared_ptr<Node> right;
};

/// BST implementation
/// All operations are O(h) unless stated otherwise
/// h is the height of the tree
/// h is "n" in the worst case but
/// "log(n)' on average.
class BinarySearchTree {
  public:
    BinarySearchTree()
        : m_root(nullptr) {}

    void insert(const int val) {
        // if there is no root, create one
        if (!m_root) {
            m_root = make_shared<Node>(val);
            return;
        }
        return insert_helper(m_root, val);
    }

    shared_ptr<Node> search(const int val) const {
        return search_helper(m_root, val);
    }

    shared_ptr<Node> find_min() const {
        return find_min_helper(m_root);
    }

    shared_ptr<Node> find_max() const {
        return find_max_helper(m_root);
    }

    // Value based, finds next large "val" in the tree
    // Note that a key of provided val must be in the tree
    // e.g. for 14 15 15 15 17 with key = 15, this would
    // return 17
    // Otherwise this returns nullptr
    shared_ptr<Node> find_next_larger(const int val) const {
        if (const auto n = search(val))
            return n->right;
        return nullptr;
    }

    // Similar to find_next_larger.. also value based
    // e.g. for 14 15 15 15 17 with key = 15, this would
    // return 14
    shared_ptr<Node>
    find_prev_smaller(const int val) const {
        if (auto n = search(val)) {
            // Our invariant (based on insertion) is:
            // left sub tree has <= (less equal) elements
            // right sub tree has > (greater) elements
            // so to avoid duplicates, we go further left if
            // needed.. because of this, we also need
            // to go right in the left subtree to find
            // largest smallest element
            // 1. Go all the way to the left
            while (n && n->left && n->left->key == val)
                n = n->left;
            // 2. Go all the way right in the left subtree
            if ((n = n->left)) {
                while (n->right && n->right->key < val)
                    n = n->right;
            }
            return n;
        }
        return nullptr;
    }

    /// Height of node = length (# edges) of longest
    /// downward
    /// path to a leaf
    /// Leaf has a height of 0 by definition
    /// h(node) = max(h(left_subtree), h(right_subtree)) + 1
    /// Same logic for generic binary tree, have to visit
    /// all nodes to calculate height
    int height() const {
        return height_helper(m_root);
    }

    /// just an inorder traversal (depth first)
    vector<int> sorted_list() const {
        vector<int> sorted;
        sorted_list_helper(m_root, sorted);
        return sorted;
    }

  private:
    void insert_helper(shared_ptr<Node>& root,
                       const int val) {
        if (!root) {
            root = make_shared<Node>(val);
            return;
        }
        if (val <= root->key) {
            insert_helper(root->left, val);
        } else { // val > root->key
            insert_helper(root->right, val);
        }
    }

    shared_ptr<Node>
    search_helper(const shared_ptr<Node>& root,
                  const int val) const {
        if (!root)
            return nullptr;

        if (val < root->key) {
            return search_helper(root->left, val);
        } else if (val > root->key) {
            return search_helper(root->right, val);
        } else { // val == root->key
            return root;
        }
    }

    shared_ptr<Node>
    find_min_helper(const shared_ptr<Node>& root) const {
        if (!root || !root->left)
            return root;
        return find_min_helper(root->left);
    }

    shared_ptr<Node>
    find_max_helper(const shared_ptr<Node>& root) const {
        if (!root || !root->right)
            return root;
        return find_max_helper(root->right);
    }

    /// We recurse till the very end i.e. one step next to
    /// leaf when we reach null.. at this point, we return
    /// -1, so that in the prev stack frame, the height of
    /// leaf comes out to be (-1) + 1 = 0
    /// https://stackoverflow.com/questions/19202692/complexity-for-the-function-maxheight-in-a-binary-tree
    /// Time: O(n) where n is the number of nodes in the
    /// tree
    /// Space: O(h) since stack is bound by height of tree
    int height_helper(const shared_ptr<Node>& root) const {
        if (!root)
            return -1;
        return max(height_helper(root->left),
                   height_helper(root->right)) +
               1;
    }

    /// just an inorder traversal (depth first)
    void sorted_list_helper(const shared_ptr<Node>& root,
                            vector<int>& sorted) const {
        if (!root)
            return;
        sorted_list_helper(root->left, sorted);
        sorted.push_back(root->key);
        sorted_list_helper(root->right, sorted);
    }

    shared_ptr<Node> m_root;
};

void print(const vector<int>& list) {
    for (auto e : list)
        cout << e << " ";
    cout << "\n";
}

/// prints preorder sequence of tree rooted
/// at given root.
void print(const shared_ptr<Node> root) {
    if (!root)
        return;
    cout << root->key << " ";
    print(root->left);
    print(root->right);
}

namespace problems {
    int get_transition_idx(const vector<int>& preorder,
                           const int start, const int end) {
        for (int i = start + 1; i <= end; ++i) {
            if (preorder[i] > preorder[start])
                return i;
        }
        return -1;
    }
    shared_ptr<Node>
    reconstruct_bst_helper(const vector<int>& preorder,
                           const int start, const int end) {
        if (start < 0 || start > preorder.size() - 1 ||
            start > end)
            return nullptr;
        auto root = make_shared<Node>(preorder[start]);
        const int transition_idx =
            get_transition_idx(preorder, start, end);
        root->left = reconstruct_bst_helper(
            preorder, start + 1, transition_idx - 1);
        root->right = reconstruct_bst_helper(
            preorder, transition_idx, end);
        return root;
    }
    shared_ptr<Node>
    reconstruct_bst(const vector<int>& preorder) {
        if (preorder.empty())
            return nullptr;
        return reconstruct_bst_helper(preorder, 0,
                                      preorder.size() - 1);
    }
}

int main() {
    // Output:
    // height: 6
    // found: 27
    // min: 2
    // max: 25
    // Next larger to 15: 17
    // Prev smaller to 15: 14
    // 2 2 5 5 7 14 14 15 15 15 15 17 27 27 35 35
    // preorder sequence: 43 23 27 29 31 41 47 53

    BinarySearchTree bst;
    bst.insert(5);
    bst.insert(5);
    bst.insert(15);
    bst.insert(15);
    bst.insert(2);
    bst.insert(7);
    bst.insert(14);
    bst.insert(15);
    bst.insert(17);
    bst.insert(15);
    bst.insert(35);
    bst.insert(27);
    bst.insert(2);
    bst.insert(35);
    bst.insert(14);
    bst.insert(27);

    cout << "height: " << bst.height() << endl;

    if (const auto n = bst.search(27))
        cout << "found: " << n->key << endl;

    if (const auto n = bst.find_min())
        cout << "min: " << n->key << endl;

    if (const auto n = bst.find_max())
        cout << "max: " << n->key << endl;

    if (const auto n = bst.find_next_larger(15))
        cout << "Next larger to 15: " << n->key << endl;

    if (const auto n = bst.find_prev_smaller(15))
        cout << "Prev smaller to 15: " << n->key << endl;

    const auto sorted_list = bst.sorted_list();
    print(sorted_list);

    // misc problems
    using namespace problems;
    const vector<int> preorder = {43, 23, 27, 29,
                                  31, 41, 47, 53};
    cout << "preorder sequence: ";
    if (const auto n = reconstruct_bst(preorder))
        print(n);
    cout << endl;

    return 0;
}
