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

    // find in vector
    // prints: 7
    vector<int> E = {3, 7, 8, 1, 2};
    // vector.find() unfortunately isn't support in vector class:
    // auto it = E.find(7);
    // we have a generic find in stl though which works on different containers:
    auto it = find(E.begin(), E.end(), 7);
    if (it != E.end())
        cout << *it << "\n";
}

void f_string() {
    string s = "foo bar";

    // extract first 3 elements i.e. "foo"
    // note 2nd argument to substr is "length" of substr
    //      1st argument is starting index
    // prints: "foo"
    cout << s.substr(0, 3) << "\n";

    // extra from index i to j
    // prints: "o ba"
    // note: length from i to j is: j - i + 1
    int i = 2, j = 5;
    cout << s.substr(2, 5 - 2 + 1) << "\n";

    // can sort string lexograpgically
    // prints: " abfoor"
    string s_copy(s); // equivalent: string s_copy = s;
    sort(s_copy.begin(), s_copy.end());
    cout << s_copy << "\n";

    // can reverse string as well
    // prints: "rab oof"
    string s_another_copy(s); // equivalent: string s_copy = s;
    reverse(s_another_copy.begin(), s_another_copy.end());
    cout << s_another_copy << "\n";

    // Is character "c" present in string?
    // prints: "b was found"
    char char_to_find = 'b';
    auto it1 = s.find(char_to_find);
    if (it1 != string::npos)
        cout << char_to_find << " was found" << "\n";

    // Is substring "ba" present in string?
    // prints: "ba was found"
    string substr_to_find = "ba";
    auto it2 = s.find(substr_to_find);
    if (it2 != string::npos)
        cout << substr_to_find << " was found" << "\n";

    // Note: More powerful searches can be made in string
    // using find's pos (starting index) and count (length of search space)
}

void f_hash_map() {
    class PairHashFnctor {
        public:
            size_t operator()(const pair<int, int>& p) const {
                return p.first ^ p.second; // ^ === XOR
            }
    };

    // key: pair<int, int>
    // value: string
    // key value pair: < pair<int, int> , string >
    // since pair<int, int> doesn't have a default std::hash,
    // we'll have to provide one for this cache code to compile
    unordered_map<pair<int, int>, string, PairHashFnctor> cache;
    cache[{4,3}] = "abc";
    cache[{7, -1}] = "def";
    // prints: "abc"
    cout << cache[{4,3}] << "\n";
}

void f_stack_queue() {
    // STACK
    stack<int> stack;
    // push 5, 7, 1, 10
    stack.push(5);
    stack.push(7);
    stack.push(1);
    stack.push(10);
    // now keep removing elements from the top
    // of the stack until we empty it
    // prints: 10 1 7 5
    while (!stack.empty()) {
        cout << stack.top() << " ";
        stack.pop();
    }
    cout << "\n";

    // QUEUE
    queue<int> queue;
    // push 5, 7, 1, 10
    // push === push at the back of the queue
    queue.push(5);
    queue.push(7);
    queue.push(1);
    queue.push(10);
    // now keep removing elements from the front
    // of the queue until we empty it
    // prints: 5 7 1 10
    while (!queue.empty()) {
        cout << queue.front() << " ";
        queue.pop(); // pops from front
    }
    cout << "\n";
    // note: for queue, we also have back() to access
    // elements at the back of the queue. Having said that,
    // we can only push to back and pop from front.
}

void f_streams() {
    // STRING streams
    // Advantage: e.g. in serialization/deserialization, we can use
    // string streams using cout/cin easily without having to worry
    // about placement of strings i.e. the stream takes care of
    // appending and ordering. All we do is pass the stream as a reference
    // and keep writing/reading to/from it.
    // 1) serialization
    ostringstream out;
    out << "string to serialize"; // delimiter = ' '
    string serialized_str = out.str();

    // 2) deserialization
    // since 3 strings (delimited by ' ')
    // do in >> xx 3 times.
    // this will print:
    // string
    // to
    // serialize
    istringstream in(serialized_str);
    string deserialized_string;
    in >> deserialized_string;
    cout << deserialized_string << "\n";
    in >> deserialized_string;
    cout << deserialized_string << "\n";
    in >> deserialized_string;
    cout << deserialized_string << "\n";

    // note: practically, we can pass in and out as references
    // to functions and read from or write to the stream

    // By default, istringstream delimits by a space character (' ')
    string spaceStr = "ab cdefg hi jkl";
    istringstream in2(spaceStr);
    string token2;
    while (in2 >> token2) {
        cout << token2 << endl;
    }

    // We can change that. Let's say we wanted to delimit by comma (',')
    string commaStr = "ab,cdefg,hi,jkl"
    istringstream in3(commaStr);
    string token3;
    while (getline(in3, token3, ',')) {
        cout << token3 << endl;
    }
}

int main() {
    f_heap();
    f_multiset();
    f_sort();
    f_vector();
    f_string();
    f_hash_map();
    f_stack_queue();
    f_streams();
    return 0;
}
