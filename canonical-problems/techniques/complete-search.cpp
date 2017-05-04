#include <iostream>
#include <set>

namespace my {
using setType = uint16_t;
/// @brief Generates and prints all possible subsets for a set of the form
/// {0,1,2,...,n-1}
/// "n" is the size of the set
void generateSubsets(const size_t aSize);
void generateSubsets_impl(size_t aCurrIndex, const size_t aSize,
                          std::set<my::setType> aSubset);
void printSet(const std::set<setType> /*aSet*/);
}

int main() {
    my::generateSubsets(3);
    return 0;
}

void my::generateSubsets(const size_t aSize) {
    std::set<my::setType> subset;
    my::generateSubsets_impl(0, aSize, subset);
}
void my::generateSubsets_impl(size_t aCurrIndex, const size_t aSize,
                              std::set<my::setType> aSubset) {

    if (aCurrIndex == aSize) {
        printSet(aSubset);
        return;
    }
    my::generateSubsets_impl(aCurrIndex + 1, aSize, aSubset);
    aSubset.insert(aCurrIndex);
    my::generateSubsets_impl(aCurrIndex + 1, aSize, aSubset);
    aSubset.erase(*(aSubset.end()));
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
