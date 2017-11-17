#include <iostream>
#include <limits>
#include <vector>

using namespace std;

/// Find median of two sorted arrays
/// https://leetcode.com/problems/median-of-two-sorted-arrays/description/
// Example 1:
//   nums1 = [1, 3]
//   nums2 = [2]
//   The median is 2.0
// Example 2:
//   nums1 = [1, 2]
//   nums2 = [3, 4]
//   The median is (2 + 3)/2 = 2.5
double mean(int x, int y) {
    return double((x + y)) / 2;
}
double median_single(const vector<int>& A) {
    if (A.empty())
        return -1;
    if (A.size() % 2 == 0) { // even
        return double(A[A.size() / 2] +
                      A[(A.size() / 2) - 1]) /
               2;
    } else { // odd
        return A[A.size() / 2];
    }
}
double median(const vector<int>& A, const vector<int>& B) {
    if (A.empty())
        return median_single(B);
    if (B.empty())
        return median_single(A);

    // A must be smallest for our algo
    if (A.size() > B.size())
        return median(B, A);

    int start = 0, end = A.size();
    const int total_length = A.size() + B.size();
    while (start <= end) {
        const int pA = (start + end) / 2;
        const int pB = ((total_length + 1) / 2) - pA;

        // to cover empty partition edge cases, we
        // assign -INF or +INF
        const int maxLeftA =
            pA == 0 ? numeric_limits<int>::lowest()
                    : A[pA - 1];
        const int maxLeftB =
            pB == 0 ? numeric_limits<int>::lowest()
                    : B[pB - 1];
        const int minRightA =
            pA == A.size() ? numeric_limits<int>::max()
                           : A[pA];
        const int minRightB =
            pB == B.size() ? numeric_limits<int>::max()
                           : B[pB];
        if (maxLeftA <= minRightB &&
            maxLeftB <= minRightA) {
            // found valid partition, return median here
            if (total_length % 2 == 0)
                return mean(max(maxLeftA, maxLeftB),
                            min(minRightA, minRightB));
            else
                return max(maxLeftA, maxLeftB);
        }

        if (maxLeftA > minRightB) { // move end towards left
            end = pA - 1;
        } else { // move start towards right
            start = pA + 1;
        }
    }

    cout << "should never reach here" << endl;
    return -1;
}

int main() {
    const vector<int> A = {1, 3, 8, 9, 15};
    const vector<int> B = {7, 11, 18, 19, 21, 25};
  
    cout << "median: " << median(A, B) << endl;

    return 0;
}
