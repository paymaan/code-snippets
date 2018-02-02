#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template<typename T> void print_pq(T pq) {
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << "\n";
}

void f_heap() {
    vector<int> A = {3, 7, 8, 1, 2};

    // Max heap (default)
    // prints: 8 7 3 2 1
    priority_queue<int> max_heap(A.begin(), A.end());
    print_pq(max_heap);

    // Min heap (using greater<int>)
    // prints: 1 2 3 7 8
    priority_queue<int, vector<int>, greater<int>> min_heap(A.begin(), A.end());
    print_pq(min_heap);

    // Custom comparator
    // prints: 1 2 3 7 8
    class CustomCompFnctor {
        public:
            // In heap, we want to order b and then a
            // Note order in prototype
            // For max heap, b > a
            // For min heap, b < a
            bool operator()(const int a, const int b) const {
                //return b > a; // max heap
                return b < a; // min heap
            }
    };
    priority_queue<int, vector<int>, CustomCompFnctor> my_heap(A.begin(), A.end());
    print_pq(my_heap);
}

// Multiset can be used as an alternative to priority_queue
// Advantage: has begin(), rbegin(), end, rend(), find()
void f_multiset() {
    vector<int> A = {3, 7, 8, 1, 2};

    // Basic multiset (default order is ascending)
    // prints: 1 2 3 7 8
    multiset<int> s1(A.begin(), A.end());
    print(s1);

    // Multiset (descending)
    // prints: 8 7 3 2 1
    multiset<int, greater<int>> s2(A.begin(), A.end());
    print(s2);

    // Custom comparator multiset
    // prints: 1 2 3 7 8
    class CustomCompFnctor {
        public:
            // In set/multiset, we want to order a and then b
            // Note order in prototype
            // For max heap: a > b (descending)
            // For min heap: a < b (ascending)
            bool operator()(const int a, const int b) const {
                return a < b;
            }
    };
    multiset<int, CustomCompFnctor> s3(A.begin(), A.end());
    // 3 cout's below print:
    // 1
    // 8
    // 7
    cout << *s3.begin() << endl;
    cout << *s3.rbegin() << endl;
    auto it = s3.find(7);
    if (it != s3.end()) {
        cout << *it << endl;
    }
    print(s3);
}

void f_sort() {
    vector<int> A = {3, 7, 8, 1, 2};

    // default sort (ascending)
    // prints: 1 2 3 7 8
    sort(A.begin(), A.end());
    print(A);

    // descending sort
    // prints: 8 7 3 2 1
    sort(A.begin(), A.end(), greater<int>());
    print(A);

    // sort with custom comparator
    // prints: 1 2 3 7 8
    class CustomCompFnctor {
        public:
            // For std::sort, we want to order a and then b
            // Note order in prototype
            // return a > b (descending)
            // return a < b (ascending)
            bool operator()(const int a, const int b) const {
                return a < b;
            }
    };
    sort(A.begin(), A.end(), CustomCompFnctor());
    print(A);
}

void f_vector() {
    // sort only first 3 elements in descending order
    // note: A.begin() -> index 0
    //       A.begin() + 3 -> index 3
    // Non strict range: [0, 3) == [0, 2]
    // so we sort elements 0, 1, and 2.
    // prints: 8 7 3 1 2
    vector<int> A = {3, 7, 8, 1, 2};
    sort(A.begin(), A.begin() + 3, greater<int>());
    print(A);

    // sort only last 3 elements in ascending order
    // note: A.end() -> index A.size() i.e. 1 after last index!
    //       A.end() - 3 -> index A.size() - 3
    // Non-strict range: [A.size() - 3, A.size()) == [A.size() - 3, A.size() - 1]
    // so we sort last 3 elements
    // e.g. size = 5 (index 0 to 4). We sort element at indices 2, 3, and 4.
    // prints: 3 7 1 2 8
    vector<int> B = {3, 7, 8, 1, 2};
    sort(B.end() - 3, B.end());
    print(B);

    // extract subvector; this is O(n) time where n = y - x
    // where we subvector starts from x and ends at y
    // Here, we extract elements indices 1 to 3
    // note: when extracting, we follow [a, b) non strict range
    // == [a, b - 1]
    // i.e. {C.begin() + 1, C.begin() + 1 + 3} will extract
    // elements at indices 1, 2, 3
    // prints: 7 8 1
    vector<int> C = {3, 7, 8, 1, 2};
    vector<int> sub_c = {C.begin() + 1, C.begin() + 1 + 3};
    print(sub_c);

    // another way to create same sub-vector as before:
    // this uses initializer of std::vector
    // prints: 7 8 1
    vector<int> D = {3, 7, 8, 1, 2};
    vector<int> sub_d(D.begin() + 1, D.begin() + 1 + 3);
    print(sub_d);
}

int main() {
    f_heap();
    f_multiset();
    f_sort();
    f_vector();
    f_string();
    return 0;
}
