#include <iostream>
#include <cmath>
#include <random>
const int N = 100000;
int unique_numbers_count(double*, int);
double elems_product(double*, int);
void array_transform(double*, int);
int main() {
    double arr[N];
    std::cout << "Enter a natural number n under 100000: ";
    int n;
    if (!(std::cin >> n) || n < 1 || n >= N) {
        std::cout << "Error! You should enter a natural number under 100000";
        std::exit(1);
    }
    std::cout << "Do you want to enter numbers from keyboard? Y/n: ";
    char user_answer;
    if (!(std::cin >> user_answer) || !(user_answer == 'Y' || user_answer == 'n')) {
        std::cout << "Error! You should enter a char('Y' or 'n')";
        std::exit(1);
    }
    if (user_answer == 'Y') {
        for (int i = 0; i < n; i++) {
            if (!(std::cin >> arr[i])) {
                std::cout << "Error! You should enter a real number";
                std::exit(1);
            }
        }
    }
    else {
        std::cout << "Enter a and b for gen random numbers in [a, b]: ";
        double a, b;
        if (!(std::cin >> a >> b)) {
            std::cout << "Error! You should enter two real numbers";
            std::exit(1);
        }
        std::mt19937 gen(45218965);
        std::uniform_real_distribution<double> dist(a, b);
        for (int i = 0; i < n; i++) {
            arr[i] = dist(gen);
        }
    }
    std::cout << "Number of different elements in the array: " <<  unique_numbers_count(arr, n) << '\n';
    std::cout << "Product of elements before abs min: " << elems_product(arr, n) << '\n';
    array_transform(arr, n);
    std::cout << "Transformed array: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << ' ';
    }

}
int unique_numbers_count(double* arr, int n) {
    int unique_counter = 1;
    for (int i = 1; i < n; i++) {
        bool is_unique = 1;
        for (int j = 0; j < i; j++) {
            if (arr[i] == arr[j]) {
                is_unique = 0;
                break;
            }
        }
        if (is_unique) {
            unique_counter++;
        }
    }
    return unique_counter;
}
double elems_product(double* arr, int n) {
    int min_index = 0, min_el = fabs(arr[0]);
    for (int i = 0; i < n; i++) {
        if (fabs(arr[i]) < min_el) {
            min_el = fabs(arr[i]);
            min_index = i;
        }
    }
    if (min_index == 0) {
        return 0;
    }
    double product = 1.0;
    for (int i = 0; i < min_index; i++) {
        product *= arr[i];
    }
    return product;
}
void array_transform(double* arr, int n) {
    for (int i = 0; i < n; i++) {
        double cur_elem = arr[i];
        if (cur_elem < 0) {
            int j = i;
            while (j > 0 && arr[j - 1] >= 0) {
                arr[j] = arr[j - 1];
                j--;
            }
            arr[j] = cur_elem;
        }
        else if (cur_elem == 0) {
            int j = i;
            while (j > 0 && arr[j - 1] > 0) {
                arr[j] = arr[j - 1];
                j--;
            }
            arr[j] = cur_elem;
        }
    }
}