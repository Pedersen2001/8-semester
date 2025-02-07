#include <iostream>
#include <vector>
#include <utility>
#include <chrono>
#include <cstring>
using namespace std;
using namespace std::chrono;

void swap_ends(int arr[], int size) {
    for (int i = size/2 - 1, j = size - 1; i >= 0; --i, --j)
        swap(arr[i], arr[j]);
}

void swap_ends(std::vector<int>& arr) {
    for (int i = arr.size()/2 - 1, j = arr.size() - 1; i >= 0; --i, --j)
        swap(arr[i], arr[j]);
}

constexpr int arr_size = 10'000'000;
int c_arr[arr_size];
vector<int> vec(arr_size);

int main() {
    // do some warm up work here
    auto t0 = high_resolution_clock::now();
    swap_ends(c_arr, arr_size);
    auto t1 = high_resolution_clock::now();
    std::cout << duration<double, std::milli>(t1-t0).count() << "ms (array)\n";

    auto t3 = high_resolution_clock::now();
    swap_ends(vec);
    auto t4 = high_resolution_clock::now();
    std::cout << duration<double, std::milli>(t4-t3).count() << "ms (vector)\n";
}