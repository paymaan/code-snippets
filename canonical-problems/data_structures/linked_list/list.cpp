/// This is just a prototype and is not meant for
/// prodduction use
/// I'm just playing around and creating some common data
/// structures

#include "list.hpp"

int main() {
    // Output:
    //     45 -> 30 -> 5 -> 15 -> 25 -> 50
    //     size: 6
    //     5 -> 15 -> 25 -> 50
    //     size: 4
    //     5 -> 15
    //     size: 2
    //     5
    //     size: 1
    List list;
    list.push_back(5);
    list.push_back(15);
    list.push_back(25);
    list.push_front(30);
    list.push_front(45);
    list.push_back(50);
    list.print();
    cout << "size: " << list.size() << "\n";
    list.pop_front();
    list.pop_front();
    list.print();
    cout << "size: " << list.size() << "\n";
    list.pop_back();
    list.pop_back();
    list.print();
    cout << "size: " << list.size() << "\n";
    list.pop_back();
    list.print();
    cout << "size: " << list.size() << "\n";

    return 0;
}
