#include <iostream>
#include <random>

void merge(int *, int, int, int, int*);
void mergeSort(int*, int, int, int*);
void bubble_sort(int*, int);
void dynamic_array_cleaning(int**, int);
void sortInsertMod(int*, int);
bool ascComp(int, int);
bool descComp(int, int);


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
    std::cout << "Do you want to enter numbers from keyboard? y/n: ";
    char user_answer;
    if (!(std::cin >> user_answer) || !(user_answer == 'y' || user_answer == 'n')) {
        std::cout << "Error! You should enter a char('y' or 'n')";
        dynamic_array_cleaning(arr, n);
        std::exit(1);
    }
    switch (user_answer) {
        case ('y'):
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (!(std::cin >> arr[i][j])) {
                        std::cout << "Error! You should enter a real number";
                        dynamic_array_cleaning(arr, n);
                        std::exit(1);
                    }
                }
            }
            break;
        case ('n'):
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
            break;
    }

    std::cout << "What sort type do you want to use?\n";
    std::cout << "Enter 'B'(Bubble), 'I'(Insert) or 'M'(Merge): ";
    char sort_mode;
    if (!(std::cin >> sort_mode) || !(sort_mode == 'B' || sort_mode == 'I' || sort_mode == 'M')) {
        std::cout << "Error! You should enter a char('B', 'I', 'M')";
        dynamic_array_cleaning(arr, n);
        std::exit(1);
    }
    switch (sort_mode) {
        case ('B'):

        case ('I'):

        case ('M'):

    }
    bool (*comp)(int, int);
    char elems_order;
    std::cout << "What order of elements do you want?\n";
    std::cout << "Enter 'A'(Ascending), 'D'(Descending): ";
    if (!(std::cin >> elems_order) || !(elems_order == 'D' || elems_order == 'A')) {
        std::cout << "Error! You should enter a char('A', 'D')";
        dynamic_array_cleaning(arr, n);
        std::exit(1);
    }
    switch (elems_order) {
        case ('A'):
            comp = ascComp;
            break;
        case ('D'):
            comp = descComp;
            break;
    }

}

void merge(int *a, int left, int mid, int right, int* temp)
{
    int i = left;
    int j = mid;
    int k = left;
    while(i < mid && j < right)
    {
        if(a[i] <= a[j])
        {
            temp[k++] = a[i++];
        }
        else
        {
            temp[k++] = a[j++];
        }
    }
    while(i < mid)
    {
        temp[k] = a[i];
        i++;
        k++;
    }
    while(j < right)
    {
        temp[k] = a[j];
        j++;
        k++;
    }
    for(int t = left; t < right; t++)
        a[t] = temp[t];
}

void mergeSort(int* a, int left, int right, int* temp)
{
    if(right - left <= 1) return;

    int mid = (left + right) / 2;

    mergeSort(a, left, mid, temp);
    mergeSort(a, mid, right, temp);

    merge(a, left, mid, right, temp);
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

void dynamic_array_cleaning(int** arr, int n) {
    for (int i = 0; i < n; i++) {
        delete [] arr[i];
    }
    delete [] arr;
}

void SortInsertMod(int* arr, int n, bool (*comp)(int, int)) {
    int j;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        for (j = i - 1; j >= 0 && comp(key, arr[j]); j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = key;
    }
}

bool ascComp(int first, int last) {
    return first < last;
}

bool descComp(int first, int last) {
    return first > last;
}