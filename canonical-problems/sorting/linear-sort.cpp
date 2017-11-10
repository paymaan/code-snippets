#include <iostream>
#include <cstring>

using namespace std;

// Notes:
// Arrays can be used in very smart ways:
// 1) As a map with key being index to map. This can
// reduce the hashing overhead. But only useful if we know
// that the keys are integers and have a pre known range.
// 2) For linear O(n) sorting again if keys are integers and
// have a known range e.g. [0, k-1].

// Note that 2) Linear sort, requires O(k) space and O(n + k) time in
// 	      general (see 6.006 OCW notes) for couting sort.
// 	      If k = O(n), we get O(n) time overall.
// 	      Also note that this sort is not in-place (requires separate O(k) space). 
// 	      Along with integer and pre known range condition, another
// 	      condition is that the integer should fit in a word size because manipulating
// 	      words is O(1) and we need that to come with linear sorting algorithm.


int main() {
  const size_t n = 10;
  const size_t k = 100; // k = 100 for range [0, 99]
  int arr[n] = {5, 2, 11, 45, 18, 13, 11, 75, 2, 2};

  /// Output: "2 2 2 5 11 11 13 18 45 75"
  /// Linear/Integer sort using Counting sort algorithm
  // 1. Allocate O(k) array where k = range
  int sorted[k];
  memset(sorted, 0, sizeof(sorted)); // initialize
  // 2. Traverse arr and update counters in sorted array
  for (auto e : arr)
    ++sorted[e];
  // 3. Print sorted result
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < sorted[i]; ++j) {
      cout << i << " ";
    }      
  }
  cout << endl;
  
  return 0;
}
