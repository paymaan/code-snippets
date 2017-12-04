#include <cmath>
#include <iostream>

using namespace std;

/// Common masking tricks:
/// Extracting ith bit in x:
/// (x >> i) & 1 will give 1 or 0
/// if ith bit is 1 or 0.
/// Extracting ith bit in position:
/// x & (1 << i)

/// CountBits(5) = 2 because (5)_10 = (101)_2 #1's = 2

/// Approach 1
/// If unsigned number, and n bit binary number:
/// min decimal value = 0
/// max decimal value = 2^n - 1
/// Let v be a decimal number, what are the
/// min number of bits needed to reprensent v?
/// v <= 2^n -1        =>
/// n >= log(v + 1)    =>
/// n = ceil(log(v+1)), where n = min bits needed
/// Time: O(min bits needed) = O(ceil(log(n+1)))
/// where n = input number
/// Space: O(1) except copying input x
// short CountBits(unsigned int x) {
//     short min_bits_needed = ceil(log(x + 1) / log(2));
//     short num_1_bits = 0;
//     for (short i = 0; i < min_bits_needed; ++i) {
//         if (x & (1 << i))
//             ++num_1_bits;
//     }
//     return num_1_bits;
// }

/// Approach 2
/// Without needing min_num_bits
/// Keep chopping off LS bits from x
/// by right shifting by 1
/// and AND with 1
/// Time: O(min bits needed) = O(ceil(log(n+1)))
/// where n = input number
/// Space: O(1) except copying input x
// short CountBits(unsigned int x) {
//     short num_1_bits = 0;
//     while (x) {
//         num_1_bits += x & 1;
//         x = x >> 1; // more efficient than x = x / 2
//     }
//     return num_1_bits;
// }

/// Approach 3
/// Approach 2 but with optimization that
/// makes time complexity O(k) where k is
/// number of 1 bits in x.
/// Optimization is:
/// x & (x - 1) erases the lowest 1 bit in x
/// Similarly,
/// x & ~(x - 1) isolated the lowest 1 bit in x
short CountBits(unsigned int x) {
    short num_1_bits = 0;
    while (x) {
        ++num_1_bits;
        x = x & (x - 1);
    }
    return num_1_bits;
}

/// Parity(5) = 0 because 5 = (101) i.e.
/// even number of 1's. Parity(7) = 1
/// because (111) has 3 or odd # of 1's.
/// Approach 1
/// Simple masking and shifting, use
/// res = res XOR (bit is 1) which would
/// result in 1 iff # bits that are 1 are odd.
// short Parity(unsigned long x) {
//     short result = 0;
//     while (x) {
//         result ^= x & 1;
//         x >>= 1;
//     }
//     return result;
// }

/// Approach 2
/// O(k) in time where k is number of 1 bits in x
// short Parity(unsigned long x) {
//     short result = 0;
//     while (x) {
//         result ^= 1;
//         x &= x - 1; // same optimization as before
//     }
//     return result;
// }

/// Approach 3
/// Very optimized: O(log(n))
/// n = number of bits in x
/// Can be better than approach 2 because
/// approach 2 has worst case O(n) if all 1's.
short Parity(unsigned long x) {
    x ^= x >> 32;
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return x & 1;
}

/// Swap(12, 3, 1) = 6 because
/// 12 = 1100
/// Swapping 3th and 1st index:
/// 0110 which is 6
/// Notice indexing is 0 based from right
/// to left i.e. LSB to MSB
/// O(1) time and space
long SwapBits(long x, int i, int j) {
    // We only need to swap if ith and jth
    // bits differ.
    if (((x >> i) & 1) != ((x >> j) & 1)) {
        // We need to swap now.. swapping is equivalent
        // to just flipping the ith and jth bits to their
        // complements i.e. 1 -> 0 and 0 -> 1.
        // This can be done easily using XOR with 1 since
        // XOR(0, 1) = 1 and XOR(1, 1) = 0
        unsigned long bit_mask = (1 << i) | (1 << j);
        x ^= bit_mask;
    }
    return x;
}

/// ReverseBits(12) is 3
/// because 12 = 1100
/// reverse is 0011
/// which is 3
/// Assuming x is at most 64 bits, we need
/// to swap 32 bits on each side with
/// each other. Notice, in swap, we just need
/// to swap one half with the other. If odd,
/// the central element is untouched but here we
/// don't have that case.
/// Note: if x == ReverseBits(x), then
/// x is bitwise palindrome.
/// Parameterizing on "N" min bits
/// e.g. 12 has 4 min bits
/// Index: [0, N - 1]
/// Note: N has to be even here.
long ReverseBits(long x, int N) {
    for (int i = 0; i <= (N / 2) - 1; ++i) {
        x = SwapBits(x, i, (N - 1) - i);
    }
    return x;
}

unsigned Multiply(unsigned x, unsigned y) {
    return 0;
}

unsigned Add(unsigned a, unsigned b) {
    return 0;
}

unsigned Divide(unsigned x, unsigned y) {
    return 0;
}

/// Power(2, 3) = 8 i.e. 2^3
/// Basically just exponent
/// Implement without any native c++ operators
double Power(double x, int y) {
    return 0;
}

/// Reverse in base 10
/// Reverse(547) = 745
/// Reverse(-926) = -629
/// Note x /= 10 basically chops off
/// the last digit in base 10 just like
/// x /= 2 (or x >> 1) chops off the last bit.
/// Extracting the last digit in base 10
/// is done using x % 10
long Reverse(int x) {
    bool is_neg = x < 0;
    int result = 0;
    if (is_neg)
        x = abs(x);
    while (x) {
        result = (result * 10) + (x % 10);
        x /= 10;
    }
    return is_neg ? -1 * result : result;
}

bool IsPalindromeNumber(int x) {
    return false;
}

string IntToString(int x) {
    return "";
}

int StringToInt(const string& s) {
    return -1;
}

string ConvertBase(const string& num_as_string, int b1,
                   int b2) {
    return "";
}

int main() {
    cout << CountBits(5) << endl;
    cout << Parity(7) << endl;
    cout << SwapBits(12, 3, 1) << endl;
    cout << ReverseBits(12, 4) << endl;
    cout << Reverse(73569) << endl;
    return 0;
}