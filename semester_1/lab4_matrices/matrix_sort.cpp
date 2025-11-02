#include <iostream>
#include <random>

void selection_sort(int*, int, bool (*)(int, int));
void merge(int *, int, int, int, int*, bool (*)(int, int));
void merge_sort(int*, int, int, int*, bool (*)(int, int));
void merge_sort_runner(int*, int, bool (*)(int, int));
void bubble_sort(int*, int, bool (*)(int, int));
void dynamic_array_cleaning(int**, int);
void sort_insert_mod(int*, int, bool (*)(int, int));
bool asc_comp(int, int);
bool desc_comp(int, int);
void allocate_matrix(int***, int, int);
void random_input(std::mt19937& gen, int** matrix, int rows, int columns, int l_border, int r_border);
void enter_rows_columns(int& rows, int& columns);
void manual_matrix_input(int** matrix, int rows, int columns);
void random_matrix_input(std::mt19937& gen, int** matrix, int rows, int columns);
char enter_input_mode(int** matrix, int rows);
char enter_sort_order(int** matrix, int rows);
char enter_sort_mode(int** matrix, int rows);
void matrix_output(int** matrix, int rows, int columns);

int main() {
    try {
        int rows, columns;
        enter_rows_columns(rows, columns);
        int** matrix;
        allocate_matrix(&matrix, rows, columns);
        switch (enter_input_mode(matrix, rows)) {
            case 'y':
            case 'Y': {
                manual_matrix_input(matrix, rows, columns);
                break;
            }
            case 'n':
            case 'N': {
                std::mt19937 gen(45218965);
                random_matrix_input(gen, matrix, rows, columns);
                break;
            }
            default: {
                dynamic_array_cleaning(matrix, rows);
                throw "Error. You must enter a char('y' or 'n')\n";
            }
        }
        std::cout << "Your basic matrix:\n";
        matrix_output(matrix, rows, columns);
        bool (*comp)(int, int){};
        switch (enter_sort_order(matrix, rows)) {
            case 'A':
            case 'a':
                comp = asc_comp;
                break;
            case 'D':
            case 'd':
                comp = desc_comp;
                break;
            default: {
                dynamic_array_cleaning(matrix, rows);
                throw "Error. You must enter a char('A' or 'D')";
            }
        }
        void (*sort_func)(int*, int, bool (*)(int, int)){};
        switch (enter_sort_mode(matrix, rows)) {
            case 'B':
                sort_func = bubble_sort;
                break;
            case 'I':
                sort_func = sort_insert_mod;
                break;
            case 'S':
                sort_func = selection_sort;
            case 'M':
                sort_func = merge_sort_runner;
                break;
            default: {
                dynamic_array_cleaning(matrix, rows);
                throw "Error. You must enter a char('B', 'I', 'S' or 'M')\n";
            }
        }
        for (int i = 0; i < rows; i++) {
            sort_func(matrix[i], columns, comp);
        }
        std::cout << "Result matrix:\n";
        matrix_output(matrix, rows, columns);
        dynamic_array_cleaning(matrix, rows);
    }
    catch (const char* msg) {
        std::cerr << msg << '\n';
    }
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

void enter_rows_columns(int& rows, int& columns) {
    std::cout << "Enter two natural numbers rows and columns: ";
    if (!(std::cin >> rows >> columns) || rows < 1 || columns < 1) {
        throw "Error. Rows and columns must be natural\n";
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

void random_input(std::mt19937& gen, int** matrix, int rows, int columns, int l_border, int r_border) {
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
            if (!(std::cin >> matrix[i][j])) {
                dynamic_array_cleaning(matrix, rows);
                throw "Error. matrix elements must be integers";
            }
        }
    }
}

void random_matrix_input(std::mt19937& gen, int** matrix, int rows, int columns) {
    std::cout << "Enter l_border and r_border for gen random numbers in [l_border, r_border]: ";
    double l_border, r_border;
    if (!(std::cin >> l_border >> r_border)) {
        dynamic_array_cleaning(matrix, rows);
        throw "Error. l_border and r_border must be real!";
    }
    random_input(gen, matrix, rows, columns, l_border, r_border);
}

char enter_input_mode(int** matrix, int rows) {
    std::cout << "Do you want to enter numbers from keyboard? y/n: ";
    char user_answer;
    if (!(std::cin >> user_answer)) {
        dynamic_array_cleaning(matrix, rows);
        throw "Error. Your answer must be a char\n";
    }
    return user_answer;
}

char enter_sort_order(int** matrix, int rows) {
    char elems_order;
    std::cout << "What order of elements do you want?\n";
    std::cout << "Enter 'A'(Ascending), 'D'(Descending): ";
    if (!(std::cin >> elems_order)) {
        dynamic_array_cleaning(matrix, rows);
        throw "Error. Your answer about sort order must be a char";
    }
    return elems_order;
}

char enter_sort_mode(int** matrix, int rows) {
    std::cout << "What sort type do you want to use?\n";
    std::cout << "Enter 'B'(Bubble), 'I'(Insert), 'S'(Selection) or 'M'(Merge): ";
    char sort_mode;
    if (!(std::cin >> sort_mode)) {
        dynamic_array_cleaning(matrix, rows);
        throw "Error. Your answer about sort mode must be a char";
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

void selection_sort(int* arr, int n, bool (*comp)(int, int)) {
    for (int i = 0; i < n - 1; i++) {
        int cur_index = i;
        for (int j = i + 1; j < n; j++) {
            if (comp(arr[j], arr[cur_index])) {
                cur_index = j;
            }
        }
        if (cur_index != i) {
            std::swap(arr[i], arr[cur_index]);
        }
    }
}

void merge_sort_runner(int* arr, int columns, bool (*comp)(int, int)) {
    int* temp = new int[columns];
    merge_sort(arr, 0, columns, temp, comp);
    delete[] temp;
}