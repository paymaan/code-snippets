#include <iostream>
#include <set>
#include <vector>

namespace my {
    using setType = uint16_t;
    /// @brief Generates and prints all possible subsets for a set of the form
    /// {0,1,2,...,n-1}
    /// "n" is the size of the set
    void generateSubsets(const size_t n);

    /// @brief bit vector way of generateSubsets
    void generatedSubsets_bitVec(const size_t n);

    /// @brief Generate all possible combination of a given subset
    ///        of the form {a1,a2,a3,..,an} where a's are random numbers
    void generateSubsets(std::vector<my::setType> aSet);
    void printSet(const std::set<setType> /*aSet*/);
}

int main() {
    my::generateSubsets(3);
    std::cout << "----------" << std::endl;
    my::generatedSubsets_bitVec(4);
    std::cout << "----------" << std::endl;
    std::vector<my::setType> mySet = {5, 12, 7};
    my::generateSubsets(mySet);

    return 0;
}

namespace my {
    void generateSubsets_impl(size_t aCurrIndex, const size_t n,
                              std::set<my::setType> aSubset) {
        if (aCurrIndex == n) {
            my::printSet(aSubset);
            return;
        }
        generateSubsets_impl(aCurrIndex + 1, n, aSubset);
        aSubset.insert(aCurrIndex);
        generateSubsets_impl(aCurrIndex + 1, n, aSubset);
        aSubset.erase(*(aSubset.end()));
    }
}

void my::generateSubsets(const size_t n) {
    std::set<my::setType> subset;
    my::generateSubsets_impl(0, n, subset);
}

void my::generatedSubsets_bitVec(const size_t n) {
    for (int b = 0; b < (1 << n); ++b) {
        // all subsets (e.g. 0110; note MSB will always be 0)
        // now, for all 1's in b, insert to set
        std::set<my::setType> subset;
        for (int i = 0; i < n; ++i) {
            if (b & 1 << i) // condition > 0
                subset.insert(i);
        }
        my::printSet(subset);
    }
}

namespace my {
    void generateSubsets_impl(const std::vector<my::setType> aSet,
                              std::set<my::setType> aSubset,
                              size_t aCurrIndex) {
        if (aCurrIndex == aSet.size()) {
            my::printSet(aSubset);
            return;
        }
        generateSubsets_impl(aSet, aSubset, aCurrIndex + 1);
        aSubset.insert(aSet[aCurrIndex]);
        generateSubsets_impl(aSet, aSubset, aCurrIndex + 1);
        aSubset.erase(*(aSubset.end()));
    }
}

void my::generateSubsets(std::vector<my::setType> aSet) {
    std::set<my::setType> subset;
    generateSubsets_impl(aSet, subset, 0);
}

void my::printSet(const std::set<my::setType> aSet) {
    if (aSet.empty()) {
        std::cout << "*empty*" << std::endl;
        return;
    }
    for (const auto setElem : aSet) {
        std::cout << setElem << " ";
    }
    std::cout << std::endl;
}
