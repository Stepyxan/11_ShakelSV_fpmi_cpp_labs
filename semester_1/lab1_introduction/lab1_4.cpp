#include <iostream>

int main()
{
    int k;
    int d_factorial = 1;
    std::cin >> k;
    for (int i = k; i >= 1; i -= 2) {
        d_factorial *= i;
    }
    std::cout << d_factorial;
}