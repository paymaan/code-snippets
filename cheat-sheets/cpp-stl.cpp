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

int main() {
    f_heap();
    f_multiset();
    f_sort();
    return 0;
}
