// ex01_sizeof_and_limits.cpp
//
// Goal: print the size (in bytes) and min/max range of the core
// fundamental types on this machine, using sizeof and <limits>.
// Don't hardcode the numbers — pull them from the type itself so it
// stays correct on any platform.

#include <iostream>
#include <limits>

template <typename T>
void printInfo(const char* name) {
    std::cout << name
              << " | size: " << sizeof(T) << " bytes"
              << " | min: " << +std::numeric_limits<T>::min()
              << " | max: " << +std::numeric_limits<T>::max()
              << '\n';
}

int main() {
    printInfo<short>("short");
    printInfo<int>("int");
    printInfo<long>("long");
    printInfo<long long>("long long");
    printInfo<unsigned int>("unsigned int");
    printInfo<float>("float");
    printInfo<double>("double");
    printInfo<char>("char");
    printInfo<bool>("bool");

    // TODO: add int8_t, uint8_t, int32_t from <cstdint> and compare
    // their sizes/ranges to the plain types above.

    return 0;
}
