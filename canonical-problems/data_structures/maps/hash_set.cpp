/// This is just a prototype and is not meant for
/// production use
/// I'm just playing around and creating some common data
/// structures

#include "../linked_list/list.hpp"
#include <iostream>
#include <memory>

using namespace std; // not recommended obviously but saves
                     // some keystrokes for now :)

template <typename T>
class HashSet {
  public:
    void insert(T key) {}

    void remove(T key) {}

    bool empty() const {
        return false;
    }

    size_t size() const {
        return 0;
    }

    bool exists(T key) const {
        return true;
    }

  private:
};

int main() {
    cout << "to start\n";
    return 0;
}
