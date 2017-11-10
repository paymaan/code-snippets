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

/// SharedPtr is a smart pointer that takes care of
/// memory management of its underyling memory.
/// Multiple SharedPtr's can point to the same memory.
/// When no SharedPtr points at that piece of memory,
/// that memory is deallocated/freed.
/// Another similar COW smart pointer can be found here:
/// https://github.com/HadrienG2/copy-on-write-ptr
template <typename T> class SharedPtr {
  public:
    SharedPtr(T* raw_ptr)
        : m_ref_count(0)
        , m_raw_ptr(raw_ptr) {
        assert(m_raw_ptr);
        increment_ref_count(1);
    }

    ~SharedPtr() {
        decrement_ref_count(1);
	cout << m_ref_count << endl;
        if (m_ref_count == 0)
            delete m_raw_ptr;
    }

    SharedPtr(SharedPtr<T>& other)
        : SharedPtr(other.get_raw_ptr()) {
        this->increment_ref_count(other.get_ref_count());
        other.increment_ref_count(1);
    }

    SharedPtr<T>& operator=(const SharedPtr<T>&) = delete;

    T& operator*() {
        assert(m_raw_ptr);
        return *m_raw_ptr;
    }

    T* operator->() {
        assert(m_raw_ptr);
        return m_raw_ptr;
    }

  private:
    int m_ref_count;
    T* m_raw_ptr;

    T* get_raw_ptr() {
        return m_raw_ptr;
    }

    inline void increment_ref_count(const int i) {
        m_ref_count += i;
    }

    inline void decrement_ref_count(const int i) {
        m_ref_count -= i;
    }

    inline int get_ref_count() const {
        return m_ref_count;
    }
};

static void print(const vector<int>& vec) {
    for (const auto& e : vec)
        cout << e << " ";
    cout << "\n";
}

int main() {
    SharedPtr<vector<int>> ptr1(
        new vector<int>({45, 55, 65}));
    print(*ptr1);
    ptr1->push_back(75);
    print(*ptr1);

    SharedPtr<vector<int>> ptr2(ptr1);
    ptr2->push_back(85);
    print(*ptr2);

    SharedPtr<vector<int>> ptr3(ptr2);
    ptr3->push_back(95);
    print(*ptr3);
    
    return 0;
}
