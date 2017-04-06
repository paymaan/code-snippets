#include <algorithm>
#include <iostream>
#include <vector>

namespace my {

/// @brief Performs merge sort on array
std::vector<int> mergeSort(std::vector<int>& array);

/// @brief Merge two sorted arrays
std::vector<int> mergeSortedArrays(std::vector<int>& firstSortedArray,
                                   std::vector<int>& secondSortedArray);

/// @brief Prints a given array
void printArrayToStdOut(const std::vector<int>& array);
}

int main() {
    using namespace my;

    // for this example, array size has to be of the form 2^n where n a
    // non-negative integer
    std::vector<int> array = {3,  2,  87, 45, 43,  77,  12,  99,
                              34, 75, 23, 74, 105, 950, 450, 346};

    printArrayToStdOut(array);

    printArrayToStdOut(mergeSort(array));

    return 0;
}

std::vector<int> my::mergeSort(std::vector<int>& array) {
    const size_t arraySize = array.size();
    if (arraySize <= 1)
        return array;

    const bool isArraySizeEven = (arraySize % 2 == 0);
    if (!isArraySizeEven) {
        std::cout << "Only even sized arrays supported for now" << std::endl;
        return array;
    }

    std::vector<int> leftArray;
    std::vector<int> rightArray;

    for (size_t vectorIndex = 0; vectorIndex < array.size(); ++vectorIndex) {
        if (vectorIndex <= array.size() / 2 - 1) {
            leftArray.push_back(array[vectorIndex]);
        } else {
            rightArray.push_back(array[vectorIndex]);
        }
    }

    leftArray = mergeSort(leftArray);
    rightArray = mergeSort(rightArray);

    return mergeSortedArrays(leftArray, rightArray);
}

std::vector<int> my::mergeSortedArrays(std::vector<int>& firstSortedArray,
                                       std::vector<int>& secondSortedArray) {
    // no need to do anything if arrays are empty
    if (firstSortedArray.empty() && secondSortedArray.empty())
        return firstSortedArray;
    if (firstSortedArray.empty())
        return secondSortedArray;
    if (secondSortedArray.empty())
        return firstSortedArray;

    // ensure firstSortedArray is the same size as secondSortedArray
    if (firstSortedArray.size() != secondSortedArray.size()) {
        // Until I setup asserts...
        std::cout << "Arrays must be the same size" << std::endl;
        return firstSortedArray;
    }

    size_t firstSortedArrayPtrIndex = 0;
    size_t secondSortedArrayPtrIndex = 0;
    size_t mergedArrayPtrIndex = 0;

    std::vector<int> mergedArray;
    while (mergedArrayPtrIndex <= 2 * firstSortedArray.size() - 1) {
        const bool allFirstSortedArrayValuesUsed =
            firstSortedArrayPtrIndex > firstSortedArray.size() - 1;
        const bool allSecondSortedArrayValuesUsed =
            secondSortedArrayPtrIndex > secondSortedArray.size() - 1;
        const bool useFirstSortedArrayValue =
            !allFirstSortedArrayValuesUsed &&
            (allSecondSortedArrayValuesUsed ||
             (firstSortedArray[firstSortedArrayPtrIndex] <
              secondSortedArray[secondSortedArrayPtrIndex]));
        if (useFirstSortedArrayValue) {
            mergedArray.push_back(firstSortedArray[firstSortedArrayPtrIndex]);
            ++firstSortedArrayPtrIndex;
        } else {
            mergedArray.push_back(secondSortedArray[secondSortedArrayPtrIndex]);
            ++secondSortedArrayPtrIndex;
        }

        ++mergedArrayPtrIndex;
    }

    return mergedArray;
}

void my::printArrayToStdOut(const std::vector<int>& array) {
    std::cout << "[ ";
    for (const auto& element : array) {
        std::cout << element << " ";
    }
    std::cout << "] " << std::endl;
}
