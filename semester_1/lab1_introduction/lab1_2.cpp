#include <iostream>

int main()
{
    int n, even_sum = 0, odd_mult = 1;
    if (!(std::cin >> n) || n < 1) {
        std::cout << "error";
        std::exit(1);
    }
    for (int i = 1; i <= n; i) {
        if (i % 2) {
            odd_mult *= i;
        }
        else {
            even_sum += i;
        }
    }
    std::cout << even_sum << ' ' << odd_mult;
}