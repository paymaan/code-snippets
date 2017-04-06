#include <array>
#include <iostream>

namespace my {

/// @brief Swaps array[firstIndex] with array[secondIndex]
template <size_t SIZE>
void swap(std::array<int, SIZE>& array, size_t firstIndex, size_t secondIndex);

/// @brief Performs insertion sort on array
template <size_t SIZE> void insertionSort(std::array<int, SIZE>& array);

/// @brief Prints a given array
template <size_t SIZE>
void printArrayToStdOut(const std::array<int, SIZE>& array);
}

int main() {
    using namespace my;

    std::array<int, 18> array = {3,  2,  87, 45,  43,  77,  12,  99,  34,
                                 75, 23, 74, 105, 950, 450, 346, 210, 323};

    printArrayToStdOut(array);

    insertionSort(array);

    printArrayToStdOut(array);

    return 0;
}

template <size_t SIZE> void my::insertionSort(std::array<int, SIZE>& array) {
    for (int i = 1; i <= SIZE - 1; ++i) {
        const int key = array[i];
        for (int j = i - 1; j >= 0; --j) {
            // if at any posize_t when going left, we find an element that is
            // smaller than the
            // key, we can safely break. This is because we know that the left
            // section is sorted
            // and if an element is already smaller than the key, than we don't
            // need to go any more left.
            if (array[j] <= key) {
                break;
            }
            if (array[j] > array[j + 1]) {
                swap(array, j, j + 1);
            }
        }
    }
}

template <size_t SIZE>
void my::swap(std::array<int, SIZE>& array, size_t firstIndex,
              size_t secondIndex) {
    // another way of swapping without using temp
    // don't like this too much because of potential integer overflows :)
    array[firstIndex] = array[firstIndex] + array[secondIndex];
    array[secondIndex] = array[firstIndex] - array[secondIndex];
    array[firstIndex] = array[firstIndex] - array[secondIndex];
}

template <size_t SIZE>
void my::printArrayToStdOut(const std::array<int, SIZE>& array) {
    std::cout << "[ ";
    for (const auto& element : array) {
        std::cout << element << " ";
    }
    std::cout << "] " << std::endl;
}
