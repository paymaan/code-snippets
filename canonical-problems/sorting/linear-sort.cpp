#include <algorithm>
#include <cmath>
#include <cstring>
#include <forward_list>
#include <iostream>
#include <vector>

using namespace std;

// Notes:
// Arrays can be used in very smart ways:
// 1) As a map with key being index to map. This can
// reduce the hashing overhead. But only useful if we know
// that the keys are integers and have a pre known range.
// 2) For linear O(n) sorting again if keys are integers and
// have a known range e.g. [0, k-1].

// Note that 2) Linear sort, requires O(k) space and O(n +
// k) time in
// 	      general (see 6.006 OCW notes) for couting
// sort.
// 	      If k = O(n), we get O(n) time overall.
// 	      Also note that this sort is not in-place
// (requires separate O(k) space).
// 	      Along with integer and pre known range
// condition, another
// 	      condition is that the integer should fit in a
// word size because manipulating
// 	      words is O(1) and we need that to come with
// linear sorting algorithm.

vector<int> counting_sort(const vector<int>& arr,
                          const size_t k) {
    /// Linear/Integer sort using Counting sort algorithm
    /// n == arr.size()
    // 1. Allocate O(k) array where k = range
    int counts[k];
    memset(counts, 0, sizeof(counts)); // initialize
    // 2. Traverse arr and update counters in counts array
    for (auto key : arr)
        ++counts[key];
    // 3. Populate sorted result
    vector<int> sorted;
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < counts[i]; ++j) {
            sorted.push_back(i);
        }
    }
    return sorted;
}

/// we make counting sort stable by using a singly linked
/// list in our counts array/vector
/// Unfortunately C++'s singly list does not have a
/// O(1) push_back.. so will just use vector internally.
vector<int> counting_sort_stable(const vector<int>& arr,
                                 const size_t k) {
    using List =
        vector<int>; // replacement to singly linked list

    // 1. Allocate O(k) array where k = range
    // Using vector instead of raw array to avoid
    // constant size k issues
    vector<List> counts(k);

    // 2. Traverse arr and update counters in counts array
    for (auto key : arr) {
        const auto& value =
            key; // key == value in this example
        counts[key].push_back(value);
    }

    // 3. Populate sorted result
    vector<int> sorted;
    for (int i = 0; i < k; ++i) {
        const auto list = counts[i];
        for (int j = 0; j < list.size(); ++j) {
            sorted.push_back(list[j]);
        }
    }

    return sorted;
}

/// assert idx < num.size()
/// Example:
/// 3 2 1 0  --- idx
/// 5 2 3 7  --- num
/// extract_digit(num, 0) -> 7
/// extract_digit(num, 1) -> 3
/// extract_digit(num, 2) -> 2
/// extract_digit(num, 3) -> 5
/// b = base, mostly 10 (as above)
/// first, num is convered to another num in base b
/// then we extract the digit at idx
int extract_digit(int num, const int b, const int idx) {
    int digit = -1;
    for (int i = 0; i <= idx; ++i) {
        digit = num % b;
        num /= b;
    }
    return digit;
}

vector<int>
counting_sort_stable_radix(const vector<int>& arr,
                           const size_t k, const int b,
                           const int d_idx) {
    using List =
        vector<int>; // replacement to singly linked list

    // 1. Allocate O(k) array where k = range
    // Using vector instead of raw array to avoid
    // constant size k issues
    vector<List> counts(b);

    // 2. Traverse arr and update counters in counts array
    for (auto value : arr) {
        const int key = extract_digit(value, b, d_idx);
        counts[key].push_back(value);
    }

    // 3. Populate sorted result
    vector<int> sorted;
    for (int i = 0; i < b; ++i) {
        const auto list = counts[i];
        for (int j = 0; j < list.size(); ++j) {
            sorted.push_back(list[j]);
        }
    }

    return sorted;
}

vector<int> radix_sort(const vector<int>& arr,
                       const size_t k) {
    const int n = arr.size();
    const int b = n; // b (base) has to be O(n)
    const int d =
        (log(k) / log(b)) + 1; // d = max # of digits
                               // for an integer in arr;
                               // is floor(log base b of
                               // k)
    vector<int> sorted(arr); // can do in place arr as well
                             // i.e directly use arr and
                             // sort it

    for (int d_idx = 0; d_idx < d; ++d_idx) {
        sorted =
            counting_sort_stable_radix(sorted, k, b, d_idx);
    }

    return sorted;
}

void bucket_sort(vector<float>& arr) {
    const size_t n = arr.size();
    // 1. Create "n" empty buckets
    // We have an array of vectors (or linked lists)
    vector<vector<float>> buckets(n);
    // 2. Put array elements in different buckets
    // After this loop, element across buckets are sorted
    // Only within a bucket, we need to sort elements
    for (int i = 0; i < n; ++i) {
        // Assuming that arr[i] is in range [0, 1]
        // This implies that bucket_idx is [0, n]
        // Note that we multiple by n and floor (int
        // implicit)
        // We can think of bucket_idx as key for arr[i]
        const int bucket_idx = n * arr[i];
        buckets[bucket_idx].push_back(arr[i]);
    }
    // 3. Sort individual buckets
    // This step can be O(n) if input is uniformly
    // distributed. That's why average time for bucket
    // sort is O(n) but worst time is (n ^ 2)
    for (int i = 0; i < n; ++i)
        sort(buckets[i].begin(), buckets[i].end());
    // 4. Traverse buckets array and update arr in place
    int index = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < buckets[i].size(); ++j)
            arr[index++] = buckets[i][j];
}

template <typename T> void print(const vector<T>& arr) {
    for (auto e : arr)
        cout << e << " ";
    cout << "\n";
}

int main() {
    const size_t k = 100; // k = 100 for range [0, 99]
    const vector<int> arr = {5,  2,  11, 45, 18,
                             13, 11, 75, 2,  2};

    /// All outputs: "2 2 2 5 11 11 13 18 45 75"
    print(counting_sort(arr, k));
    print(counting_sort_stable(arr, k));
    print(radix_sort(arr, k));

    cout << "-----"
         << "\n";

    /// Outputs: "0.1234 0.3434 0.565 0.656 0.665 0.897"
    vector<float> arr2 = {0.897,  0.565, 0.656,
                          0.1234, 0.665, 0.3434};
    print(arr2);
    bucket_sort(arr2);
    print(arr2);

    return 0;
}
