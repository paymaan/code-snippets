#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
namespace my {
    namespace interleaving {
        // Non memoized DP
        bool dp(const std::string& s1, const std::string& s2,
                const std::string& s3, const int j, const int k, const int i) {
            if (i < 0)
                return s1.substr(0, j + 1).empty() &&
                       s2.substr(0, k + 1).empty();
            if (j < 0 && k < 0)
                return s3.substr(0, i + 1).empty();
            if (j < 0)
                return s3.substr(0, i + 1) == s2.substr(0, k + 1);
            if (k < 0)
                return s3.substr(0, i + 1) == s1.substr(0, j + 1);

            const bool dpI =
                (s3[i] == s1[j] && dp(s1, s2, s3, j - 1, k, i - 1)) ||
                (s3[i] == s2[k] && dp(s1, s2, s3, j, k - 1, i - 1));

            return dpI;
        }

        /// Can string A/s1 be formed by interleaving B/s2 and C/s3?
        bool isInterleave(const std::string& A, const std::string& B,
                          const std::string& C) {
            if (C.size() != A.size() + B.size())
                return false;
            return dp(A, B, C, A.size() - 1, B.size() - 1, C.size() - 1);
        }
    }

    namespace longest_common_subsequence {
        std::string max(const std::string& s1, const std::string& s2) {
            if (s2.size() >= s1.size())
                return s2;
            return s1;
        }

        /// Non memoized DP. Can easily be memoized by using a hash map
        /// (std::unordered_map) with custom parameters object as key.
        /// parameters object is something like:
        /// struct { string x; string y; int i; int j }.
        /// Can also be implemented with for-loops as a bottom-up DP.
        std::string dp(const std::string& x, const std::string& y, int i,
                       int j) {
            if (i < 0 || j < 0)
                return "";

            const std::string dpI =
                x[i] == y[j] ? dp(x, y, i - 1, j - 1) + x[i]
                             : max(dp(x, y, i - 1, j), dp(x, y, i, j - 1));
            return dpI;
        }

        std::string lcs(const std::string& x, const std::string& y) {
            return dp(x, y, x.size() - 1, y.size() - 1);
        }
    }

    /// Non memoized DP. Can easily be memoized by using a hash map
    /// Same technique to do that as mentioned above
    namespace min_char_palindrome {
        int min(const int a, const int b) { return a < b ? a : b; }
        int dp(const std::string& x, const int i, const int j) {
            if (i == j)
                return 0;
            return x[i] != x[j] ? 1 + min(dp(x, i + 1, j), dp(x, i, j - 1))
                                : dp(x, i + 1, j - 1);
        }
        int mcp(const std::string& x) {
            if (x.empty())
                return 0;
            return dp(x, 0, x.size() - 1);
        }
    }

    namespace unweighted_intervals {
        struct interval {
            interval(int start, int end, int weight)
                : _start(start), _end(end), _weight(weight) {}
            int _start;
            int _end;
            int _weight;
        };

        using intervalList = std::vector<interval>;

        void printIntervalList(intervalList& intervals) {
            for (const auto interval : intervals) {
                std::cout << "(" << interval._start << ", " << interval._end
                          << ") with weight " << interval._weight << std::endl;
            }
        }

        void sortIntervals(intervalList& intervals) {
            auto comparator = [](interval x, interval y) /*-> bool*/ {
                // sort in ascending order
                return x._end < y._end;
            };
            std::sort(intervals.begin(), intervals.end(), comparator);
        }

        int sumOfIntervalWeights(intervalList intervals) {
            int sum = 0;
            for (const auto& interval : intervals)
                sum += interval._weight;
            return sum;
        }

        intervalList maxOfIntervals(intervalList intervalList1,
                                    intervalList intervalList2) {
            return sumOfIntervalWeights(intervalList1) >=
                           sumOfIntervalWeights(intervalList2)
                       ? intervalList1
                       : intervalList2;
        }

        // note: intervals must be sorted before calling this function
        // max ~ "latest"
        // O(n) but can be O(logn) by using binary search
        int maxNonOverLappingIntervalBefore(const intervalList& intervals,
                                            const int idx) {
            const auto intervalAtIdx = intervals[idx];
            for (int i = idx - 1; i >= 0; --i) {
                if (intervals[i]._end <= intervalAtIdx._start) {
                    return i;
                }
            }
            return -1;
        }

