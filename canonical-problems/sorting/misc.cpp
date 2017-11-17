/// Toy examples related to sorting
/// Just playing around, not prodcution quality code.

#include <iostream>
#include <vector>

using namespace std;

void print(const vector<int>& vec) {
    for (auto e : vec)
        cout << e << " ";
    cout << endl;
}

vector<int> merge_sorted(const vector<int>& v1,
                         const vector<int>& v2) {
    if (v1.empty())
        return v2;
    if (v2.empty())
        return v1;

    // 2 pointer method
    // i is v1 pointer and j is v2 pointer
    // increment them one at a time
    int i = 0, j = 0;
    vector<int> merged;
    // first move i and j till we reach end
    // of atleast one array
    while (i < v1.size() && j < v2.size()) {
        if (v1[i] < v2[j])
            merged.push_back(v1[i++]);
        else
            merged.push_back(v2[j++]);
    }
    // go through rest of the array that is left
    // one of these while loops will actually be hit
    while (i < v1.size())
        merged.push_back(v1[i++]);
    while (j < v2.size())
        merged.push_back(v2[j++]);

    return merged;
}

int main() {
    /// Combine two sorted arrays into one
    /// sorted array in O(m + n) time where
    /// m and n are sizes of the two arrays.
    vector<int> x1 = {5, 6, 8, 10};
    vector<int> x2 = {3, 4, 7, 9, 11, 14};
    /// prints: 3 4 5 6 7 8 9 10 11 14
    print(merge_sorted(x1, x2));

    return 0;
}
