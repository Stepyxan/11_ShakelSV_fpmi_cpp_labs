#include <iostream>
#include <cmath>
#include <random>
struct Interval {
    int first;
    int last;
};
void index_check(int&, int&);
double sum_btw(double*, int);
void array_transform(double*, int);
Interval asc_chain(double*, int);
int main() {
    std::cout << "Enter a natural number n: ";
    int n;
    if (!(std::cin >> n) || n < 1) {
        std::cout << "Error! You should enter a natural number";
        std::exit(1);
    }
    double* arr = new double[n];
    std::cout << "Do you want to enter numbers from keyboard? Y/n: ";
    char user_answer;
    if (!(std::cin >> user_answer) || !(user_answer == 'Y' || user_answer == 'n')) {
        std::cout << "Error! You should enter a char('Y' or 'n')";
        delete[] arr;
        std::exit(1);
    }
    if (user_answer == 'Y') {
        for (int i = 0; i < n; i++) {
            if (!(std::cin >> arr[i])) {
                std::cout << "Error! You should enter a real number";
                delete[] arr;
                std::exit(1);
            }
        }
    }
    else {
        std::cout << "Enter a and b for gen random numbers in [a, b]: ";
        double a, b;
        if (!(std::cin >> a >> b)) {
            std::cout << "Error! You should enter two real numbers";
            delete[] arr;
            std::exit(1);
        }
        std::mt19937 gen(45218965);
        std::uniform_real_distribution<double> dist(a, b);
        for (int i = 0; i < n; i++) {
            arr[i] = dist(gen);
        }
    }
    std::cout << "Sum between the first max and the last min: " << sum_btw(arr, n) << '\n';
    std::cout << "Max length chain: ";
    Interval interv = asc_chain(arr, n);
    for (int i = interv.first; i <= interv.last; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << "\nChanged array: ";
    array_transform(arr, n);
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << ' ';
    }
    delete[] arr;
}
void index_check(int& start, int& end) {
    if (start > end) {
        int temp = start;
        start = end;
        end = temp;
    }
}
double sum_btw(double* arr, int n) {
    int min_el = arr[0], max_el = arr[0];
    int min_index = 0, max_index = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_el) {
            max_el = arr[i];
            max_index = i;
        }
        if (arr[i] <= min_el) {
            min_el = arr[i];
            min_index = i;
        }
    }
    index_check(max_index, min_index);
    float sum = 0;
    for (int i = max_index + 1; i < min_index; i++) {
        sum += arr[i];
    }
    return sum;
}
Interval asc_chain(double* arr, int n) {
    int max_chain_len = 1;
    int first_elem_ind = 0;
    for (int i = 0; i < n; i++) {
        int cur_chain_len = 1;
        for (int j = i + 1; j < n; j++) {
            if (arr[j - 1] < arr[j]) {
                cur_chain_len++;
            }
            else {
                if (cur_chain_len > max_chain_len) {
                    max_chain_len = cur_chain_len;
                    first_elem_ind = i;
                }
                break;
            }
            if (cur_chain_len > max_chain_len) {
                max_chain_len = cur_chain_len;
                first_elem_ind = i;
            }
        }
    }
    Interval interv;
    interv.first = first_elem_ind;
    interv.last = first_elem_ind + max_chain_len - 1;
    return interv;
}
void array_transform(double* arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (fabs(arr[i]) < fabs(arr[j])) {
                double temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}