        // non-memoized
        intervalList dp(const intervalList& intervals, const int i) {
            intervalList subset;
            if (i == 0) {
                subset.push_back(intervals[0]);
                return subset;
            }

            intervalList includedI;
            // note: k < i by definition of maxNonOverLappingIntervalBefore
            const int k = maxNonOverLappingIntervalBefore(intervals, i);
            if (k >= 0)
                includedI = dp(intervals, k);
            includedI.push_back(intervals[i]);

            intervalList excludedI = dp(intervals, i - 1);

            intervalList dpI = maxOfIntervals(includedI, excludedI);

            return dpI;
        }

        /// uis == unweighted interval subset
        intervalList uis(intervalList& intervals) {
            sortIntervals(intervals);
            return dp(intervals, intervals.size() - 1);
        }
    }
}

// Code Output if you run this code:
// $clang++ dynamic-programming.cpp && ./a.out
//    x   : ABCBDAB
//    y   : XYZAYZXBDCABC
//    lcs : ABDAB with length = 5
//    -----------
//    z: Ab3bd
//    mcpCount: 2
//    -----------
//    s1: noUdRp97xFvpifeSXGwOjcVNhHo9N2D
//    s2: 6iZItw9A3fj86uYx04tvWKLtl9BK
//    s3: n6ioUdRpZ97ItwxF9Av3fj86upYxif0eS4XtvWKLtlG9wOBKjcVNhHo9N2D
//    s3 interleaved form of s1 and s2? Yes
//    -----------
//    Interval list:
//    (1, 2) with weight 50
//    (3, 5) with weight 90
//    (6, 19) with weight 100
//    (2, 100) with weight 200
//    Optimum Subset interval list:
//    (1, 2) with weight 50
//    (2, 100) with weight 200
int main() {
    using namespace my;
    const std::string x = "ABCBDAB";
    const std::string y = "XYZAYZXBDCABC";

    const std::string lcsStr = longest_common_subsequence::lcs(x, y);
    std::cout << "x   : " << x << std::endl;
    std::cout << "y   : " << y << std::endl;
    std::cout << "lcs : " << lcsStr << " with length = " << lcsStr.size()
              << std::endl;

    std::cout << "-----------" << std::endl;

    const std::string z = "Ab3bd";
    const int mcpCount = min_char_palindrome::mcp(z);
    std::cout << "z: " << z << std::endl;
    std::cout << "mcpCount: " << mcpCount << std::endl;

    std::cout << "-----------" << std::endl;

    const std::string s1 = "noUdRp97xFvpifeSXGwOjcVNhHo9N2D";
    const std::string s2 = "6iZItw9A3fj86uYx04tvWKLtl9BK";
    const std::string s3 =
        "n6ioUdRpZ97ItwxF9Av3fj86upYxif0eS4XtvWKLtlG9wOBKjcVNhHo9N2D";
    const std::string isInterleavePossible =
        interleaving::isInterleave(s1, s2, s3) ? "Yes" : "No";
    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
    std::cout << "s3: " << s3 << std::endl;
    std::cout << "s3 interleaved form of s1 and s2? " << isInterleavePossible
              << std::endl;

    std::cout << "-----------" << std::endl;

    auto interval1 = unweighted_intervals::interval(1, 2, 50);
    auto interval2 = unweighted_intervals::interval(3, 5, 90);
    auto interval3 = unweighted_intervals::interval(6, 19, 100);
    auto interval4 = unweighted_intervals::interval(2, 100, 200);
    std::vector<unweighted_intervals::interval> intervals;
    intervals.push_back(interval1);
    intervals.push_back(interval2);
    intervals.push_back(interval3);
    intervals.push_back(interval4);
    std::cout << "Interval list: " << std::endl;
    unweighted_intervals::printIntervalList(intervals);
    auto subsetIntervals = unweighted_intervals::uis(intervals);
    std::cout << "Optimum Subset interval list: " << std::endl;
    unweighted_intervals::printIntervalList(subsetIntervals);

    return 0;
}
