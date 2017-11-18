/// This is just a prototype and is not meant for
/// production use
/// I'm just playing around and creating some common data
/// structures

#include <forward_list>
#include <iostream>
#include <vector>

using namespace std; // not recommended obviously but saves
                     // some keystrokes for now :)

/// Hash set implementation
/// Chaining for hash collisions
/// Using singly linked list for chaining
/// instead of dynamic array (vector) because
/// linked lists can be useful when copying
/// hash set objects.. plus vector also will resize
/// so it's not as performant as linked list.. it does
/// have O(1) direct access but we don't need it.
template <typename T> class HashSet {
  public:
    HashSet()
        : m(100)
        , n(0)
        , buckets(m) {}

    void insert(T key) {
        auto& chain = buckets[hash(key)];
        // if key exists, return early to avoid duplicates
        for (const auto& e : chain) {
            if (e == key)
                return;
        }
        chain.push_front(key);
        ++n;
    }

    void remove(T key) {
        auto& chain = buckets[hash(key)];
        typename forward_list<T>::iterator prev =
            chain.before_begin();
        for (auto it = chain.begin(); it != chain.end();
             ++it) {
            if (*it == key) {
                chain.erase_after(prev);
                --n;
                return;
            }
            prev = it;
        }
    }

    bool empty() const {
        return n == 0;
    }

    size_t size() const {
        return n;
    }

    bool exists(T key) const {
        for (const auto& e : buckets[hash(key)]) {
            if (e == key)
                return true;
        }
        return false;
    }

    double load_factor() const {
        return double(n) / double(m);
    }

  private:
    int hash(T key) const {
        // k % m would produce a hash in range [0, m - 1]
        // which fits with our buckets indices
        return key % m;
    }

    int m;    // # of buckets
    size_t n; // size
    vector<forward_list<T>> buckets;
};

int main() {
    HashSet<int> set;
    set.insert(2);
    set.insert(4);
    set.insert(2);
    set.insert(5);
    set.insert(17);
    set.insert(5);

    cout << "size: " << set.size() << endl;
    cout << "load factor: " << set.load_factor() << endl;

    if (set.exists(5))
        cout << "5 exists in set" << endl;
    if (!set.exists(10))
        cout << "10 does not exist in set" << endl;
    if (set.exists(17))
        cout << "17 exists in set" << endl;

    cout << endl;

    set.remove(2);
    set.remove(5);

    cout << "size: " << set.size() << endl;
    cout << "load factor: " << set.load_factor() << endl;

    if (!set.exists(5))
        cout << "5 does not exist in set" << endl;
    if (!set.exists(2))
        cout << "2 does not exist in set" << endl;

    return 0;
}
