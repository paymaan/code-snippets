#include <iostream>
#include <string>

namespace my {
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
    std::string dp(const std::string& x, const std::string& y, int i, int j) {
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

// Code Output if you run this code:
// $clang++ dynamic-programming.cpp && ./a.out
//    x   : ABCBDAB
//    y   : XYZAYZXBDCABC
//    lcs : ABDAB with length = 5

int main() {
    using namespace my;
    const std::string x = "ABCBDAB";
    const std::string y = "XYZAYZXBDCABC";

    const std::string lcsStr = lcs(x, y);
    std::cout << "x   : " << x << std::endl;
    std::cout << "y   : " << y << std::endl;
    std::cout << "lcs : " << lcsStr << " with length = " << lcsStr.size()
              << std::endl;

    return 0;
}
