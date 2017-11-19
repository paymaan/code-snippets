#include <iostream>
#include <vector>

using namespace std;

template <typename T> class BinaryHeap {
  public:
    BinaryHeap()
        : heap() {}

  private:
    vector<T> heap;
};

int main() {
    BinaryHeap<int> bh;
    return 0;
}
