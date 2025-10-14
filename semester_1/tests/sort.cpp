#include <iostream>
void bubble_sort(int* arr, int n) {
    if (arr != nullptr && n > 0) {
        bool is_swap = false;
        for (int i = 0; i < n - 1; i++) {
            is_swap = false;
            for (int j = 0; j < n - i - 1; j++) {
                if (abs(arr[j]) > abs(arr[j + 1])) {
                    std::swap(arr[j], arr[j + 1]);
                    is_swap = true;
                }
            }
            if (!is_swap) {
                break;
            }
        }
    }
}

int main() {
    int n;
    if (!(std::cin >> n) || n < 1) {
        std::cout << "You must enter a natural number";
        std::exit(1);
    }
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        if (!(std::cin >> arr[i])) {
            std::cout << "You must enter natural numbers into your array";
            delete [] arr;
            std::exit(1);
        }
    }
    bubble_sort(arr, n);
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << ' ';
    }
}