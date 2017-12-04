#include <cmath>
#include <iostream>

using namespace std;

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
short CountBits(unsigned int x) {
    short num_1_bits = 0;
    while (x) {
        num_1_bits += x & 1;
        x = x >> 1; // more efficient than x = x / 2
    }
    return num_1_bits;
}

short Parity(unsigned long x) {
    return 0;
}

long SwapBits(long x, int i, int j) {
    return 0;
}

long ReverseBits(long x) {
    return 0;
}

unsigned Multiply(unsigned x, unsigned y) {
    return 0;
}

unsigned Divide(unsigned x, unsigned y) {
    return 0;
}

double Power(double x, int y) {
    return 0;
}

long Reverse(int x) {
    return 0;
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
    return 0;
}
