#include <iostream>
#include <random>

int count_columns_without_elem(int** arr, int elem, int n, int m);
int define_row_number_with_longest_chain(int** arr, int n, int m);
void dynamic_array_cleaning(int**, int);

int main() {
    std::cout << "Enter natural numbers n and m: ";
    int n, m;
    if (!(std::cin >> n >> m) || n < 1 || m < 1) {
        std::cout << "Error! You should enter natural numbers";
        std::exit(1);
    }
    int** arr = new int* [n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int [m];
    }
    std::cout << "Do you want to enter numbers from keyboard? Y/n: ";
    char user_answer;
    if (!(std::cin >> user_answer) || !(user_answer == 'Y' || user_answer == 'n')) {
        std::cout << "Error! You should enter a char('Y' or 'n')";
        dynamic_array_cleaning(arr, n);
        std::exit(1);
    }
    if (user_answer == 'Y') {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!(std::cin >> arr[i][j])) {
                    std::cout << "Error! You should enter a real number";
                    dynamic_array_cleaning(arr, n);
                    std::exit(1);
                }
            }
        }
    }
    else {
        std::cout << "Enter a and b for gen random numbers in [a, b]: ";
        double a, b;
        if (!(std::cin >> a >> b)) {
            std::cout << "Error! You should enter two real numbers";
            dynamic_array_cleaning(arr, n);
            std::exit(1);
        }
        std::mt19937 gen(45218965);
        std::uniform_real_distribution<double> dist(a, b);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                arr[i][j] = dist(gen);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << arr[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "Number of columns wuthout a[1][1] value: ";
    std::cout << count_columns_without_elem(arr, arr[1][1], n, m) << '\n';
    std::cout << "Row with the longest chain of identical elements: ";
    std::cout << define_row_number_with_longest_chain(arr, n, m) << '\n';
}
int count_columns_without_elem(int** arr, int elem, int n, int m) {
    int counter = 0;
    bool is_equal_number = false;
    for (int j = 0; j < m; j++) {
        is_equal_number = false;
        for (int i = 0; i < n; i++) {
            if (arr[i][j] == elem) {
                is_equal_number = true;
                break;
            }
        }
        if (!is_equal_number) {
            counter++;
        }
    }
    return counter;
}

int define_row_number_with_longest_chain(int** arr, int n, int m) {
    int row_number = 0, max_chain = 0, step_max_chain = 0;
    for (int i = 0; i < n; i++) {
        step_max_chain = 0;
        for (int j = 0; j < m - 1; j++) {
            if (arr[i][j] == arr[i][j + 1]) {
                step_max_chain++;
            }
            else {
                if (max_chain < step_max_chain) {
                    row_number = i;
                    max_chain = step_max_chain;
                }
                step_max_chain = 0;
            }
        }
        if (max_chain < step_max_chain) {
            max_chain = step_max_chain;
            row_number = i;
        }
    }
    return row_number;
}

void dynamic_array_cleaning(int** arr, int n) {
    for (int i = 0; i < n; i++) {
        delete [] arr[i];
    }
    delete [] arr;
}