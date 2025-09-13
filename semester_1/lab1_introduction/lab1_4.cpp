#include <iostream>

int main()
{
    int k;
    int d_factorial = 1;
    if (!(std::cin >> k) || k < 1) {
        std::cout << "error";
        std::exit(1);
    }
    for (int i = k; i >= 1; i -= 2) {
        d_factorial *= i;
    }
    std::cout << d_factorial;
}