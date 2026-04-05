#include <iostream>

int main() {

    // 1)
    int altitudeTotal;
    std::cout << "How many altitude readings to store?: " << std::endl;
    std::cin >> altitudeTotal;

    // 2)
    int* arr = new int[altitudeTotal];

    // 3)
    for (int i = 0; i < altitudeTotal; i++) {
        std::cout << "Altitude at index " << i << " is: " << std::endl;
        std::cin >> arr[i];
    }

    for (int i = 0; i < altitudeTotal; i++) {
        std::cout << arr[i] << std::endl;
    }

    delete[] arr;

}