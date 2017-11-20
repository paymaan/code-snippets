#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

void print(const vector<int>& vec) {
    for (auto e : vec)
        cout << e << " ";
    cout << endl;
}

template <typename T>
void swap(vector<T>& A, size_t i, size_t j) {
    assert(i >= 0 && i < A.size() && j >= 0 &&
           j < A.size());
    const T temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

/// Binary Heap (Max) Implementation
/// Max heap
/// Heap invariant: Every parent node's key
/// is >= all of its children keys
/// n = # of nodes in heap
/// Not a BST! So search is not O(log(n))
/// Just a binary tree (nearly complete)
/// implemented as an array.
template <typename T> class BinaryHeap {
  public:
    BinaryHeap(vector<T> A) {
        build_max_heap(A);
        heap = A;
    }

    /// Assume that tree rooted at left(i) and right(i)
    /// are max heaps. If heap[i] violates max heap
    /// invariant,
    /// max_heapify(i) fixes that.
    /// O(h) time but h = log(n) for heaps, so:
    /// O(log(n)) operation where n = heap.size()
    /// After max_heapify(i), tree rooted at i will
    /// be a max heap (and all of its child subtrees
    /// by definition).
    /// Heapify A[i, j]
    static void max_heapify(vector<T>& A, const size_t i,
                            const size_t j) {
        assert(i >= 0 && i < A.size() && j >= 0 &&
               j < A.size());
        const size_t left_child_idx = left_idx(i);
        const size_t right_child_idx = right_idx(i);
        // if any index is larger than j, return
        if (max(i, max(left_child_idx, right_child_idx)) >
            j)
            return;
        size_t largest_idx = i;
        if (left_child_idx < A.size() &&
            A[left_child_idx] > A[i])
            largest_idx = left_child_idx;
        if (right_child_idx < A.size() &&
            A[right_child_idx] > A[largest_idx])
            largest_idx = right_child_idx;
        if (largest_idx != i) {
            swap(A, i, largest_idx);
            // call max_heapify downwards in the tree
            max_heapify(A, largest_idx, j);
        }
    }

    /// Converts given array to a valid
    /// binary max heap
    /// i.e. converts A[0,...,n-1] to a max heap
    /// Naive time analysis: O(n * log(n))
    /// since O(n) calls to max_heapify
    /// But tighter upper bound is actually O(n)
    /// See
    /// http://www.cs.umd.edu/~meesh/351/mount/lectures/lect14-heapsort-analysis-part.pdf
    static void build_max_heap(vector<T>& A) {
        const int n = A.size();
        for (int i = (n / 2) - 1; i >= 0; --i) {
            max_heapify(A, i, A.size() - 1);
        }
    }

    /// O(log(n)) in time
    void insert(const T val) {
        heap.push_back(numeric_limits<T>::lowest());
        increase_val(heap.size() - 1, val);
    }

    /// O(1) time
    bool empty() const {
        return heap.empty();
    }

    /// O(1) time
    T max_elem() const {
        assert(!heap.empty());
        return heap[0];
    }

    /// O(1) time
    size_t num_elems() const {
        return heap.size();
    }

  private:
    /// O(log(n)) in time
    /// Update the value at index i to a new
    /// greater value, val.
    void increase_val(size_t i, const T val) {
        assert(i >= 0 && i < heap.size());
        assert(val >= heap[i]);
        heap[i] = val;
        if (i <= 0)
            return;
        /// keep pushing the value to the parent
        /// if needed
        while (i >= 1 && heap[parent_idx(i)] < heap[i]) {
            swap(heap, i, parent_idx(i));
            // go to parent upwards
            i = parent_idx(i);
        }
    }

    static size_t parent_idx(const size_t child_idx) {
        return (child_idx - 1) / 2;
    }

    static size_t left_idx(const size_t parent_idx) {
        return 2 * parent_idx + 1;
    }

    static size_t right_idx(const size_t parent_idx) {
        return left_idx(parent_idx) + 1;
    }

    /// root is at i = 0
    /// parent(i) = floor((i - 1) / 2)
    /// left(i) = 2i + 1
    /// right(i) = 2i + 2
    /// left to right of this array === BFS of binary tree
    vector<T> heap;
};

/// Worst case: O(n * log(n))
/// In-place sort unlike merge sort (and like insertion
/// sort)
/// Best of both algorithms!
/// See heap sort:
/// https://www.cs.bgu.ac.il/~ds122/wiki.files/Presentation09.pdf
void heap_sort(vector<int>& A) {
    BinaryHeap<int>::build_max_heap(A);
    for (int i = A.size() - 1; i >= 1; --i) {
        swap(A, 0, i);
        // max heapify on the rest of the array
        // since invariant possibly broken there
        BinaryHeap<int>::max_heapify(A, 0, i - 1);
    }
}

int main() {
    // Binary heap
    // Output:
    // max elem: 76
    // size: 11
    BinaryHeap<int> bh({});
    bh.insert(5);
    bh.insert(15);
    bh.insert(20);
    bh.insert(25);
    bh.insert(3);
    bh.insert(17);
    bh.insert(76);
    bh.insert(50);
    bh.insert(33);
    bh.insert(14);
    bh.insert(23);
    cout << "max elem: " << bh.max_elem() << endl;
    cout << "size: " << bh.num_elems() << endl;

    // Heap sort
    // Output:
    // 1 3 4 5 8 10
    vector<int> A = {5, 3, 10, 4, 8, 1};
    heap_sort(A);
    print(A);
    return 0;
}
