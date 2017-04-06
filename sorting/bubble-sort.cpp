#include <array>
#include <iostream>

namespace my {

/// @brief Swaps array[firstIndex] with array[secondIndex]
template <size_t SIZE>
void swap(std::array<int, SIZE>& array, size_t firstIndex, size_t secondIndex);

/// @brief Performs bubble sort on array
template <size_t SIZE> void bubbleSort(std::array<int, SIZE>& array);

/// @brief Prints a given array
template <size_t SIZE>
void printArrayToStdOut(const std::array<int, SIZE>& array);
}

int main() {
    using namespace my;

    std::array<int, 18> array = {3,  2,  87, 45,  43,  77,  12,  99,  34,
                                 75, 23, 74, 105, 950, 450, 346, 210, 323};

    printArrayToStdOut(array);

    bubbleSort(array);

    printArrayToStdOut(array);

    return 0;
}

template <size_t SIZE> void my::bubbleSort(std::array<int, SIZE>& array) {
    for (size_t i = 0; i < SIZE - 1; ++i) {
        for (size_t j = 0; j < SIZE - 1 - i; ++j) {
            if (array[j] > array[j + 1]) {
                swap(array, j, j + 1);
            }
        }
    }
}

template <size_t SIZE>
void my::swap(std::array<int, SIZE>& array, size_t firstIndex,
              size_t secondIndex) {
    const int firstIndexOriginalValue = array[firstIndex];
    array[firstIndex] = array[secondIndex];
    array[secondIndex] = firstIndexOriginalValue;
}

template <size_t SIZE>
void my::printArrayToStdOut(const std::array<int, SIZE>& array) {
    std::cout << "[ ";
    for (const auto& element : array) {
        std::cout << element << " ";
    }
    std::cout << "] " << std::endl;
}
