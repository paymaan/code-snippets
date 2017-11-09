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
    UniquePtr(T* raw_ptr = nullptr)
        : m_raw_ptr(raw_ptr) {}

    ~UniquePtr() {
        if (m_raw_ptr)
            delete m_raw_ptr;
    }

    // copy ctor
    // UniquePtr can never be copied because of
    // "one owner" semantic
    UniquePtr(const UniquePtr<T>&) = delete;

    // copy assignment operator
    // UniquePtr can never be assigned to another
    // UniquePtr because of "one owner" semantic
    UniquePtr<T>& operator=(const UniquePtr<T>&) = delete;

    T& operator*() {
        assert(m_raw_ptr);
        return *m_raw_ptr;
    }

    T* operator->() {
        assert(m_raw_ptr);
        return m_raw_ptr;
    }

    void grant_ownership(UniquePtr<T>& to) {
        to.set_raw_ptr(m_raw_ptr);
	m_raw_ptr = nullptr;
    }

  private:
    T* m_raw_ptr;

    void set_raw_ptr(T* raw_ptr) {
        m_raw_ptr = raw_ptr;
    }
};

static void print(const vector<int>& vec) {
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
    print(*ptr2);

    // Outputs
    // Transfer ownership from ptr2 to ptr3
    UniquePtr<vector<int>> ptr3;
    ptr2.grant_ownership(ptr3);
    ptr3->push_back(121);
    print(*ptr3);

    return 0;
}
