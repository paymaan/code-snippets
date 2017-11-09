/// This is just a prototype and is not meant for
/// prodduction use
/// I'm just playing around and creating some common data
/// structures

#include <cassert>
#include <iostream>
#include <new>
#include <vector>

using namespace std; // not recommended obviously but saves
                     // some keystrokes for now :)

/// UniquePtr is a wrapper around raw C++ pointer
/// UniquePtr does memory management of the raw C++ pointer
/// it points to.
/// The raw memory is "owned" by the UniquePtr only i.e.
/// no one else can point to this memory, atleast through
/// the UniquePtr interface
/// When UniquePtr object goes out of scope, we
/// deallocate/free
/// the pointed memory (pointee).
/// Clients can also "move" the ownership of the raw memory
/// from one UniquePtr object to another.
/// As of now, UniquePtr can only point to a pointer, not a
/// pointer array (new [])
/// Clients should only instantiate UniquePtr like so:
/// UniquePtr ptr(new T(T args));
template <typename T> class UniquePtr {
  public:
    UniquePtr(T* raw_ptr)
        : m_raw_ptr(raw_ptr) {
        // clients must provide a non-null pointer.
        assert(raw_ptr);
    }

    ~UniquePtr() {
        delete m_raw_ptr;
    }

    T& operator*() {
        return *m_raw_ptr;
    }

    T* operator->() {
        return m_raw_ptr;
    }

  private:
    T* m_raw_ptr;
};

void print(const vector<int>& vec) {
    for (const auto& e : vec)
        cout << e << " ";
    cout << "\n";
}

int main() {
    // Outputs "42"
    UniquePtr<int> ptr(new int(42));
    cout << *ptr << endl;

    // Outputs "42 23 77 99"
    UniquePtr<vector<int>> ptr2(
        new vector<int>({42, 23, 77}));
    ptr2->push_back(99);
    auto& vec = *ptr2;
    print(vec);

    return 0;
}
