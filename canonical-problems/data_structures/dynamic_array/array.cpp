/// This is just a prototype and is not meant for
/// prodduction use
/// I'm just playing around and creating some common data
/// structures

#include <cassert>
#include <iostream>
#include <memory>
#include <new>

using namespace std; // not recommended obviously but saves
                     // some keystrokes for now :)

/// Dynamic array is an array allocated  on the heap that
/// is laid down contiguously in memory (invariant)
/// It's sort of like std::vector in C++ STL
/// It's size is dynamically modified (expanded and shrunk) at runtime
/// In the future, I should also implement a toy SmallVector
/// which
/// switches between allocation on stack and heap for
/// performance reasons.
/// All operations are O(1) unless otherwise stated
/// !=, ==, cout can be implemented further
template <typename T> class DynamicArray {
  public:
    DynamicArray(const size_t init_capacity = 5)
        : m_capacity(init_capacity)
        , m_size(0)
        , m_growth_factor(2)
        , m_ptr(make_unique<T[]>(init_capacity)) {
        throw_bad_alloc_if_needed();
    }

    bool empty() const {
        return size() == 0;
    }

    inline size_t size() const {
        return m_size;
    }

    // pushes at end/back
    // amortized O(1)
    void push(const T& x) {
        expand_if_needed();
        m_ptr[size()] = x;
        ++m_size;
    }

    // removes the last element
    // amortized O(1)
    void pop() {
        shrink_if_needed();
        --m_size;
    }

    void print() const {
        for (size_t i = 0; i < size(); ++i)
            cout << m_ptr[i] << " ";
        cout << "\n";
    }

    // element access
    // possible call sites for accessing element:
    // cout << arr[12] << endl;
    // cout << arr.operator[](12) << endl;
    // this method has no bounds check
    T& operator[](const size_t idx) {
        return m_ptr[idx];
    }

    // element update
    // possible call sites for updating element:
    // arr[12] = 54;
    // arr.operator[](12) = 54;
    // this method has no bounds check
    const T& operator[](const size_t idx) const {
        return m_ptr[idx];
    }

  private:
    size_t m_capacity; // capacity of block
    size_t m_size;     // number of elements in the block;
                       // size <= capacity
    uint8_t m_growth_factor;
    unique_ptr<T[]> m_ptr; // pointer to block of memory

    void expand_if_needed() {
        if (size() == m_capacity) {
            const size_t new_capacity =
                m_capacity * m_growth_factor;
            reallocate(new_capacity);
            // update capacity
            m_capacity = new_capacity;
        }
    }

    /// The shrinking is not optimal for now.
    /// It is easily susceptible to abrupt growing
    /// even if one element is added immediately after a
    /// shrink.
    void shrink_if_needed() {
        if (size() == m_capacity / m_growth_factor) {
            const size_t new_capacity =
                m_capacity / m_growth_factor;
            reallocate(new_capacity);
            // update capacity
            m_capacity = new_capacity;
        }
    }

    void reallocate(const size_t new_capacity) {
        // move ownership to a temp ptr for copying later
        auto temp_ptr = move(m_ptr);
        // allocate expanded memory
        m_ptr = make_unique<T[]>(new_capacity);
        // check if allocation was successful
        throw_bad_alloc_if_needed();
        // copy over previous values to new memory
        assert(size() <= new_capacity);
        for (size_t i = 0; i < size(); ++i)
            m_ptr[i] = temp_ptr[i];
    }

    void throw_bad_alloc_if_needed() {
        if (!m_ptr)
            throw bad_alloc();
    }
};

int main() {
    // Output:
    // 13
    // 1 2 3 574 5 6 7 8 9 10
    try {
        DynamicArray<int> arr;
        for (int i = 1; i <= 150; ++i)
            arr.push(i);
        cout << arr[12] << endl;
        arr[3] = 574;
        for (int i = 0; i < 140; ++i)
            arr.pop();
        arr.print();
    } catch (const bad_alloc& e) {
        cout << "Allocation failed: " << e.what() << "\n";
    }
    return 0;
}
