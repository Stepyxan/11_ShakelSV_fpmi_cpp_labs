#include <iostream>
#include <random>

void clear_input();
void merge(int *, int, int, int, int*, bool (*)(int, int));
void merge_sort(int*, int, int, int*, bool (*)(int, int));
void bubble_sort(int*, int, bool (*)(int, int));
void dynamic_array_cleaning(int**, int);
void sort_insert_mod(int*, int, bool (*)(int, int));
bool asc_comp(int, int);
bool desc_comp(int, int);
void allocate_matrix(int***, int, int);
void random_input(int** matrix, int rows, int columns, int l_border, int r_border);
void enter_rows_columns(int* rows, int* columns);
void manual_matrix_input(int** matrix, int rows, int columns);
void random_matrix_input(int** matrix, int rows, int columns);
char enter_input_mode();
char enter_sort_order();
char enter_sort_mode();
void matrix_output(int** matrix, int rows, int columns);

int main() {
    int rows, columns;
    enter_rows_columns(&rows, &columns);
    int** matrix;
    allocate_matrix(&matrix, rows, columns);
    switch (enter_input_mode()) {
        case ('y'):
            manual_matrix_input(matrix, rows, columns);
            break;
        case ('n'):
            random_matrix_input(matrix, rows, columns);
            break;
    }
    bool (*comp)(int, int);
    switch (enter_sort_order()) {
        case ('A'):
            comp = asc_comp;
            break;
        case ('D'):
            comp = desc_comp;
            break;
    }
    switch (enter_sort_mode()) {
        case ('B'):
            for (int i = 0; i < rows; i++) {
                bubble_sort(matrix[i], columns, comp);
            }
            break;
        case ('I'):
            for (int i = 0; i < rows; i++) {
                sort_insert_mod(matrix[i], columns, comp);
            }
            break;
        case ('M'):
            for (int i = 0; i < rows; i++) {
                int* temp = new int[columns];
                merge_sort(matrix[i], 0, columns, temp, comp);
                delete [] temp;
            }
            break;
    }
    matrix_output(matrix, rows, columns);
    dynamic_array_cleaning(matrix, rows);
}

void allocate_matrix(int*** matrix, int rows,  int columns) {
    *matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        (*matrix)[i] = new int [columns];
    }
}

void merge(int *arr, int left, int mid, int right, int* temp, bool (*comp)(int, int))
{
    int i = left;
    int j = mid;
    int k = left;
    while (i < mid && j < right) {
        if (comp(arr[i], arr[j])) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
        }
    }
    while (i < mid) {
        temp[k] = arr[i];
        i++;
        k++;
    }
    while (j < right) {
        temp[k] = arr[j];
        j++;
        k++;
    }
    for (int t = left; t < right; t++) {
        arr[t] = temp[t];
    }
}

void merge_sort(int* arr, int left, int right, int* temp, bool (*comp)(int, int))
{
    if (right - left <= 1) return;
    int mid = (left + right) / 2;
    merge_sort(arr, left, mid, temp, comp);
    merge_sort(arr, mid, right, temp, comp);
    merge(arr, left, mid, right, temp, comp);
}

void bubble_sort(int* arr, int n, bool (*comp)(int, int)) {
    if (arr != nullptr && n > 0) {
        bool is_swap = false;
        for (int i = 0; i < n - 1; i++) {
            is_swap = false;
            for (int j = 0; j < n - i - 1; j++) {
                if (comp(arr[j + 1], arr[j])) {
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

void enter_rows_columns(int* rows, int* columns) {
    std::cout << "Enter 2 natural number (rows/columns): \n";
    while (!(std::cin >> *rows >> *columns) || *rows < 1 || *columns < 1) {
        std::cout << "Try again. Enter natural numbers (rows/columns): \n";
        clear_input();
    }
}

void dynamic_array_cleaning(int** arr, int rows) {
    for (int i = 0; i < rows; i++) {
        delete [] arr[i];
    }
    delete [] arr;
}

void sort_insert_mod(int* arr, int n, bool (*comp)(int, int)) {
    int j;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        for (j = i - 1; j >= 0 && comp(key, arr[j]); j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = key;
    }
}

bool asc_comp(int first, int last) {
    return first < last;
}

bool desc_comp(int first, int last) {
    return first > last;
}

void clear_input() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void random_input(int** matrix, int rows, int columns, int l_border, int r_border) {
    std::mt19937 gen(45218965);
    std::uniform_real_distribution<double> dist(l_border, r_border);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = dist(gen);
        }
    }
}

void manual_matrix_input(int** matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            while (!(std::cin >> matrix[i][j])) {
                std::cout << "Try again. You should enter a real number:";
                clear_input();
            }
        }
    }
}

void random_matrix_input(int** matrix, int rows, int columns) {
    std::cout << "Enter l_border and r_border for gen random numbers in [l_border, r_border]: ";
    double l_border, r_border;
    while (!(std::cin >> l_border >> r_border)) {
        std::cout << "Try again. You should enter two real numbers: ";
        clear_input();
    }
    random_input(matrix, rows, columns, l_border, r_border);
}

char enter_input_mode() {
    std::cout << "Do you want to enter numbers from keyboard? y/n: ";
    char user_answer;
    while (!(std::cin >> user_answer) || !(user_answer == 'y' || user_answer == 'n')) {
        std::cout << "Try again. You should enter a char('y' or 'n'): \n";
        clear_input();
    }
    return user_answer;
}

char enter_sort_order() {
    char elems_order;
    std::cout << "What order of elements do you want?\n";
    std::cout << "Enter 'A'(Ascending), 'D'(Descending): ";
    while (!(std::cin >> elems_order) || !(elems_order == 'D' || elems_order == 'A')) {
        std::cout << "Try again. You should enter a char('A', 'D'): ";
        clear_input();
    }
    return elems_order;
}

char enter_sort_mode() {
    std::cout << "What sort type do you want to use?\n";
    std::cout << "Enter 'B'(Bubble), 'I'(Insert) or 'M'(Merge): ";
    char sort_mode;
    while (!(std::cin >> sort_mode) || !(sort_mode == 'B' || sort_mode == 'I' || sort_mode == 'M')) {
        std::cout << "Try again. You should enter a char('B', 'I', 'M'): ";
        clear_input();
    }
    return sort_mode;
}

void matrix_output(int** matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
}