/// This is just a prototype and is not meant for
/// production use
/// I'm just playing around and creating some common data
/// structures

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std; // not recommended obviously but saves
                     // some keystrokes for now :)

/// TrieNode
class Node {
  public:
    Node()
        : children()
        , end_of_word(false) {}
    unordered_map<char, shared_ptr<Node>> children;
    bool end_of_word;
};

class Trie {
  public:
    Trie()
        : m_root(make_shared<Node>()) {}

    /// Time: O(L) where L = s.size()
    /// For n words, time is O(n * L) where
    /// L is the average size of input words/strings
    void insert(const std::string& s) {
        auto ptr = m_root;
        for (int i = 0; i < s.size(); ++i) {
            const auto c = s[i];
            const bool is_child = ptr->children.find(c) !=
                                  ptr->children.end();
            if (is_child) {
                ptr = ptr->children[c];
            } else {
                ptr->children[c] = make_shared<Node>();
                ptr = ptr->children[c];
                if (i == s.size() - 1)
                    ptr->end_of_word = true;
            }
        }
    }

    /// O(L) where L = prefix.size()
    /// Doesn't return true or false, but
    /// Returns pointer to child node (after prefix)
    /// Else returns null if prefix not found
    shared_ptr<Node>
    prefix_search(const std::string& prefix) const {
        auto ptr = m_root;
        for (const auto c : prefix) {
            const bool is_child = ptr->children.find(c) !=
                                  ptr->children.end();
            if (!is_child)
                return nullptr;
            ptr = ptr->children[c];
        }
        return ptr;
    }

    /// Similar to prefix_search but extra constraint
    /// that we must have end_of_word == true
    /// O(L) where L = word.size()
    bool word_search(const std::string& word) const {
        const auto ptr = prefix_search(word);
        return ptr ? ptr->end_of_word : false;
    }

    /// Given a prefix, list all words with that prefix
    vector<string> list_words(const std::string& prefix) {
        vector<string> list;
        const auto ptr = prefix_search(prefix);
        if (!ptr)
            return list;
        list_words_helper(ptr, list, prefix, "");
        return list;
    }

  private:
    void list_words_helper(const shared_ptr<Node>& root,
                           vector<string>& list,
                           const std::string& prefix,
                           const std::string& temp) {
        // keep adding complete words while traversing
        // the tree
        if (root->end_of_word) {
            list.push_back(prefix + temp);
        }
        const auto children = root->children;
        // base case is when children is empty
        // no need to explicitly say that because
        // loop will just not run in that case
        for (const auto child : children) {
            list_words_helper(child.second, list, prefix,
                              temp + child.first);
        }
    }
    shared_ptr<Node> const m_root;
};

int main() {
    // Output:
    // abc prefix found
    // abcd prefix found
    // m prefix not found

    // abc word found
    // abcd word not found
    // lmn word found
    // xyz word not found

    // words with "ab" as prefix:
    // abc
    // abcde
    // abgl
    Trie trie;
    trie.insert("abc");
    trie.insert("abgl");
    trie.insert("cdf");
    trie.insert("abcde");
    trie.insert("lmn");

    if (trie.prefix_search("abc"))
        cout << "abc prefix found" << endl;
    if (trie.prefix_search("abcd"))
        cout << "abcd prefix found" << endl;
    if (!trie.prefix_search("m"))
        cout << "m prefix not found" << endl;
    cout << endl;
    if (trie.word_search("abc"))
        cout << "abc word found" << endl;
    if (!trie.word_search("abcd"))
        cout << "abcd word not found" << endl;
    if (trie.word_search("lmn"))
        cout << "lmn word found" << endl;
    if (!trie.word_search("xyz"))
        cout << "xyz word not found" << endl;
    cout << endl;
    const auto words = trie.list_words("ab");
    cout << "words with \"ab\" as prefix:" << endl;
    for (const auto word : words)
        cout << word << endl;

    return 0;
}
