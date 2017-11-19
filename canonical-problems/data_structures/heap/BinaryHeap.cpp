#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

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
    void max_heapify(const size_t i) {
        max_heapify_helper(heap, i, heap.size() - 1);
    }

    /// Heapify A[i, j]
    static void max_heapify_helper(vector<T>& A,
                                   const size_t i,
                                   const size_t j) {
        assert(i >= 0 && i < A.size() && j >= 0 &&
               j < A.size());
        const size_t left_idx = 2 * i + 1;
        const size_t right_idx = left_idx + 1;
        // if any index is larger than j, return
        if (max(i, max(left_idx, right_idx)) > j)
            return;
        size_t largest_idx = i;
        if (left_idx < A.size() && A[left_idx] > A[i])
            largest_idx = left_idx;
        if (right_idx < A.size() &&
            A[right_idx] > A[largest_idx])
            largest_idx = right_idx;
        if (largest_idx != i) {
            // swap
            const T temp = A[i];
            A[i] = A[largest_idx];
            A[largest_idx] = temp;
            // call max_heapify downwards in the tree
            max_heapify_helper(A, largest_idx, j);
        }
    }

    /// Builds max heap from a given array
    /// i.e. converts A[0,...,n-1] to a max heap
    /// Naive time analysis: O(n * log(n))
    /// since O(n) calls to max_heapify
    /// But tighter upper bound is actually O(n)
    /// See
    /// http://www.cs.umd.edu/~meesh/351/mount/lectures/lect14-heapsort-analysis-part.pdf
    static void build_max_heap(vector<T>& A) {
        const int n = A.size();
        for (int i = (n / 2) - 1; i >= 0; --i) {
            max_heapify_helper(A, i, A.size() - 1);
        }
    }

    bool empty() const {
        return heap.empty();
    }

  private:
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
        // swap
        const int temp = A[0];
        A[0] = A[i];
        A[i] = temp;
        // max heapify on the rest of the array
        // since invariant possible broken there
        BinaryHeap<int>::max_heapify_helper(A, 0, i - 1);
    }
}

void print(const vector<int>& vec) {
    for (auto e : vec)
        cout << e << " ";
    cout << endl;
}

int main() {
    BinaryHeap<int> bh({});
    vector<int> A = {5, 3, 10, 4, 8, 1};
    heap_sort(A);
    print(A);
    return 0;
}
