#include <iostream>
#include <random>

void dynamic_array_cleaning(int** matrix, int rows);
int count_columns_without_elem(int** matrix, int elem, int rows, int columns);
int define_row_number_with_longest_chain(int** matrix, int rows, int columns);
void random_input(std::mt19937& gen, int** matrix, int rows, int columns, int l_border, int r_border);
void allocate_matrix(int*** matrix_pointer, int rows, int columns);
void enter_rows_columns(int& rows, int& columns);
char enter_input_mode(int** matrix, int rows);
void manual_matrix_input(int** matrix, int rows, int columns);
void random_matrix_input(std::mt19937& gen, int** matrix, int rows, int columns);
void matrix_output(int** matrix, int rows, int columns);

int main() {
    int rows, columns;
    try {
        enter_rows_columns(rows, columns);
        int** matrix{};
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
        matrix_output(matrix, rows, columns);
        std::cout << "Number of columns without a[1][1] value: ";
        std::cout << count_columns_without_elem(matrix, matrix[1][1], rows, columns) << '\n';
        std::cout << "Row with the longest chain of identical elements: ";
        std::cout << define_row_number_with_longest_chain(matrix, rows, columns) << '\n';
        dynamic_array_cleaning(matrix, rows);
    }
    catch(const char* msg){
        std::cerr << msg;
    }
    return 0;
}

int count_columns_without_elem(int** matrix, int elem, int rows, int columns) {
    int counter = 0;
    bool is_equal_number = false;
    for (int j = 0; j < columns; j++) {
        is_equal_number = false;
        for (int i = 0; i < rows; i++) {
            if (matrix[i][j] == elem) {
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

int define_row_number_with_longest_chain(int** matrix, int rows, int columns) {
    int row_number = 0, max_chain = 0, step_max_chain = 0;
    for (int i = 0; i < rows; i++) {
        step_max_chain = 0;
        for (int j = 0; j < columns - 1; j++) {
            if (matrix[i][j] == matrix[i][j + 1]) {
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

void dynamic_array_cleaning(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete [] matrix[i];
    }
    delete [] matrix;
}

void allocate_matrix(int*** matrix_pointer, int rows, int columns) {
    *matrix_pointer = new int* [rows];
    for (int i = 0; i < rows; i++) {
        (*matrix_pointer)[i] = new int [columns];
    }
}

void random_input(std::mt19937& gen, int** matrix, int rows, int columns, int l_border, int r_border) {
    std::uniform_real_distribution<double> dist(l_border, r_border);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = dist(gen);
        }
    }
}

void enter_rows_columns(int& rows, int& columns) {
    std::cout << "Enter two natural numbers rows and columns: ";
    if (!(std::cin >> rows >> columns) || rows < 1 || columns < 1) {
        throw "Error. Rows and columns must be natural\n";
    }
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

void random_matrix_input(std::mt19937& gen, int** matrix, int rows, int columns) {
    std::cout << "Enter l_border and r_border for gen random numbers in [l_border, r_border]: ";
    double l_border, r_border;
    if (!(std::cin >> l_border >> r_border)) {
        dynamic_array_cleaning(matrix, rows);
        throw "Error. l_border and r_border must be real!";
    }
    random_input(gen, matrix, rows, columns, l_border, r_border);
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

void matrix_output(int** matrix, int rows, int columns) {
    std::cout << "Your matrix:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
}