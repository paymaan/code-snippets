#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

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

/// Tells if a given number is a power of 2
/// i.e. 1, 2, 4, 8, 16, 32 will all return true
/// Key is to realize:
/// x is a power of 2 iff only single 1 bit in x
/// Then we can reduce the problem to find this
/// We know that x & (x - 1) erases the lowest 1 bit
/// so if we do that, and we are left with all zeros (= 0)
/// then our number is a power of two.
/// O(k) time where k = distance between LSB and lowest 1
/// bit We obviously assume here that & and == operators are
/// O(1). Space is O(1)
bool IsPowerOfTwo(unsigned int x) {
    if (x <= 0)
        return false;
    return (x & (x - 1)) == 0;
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
long ReverseBits(long x) {
    short min_bits = ceil(log(x + 1) / log(2));
    for (int i = 0; i <= (min_bits / 2) - 1; ++i) {
        x = SwapBits(x, i, (min_bits - 1) - i);
    }
    return x;
}

// Time: O(n) where n = # of bits
// Space: O(n)
// Algorithm:
// Adding two numbers, "a" and "b":
// 1) Add two numbers (sum) but forget the carry
//    This way, ith bit in sum will be 0 iff a and b
//    have the same ith bit i.e. 1,1 or 0,0.
//    This is just XOR.
// 2) Add two numbers but ONLY carry. This way, ith
//    bit in sum (we call this variably "carry") will
//    be 1 iff (i - 1) bit of a and b are both 1's, else
//    we'll get zero. This is essentially AND << 1.
// 3) Keep iterating until there is no carry.
unsigned Add(unsigned x, unsigned y) {
    while (y) {
        unsigned sum = x ^ y; // add without carrying
        unsigned carry = (x & y)
                         << 1; // carry, but don't add
        x = sum;
        y = carry;
    }
    return x;
}

// Two ways to solve this:
// 1) x * y = x + x + x ... (y times) => O(2 ^ n) time where
//    n = # of bits
// 2) Shift and add method. For example, in base 10:
//    21 * 3 = (1 * 3 x 10^0) + (2 * 3 x 10^1)
//           = 3 + 60 = 63
//    In binary can do the same, except that we have
//    either 1 * (bit * 2^k) or 0 * (bit * 2^k)
//    We don't count 0, and only count 1, for which we
//    don't have to multiply by 1 either because 1 * bit =
//    bit If 1, we just add to the running_sum. In each
//    iteration, we keep shifting "x" to the right by 1 bit
//    and "y" to the left. "y" represents 2^k part which we
//    have to add if needed. Note we still need "add" as a
//    sub-routine. Time: O(n ^ 2) where n = # of bits in x/y
//    that the operands operate on Quadratic because add
//    itself is O(n). Space: O(n) to store sum.
unsigned Multiply(unsigned x, unsigned y) {
    unsigned sum = 0;
    while (x) {
        if (x & 1)
            sum = Add(sum, y);
        x = x >> 1;
        y = y << 1;
    }
    return sum;
}

/// Compute x/y using only addition, subtraction, and
/// shifting operators
/// Here, we return the quoteient, but we can return
/// remainder as well if needed.
/// Example: x = 11, y = 2
/// x/y = 11/2 => quotient = 5, remainder = 1
/// One algorithm is to keep subtracting "y" from "x"
/// until x <= y. In this case, 11 - 2 - 2 - 2 - 2 - 2 = 1
/// Since 1 <= 2, we stop.
/// Quotient is 5 since we had to subtract 2 five times
/// Remainder is 1 since that is what was left at the end
/// This works but complexity is O(x) which is really,
/// really bad! Imagine, x = 2 ^ 31, y = 1; we'll have to
/// subtract 1 O(2 ^ 31) times!
/// Another better algorithm
/// which runs in O(n) where n = # of bits, is given below:
/// Instead of removing "y" each time, remove 2^k * y where
/// k is the largest integer s.t. 2^k * y <= x
/// Let's run through an example:
/// 11 -> 11 - 2^2 * 2
/// We chose k = 2 because k = 3, 2^3 * 2 = 16 > 11
/// 11 - 2^2 * 2 = 3
/// Next iteration:
/// 3 - 2^0 * 2  = 1(chose k = 0)
/// Done since 1 < 2
/// Quotient: 2^2 + 2^0 = 5
/// Remainder: 1 (whatever left at the end)
/// Time: O(n) where n = # of bits
/// Space: O(n) because we have to store temporaries and
/// return final answer
unsigned Divide(unsigned x, unsigned y) {
    unsigned quotient = 0;
    int k = 32; // max can be 32
    unsigned long long two_k_y =
        static_cast<unsigned long long>(y)
        << 32; // starting 2^k * y
    while (x >= y) {
        // calculate biggest k s.t. 2^k * y <= x
        // can do while (!(two_k_y <= x)) OR:
        while (two_k_y > x) {
            --k;
            two_k_y = two_k_y >> 1;
        }
        // largest k found, just add 2^k (1U << k) now
        // to running sum or quotient:
        quotient += 1U << k;
        // Finally, new "x" becomes whatever was left
        x = x - two_k_y;
    }
    return quotient;
}

/// Power(2, 3) = 8 i.e. 2^3
/// Basically just exponent
/// Can use multiply and shift operators.
/// Can ignore underflow and overflow
/// Brute force algorithm for calculating x ^ y
/// would be to multiply x with running_product y
/// times. This takes (y - 1) multiplications => O(2^n) time
/// A better algorithm will be to reduce the number of
/// multiplications Here's the trick which utilizes exponent
/// property: x ^ (a + b) = x ^ a * x ^ b So: x ^ y = x ^ (y
/// / 2 + y / 2)
///       = (x ^ y / 2) * (x ^ y / 2)
///       = (x ^ y / 2) * (x ^ y / 2)
/// The above is only possible when "y" is even
/// When y is odd, y / 2 in C++ would be floor(y / 2), so:
/// x ^ y = x ^ (y/2 + y/2 + 1)
///       = (x ^ (y/2 + y/2)) * x
///       = (x ^ y / 2) ^ 2   * x
///       = (x ^ y / 2) * (x ^ y / 2) * x
/// This way we get a recursive way to compute x ^ y.
/// This means that if y is a power of 2, instead of doing:
/// x ^ 32 = x * x * x * x ... * x (32 times), we can do:
/// x ^ 32 = x -> x^2 -> x^4 -> x^8 -> x^16 -> x^32
/// we do this by power >> 1 and by keeping a running
/// product If y is negative, x -> 1/x and y -> -y Time:
/// O(n) where n = # of bits This is because number of
/// multiplications is at most 2 times the index of y's MSB.
double Power(double x, int y) {
    double running_product = 1.0;
    long long power = y;
    if (power < 0) {
        power = -1 * power;
        x = double(1) / x;
    }
    while (power) {
        if (power & 1) {
            running_product = running_product * x;
        }
        x = x * x;
        power = power >> 1;
    }
    return running_product;
}

/// Reverse in base 10
/// Reverse(547) = 745
/// Reverse(-926) = -629
/// 1) Note x /= 10 basically chops off
///    the last digit in base 10 just like
///    x /= 2 (or x >> 1) chops off the last bit.
///    i.e. x / 10 is x without its last digit.
///    The last digit itself can be found using (2).
/// 2) Extracting the last digit in base 10
///    is done using x % 10 i.e. x mod with 10
///    gives the last digit in a number.
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

/// Returns number of digits for (x)_base
/// Examples:
/// num_digits(11, 2) gives 4 since there are 4 bits
/// Note: (11)_10 = (1011)_2
/// Similarly,
/// num_digits(547, 10) gives 3 since there are 3 digits
/// O(1) time
int num_digits(int x, int base) {
    return ceil(log(x + 1) / log(base));
}

/// extract_digit(5467, 0) == 7
/// extract_digit(5467, 1) == 6
/// extract_digit(5467, 2) == 4
/// extract_digit(5467, 3) == 5
/// Only base 10
/// Idea:
/// extract_digit(5467, 1) =
/// 5467 / 10^1 - 10 * (5467 / 10^2) =
/// 546 - 10*54 = 546 - 540 = 6
/// O(1) time assuming Power() is O(1)
int extract_digit(int x, int idx) {
    return floor(x / Power(10, idx)) -
           (10 * floor(x / Power(10, idx + 1)));
}

/// Idea is simple:
/// Find number of digits e.g. 5
/// for 62458
/// Now extract most significant digit (msd)
/// and least significant digit (lsd)
/// Compare to ensure same, else early return false
/// Continue to next smaller number by chopping off
/// msd and lsd.
/// Note: Negative numbers can never be palindrome.
/// Time: O(n) where n = # of bits
/// Space: O(1)
/// An alternative approach is:
/// Reverse(x) == x
bool IsPalindromeNumber(int x) {
    if (x < 0)
        return false;
    int n = num_digits(x, 10);
    int msd_mask = pow(10, n - 1);
    for (int i = 0; i < n / 2; ++i) {
        int msd = x / msd_mask;
        int lsd = x % 10;
        if (msd != lsd)
            return false;
        // chop off msd
        x = x % msd_mask;
        // chop off lsd
        x = x / 10;
        // since we chopped off 2 digits, update msd_mask
        // by 10^2
        msd_mask = msd_mask / 100;
    }
    return true;
}

/// Convert char to its ascii value
int AsciiValue(char c) {
    return int(c);
}

/// Convert char to int
/// CharToInt('7') = 7
int CharToInt(char c) {
    return int(c) - int('0');
}

/// Convert int to char
/// IntToChar(7) = '7'
char IntToChar(int x) {
    return char(x + int('0'));
}

/// IntToString(45) = "45"
string IntToString(int x) {
    // Using C++11 to_string in <string>
    return to_string(x);
}

/// Implementation without using standard
/// library functions.
string MyIntToString(int x) {
    bool is_neg = x < 0;
    string str = "";
    while (x) {
        str += IntToChar(x % 10);
        x /= 10;
    }
    // make negative if needed
    if (is_neg)
        str += '-';
    // reverse string
    str = {str.rbegin(), str.rend()};
    return str;
}

/// StringToInt("45") = 45
int StringToInt(const string& s) {
    /// Using C++11 stoi in <string>
    return stoi(s);
}

/// Note on base number system
/// The base number system generalizes the decimal
/// number system: the base-b number
/// "a_k-1 a_k-2 ... a_1 1_0",
/// where 0 <= a_i < b and 0 <= i <= k - 1
/// The base-b number mentioned above is the below
/// base-10 integer:
/// (a_0 * b^0) + (a_1 * b^1) + ... + (a_k-1 * b^k-1)

/// Implementation without using standard
/// library functions.
/// Remember, a base 10 number d3d2d1d0 encodes the number:
/// (d3 * 10^3) + (d2 * 10^2) + (d1 * 10^1) + (d0 * 10^0)
/// e.g. 475 = (4 * 100) + (7 * 10) + (5 * 1)
///          = 400 + 70 + 5
///          = 5
/// This is similar to base 2 where we just have
/// (2 ^ n) instead of (10 ^ n)
// int MyStringToInt(const string& s) {
//     int num = 0;
//     for (int i = s.size() - 1; i >= 0; --i) {
//         int exp = (s.size() - 1) - i;
//         num += CharToInt(s[i]) * pow(10, exp);
//     }
//     return num;
// }

/// A more elegant solution is to go from left to right
/// and add keep multiplying by 10 each time. For example:
/// Number = 475, res = 0
/// res = (0 * 10) + 4 = 4
/// res = (4 * 10) + 7 = 47
/// res = (47 * 10) + 5 = 475
// int MyStringToInt(const string& s) {
//     int num = 0;
//     for (int i = 0; i < s.size(); ++i) {
//         num = (num * 10) + CharToInt(s[i]);
//     }
//     return num;
// }

// Now just adding negative number capability:
int MyStringToInt(const string& s) {
    if (s.empty())
        return -1;
    const bool is_neg = s[0] == '-';
    int num = 0;
    for (int i = is_neg ? 1 : 0; i < s.size(); ++i) {
        num = (num * 10) + CharToInt(s[i]);
    }
    return is_neg ? -1 * num : num;
}

/// Mapping of numbers based on input char
/// Helper for ConvertBase
/// ['1', '2', ... , '9'] maps to [1, 2, ..., 9]
/// ['A', 'B', 'C', 'D', 'E', 'F'] maps to:
/// [10 ,  11,  12,  13,  14,  15]
/// Num can be in a non 10 base
int MapCharToNum(char c) {
    if (isdigit(c))
        return CharToInt(c);
    else
        return int(c) - 'A' + 10;
}

/// opposite mapping of
/// MapCharToNum
char MapNumToChar(int x) {
    if (x >= 1 && x <= 9)
        return IntToChar(x);
    else if (x >= 10 && x <= 15)
        return char(x - 10 + int('A'));
    else
        assert(false); // should not reach here
}

/// ConvertBase("615", 7, 13) = "1A7"
/// b1 >= 2 and b2 <= 16
/// if x in base b is denoted by: (x)_b, then:
/// (615)_7 = (306)_10 = (1A7)_13
/// Note:
/// Our approach is to convert number from b1 -> base10
/// and then base10 -> b2
/// To convert from base b to base 10,
/// we use the typical technique:
/// (XYZ)_b = ((X * b ^ 2) + (Y * b ^ 1) + (Z * b ^ 0))_10
/// An equivalent more efficient way to implement this:
/// res = 0
/// res = (res * b) + s[i]
/// where s[i] = number representation of input string at i
/// and b = base from which we convert to base 10
string ConvertBase(const string& num_as_string, int b1,
                   int b2) {
    if (num_as_string.empty())
        return "";
    int num_base10 = 0;
    // step 1: convert from b1 -> base10
    for (int i = 0; i < num_as_string.size(); ++i) {
        num_base10 = (num_base10 * b1) +
                     MapCharToNum(num_as_string[i]);
    }
    // step 2: convert from base10 -> b2
    string num_base_b2 = "";
    while (num_base10) {
        num_base_b2 += MapNumToChar(num_base10 % b2);
        num_base10 /= b2;
    }
    reverse(num_base_b2.begin(), num_base_b2.end());
    return num_base_b2;
}

/// Some more questions involving bit manipulation.

/// Convert decimal number to base2
/// Time: O(M); Space: O(M)
/// M = # of bits in 'n'
/// This assumes >> 1 (bit right shift) is O(1)
/// Uses LSB extraction technique
string binaryLSB(int n) {
    if (n <= 0) return "0";
    string result;
    while (n) {
        result += to_string(n & 1); // append LSB
        n = n >> 1; // n = n / 2
    }
    reverse(result.begin(), result.end());
    return result;
}

/// Helper utility that extracts MSB given a number
/// and it's number of bits. Note: Number of bits can
/// be calculated inside the function as well!
int extractMSB(int n, int numBits) {
    int mask = (1 << (numBits - 1)); // create mask like 100000
    n = n & mask; // AND with mask to get MSB followed by zeros
    n = n >> (numBits - 1); // Now move that single 1/0 to the right again
    return n;
}

/// Convert decimal number to base2
/// Same as binary above but extracts MSB instead of LSB
/// so we don't need to reverse at the end.
string binaryMSB(int n) {
    if (n <= 0) return "0";
    string result;
    int numBits = floor(log(n) / log(2)) + 1;
    while (n) {
        result += to_string(extractMSB(n, numBits)); // append MSB
        n = n & (~(1 << (numBits - 1))); // mask = ~(1000) = 0111.. this saves every bit except MSB which we've appended already
        --numBits;
    }
    return result;
}

int main() {
    cout << CountBits(5) << endl;
    cout << Parity(7) << endl;
    cout << SwapBits(12, 3, 1) << endl;
    cout << ReverseBits(12) << endl;
    cout << Reverse(73569) << endl;
    cout << AsciiValue('B') << endl;
    cout << CharToInt('7') << endl;
    cout << IntToChar(5) << endl;
    cout << IntToString(45) << endl;
    cout << MyIntToString(45) << endl;
    cout << StringToInt("12") << endl;
    cout << MyStringToInt("12") << endl;
    cout << ConvertBase("615", 7, 13) << endl;
    return 0;
}
